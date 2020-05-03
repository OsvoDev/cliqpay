--TEST--
LiqPay->__construct() Error custom api_url behaviour "string or null"
--CREDITS--
Victor Simon <viktorsimon@i.ua>
--SKIPIF--
<?php if(!extension_loaded("liqpay")) print "skip"; ?>
--FILE--
<?php
require_once 'require.inc';
$api_url = [];
$liqpay = new LiqPay($public_key, $private_key, $api_url);

var_dump($liqpay);
?>
===[END]===

--EXPECTF--
Fatal error: Uncaught TypeError: Argument 3 passed to LiqPay::__construct() must be of the type string, array given in %s:%i
Stack trace:
#0 %s(%i): LiqPay->__construct('pub_k_00000', 'prv_k_00000', Array)
#1 {main}
  thrown in %s on line %i