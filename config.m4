dnl Copyright (c) 2020, Osvo All rights reserved.
dnl     Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
dnl     - Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
dnl     - Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer
dnl         in the documentation and/or other materials provided with the distribution.
dnl     - Neither the name of the Osvo nor the names of its contributors may be used to endorse or promote products derived from this software
dnl         without specific prior written permission.
dnl
dnl THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
dnl LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
dnl IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
dnl OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
dnl OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
dnl OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

PHP_ARG_ENABLE(liqpay, Whether to enable the "LiqPay" support, [ --enable-liqpay Enable "LiqPay" support])
if test "$PHP_LIQPAY" != "no"; then
    AC_DEFINE(HAVE_LIQPAY, 1, [Whether you have LiqPay])
    liqpay_src = "php_liqpay.c liqpay_class.c liqpay_functions.c"
    PHP_NEW_EXTENSION(liqpay, $liqpay_src, $ext_shared)
    PHP_SUBST(LIQPAY_SHARED_LIBADD)
    AC_DEFINE(LIQPAY_RELEASE, 1, [LiqPay release])
fi
