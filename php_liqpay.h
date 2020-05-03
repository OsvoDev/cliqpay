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

#ifndef LIQPAY_PHP_LIQPAY_H
#define LIQPAY_PHP_LIQPAY_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef ZTS
#include <TSRM.h>
#endif

#ifndef ZEND_DEBUG
#define ZEND_DEBUG 0
#endif

#include <php.h>
#include <php_main.h>
#include <ext/standard/info.h>
#include <Zend/zend_modules.h>
#include <zend_types.h>
#include <zend_API.h>
#include "definitions.h"

#if defined(ZTS) && defined(COMPILE_DL_LIQPAY)
ZEND_TSRMLS_CACHE_EXTERN();
#endif

extern zend_module_entry liqpay_module_entry;
#define phpext_liqpay_ptr &liqpay_module_entry

PHP_MINIT_FUNCTION(liqpay);
PHP_MINFO_FUNCTION(liqpay);
PHP_MSHUTDOWN_FUNCTION(liqpay);

ZEND_BEGIN_ARG_INFO_EX(LiqPay__construct, 0, 0, 2)
                ZEND_ARG_TYPE_INFO(0, public_key, IS_STRING, 0)
                ZEND_ARG_TYPE_INFO(0, private_key, IS_STRING, 0)
                ZEND_ARG_TYPE_INFO(0, api, IS_STRING, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(LiqPay__api, 0, 0, 1)
                ZEND_ARG_TYPE_INFO(0, path, IS_STRING, 0)
                ZEND_ARG_ARRAY_INFO(0, params, 1)
                ZEND_ARG_TYPE_INFO(0, timeout, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(Liqpay__get_reponse_code, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(Liqpay__array_param, 0)
                ZEND_ARG_ARRAY_INFO(0, params, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(Liqpay__decode_params, 0)
                ZEND_ARG_TYPE_INFO(0, params, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(Liqpay__str_to_sign, 0)
                ZEND_ARG_TYPE_INFO(0, str, IS_STRING, 0)
ZEND_END_ARG_INFO()

PHP_METHOD (LiqPay, __construct);
PHP_METHOD (LiqPay, api);
PHP_METHOD (LiqPay, get_response_code);
PHP_METHOD (LiqPay, cnb_form);
PHP_METHOD (LiqPay, cnb_form_raw);
PHP_METHOD (LiqPay, cnb_signature);
PHP_METHOD (LiqPay, cnb_params);
PHP_METHOD (LiqPay, encode_params);
PHP_METHOD (LiqPay, decode_params);
PHP_METHOD (LiqPay, str_to_sign);

static const zend_function_entry liqpay_methods[] = {
        PHP_ME(LiqPay, __construct, LiqPay__construct, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
        PHP_ME(LiqPay, api, LiqPay__api, ZEND_ACC_PUBLIC)
        PHP_ME(LiqPay, get_response_code, Liqpay__get_reponse_code, ZEND_ACC_PUBLIC)
        PHP_ME(LiqPay, cnb_form, Liqpay__array_param, ZEND_ACC_PUBLIC)
        PHP_ME(LiqPay, cnb_form_raw, Liqpay__array_param, ZEND_ACC_PUBLIC)
        PHP_ME(LiqPay, cnb_signature, Liqpay__array_param, ZEND_ACC_PUBLIC)
#ifdef LIQPAY_RELEASE
        PHP_ME(LiqPay, cnb_params, Liqpay__array_param, ZEND_ACC_PRIVATE)
        PHP_ME(LiqPay, encode_params, Liqpay__array_param, ZEND_ACC_PRIVATE)
        PHP_ME(LiqPay, decode_params, Liqpay__decode_params, ZEND_ACC_PRIVATE)
#else
        PHP_ME(LiqPay, cnb_params, Liqpay__array_param, ZEND_ACC_PUBLIC)
        PHP_ME(LiqPay, encode_params, Liqpay__array_param, ZEND_ACC_PUBLIC)
        PHP_ME(LiqPay, decode_params, Liqpay__decode_params, ZEND_ACC_PUBLIC)
#endif
        PHP_ME(LiqPay, str_to_sign, Liqpay__str_to_sign, ZEND_ACC_PUBLIC)
        PHP_FE_END
};


zend_class_entry *liqpay_ce;

#include "liqpay_functions.h"

#endif //LIQPAY_PHP_LIQPAY_H
