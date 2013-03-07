<?php

//Variables
$ipaddress = $_SERVER['REMOTE_ADDR'];
$query_string = $_SERVER['QUERY_STRING'];
$press_id = $_GET['press_id'];
$status_id = $_GET['status_id'];
$startup_id = $_GET['startup_id'];

$press_id = mysql_real_escape_string($press_id);
$status_id = mysql_real_escape_string($status_id);
$startup_id = mysql_real_escape_string($startup_id);

mysql_connect("localhost","root","password") or die("Could not connect ".mysql_error());
mysql_select_db("viscon");

// Update REALTIME Table.
mysql_query("UPDATE realtime
            SET status_id = $status_id
               WHERE press_id = $press_id");

// Insert into HIST_RT Table.
mysql_query("INSERT INTO hist_rt
            (press_id, status_id, startup_id)
            VALUES
            ('$press_id','$status_id','$startup_id')");

//$result = mysql_query($sql);

/*
if ($result) {
    echo "<br>Input data successful<br>";
} else {
    echo "<br>Input data failed <br>";
    echo mysql_errno(). "<br>";
    echo mysql_error();
    echo "<br><br>";
    echo "Query String: ".$query_string."<br>";
    echo "Press Number: <b>".$press_id."</b><br />";
    echo "Status Code: <b>" .$status_id."</b><br />";
    echo "Startup Code: <b>" .$startup_id. "</b><br />";
    echo "Client IP Address: <b>".$ipaddress."</b><br />";

}
*/



mysql_close();
?>
