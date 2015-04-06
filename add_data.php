<?php
    // Connect to MySQL
    include("dbconnect.php");

	$SQL = "INSERT INTO motion (motion) VALUES ('".$_GET["motionornot"]."')";     

    // Execute SQL statement
    
	$dbh->query($SQL);
    // Go to the review_data.php (optional)
    header("Location: review_data.php");
?>
