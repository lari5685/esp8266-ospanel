<?php 
$myFile = "data_temp";
$fh = fopen($myFile, 'r');
$theData = fread($fh, 5);
fclose($fh);
echo $theData;
?>