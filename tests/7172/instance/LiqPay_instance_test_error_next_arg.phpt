--TEST--
LiqPay->__construct() Error 2 arg behaviour "type string"
--CREDITS--
Victor Simon <viktorsimon@i.ua>
--SKIPIF--
<?php if(!extension_loaded("liqpay")) print "skip"; ?>
--FILE--
<?php
require_once 'require.inc';
$private_key = [];
$liqpay = new LiqPay($public_key, $private_key);

var_dump($liqpay);
?>
===[END]===

--EXPECTF--
Fatal error: Uncaught TypeError: Argument 2 passed to LiqPay::__construct() must be of the type string, array given in %s:%i
Stack trace:
#0 %s(%i): LiqPay->__construct('pub_k_00000', Array)
#1 {main}
  thrown in %s on line %i