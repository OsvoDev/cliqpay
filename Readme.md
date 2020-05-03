# cliqpay
### LiqPay on C. PHP extension for the LiqPay API

API documentation (en): [www.liqpay.ua/documentation/en](https://www.liqpay.ua/documentation/en)

API documentation (ru): [www.liqpay.ua/documentation/ru](https://www.liqpay.ua/documentation/ru)

## Compile

PHP Supported Versions : 7.0 >= 7.4.4

### Dependencies

1. Standard
2. Spl
3. Curl
4. Json

----------------------------------------------

****You must make sure that you have all the necessary libraries for the normal operation of cURL, more information [here](https://www.php.net/manual/en/curl.installation.php)***

----------------------------------------------

##### Commands:

*Standard :*

`--enable-cli --enable-cgi --enable-json --enable-liqpay`

*Fast and clean :*

`--disable-all --enable-cli --enable-cgi --enable-json --enable-liqpay`

To enable [ZTS](http://www.phpinternalsbook.com/php7/extensions_design/globals_management.html#using-tsrm-macros-to-protect-global-space) you need to add `--enable-zts` and to disable it `--disable-zts`

And to use this extension in production, add the command `--enable-liqpay-release`

Example : `--disable-all --enable-cli --enable-cgi --enable-json --enable-liqpay --enable-liqpay-release`

---------------------------------------------

****You need to download a version of Visual Studio in advance (Community is fine) for a specific version of PHP***

#### To compile on Windows you need to download the appropriate version of phpsdk:
**[7.4](https://windows.php.net/download#php-7.4)**

**[7.3](https://windows.php.net/download#php-7.3)**

**[7.2](https://windows.php.net/download#php-7.2)**

#### or download php-sdk from Microsoft:

[php-sdk-binary-tools](https://github.com/microsoft/php-sdk-binary-tools)

#### or download compiled libraries for your architecture and version PHP [here](https://github.com/OsvoDev/cliqpay/releases/tag/1.0.0)

#### To compile on Linux :
