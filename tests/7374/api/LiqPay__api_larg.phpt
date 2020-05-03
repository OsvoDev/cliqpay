--TEST--
LiqPay->api() Error last arg
--CREDITS--
Victor Simon <viktorsimon@i.ua>
--SKIPIF--
<?php if(!extension_loaded("liqpay")) print "skip"; ?>
--FILE--
<?php
require_once 'require.inc';

$liqpay = new LiqPay($public_key, $private_key);
$timeout = [];
$liqpay_test = $liqpay->api($path, $params, $timeout);

var_dump($liqpay_test);
?>
===[END]===

--EXPECTF--
Fatal error: Uncaught TypeError: Argument 3 passed to LiqPay::api() must be of the type int or null, array given in %s:%i
Stack trace:
#0 %s(%i): LiqPay->api('error_path', Array, Array)
#1 {main}
  thrown in %s on line %i