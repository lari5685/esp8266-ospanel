<?php 
$myFile = "data_temp";
$fh = fopen($myFile, 'r');
$theData = fread($fh, 60);
fclose($fh);
$temp = substr($theData, 5);
echo $temp;
?>