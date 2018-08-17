<!DOCTYPE html>
<html lang="ru">
<head>
	<meta charset="UTF-8">
	<title>SH</title>
	<link rel="stylesheet" type="text/css" href="stile.css">
	<script src="//code.jquery.com/jquery-1.11.0.min.js">
  </script>
  <script>  
  function show()  
  {  
    
    $.ajax({  
    url: "data/temp-1.php",  
    cache: false,  
    success: function(html)
      {  
      $("#content").html(html); 
      }
    }); 

    $.ajax({  
    url: "data/hibr.php",  
    cache: false,  
    success: function(html)
      {  
      $("#content-1").html(html); 
      }
    }); 
    
             
        }
        
        $(document).ready(function(){  
            show();  
            setInterval('show()',1000);  
        }); 
</script>
</head>

<body>
	<div>
		<form action="index.php" method="post">			
			<input type="submit" value="rele_1_on" name="button">
			<input type="submit" value="rele_2_on" name="button">
			<input type="submit" value="rele_3_on" name="button">
			<input type="submit" value="rele_4_on" name="button">
		</form>
		<form action="index.php" method="post">
			<input type="submit" value="rele_1_off" name="button">
			<input type="submit" value="rele_2_off" name="button">
			<input type="submit" value="rele_3_off" name="button">
			<input type="submit" value="rele_4_off" name="button">
		</form>
	</div>
	<div>
	<?php
		$button = $_POST['button'];
		if ($button =='rele_1_on')
			{$a=1; $flag='a';}
		if ($button =='rele_2_on')
			{$b=1; $flag='b';}
		if ($button =='rele_3_on')
			{$c=1; $flag='c';}
		if ($button =='rele_4_on')
			{$d=1; $flag='d';}

		if ($button =='rele_1_off')
			{$a=0; $flag='a';}
		if ($button =='rele_2_off')
			{$b=0; $flag='b';}
		if ($button =='rele_3_off')
			{$c=0; $flag='c';}
		if ($button =='rele_4_off')
			{$d=0; $flag='d';}

		$fr = fopen('data/data_rele', 'r');
		$t = fgets($fr, 10);
		fclose($fr);

		if ($flag == 'a' )
			$t[0]=$a;
		if ($flag == 'b' )
			$t[1]=$b;
		if ($flag == 'c' )
			$t[2]=$c;
		if ($flag == 'd' )
			$t[3]=$d;
		$fr = fopen('data/data_rele', 'w+');
		$test = fwrite($fr, $t);
		fclose($fr);

		if ($t[0] == 1)
			echo "<img src='img/green.png'>";
		else echo "<img src='img/red.png'>";
		if ($t[1] == 1)
			echo "<img src='img/green.png'>";
		else echo "<img src='img/red.png'>";
		if ($t[2] == 1)
			echo "<img src='img/green.png'>";
		else echo "<img src='img/red.png'>";
		if ($t[3] == 1)
			echo "<img src='img/green.png'>";
		else echo "<img src='img/red.png'>";
	?>
	</div>
	<div>
	<?php  
		$ft = fopen('data/data_temp', 'r');
		$t = fgets($ft, 99);
		fclose($ft);
		$temp = substr($t, 0, 5);
		$hirb = substr($t, 6);
		echo '<div> температура: <b id="content"></b>℃</div>';
		echo '<div> влажность: <b id="content-1"></b>%</div>';

	?>
	</div>
</body>
</html>