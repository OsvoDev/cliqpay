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

#include "php_liqpay.h"

#define LZS(x) ZEND_STRL(#x), ZEND_STRL(x)

PHP_INI_BEGIN()
    PHP_INI_ENTRY("liqpay.curl_cainfo", "", PHP_INI_SYSTEM, NULL)
PHP_INI_END()

PHP_MINIT_FUNCTION(liqpay){
    {
        zend_class_entry ce;
        memset(&ce, 0, sizeof(zend_class_entry));
        INIT_CLASS_ENTRY(ce, "LiqPay", liqpay_methods);
        liqpay_ce = zend_register_internal_class(&ce);
        liqpay_ce->ce_flags |= 0;
    }

    zend_declare_class_constant_stringl(liqpay_ce, LZS(CURRENCY_EUR));
    zend_declare_class_constant_stringl(liqpay_ce, LZS(CURRENCY_USD));
    zend_declare_class_constant_stringl(liqpay_ce, LZS(CURRENCY_UAH));
    zend_declare_class_constant_stringl(liqpay_ce, LZS(CURRENCY_RUB));
    zend_declare_class_constant_stringl(liqpay_ce, LZS(CURRENCY_RUR));

#ifdef LIQPAY_RELEASE
    zend_declare_property_stringl(liqpay_ce, ZEND_STRL("_api_url"), ZEND_STRL("https://www.liqpay.ua/api/"),
                                  ZEND_ACC_PRIVATE);
    zend_declare_property_stringl(liqpay_ce, ZEND_STRL("_checkout_url"),
                                  ZEND_STRL("https://www.liqpay.ua/api/3/checkout"), ZEND_ACC_PRIVATE);
    zend_declare_property_null(liqpay_ce, ZEND_STRL("_supportedCurrencies"), ZEND_ACC_PROTECTED);
    zend_declare_property_null(liqpay_ce, ZEND_STRL("_public_key"), ZEND_ACC_PRIVATE);
    zend_declare_property_null(liqpay_ce, ZEND_STRL("_private_key"), ZEND_ACC_PRIVATE);
    zend_declare_property_null(liqpay_ce, ZEND_STRL("_server_response_code"), ZEND_ACC_PRIVATE);
#else
    zend_declare_property_stringl(liqpay_ce, ZEND_STRL("_api_url"), ZEND_STRL("https://www.liqpay.ua/api/"),
                                  ZEND_ACC_PUBLIC);
    zend_declare_property_stringl(liqpay_ce, ZEND_STRL("_checkout_url"),
                                  ZEND_STRL("https://www.liqpay.ua/api/3/checkout"), ZEND_ACC_PUBLIC);
    zend_declare_property_null(liqpay_ce, ZEND_STRL("_supportedCurrencies"), ZEND_ACC_PUBLIC);
    zend_declare_property_null(liqpay_ce, ZEND_STRL("_public_key"), ZEND_ACC_PUBLIC);
    zend_declare_property_null(liqpay_ce, ZEND_STRL("_private_key"), ZEND_ACC_PUBLIC);
    zend_declare_property_null(liqpay_ce, ZEND_STRL("_server_response_code"), ZEND_ACC_PUBLIC);
#endif
    REGISTER_INI_ENTRIES();
    return SUCCESS;
}

PHP_MINFO_FUNCTION(liqpay){
    php_info_print_table_start();
    php_info_print_table_colspan_header(2, PHP_EXTENSION_NAME);
    php_info_print_table_row(2, "LiqPay Support", "enable");
    php_info_print_table_row(2, "Status Extension", PHP_EXTENSION_STATUS);
    php_info_print_table_row(2, "LiqPay Full Extension Version", PHP_EXTENSION_VERSION);
    php_info_print_table_row(2, "LiqPay API Version", PHP_EXTENSION_API_V);
    php_info_print_table_end();

    php_info_print_table_start();
    php_info_print_table_row(2, "Author", PHP_EXTENSION_AUTHOR_NAME);
    php_info_print_table_row(2, "Build", __DATE__ " " __TIME__);
    php_info_print_table_end();

    DISPLAY_INI_ENTRIES();
}

static const zend_module_dep liqpay_mod_deps[] = {
        ZEND_MOD_REQUIRED("standard")
        ZEND_MOD_REQUIRED("spl")
        ZEND_MOD_REQUIRED("json")
        ZEND_MOD_END
};

PHP_MSHUTDOWN_FUNCTION(liqpay)
{
    UNREGISTER_INI_ENTRIES();
    return SUCCESS;
}

static const zend_function_entry liqpay_functions[] = {
        PHP_FE_END
};

zend_module_entry liqpay_module_entry = {
        STANDARD_MODULE_HEADER_EX,
        NULL,
        liqpay_mod_deps,
        PHP_EXTENSION_NAME,
        liqpay_functions,
        PHP_MINIT(liqpay),
        PHP_MSHUTDOWN(liqpay),
        NULL,
        NULL,
        PHP_MINFO(liqpay),
        PHP_EXTENSION_VERSION,
        STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_LIQPAY
ZEND_GET_MODULE(liqpay)
#endif
