--TEST--
LiqPay->__construct() Error first arg behaviour "type string"
--CREDITS--
Victor Simon <viktorsimon@i.ua>
--SKIPIF--
<?php if(!extension_loaded("liqpay")) print "skip"; ?>
--FILE--
<?php
require_once 'require.inc';
$public_key = [];
$liqpay = new LiqPay($public_key, $private_key);

var_dump($liqpay);
?>
===[END]===

--EXPECTF--
Fatal error: Uncaught TypeError: Argument 1 passed to LiqPay::__construct() must be of the type string, array given in %s:%i
Stack trace:
#0 %s(%i): LiqPay->__construct(Array, 'prv_k_00000')
#1 {main}
  thrown in %s on line %i