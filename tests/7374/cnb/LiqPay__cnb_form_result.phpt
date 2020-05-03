--TEST--
LiqPay->cnb_form() Good <form> from current data
--CREDITS--
Victor Simon <viktorsimon@i.ua>
--SKIPIF--
<?php if(!extension_loaded("liqpay")) print "skip"; ?>
--FILE--
<?php
require_once 'require.inc';

$liqpay = new LiqPay($public_key, $private_key);
$params = [
        'version' => 3,
        'amount' => 100,
        'currency' => LiqPay::CURRENCY_UAH,
        'description' => 'test form payment'
];
$liqpay_test = $liqpay->cnb_form($params);

var_dump($liqpay_test);
?>
===[END]===

--EXPECTF--
string(534) "
            <form method="POST" action="https://www.liqpay.ua/api/3/checkout" accept-charset="utf-8">
                <input type="hidden" name="data" value="eyJ2ZXJzaW9uIjozLCJhbW91bnQiOjEwMCwiY3VycmVuY3kiOiJVQUgiLCJkZXNjcmlwdGlvbiI6InRlc3QgZm9ybSBwYXltZW50IiwicHVibGljX2tleSI6InB1Yl9rXzAwMDAwIn0=" />
                <input type="hidden" name="signature" value="tpawuy+AccEuZatAfKZ9ypGDssk=" />
                <input type="image" src="//static.liqpay.ua/buttons/p1ru.radius.png" name="btn_text" />
            </form>
            "
===[END]===
