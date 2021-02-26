--TEST--
test1() Basic test
--SKIPIF--
<?php
if (!extension_loaded('opus')) {
    echo 'skip';
}
?>
--FILE--
<?php
$ret = test1();

var_dump($ret);
?>
--EXPECT--
The extension opus is loaded and working!
NULL
