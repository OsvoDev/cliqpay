--TEST--
LiqPay->cnb_form() Result form output
--CREDITS--
Victor Simon <viktorsimon@i.ua>
--SKIPIF--
<?php if(!extension_loaded("liqpay")) print "skip"; ?>
--FILE--
<?php
require_once 'require.inc';

$liqpay = new LiqPay($public_key, $private_key);
$liqpay_test = $liqpay->cnb_form($params);

var_dump($liqpay_test);
?>
===[END]===

--EXPECT--
string(550) "
            <form method="POST" action="https://www.liqpay.ua/api/3/checkout" accept-charset="utf-8">
                <input type="hidden" name="data" value="eyJ2ZXJzaW9uIjozLCJhbW91bnQiOjEwMDAsImN1cnJlbmN5IjoiVVNEIiwiZGVzY3JpcHRpb24iOiJUZXN0IHBheW1lbnQgZGQtbW0teXl5eSBoOmk6cyIsInB1YmxpY19rZXkiOiJwdWJfa18wMDAwMCJ9" />
                <input type="hidden" name="signature" value="8ekHryORuC0zRCEbi7kb3TrgBGc=" />
                <input type="image" src="//static.liqpay.ua/buttons/p1ru.radius.png" name="btn_text" />
            </form>
            "
===[END]===
