--TEST--
LiqPay->api() and next call Liqpay->get_response_code()
--CREDITS--
Victor Simon <viktorsimon@i.ua>
--SKIPIF--
<?php 
if(!extension_loaded('liqpay')) print "skip";?>
--FILE--
<?php
require_once 'require.inc';

$liqpay = new LiqPay($public_key, $private_key);
$liqpay->api($path, $params, $timeout);
$liqpay_test = $liqpay->get_response_code();
var_dump($liqpay_test);
?>
===[END]===

--EXPECTF--
int(%i)
===[END]===
