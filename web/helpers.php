<?php
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
function GetSubStringFromTokenIndex($str,$tokenIndex){
        $tokenCounter=0;
        $token = strtok($str,"/");
        $outputStr="";
        while($token !== false){
                $tokenCounter++;
                $token = strtok("/");
                if($tokenCounter >= $tokenIndex){
                        $outputStr=$outputStr."/".$token;
                }
        }
        return $outputStr;
}
?>
