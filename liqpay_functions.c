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

int liqpay_in_array(zval *arr, zval *needle) {
    if (Z_TYPE_P(arr) != IS_ARRAY) {
        return FAILURE;
    }
    zval *val;
    ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(arr), val)
            {
                if (fast_equal_check_function(needle, val)) {
                    return SUCCESS;
                }
            }
    ZEND_HASH_FOREACH_END();
    return FAILURE;
}

int liqpay_array_merge(zval *return_value, zval *arr_1, zval *arr_2) {
    ZVAL_NULL(return_value);
    if (Z_TYPE_P(arr_1) != IS_ARRAY) {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "arr1 not is array");
        return FAILURE;
    }

    if (Z_TYPE_P(arr_2) != IS_ARRAY) {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "arr2 not is array");
        return FAILURE;
    }

    int arr_new_sz = COUNT_ARRAY(arr_1) + COUNT_ARRAY(arr_2);
    if (arr_new_sz < 1) {
        array_init(return_value);
        return SUCCESS;
    }

    array_init_size(return_value, arr_new_sz);
    php_array_merge(Z_ARRVAL_P(return_value), Z_ARRVAL_P(arr_1));
    php_array_merge(Z_ARRVAL_P(return_value), Z_ARRVAL_P(arr_2));

    return SUCCESS;
}

void concat_zz(zval *return_value, zval *s1, zval *s2) {
    zval cs1, cs2;
    int uc0 = 0, uc1 = 0;
    if (Z_TYPE_P(s1) != IS_STRING) {
        uc0 = zend_make_printable_zval(s1, &cs1);
        if (uc0) {
            s1 = &cs1;
        }
    }
    if (Z_TYPE_P(s2) != IS_STRING) {
        uc1 = zend_make_printable_zval(s2, &cs2);
        if (uc1) {
            s2 = &cs2;
        }
    }
    size_t length = Z_STRLEN_P(s1) + Z_STRLEN_P(s2), offset = 0;

    ZVAL_STR(return_value, zend_string_alloc(length, 0));
    memcpy(Z_STRVAL_P(return_value) + offset, Z_STRVAL_P(s1), Z_STRLEN_P(s1));
    memcpy(Z_STRVAL_P(return_value) + offset + Z_STRLEN_P(s1), Z_STRVAL_P(s2), Z_STRLEN_P(s2));
    Z_STRVAL_P(return_value)[length] = 0;
    zend_string_forget_hash_val(Z_STR_P(return_value));
    if (uc0) {
        zval_ptr_dtor(s1);
    }
    if (uc1) {
        zval_ptr_dtor(s2);
    }
}

void concat_zzz(zval *return_value, zval *s1, zval *s2, zval *s3) {
    zval cs1, cs2, cs3;
    int uc0 = 0, uc1 = 0, uc2 = 0;
    if (Z_TYPE_P(s1) != IS_STRING) {
        uc0 = zend_make_printable_zval(s1, &cs1);
        if (uc0) {
            s1 = &cs1;
        }
    }
    if (Z_TYPE_P(s2) != IS_STRING) {
        uc1 = zend_make_printable_zval(s2, &cs2);
        if (uc1) {
            s2 = &cs2;
        }
    }
    if (Z_TYPE_P(s3) != IS_STRING) {
        uc2 = zend_make_printable_zval(s3, &cs3);
        if (uc2) {
            s3 = &cs3;
        }
    }

    size_t length = Z_STRLEN_P(s1) + Z_STRLEN_P(s2) + Z_STRLEN_P(s3), offset = 0;
    ZVAL_STR(return_value, zend_string_alloc(length, 0));

    memcpy(Z_STRVAL_P(return_value) + offset, Z_STRVAL_P(s1), Z_STRLEN_P(s1));
    memcpy(Z_STRVAL_P(return_value) + offset + Z_STRLEN_P(s1), Z_STRVAL_P(s2), Z_STRLEN_P(s2));
    memcpy(Z_STRVAL_P(return_value) + offset + Z_STRLEN_P(s1) + Z_STRLEN_P(s2), Z_STRVAL_P(s3), Z_STRLEN_P(s3));
    Z_STRVAL_P(return_value)[length] = 0;
    zend_string_forget_hash_val(Z_STR_P(return_value));
    if (uc0) {
        zval_ptr_dtor(s1);
    }
    if (uc1) {
        zval_ptr_dtor(s2);
    }
    if (uc2) {
        zval_ptr_dtor(s3);
    }
}

int liqpay_json_encode(zval *return_value, zval *zvalv) {
    ZVAL_NULL(return_value);
    int liqpay_error = SUCCESS;
    smart_str buf = {0};
#if PHP_VERSION_ID >= 70100
    liqpay_error = php_json_encode(&buf, zvalv, 0);
    CHECK_F()
#else
    php_json_encode(&buf, zvalv, 0);
#endif //PHP_VERSION_ID
    smart_str_0(&buf);
    ZVAL_STR(return_value, buf.s);
    return liqpay_error;
}

int liqpay_json_decode_ex(zval *return_value, zval *str, int boold) {
    int liqpay_error = SUCCESS, csr = 0;
    zval copy_str;
    if (UNEXPECTED(Z_TYPE_P(str) != IS_STRING)) {
        csr = zend_make_printable_zval(str, &copy_str);
        if (csr) {
            str = &copy_str;
        }
    }
    ZVAL_NULL(return_value);
#if PHP_VERSION_ID >= 70100
    liqpay_error = php_json_decode(return_value, ZEND_STRL(Z_STRVAL_P(str)), (boold ? 1 : 0), 512);
    CHECK_F()
#else
    php_json_decode(return_value, ZEND_STRL(Z_STRVAL_P(str)), (boold ? 1 : 0), 512);
#endif //PHP_VERSION_ID
    if (UNEXPECTED(csr)) {
        zval_dtor(&copy_str);
    }
    return liqpay_error;
}

int liqpay_json_decode(zval *return_value, zval *str) {
    return liqpay_json_decode_ex(return_value, str, 0);
}

int liqpay_base64_encode(zval *return_value, zval *encode) {
    ZVAL_NULL(return_value);
    if (UNEXPECTED(Z_TYPE_P(encode) != IS_STRING)) {
        THROW_INVALID_ARGUMENT_EXCEPTION_FAIL("$encode is not a type string", 0);
    }
    zend_string *res = php_base64_encode((const unsigned char *) Z_STRVAL_P(encode), Z_STRLEN_P(encode));
    if (!res) {
        ZVAL_EMPTY_STRING(return_value);
        return FAILURE;
    }
    ZVAL_STR(return_value, res);
    return SUCCESS;
}

int liqpay_base64_decode(zval *return_value, zval *decode) {
    if (UNEXPECTED(Z_TYPE_P(decode) != IS_STRING)) {
        THROW_INVALID_ARGUMENT_EXCEPTION_FAIL("$decode is not a type string", 0);
    }
    zend_string *res = php_base64_decode((const unsigned char *) Z_STRVAL_P(decode), Z_STRLEN_P(decode));
    if (!res) {
        ZVAL_NULL(return_value);
        return FAILURE;
    }
    ZVAL_STR(return_value, res);
    return SUCCESS;
}

void liqpay_sha1(zval *return_value, zend_string *str, int boold) {
    ZVAL_NULL(return_value);

    PHP_SHA1_CTX context;
    unsigned char digest[20];
    char sha_str[41];
    sha_str[0] = '\0';

    PHP_SHA1Init(&context);
    PHP_SHA1Update(&context,(unsigned char *) ZSTR_VAL(str), ZSTR_LEN(str));
    PHP_SHA1Final(digest, &context);
    if (boold) {
        RETURN_STRINGL((char *) digest, 20);
    }
    make_sha1_digest(sha_str, digest);
    RETVAL_STRING(sha_str);
}
