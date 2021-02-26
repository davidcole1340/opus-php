--TEST--
Check if opus is loaded
--SKIPIF--
<?php
if (!extension_loaded('opus')) {
    echo 'skip';
}
?>
--FILE--
<?php
echo 'The extension "opus" is available';
?>
--EXPECT--
The extension "opus" is available
