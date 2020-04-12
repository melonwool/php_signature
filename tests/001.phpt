--TEST--
Check if signature is loaded
--SKIPIF--
<?php
if (!extension_loaded('signature')) {
	echo 'skip';
}
?>
--FILE--
<?php
echo 'The extension "signature" is available';
?>
--EXPECT--
The extension "signature" is available
