<?php 
$myFile = "data_rele";
$fh = fopen($myFile, 'r');
$theData = fread($fh, 6);
fclose($fh);
echo $theData;
?>