--TEST--
LiqPay, access test for constants
--CREDITS--
Victor Simon <viktorsimon@i.ua>
--SKIPIF--
<?php if(!extension_loaded("liqpay")) print "skip"; ?>
--FILE--
<?php

echo 'LiqPay::CURRENCY_EUR - ' . LiqPay::CURRENCY_EUR . PHP_EOL;
echo 'LiqPay::CURRENCY_USD - ' . LiqPay::CURRENCY_USD . PHP_EOL;
echo 'LiqPay::CURRENCY_UAH - ' . LiqPay::CURRENCY_UAH . PHP_EOL;
echo 'LiqPay::CURRENCY_RUB - ' . LiqPay::CURRENCY_RUB . PHP_EOL;
echo 'LiqPay::CURRENCY_RUR - ' . LiqPay::CURRENCY_RUR . PHP_EOL;

?>
===[END]===

--EXPECT--
LiqPay::CURRENCY_EUR - EUR
LiqPay::CURRENCY_USD - USD
LiqPay::CURRENCY_UAH - UAH
LiqPay::CURRENCY_RUB - RUB
LiqPay::CURRENCY_RUR - RUR
===[END]===
