<?php
require_once 'require.inc';
$api_url = [];
$liqpay = new LiqPay($public_key, $private_key, $api_url);

var_dump($liqpay);
?>
===[END]===

