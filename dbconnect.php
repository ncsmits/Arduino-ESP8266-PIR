<?php
$MyUsername = "USERNAME";  // mysql username
$MyPassword = "PASSWORD";  // mysql password
$MyHostname = "localhost";      // Your Host
$Database = "DB_NAME";    // Name of your database
$dbh = mysqli_connect($MyHostname , $MyUsername, $MyPassword, $Database);
if (!$dbh) {
    die("Connection failed: " . mysqli_connect_error());
}
?>

