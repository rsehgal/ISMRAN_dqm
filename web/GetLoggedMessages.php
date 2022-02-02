<?php
include "helpers.php";

//$servername = "127.0.0.1";
$servername = "localhost";// "10.44.11.130";
$username = "ismran";
$password = "ismran123";
$dbname="ismran_db";

/*$day=$_POST['day'];
$month=$_POST['month'];
$year=$_POST['year'];

$queryDate=$day.$month.$year;
echo "<center>";
echo $queryDate."<br/><br/>";
echo "</center>";*/

$conn=Connect($servername,$username,$password,$dbname);
$sqlQuery="SELECT * from elog order by ts DESC";
$results=$conn->query($sqlQuery);

//echo "<center><a href='elog.php'> <b><font color='red'>Enter a new log message</font></b></center></a>";
//echo "<br/>";
echo "<center><table border='1'>";
echo "<tr bgcolor='yellow'><th>Reported By </th><th>Log Message</th> <th>Date Time</th>";
echo "</tr>";
if($results->num_rows > 0){
	
	while($row=$results->fetch_assoc()){
		echo "<tr>";
		echo "<td>".$row['name']."</td> <td>".nl2br($row['message'])."</td> <td>".$row['ts']. "</td>";
		echo "</tr>";
	}
	 
}else{
	echo "0 results";
}
echo "</table></center>";
echo "</body></html>";
$conn->close();

?>
