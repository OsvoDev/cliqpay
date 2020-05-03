--TEST--
LiqPay->api() ====> result
--CREDITS--
Victor Simon <viktorsimon@i.ua>
--SKIPIF--
<?php if(!extension_loaded("liqpay")) print "skip"; ?>
--FILE--
<?php
require_once 'require.inc';

$liqpay = new LiqPay($public_key, $private_key);
$liqpay_test = $liqpay->api($path, $params, $timeout);
var_dump($liqpay_test);
?>
===[END]===

--EXPECTF--
object(stdClass)#%i (3) {
  ["err_description"]=>
  string(10) "wrong path"
  ["result"]=>
  string(5) "error"
  ["status"]=>
  string(5) "error"
}
===[END]===
