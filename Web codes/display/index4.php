<?php
$url=$_SERVER['REQUEST_URI'];
header("Refresh: 5; URL=$url"); // Refresh the webpage every 5 seconds
?>
<!DOCTYPE html>
<html lang="en">
<head>
  <title>Cow Health Monitoring</title>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="css/bootstrap.min.css">
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
  <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.7/umd/popper.min.js"></script>
  <script src="js/bootstrap.min.js"></script>
</head>
<body>

<div class="container" style = "padding-top:50px;"> 
	<div class = "row">
		<div class = "col-md-9">
			<p style = "text-align:center; margin:20px; font-size:20px;color:#6D6E70;"><b>COW HEALTH MONITORING DASHBOARD</b></p>         
		<?php
		$servername = "localhost";
		$username = "root";
		$password = "1234";
		$dbname = "smartcow";

		// Create connection
		$conn = new mysqli($servername, $username, $password, $dbname);
		// Check connection
		if ($conn->connect_error) {
			die("Connection failed: " . $conn->connect_error);
		} 

		$sql = "SELECT DeviceId, Temperature, HeartBeat FROM status ORDER BY DateTime DESC Limit 3 ";
		$result = $conn->query($sql);

		if ($result->num_rows > 0) {
			echo " 
			 <table class='table table-hover' style = 'border: 1px solid #ccc; border-radius: 20px;'>
				  <tr style ='color:#6D6E70;text-align:center;font-size:20px;' >	
					<th style = 'padding-bottom:45px;padding-top:45px;'><img src = 'img/cow-monitoring-190416-1.png' style = 'height:43px;'></th>
					<th style = 'padding-bottom:45px;padding-top:45px;'>Temperature</th>
					<th style = 'padding-bottom:45px;padding-top:45px;'>HeartBeat</th>
				  </tr>";
   // output data of each row
    while($row = $result->fetch_assoc()) {
        echo "  <tr style = 'color:#6D6E70;text-align:center;font-size:20px;'>
					<td style = 'padding-bottom:45px;padding-top:45px;'><img src = 'img/iconfinder_Cow_head_130204.png' style = 'height:43px;'> &nbsp;Cow" . $row["DeviceId"]. "</td>
					<td style = 'padding-bottom:45px;padding-top:45px;' >" . $row["Temperature"]. "°C</td>
					<td style = 'padding-bottom:45px;padding-top:45px;'>" . $row["HeartBeat"]. "</td>
				  </tr>";
			}
			echo "</table>";
		} else {
			echo "0 results";
		}

		$conn->close();
		?> 
		 </div>
		 <div class = "col-md-3" style = "margin-top:70px;">
			 <table class="table" style = "border: 1px solid #ccc;">
				  <tr style = "color:#6D6E70;text-align:center;">
					<td style = "text-align:center;color:#D0D2D3;">
						<img src = "img/cow-monitoring-190416-2.png" style = "height:60px; padding-top:10px;">
						<br/><p><b>Room Temperature</b></p>
					</td>
				  </tr>
				   <tr>
					<td style = "text-align:center; margin:20px; font-size:35px;">40°C<br/>
					<p style = "font-size:12px; color :#da6f2e;" ><b>Standard: (25-35)°C<br/>Abnormal: (36-40)°C</b></td>
				  </tr>
			 </table>
			  <table class="table" style = "border: 1px solid #ccc;">
				  <tr style = "color:#6D6E70;text-align:center;">
					<td style = "text-align:center;color:#D0D2D3;">
						<img src = "img/cow-monitoring-190416-3.png" style = "height:60px;padding-top:10px;">
						<br/>
						<p><b>Room Humidity</b></p>
					</td>
				  </tr>
				   <tr>
					<td style = "text-align:center; margin:20px; font-size:40px;">40%<br/>
					<p style = "font-size:12px; color :#da6f2e;" ><b>Standard: (25-35)%<br/>Abnormal: (36-40)%</b></td></td>
				  </tr>
			 </table>
		 </div>
	</div>
</div>

</body>
</html>






























