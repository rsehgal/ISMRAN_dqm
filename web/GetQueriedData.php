<?php
include "helpers.php";

$servername = "127.0.0.1";
$username = "ismran";
$password = "ismran123";
$dbname="ismran_db";

$conn=Connect($servername,$username,$password,$dbname);
$sqlQuery="SELECT * from ismran_files";
$results=$conn->query($sqlQuery);

echo "<center><table border='1'>";
echo "<tr bgcolor='yellow'><th>Source Path </th><th>Destination Path</th> <th>File Name</th>";
//echo "<th>File Integrity</th>;
echo "</tr>";
if($results->num_rows > 0){
	while($row=$results->fetch_assoc()){
		if($row['integrityCheck']==1)
			echo "<tr bgcolor='#56de91'>";
		else
			echo "<tr>";
		echo "<td>".$row["filePath"]."</td>";
		echo "<td>".$row['remoteFilePath']."</td>";
		echo "<td><a href='".$row['remoteFilePath']."/".$row['fileName']."'>".$row['fileName']."</a></td>";
		echo "</tr>";
	}
}else{
	echo "0 results";
}
echo "</table></center>";
echo "</body></html>";
$conn->close();

?>
