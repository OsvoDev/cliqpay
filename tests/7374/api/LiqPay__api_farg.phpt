--TEST--
LiqPay->api() Error first arg
--CREDITS--
Victor Simon <viktorsimon@i.ua>
--SKIPIF--
<?php if(!extension_loaded("liqpay")) print "skip"; ?>
--FILE--
<?php
require_once 'require.inc';

$liqpay = new LiqPay($public_key, $private_key);
$path = [];
$liqpay_test = $liqpay->api($path, $params, $timeout);

var_dump($liqpay_test);
?>
===[END]===

--EXPECTF--
Fatal error: Uncaught TypeError: Argument 1 passed to LiqPay::api() must be of the type string, array given in %s:%i
Stack trace:
#0 %s(%i): LiqPay->api(Array, Array, 5)
#1 {main}
  thrown in %s on line %i