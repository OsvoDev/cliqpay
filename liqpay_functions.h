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

#ifndef LIQPAY_LIQPAY_FUNCTIONS_H
#define LIQPAY_LIQPAY_FUNCTIONS_H

#include <php.h>
#include <zend_types.h>
#include <ext/standard/php_array.h>
#include <ext/standard/base64.h>
#include <ext/json/php_json.h>
#include <zend.h>
#include <zend_smart_str.h>
#include <Zend/zend_exceptions.h>
#include <ext/spl/spl_exceptions.h>
#include <ext/standard/sha1.h>

#if PHP_VERSION_ID >= 80000
#define TSRMLS_CC
#endif

int liqpay_in_array(zval *arr, zval *needle);
int liqpay_array_merge(zval *return_value, zval *arr_1, zval *arr_2);

void concat_zz(zval *return_value, zval *s1, zval *s2);
void concat_zzz(zval *return_value, zval *s1, zval *s2, zval *s3);

int liqpay_json_encode(zval *return_value, zval *zvalv);
int liqpay_json_decode(zval *return_value, zval *str);
int liqpay_json_decode_ex(zval *return_value, zval *str, int boold);

int liqpay_base64_encode(zval *return_value, zval *encode);
int liqpay_base64_decode(zval *return_value, zval *decode);

void liqpay_sha1(zval *return_value, zend_string *str, int boold);

#define COUNT_ARRAY(zv) zend_hash_num_elements(Z_ARRVAL_P(zv))

#define IS_EMPTY_STRING(x) Z_STRLEN_P(x) < 1
#define IS_EMPTY_ARRAY(x) COUNT_ARRAY(x) < 1

#define THROW_INVALID_ARGUMENT_EXCEPTION_FAIL(str, code) zend_throw_exception(spl_ce_InvalidArgumentException, str, code);return FAILURE
#define THROW_INVALID_ARGUMENT_EXCEPTION(str, code) zend_throw_exception(spl_ce_InvalidArgumentException, str, code);return

#define CHECK() {if(liqpay_error!=SUCCESS) return;}
#define CHECK_F() {if(liqpay_error!=SUCCESS) return FAILURE;}

#define ch_liqpay_json_encode(rv, zv) liqpay_error=liqpay_json_encode(rv, zv)
#define ch_liqpay_json_decode(rv, zv) liqpay_error=liqpay_json_decode(rv, zv)
#define ch_liqpay_json_decode_ex(rv, zv, bd) liqpay_error=liqpay_json_decode_ex(rv, zv, bd)

#define ch_liqpay_base64_encode(rv, en) liqpay_error=liqpay_base64_encode(rv, en)
#define ch_liqpay_base64_decode(rv, de) liqpay_error=liqpay_base64_decode(rv, de)

#endif //LIQPAY_LIQPAY_FUNCTIONS_H
