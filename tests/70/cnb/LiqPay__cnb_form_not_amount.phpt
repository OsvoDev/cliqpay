--TEST--
LiqPay->cnb_form() behaviour "amount is null"
--CREDITS--
Victor Simon <viktorsimon@i.ua>
--SKIPIF--
<?php if(!extension_loaded("liqpay")) print "skip"; ?>
--FILE--
<?php
require_once 'require.inc';

$liqpay = new LiqPay($public_key, $private_key);
$params = [
        'version' => 3
];
$liqpay_test = $liqpay->cnb_form($params);

var_dump($liqpay_test);
?>
===[END]===

--EXPECTF--
Fatal error: Uncaught InvalidArgumentException: amount is null in %s:%i
Stack trace:
#0 %s(%i): LiqPay->cnb_form(Array)
#1 {main}
  thrown in %s on line %i