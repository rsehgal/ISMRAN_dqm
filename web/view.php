<?php
header('Content-type: text/html');
function Connect($servername,$username,$password,$dbname){

// Create connection
$conn = new mysqli($servername, $username, $password,$dbname);

// Check connection
if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}
echo nl2br("Connected successfully\n");
return $conn;
}

$servername = "127.0.0.1";
$username = "ismran";
$password = "ismran123";
$dbname="ismran_db";
$conn=Connect($servername,$username,$password,$dbname);
$sqlQuery="SELECT * from ismran_files";
$results=$conn->query($sqlQuery);
//echo $results."\n";
if($results->num_rows > 0){
while($row=$results->fetch_assoc()){
//echo $row."\n";
echo nl2br("FileName : ".$row["hashCode"]."\n");
//echo "raman <br/>";
}
}else{
echo "0 results";
}

$conn->close();
?> 
