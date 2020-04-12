--TEST--
signature_test1() Basic test
--SKIPIF--
<?php
if (!extension_loaded('signature')) {
	echo 'skip';
}
?>
--FILE--
<?php
$ret = signature_test1();

var_dump($ret);
?>
--EXPECT--
The extension signature is loaded and working!
NULL
