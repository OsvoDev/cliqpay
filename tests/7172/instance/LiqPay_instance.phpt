--TEST--
LiqPay->__construct() create instance LiqPay
--CREDITS--
Victor Simon <viktorsimon@i.ua>
--SKIPIF--
<?php if(!extension_loaded("liqpay")) print "skip"; ?>
--FILE--
<?php
require_once 'require.inc';

$liqpay = new LiqPay($public_key, $private_key);

var_dump($liqpay);
?>
===[END]===

--EXPECTF--
object(LiqPay)#%i (6) {
  ["_api_url":"LiqPay":private]=>
  string(26) "https://www.liqpay.ua/api/"
  ["_checkout_url":"LiqPay":private]=>
  string(36) "https://www.liqpay.ua/api/3/checkout"
  ["_supportedCurrencies":protected]=>
  array(5) {
    [0]=>
    string(3) "EUR"
    [1]=>
    string(3) "USD"
    [2]=>
    string(3) "UAH"
    [3]=>
    string(3) "RUR"
    [4]=>
    string(3) "RUB"
  }
  ["_public_key":"LiqPay":private]=>
  string(11) "pub_k_00000"
  ["_private_key":"LiqPay":private]=>
  string(11) "prv_k_00000"
  ["_server_response_code":"LiqPay":private]=>
  NULL
}
===[END]===
