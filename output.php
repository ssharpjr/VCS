<?php

mysql_connect("localhost","root","password") or die("Could not connect ".mysql_error());
mysql_select_db("viscon");

// Query the database
$sql = "SELECT realtime.press_id, press_status.id, press_status.desc
        FROM realtime, press_status
        WHERE realtime.status_id = press_status.id
           ORDER BY press_id ASC";
$result = mysql_query($sql);

// Set number of columns
$maxcols = 5;
$i = 0;



?>
<!doctype html public \"-//W3C//DTD HTML 4.0 //EN\">
<html>
<meta http-equiv='refresh' content='5'>
<head>
<title>Visual Management Tool</title>
<link rel='stylesheet' href='stylesheets.css' type='text/css'>
</head>
    
<body>
<table id='fixedtable'>
<tr>
<?php
while ($row = mysql_fetch_array($result)) {
    if ($i == $maxcols){
        $i = 0;
        echo "</tr><tr>\n";
    }
    
    if ($row['id'] == '0') {
        echo "<td bgcolor='green'><font color='white'><b><center>";
    } else if ($row['id'] == '1') {
        echo "<td bgcolor='yellow'><font color='black'><b><center>";
    } else {
        echo "<td bgcolor='red'><font color='white'><b><center>";
    }
    echo $row['press_id']."<br>".$row['desc']."</center></b></font></td>";

    $i++;
}

?>

</table>
</body>
</html>