<?php
include "helpers.php";

//$servername = "127.0.0.1";
$servername = "localhost";// "10.44.11.130";
$username = "ismran";
$password = "ismran123";
$dbname="ismran_db";

$name=$_POST['name'];
$msg=$_POST['msg'];
$id=$_POST['id'];
//$name=$_POST['name_'.$id];
//$msg=$_POST['msg_'.$id];

$update=$_POST['update'];
echo "ID : $id : Update : $update <br/>";
echo $name." : ".$msg."<br/>";
$conn=Connect($servername,$username,$password,$dbname);
if($update==1){
//$sqlQuery="update elog set name='$name',message='$msg',ts=NOW(),dt=NOW() where logid=$id";
$sqlQuery="update elog set name='$name',message='$msg',ts=NOW(),dt=NOW() where logid=$id";
$results=$conn->query($sqlQuery);
$sqlQuery="INSERT into elog_history (name,ts,dt,message,logid )values('$name',NOW(),NOW(),'$msg',$id) ";
$results=$conn->query($sqlQuery);

}
else{
$sqlQuery="INSERT into elog (name,ts,dt,message )values('$name',NOW(),NOW(),'$msg') ";
$results=$conn->query($sqlQuery);
}
//echo $sqlQuery."<br/>";
//echo "Message Logged successfully. <br/>";

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

$conn->close();

?>
