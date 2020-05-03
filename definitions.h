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

#ifndef LIQPAY_DEFINITIONS_H
#define LIQPAY_DEFINITIONS_H

#define PHP_EXTENSION_NAME "LiqPay"
#define PHP_EXTENSION_VERSION "1.0.1"
#define PHP_EXTENSION_AUTHOR_NAME "Osvo"
#define PHP_EXTENSION_API_V "3"

#ifndef LIQPAY_RELEASE
#define PHP_EXTENSION_STATUS "Debug"
#else //EL_LIQPAY_RELEASE
#define PHP_EXTENSION_STATUS "Production"
#endif // LIQPAY_RELEASE

#define CURRENCY_EUR "EUR"
#define CURRENCY_USD "USD"
#define CURRENCY_UAH "UAH"
#define CURRENCY_RUB "RUB"
#define CURRENCY_RUR "RUR"

#endif //LIQPAY_DEFINITIONS_H
