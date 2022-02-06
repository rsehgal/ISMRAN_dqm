<script>
$('.updateButton').click(function (event) {
//$('#raman').click(function (event) {
                    alert("updateButton click");
                    //event.preventDefault();
                    var formData = {
                      name: $("#name_"+$(this).attr("id")).val(),
                      msg: $("#msg_"+$(this).attr("id")).val(),
                      id: $(this).attr("id"),
                      update:1
                    };
                    console.log("----------------");
                    console.log(formData);
                    console.log("----------------");

                    $.ajax({
                      type: "POST",
                      url: "StoreFormData.php",
                      data: formData,
                      dataType: "json",
                      encode: true,
		      success: function (response) {
    			    //$('p').append('status: ' + status + ', data: ' + data);
				alert("Response from StoreFormData : "+response);
    		      }

                    });/*.done(function (data) {
			alert(data);
                      console.log(data);
                    });*/

                    $('#newMessage').hide();
                    $('#loggedMessages').show();
                    //$('#loggedMessages').load("GetLoggedMessages.php");
                  });

</script>

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
//$sqlQuery="SELECT * from elog order by ts DESC";
$sqlQuery="SELECT * from elog order by logid DESC";
$results=$conn->query($sqlQuery);

//echo "<center><a href='elog.php'> <b><font color='red'>Enter a new log message</font></b></center></a>";
//echo "<br/>";
echo "<center><table border='1'>";
echo "<tr bgcolor='yellow'><th>Reported By </th><th>Log Message</th> <th>Date Time</th>";
echo "</tr>";
if($results->num_rows > 0){
	
	while($row=$results->fetch_assoc()){
		$id=$row['logid'];
		echo "<tr>";
		echo "<td><input type='text' id='name_$id' name='name_$id' value='".$row['name']."'/></td> 
		      <td><textarea id='msg_$id' name='msg_$id' rows='4' cols='50' >".$row['message']."</textarea></td> 
		      <td><input type='text' id='datetime_$id' name='datetime_$id' value='".$row['ts']."'/></td>
		      <td><input type='button' class='updateButton' id=$id name=$id value='Update' /></td>";
		echo "</tr>";
		
	}
	 
}else{
	echo "0 results";
}
echo "</table></center>";
echo "</body></html>";
$conn->close();

?>
