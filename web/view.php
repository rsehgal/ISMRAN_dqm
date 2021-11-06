<?php
header('Content-type: text/html');
function Connect($servername,$username,$password,$dbname){

// Create connection
$conn = new mysqli($servername, $username, $password,$dbname);

// Check connection
if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}
//echo nl2br("Connected successfully\n");

return $conn;
}

echo "<center><h2>ISMRAN Data Status</h2></center>";
$servername = "127.0.0.1";
//$username = "ismran";
$username = "barcq";
//$password = "ismran123";
$password = "barcq";
//$dbname="ismran_db";
$dbname="barcq";
$conn=Connect($servername,$username,$password,$dbname);
$sqlQuery="SELECT * from ismran_files";
$results=$conn->query($sqlQuery);
//echo $results."\n";
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
//echo "<td><center>".$row['integrityCheck']."</center></td>";
//echo $row."\n";
//echo nl2br("FileName : ".$row["hashCode"]."\n");
//echo "raman <br/>";
echo "</tr>";
}
}else{
echo "0 results";
}
echo "</table></center>";
$conn->close();
?> 
