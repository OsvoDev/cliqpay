--TEST--
LiqPay->api() Error next(middle) argument
--CREDITS--
Victor Simon <viktorsimon@i.ua>
--SKIPIF--
<?php if(!extension_loaded("liqpay")) print "skip"; ?>
--FILE--
<?php
require_once 'require.inc';

$liqpay = new LiqPay($public_key, $private_key);
$params = [];
$liqpay_test = $liqpay->api($path, $params, $timeout);

var_dump($liqpay_test);
?>
===[END]===

--EXPECTF--
Fatal error: Uncaught InvalidArgumentException: version is null in %s:%i
Stack trace:
#0 %s(%i): LiqPay->api('error_path', Array, 5)
#1 {main}
  thrown in %s on line %i