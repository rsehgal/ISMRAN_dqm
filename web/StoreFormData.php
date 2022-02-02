<?php
include "helpers.php";

//$servername = "127.0.0.1";
$servername = "localhost";// "10.44.11.130";
$username = "ismran";
$password = "ismran123";
$dbname="ismran_db";

$name=$_POST['name'];
$msg=$_POST['msg'];

//echo $name." : ".$msg."<br/>";
$conn=Connect($servername,$username,$password,$dbname);
$sqlQuery="INSERT into elog (name,ts,dt,message )values('$name',NOW(),NOW(),'$msg') ";
//echo $sqlQuery."<br/>";
echo "Message Logged successfully. <br/>";
$results=$conn->query($sqlQuery);
/*
echo "<center><table border='1'>";
echo "<tr bgcolor='yellow'><th>Source Path </th><th>Destination Path</th> <th>File Name</th><th>Calibration File </th>";
//echo "<th>File Integrity</th>;
echo "</tr>";
if($results->num_rows > 0){
	
	while($row=$results->fetch_assoc()){
		if($row['integrityCheck']==1)
			echo "<tr bgcolor='#56de91'>";
		else
			echo "<tr>";
		if($row['fileExistInSourceDir']==0)
		echo "<td bgcolor='#ec7063'>".$row["filePath"]."</td>";
		else
		echo "<td>".$row["filePath"]."</td>";
		echo "<td>".$row['remoteFilePath']."</td>";
		$hrefPath=GetSubStringFromTokenIndex($row['remoteFilePath'],2);
		echo "<td><a href='.".$hrefPath."/".$row['fileName']."'>".$row['fileName']."</a></td>";
		//echo "<td><a href='".$row['remoteFilePath']."/".$row['fileName']."'>".$row['fileName']."</a></td>";
		echo "<td>".$row["calibrationTag"]."</td>";
		echo "</tr>";
	}
	 
}else{
	echo "0 results";
}
echo "</table></center>";
echo "</body></html>";
*/
$conn->close();

?>
