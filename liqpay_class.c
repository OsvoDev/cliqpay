/**
 *******************************************************************************************************************************************************
 *                                                              LiqPay Php Extension                                                                   *
 *                                                                  ( v1.0.1 )                                                                         *
 *******************************************************************************************************************************************************
 * LiqPay API version           : 3                                                                                                                    *
 * More info about LiqPay API   : https://liqpay.ua/documentation/en                                                                                   *
 * PhpSdk as Example            : https://github.com/liqpay/sdk-php             License OSL-3(http://opensource.org/licenses/osl-3.0.php)              *
 *******************************************************************************************************************************************************
 *                                                                                                                                                     *
 *  Copyright (c) 2020, Osvo                                                                                                                           *
 *  All rights reserved.                                                                                                                               *
 *                                                                                                                                                     *
 *  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:     *
 *      - Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.                 *
 *      - Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer               *
 *          in the documentation and/or other materials provided with the distribution.                                                                *
 *      - Neither the name of the Osvo nor the names of its contributors may be used to endorse or promote products derived from this software         *
 *          without specific prior written permission.                                                                                                 *
 *                                                                                                                                                     *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT              *
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.                                         *
 *  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,                         *
 *  OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;               *
 *  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,                                    *
 *  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. *
 *                                                                                                                                                     *
 *******************************************************************************************************************************************************
 */

#include "liqpay_functions.h"
#include "definitions.h"
#include <curl/curl.h>
#include <curl/easy.h>
#include <standard/php_http.h>
#include <standard/url.h>

static void liqpay_custom_http_build_query(zval *_postFields, zval *tmp_arr) {
    smart_str htbq = {0};
    if (php_url_encode_hash_ex(HASH_OF(tmp_arr), &htbq, NULL, 0, NULL, 0, NULL, 0, NULL, NULL,
                               (int) PHP_QUERY_RFC1738) == FAILURE) {
        if (htbq.s) {
            smart_str_free(&htbq);
        }
        ZVAL_FALSE(_postFields);
        return;
    }

    if (!htbq.s) {
        ZVAL_STRINGL(_postFields, "", 0);
        return;
    }

    smart_str_0(&htbq);
    ZVAL_STRINGL(_postFields, ZSTR_VAL(htbq.s), ZSTR_LEN(htbq.s));
    smart_str_free(&htbq);
}

static size_t liqpay_custom_curl_return(void *write, size_t size, size_t count, void *stream) {
    if (count <= 0)
        return 0;
    size_t l = size * count;
    if (l > 0)
        smart_str_appendl((smart_str *) stream, (char *) write, l);
    return l;
}


static int
liqpay_custom_curl(zval *return_value, zval *curl_getinfo, zval *url, int timeout, zval *data, zval *signature) {
    CURL *ccrl = NULL;
    if (!(ccrl = curl_easy_init())) {
        THROW_INVALID_ARGUMENT_EXCEPTION_FAIL("I cannot create cURL resource", 0);
    }

    smart_str wr = {0};
    CURLcode error = CURLE_OK;
    zval tmp_arr, _postFields;
    int code = 0;

    array_init_size(&tmp_arr, 2);
    add_assoc_zval(&tmp_arr, "data", data);
    add_assoc_zval(&tmp_arr, "signature", signature);

    liqpay_custom_http_build_query(&_postFields, &tmp_arr);

    curl_easy_setopt(ccrl, CURLOPT_WRITEFUNCTION, liqpay_custom_curl_return);
    curl_easy_setopt(ccrl, CURLOPT_WRITEDATA, (void *) &wr);

    curl_easy_setopt(ccrl, CURLOPT_URL, Z_STRVAL_P(url));
    curl_easy_setopt(ccrl, CURLOPT_SSL_VERIFYPEER, 1);
    curl_easy_setopt(ccrl, CURLOPT_SSL_VERIFYHOST, 2);
    curl_easy_setopt(ccrl, CURLOPT_TIMEOUT, timeout);
    curl_easy_setopt(ccrl, CURLOPT_CONNECTTIMEOUT, timeout);
    curl_easy_setopt(ccrl, CURLOPT_POST, 1);

#if LIBCURL_VERSION_NUM >= 0x071101
    curl_easy_setopt(ccrl, CURLOPT_POSTFIELDSIZE, Z_STRLEN_P(&_postFields));
    curl_easy_setopt(ccrl, CURLOPT_COPYPOSTFIELDS, Z_STRVAL_P(&_postFields));
#else
    curl_easy_setopt(ccrl, CURLOPT_POSTFIELDS, Z_STRVAL_P(&_postFields));
    curl_easy_setopt(ccrl, CURLOPT_POSTFIELDSIZE, Z_STRLEN_P(&_postFields));
#endif

    char *cai;
    cai = INI_STR("openssl.cafile");

    if (!(cai && cai[0] != '\0')) {
        cai = INI_STR("curl.cainfo");
    }

    if (!(cai && cai[0] != '\0')) {
        cai = INI_STR("liqpay.curl_cainfo");
    }

    if (cai && cai[0] != '\0') {
        curl_easy_setopt(ccrl, CURLOPT_CAINFO, cai);
    }

    error = curl_easy_perform(ccrl);

    if (error != CURLE_OK && error != CURLE_PARTIAL_FILE) {
        RETVAL_FALSE;
        ZVAL_LONG(curl_getinfo, error);
        curl_easy_cleanup(ccrl);
        smart_str_free(&wr);
        return SUCCESS;
    }

    curl_easy_getinfo(ccrl, CURLINFO_HTTP_CODE, &code);
    ZVAL_LONG(curl_getinfo, code);

    if (ZSTR_LEN(wr.s) < 1) {
        RETVAL_EMPTY_STRING();
    } else {
        smart_str_0(&wr);
        RETVAL_STR(wr.s);
    }

    curl_easy_cleanup(ccrl);
    smart_str_free(&wr);
    return SUCCESS;
}

static int liqpay_cnb_form(zval *return_value, zval *params, zval *this);

static int liqpay_cnb_params(zval *return_value, zval *params, zval *this);

static int liqpay_cnb_signature(zval *return_value, zval *params, zval *this);

static int liqpay_base64_json_encode(zval *return_value, zval *zv);

static int liqpay_base64_json_decode(zval *return_value, zval *str);

static int liqpay_str_to_sign(zval *return_value, zval *str);

#define ch_liqpay_cnb_params(rv, prms) liqpay_error=liqpay_cnb_params(rv, prms, this)
#define ch_liqpay_cnb_signature(rv, prms) liqpay_error=liqpay_cnb_signature(rv, prms, this)
#define liqpay_encode_params(rv, zv) liqpay_base64_json_encode(rv, zv)
#define liqpay_decode_params(rv, zv) liqpay_base64_json_decode(rv, zv)
#define ch_liqpay_base64_json_encode(rv, zv) liqpay_error=liqpay_base64_json_encode(rv, zv)
#define ch_liqpay_base64_json_decode(rv, str) liqpay_error=liqpay_base64_json_decode(rv, str)
#define ch_liqpay_encode_params ch_liqpay_base64_json_encode
#define ch_liqpay_decode_params ch_liqpay_base64_json_decode
#define ch_liqpay_str_to_sign(rv, str) liqpay_error=liqpay_str_to_sign(rv, str)

extern zend_class_entry *liqpay_ce;

PHP_METHOD (LiqPay, __construct) {
    zval arr;
    array_init(&arr);
    add_next_index_stringl(&arr, ZEND_STRL(CURRENCY_EUR));
    add_next_index_stringl(&arr, ZEND_STRL(CURRENCY_USD));
    add_next_index_stringl(&arr, ZEND_STRL(CURRENCY_UAH));
    add_next_index_stringl(&arr, ZEND_STRL(CURRENCY_RUR));
    add_next_index_stringl(&arr, ZEND_STRL(CURRENCY_RUB));
    zend_update_property(liqpay_ce, getThis(), ZEND_STRL("_supportedCurrencies"), &arr);
    zval *public_key = NULL, *private_key = NULL, *api_url = NULL, *this = getThis();
    if (zend_parse_parameters_throw(ZEND_NUM_ARGS() TSRMLS_CC, "zz|z", &public_key, &private_key, &api_url) ==
        FAILURE) {
        return;
    }
    if (!public_key || Z_TYPE_P(public_key) != IS_STRING) {
        THROW_INVALID_ARGUMENT_EXCEPTION("public_key must be a string type", 0);
    }
    if (!private_key || Z_TYPE_P(private_key) != IS_STRING) {
        THROW_INVALID_ARGUMENT_EXCEPTION("private_key must be a string type", 0);
    }
    if (IS_EMPTY_STRING(public_key)) {
        THROW_INVALID_ARGUMENT_EXCEPTION("public_key is empty", 0);
    }
    if (IS_EMPTY_STRING(private_key)) {
        THROW_INVALID_ARGUMENT_EXCEPTION("private_key is empty", 0);
    }
    zend_update_property(liqpay_ce, this, ZEND_STRL("_public_key"), public_key);
    zend_update_property(liqpay_ce, this, ZEND_STRL("_private_key"), private_key);
    if (api_url && Z_TYPE_P(api_url) == IS_STRING) {
        zend_update_property(liqpay_ce, this, ZEND_STRL("_api_url"), api_url);
    }
}

PHP_METHOD (LiqPay, api) {
    ZVAL_NULL(return_value);
    zval *path = NULL, *params = NULL, *this = getThis();
    int timeout = 5, liqpay_error = SUCCESS;
    if (zend_parse_parameters_throw(ZEND_NUM_ARGS() TSRMLS_CC, "z|zl", &path, &params, &timeout) == FAILURE) {
        return;
    }
    if (!path || Z_TYPE_P(path) != IS_STRING) {
        THROW_INVALID_ARGUMENT_EXCEPTION("path must be a string type", 0);
    }
    if (!params || Z_TYPE_P(params) != IS_ARRAY ||
        zend_hash_str_find(Z_ARRVAL_P(params), ZEND_STRL("version")) == NULL) {
        THROW_INVALID_ARGUMENT_EXCEPTION("version is null", 0);
    }
    zval url, _signature,
            tmp0, data, tmp_data,
            *_private_key = zend_read_property(liqpay_ce, this, ZEND_STRL("_private_key"), 0, NULL),
            server_output, longval;
    ZVAL_NULL(&url);
    ZVAL_NULL(&tmp0);
    ZVAL_NULL(&tmp_data);
    ZVAL_NULL(&data);
    concat_zz(&url, zend_read_property(liqpay_ce, this, ZEND_STRL("_api_url"), 0, NULL), path);
    zval _tmp_arr;
    array_init_size(&_tmp_arr, 1);
    add_assoc_zval(&_tmp_arr, "public_key", zend_read_property(liqpay_ce, this, ZEND_STRL("_public_key"), 0, NULL));
    liqpay_array_merge(&tmp0, &_tmp_arr, params);
            ch_liqpay_encode_params(&data, &tmp0);
    CHECK()
    concat_zzz(&tmp_data, _private_key, &data, _private_key);
    ch_liqpay_str_to_sign(&_signature, &tmp_data);
    CHECK()
    liqpay_error = liqpay_custom_curl(&server_output, &longval, &url, timeout, &data, &_signature);
    CHECK()
    zend_update_property(liqpay_ce, this, ZEND_STRL("_server_response_code"), &longval);
    liqpay_json_decode(return_value, &server_output);
}

PHP_METHOD (LiqPay, get_response_code) {
    RETVAL_ZVAL(zend_read_property(liqpay_ce, getThis(), ZEND_STRL("_server_response_code"), 0, NULL), 1, 0);
}

PHP_METHOD (LiqPay, cnb_form) {
    zval *params = NULL;
    if (zend_parse_parameters_throw(ZEND_NUM_ARGS() TSRMLS_CC, "z", &params) == FAILURE) {
        return;
    }
    liqpay_cnb_form(return_value, params, getThis());
}

PHP_METHOD (LiqPay, cnb_form_raw) {
    zval *params = NULL;
    if (zend_parse_parameters_throw(ZEND_NUM_ARGS() TSRMLS_CC, "z", &params) == FAILURE) {
        return;
    }
    if (!params || Z_TYPE_P(params) != IS_ARRAY || IS_EMPTY_ARRAY(params)) {
        THROW_INVALID_ARGUMENT_EXCEPTION("version is null", 0);
    }
    int liqpay_error = SUCCESS;
    zval cparams, *this = getThis(), _encode, cnb_signature;
    ZVAL_UNDEF(&cparams);
    ZVAL_UNDEF(&_encode);
    ZVAL_UNDEF(&cnb_signature);
    ch_liqpay_cnb_signature(&cparams, params);
    CHECK()
    array_init_size(return_value, 3);
    add_assoc_zval(return_value, "url", zend_read_property(liqpay_ce, this, ZEND_STRL("_checkout_url"), 0, NULL));
            ch_liqpay_encode_params(&_encode, &cparams);
    CHECK()
    add_assoc_zval(return_value, "data", &_encode);
    ch_liqpay_cnb_signature(&cnb_signature, &cparams);
    CHECK()
    add_assoc_zval(return_value, "signature", &cnb_signature);
}

PHP_METHOD (LiqPay, cnb_signature) {
    zval *params = NULL;
    if (zend_parse_parameters_throw(ZEND_NUM_ARGS() TSRMLS_CC, "z", &params) == FAILURE) {
        return;
    }
    liqpay_cnb_signature(return_value, params, getThis());
}

PHP_METHOD (LiqPay, cnb_params) {
    zval *params = NULL;
    if (zend_parse_parameters_throw(ZEND_NUM_ARGS() TSRMLS_CC, "z", &params) == FAILURE) {
        return;
    }
    liqpay_cnb_params(return_value, params, getThis());
}

PHP_METHOD (LiqPay, encode_params) {
    zval *params = NULL;
    if (zend_parse_parameters_throw(ZEND_NUM_ARGS() TSRMLS_CC, "z", &params) == FAILURE) {
        return;
    }
    liqpay_encode_params(return_value, params);
}

PHP_METHOD (LiqPay, decode_params) {
    zval *str = NULL;
    if (zend_parse_parameters_throw(ZEND_NUM_ARGS() TSRMLS_CC, "z", &str) == FAILURE) {
        return;
    }
    liqpay_decode_params(return_value, str);
}

PHP_METHOD (LiqPay, str_to_sign) {
    zval *str = NULL;
    if (zend_parse_parameters_throw(ZEND_NUM_ARGS() TSRMLS_CC, "z", &str) == FAILURE) {
        return;
    }
    liqpay_str_to_sign(return_value, str);
}

int equal_str(zval *zstr, char *str, size_t length) {
    if((char*) Z_STRVAL_P(zstr) == str){
        return FAILURE;
    }

    if(Z_STRLEN_P(zstr) > length || Z_STRLEN_P(zstr) < length){
        return SUCCESS;
    }

    return !zend_binary_strcmp(Z_STRVAL_P(zstr), Z_STRLEN_P(zstr), str, length);
}

#define SL(x) x, strlen(x)

int have_currency(zval *currency){
    return  equal_str(currency, SL(CURRENCY_EUR)) || equal_str(currency, SL(CURRENCY_USD)) ||
            equal_str(currency, SL(CURRENCY_UAH)) || equal_str(currency, SL(CURRENCY_RUB)) ||
            equal_str(currency, SL(CURRENCY_RUR));
}

int liqpay_cnb_form(zval *return_value, zval *params, zval *this) {
    int liqpay_error = SUCCESS;
    ZVAL_NULL(return_value);
    zval _encode, cnb_sign, parameters;
    ch_liqpay_cnb_params(&parameters, params);
    CHECK_F()
    ch_liqpay_encode_params(&_encode, &parameters);
    CHECK_F()
    ch_liqpay_cnb_signature(&cnb_sign, &parameters);
    CHECK_F()
    zval *tmp_lang = zend_hash_str_find(Z_ARRVAL_P(&parameters), ZEND_STRL("language"));
    char lang[3] = "ru";
    if (tmp_lang != NULL && equal_str(tmp_lang, "en", strlen("en"))) {
        memcpy(lang, "en", strlen("en"));
        lang[2] = '\0';
    }
    char format_input[] = "<input type=\"hidden\" name=\"%s\" value=\"%s\" />";
    size_t size_data_input = strlen(format_input) + strlen("data") + Z_STRLEN_P(&_encode) + 1;
    size_t size_sign_input = strlen(format_input) + strlen("signature") + Z_STRLEN_P(&cnb_sign) + 1;
    char *data_input = NULL, *sign_input = NULL;
    data_input = (char *) emalloc(sizeof(char) * size_data_input);
    if (data_input == NULL) {
        THROW_INVALID_ARGUMENT_EXCEPTION_FAIL(
                "LiqPay::cnb_form(), not enough memory. Try increasing the value for the \"memory_limit\" directive in php.ini",
                0);
    }
    sprintf(data_input, format_input, "data", Z_STRVAL_P(&_encode));
    sign_input = (char *) emalloc(sizeof(char) * size_sign_input);
    if (sign_input == NULL) {
        THROW_INVALID_ARGUMENT_EXCEPTION_FAIL(
                "LiqPay::cnb_form(), not enough memory. Try increasing the value for the \"memory_limit\" directive in php.ini",
                0);
    }
    sprintf(sign_input, format_input, "signature", Z_STRVAL_P(&cnb_sign));
    char format_form[] = "\n"
                         "            <form method=\"POST\" action=\"%s\" accept-charset=\"utf-8\">\n"
                         "                %s\n"
                         "                %s\n"
                         "                <input type=\"image\" src=\"//static.liqpay.ua/buttons/p1%s.radius.png\" name=\"btn_text\" />\n"
                         "            </form>\n"
                         "            ";

    zval *_ch_url = zend_read_property(liqpay_ce, this, ZEND_STRL("_checkout_url"), 0, NULL);
    size_t size_result = 3 + size_data_input + size_sign_input + Z_STRLEN_P(_ch_url) + (strlen(format_form) - 8);
    char *result = NULL;
    result = (char *) emalloc(sizeof(char) * size_result);
    if (result == NULL) {
        THROW_INVALID_ARGUMENT_EXCEPTION_FAIL(
                "LiqPay::cnb_form(), not enough memory. Try increasing the value for the \"memory_limit\" directive in php.ini",
                0);
    }
    sprintf(result, format_form, Z_STRVAL_P(_ch_url), data_input, sign_input, lang);
    efree(data_input);
    efree(sign_input);
    RETVAL_STRING(result);
    efree(result);
    return liqpay_error;
}

int liqpay_cnb_params(zval *return_value, zval *params, zval *this) {
    ZVAL_NULL(return_value);
    if (Z_TYPE_P(params) != IS_ARRAY || IS_EMPTY_ARRAY(params)) {
        THROW_INVALID_ARGUMENT_EXCEPTION_FAIL("version is null", 0);
    }
    if (zend_hash_str_find(Z_ARRVAL_P(params), ZEND_STRL("version")) == NULL) {
        THROW_INVALID_ARGUMENT_EXCEPTION_FAIL("version is null", 0);
    }
    if (zend_hash_str_find(Z_ARRVAL_P(params), ZEND_STRL("amount")) == NULL) {
        THROW_INVALID_ARGUMENT_EXCEPTION_FAIL("amount is null", 0);
    }
    if (zend_hash_str_find(Z_ARRVAL_P(params), ZEND_STRL("currency")) == NULL) {
        THROW_INVALID_ARGUMENT_EXCEPTION_FAIL("currency is null", 0);
    }
#ifndef LQPNTEST
    if(!have_currency(zend_hash_str_find(Z_ARRVAL_P(params), ZEND_STRL("currency")))){
        THROW_INVALID_ARGUMENT_EXCEPTION_FAIL("currency is not supported", 0);
    }
#else
    if (liqpay_in_array(zend_read_property(liqpay_ce, this, ZEND_STRL("_supportedCurrencies"), 0, NULL),
                        zend_hash_str_find(Z_ARRVAL_P(params), ZEND_STRL("currency")) TSRMLS_CC) == FAILURE) {
        THROW_INVALID_ARGUMENT_EXCEPTION_FAIL("currency is not supported", 0);
    }
#endif
    add_assoc_zval(params, "public_key", zend_read_property(liqpay_ce, this, ZEND_STRL("_public_key"), 0, NULL));
    zval *tmp = zend_hash_str_find(Z_ARRVAL_P(params), ZEND_STRL("currency"));
    if (equal_str(tmp, CURRENCY_RUR, strlen(CURRENCY_RUR))) {
        zval rub;
        ZVAL_STRING(&rub, CURRENCY_RUB);
        zend_hash_str_update_ind(Z_ARRVAL_P(params), "currency", strlen("currency"), &rub);
    }
    if (zend_hash_str_find(Z_ARRVAL_P(params), ZEND_STRL("description")) == NULL) {
        THROW_INVALID_ARGUMENT_EXCEPTION_FAIL("description is null", 0);
    }
    RETVAL_ZVAL(params, 1, 0);
    return SUCCESS;
}

static int liqpay_cnb_signature(zval *return_value, zval *params, zval *this) {
    int liqpay_error = SUCCESS;
    zval cparams, *private_key = NULL, json, signature;
    ZVAL_NULL(return_value);
    ZVAL_UNDEF(&cparams);
    ZVAL_UNDEF(&json);
    ZVAL_UNDEF(&signature);
    ch_liqpay_cnb_params(&cparams, params);
    CHECK_F()
            ch_liqpay_encode_params(&json, &cparams);
    CHECK_F()
    private_key = zend_read_property(liqpay_ce, this, ZEND_STRL("_private_key"), 0, NULL);
    concat_zzz(&signature, private_key, &json, private_key);
    ch_liqpay_str_to_sign(return_value, &signature);
    return liqpay_error;
}

static int liqpay_base64_json_encode(zval *return_value, zval *zv) {
    int liqpay_error = SUCCESS;
    zval json;
    ch_liqpay_json_encode(&json, zv);
    CHECK_F()
    ch_liqpay_base64_encode(return_value, &json);
    return liqpay_error;
}

static int liqpay_base64_json_decode(zval *return_value, zval *str) {
    int liqpay_error = SUCCESS;
    zval base64;
    ch_liqpay_base64_decode(&base64, str);
    CHECK_F()
    ch_liqpay_json_decode_ex(return_value, &base64, 1);
    return liqpay_error;
}

static int liqpay_str_to_sign(zval *return_value, zval *str) {
    int liqpay_error = SUCCESS;
    zval sign;
    ZVAL_NULL(&sign);
    liqpay_sha1(&sign, Z_STR_P(str), 1);
    ch_liqpay_base64_encode(return_value, &sign);
    return liqpay_error;
}

