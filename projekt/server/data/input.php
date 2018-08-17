<?php 
$myFile = "data_rele";
$fh = fopen($myFile, 'r');
$theData = fread($fh, 6);
fclose($fh);
echo $theData;
$temp=$_GET['temp'];
$myFile = "data_temp";
$fh = fopen($myFile, 'w');
$the = fwrite($fh, $temp);
echo $temp;
?>