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
$temp1=$_GET['celcius'];
$heart1=$_GET['beat'];
//$voltage1=$_GET['voltage'];
//$temp1= 200;
//$heart1 = 60;
//echo "$temp1";
$sql = "INSERT INTO status (DeviceId, Temperature, HeartBeat)
VALUES ('1', '$temp1', '$heart1')";

if ($conn->query($sql) === TRUE) {
    echo "New record created successfully";
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}

$conn->close();
?>