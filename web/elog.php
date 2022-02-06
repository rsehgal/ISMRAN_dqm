<html>
<title>
ISMRAN ELog
</title>
<head>
<script src='js/jquery.js'></script>
<script>
$("form").submit(function (event) {
                    event.preventDefault();
                    var formData = {
                      name: $("#name").val(),
                      msg: $("#msg").val(),
		      neartemp:$('#neartemp').val(),
		      fartemp:$('#fartemp').val(),
		      ambtemp:$('#ambtemp').val(),
		      ambpressure:$('#ambpressure').val(),
		      ambhumidity:$('#ambhumidity').val(),

                    };

                    $.ajax({
                      type: "POST",
                      url: "StoreFormData.php",
                      data: formData,
                      dataType: "json",
                      encode: true,
                    }).done(function (data) {
                      console.log(data);
                    });

		    $('#newMessage').hide();
		    $('#loggedMessages').show();
		    $('#loggedMessages').load("GetLoggedMessages.php");
                  });

$(document).ready(function(){

	$('#tempPresHumi').click(function(){
	alert("Temp Press Humi Clicked....");
	$('#temp-pres-humi').load("GetTempPresHumiTable.php");
	});
});

</script>

</head>
<body>
<?php
echo "<form id='elog_form' method='POST' action='StoreFormData.php'>";
echo "<table border='0'>";
echo "<tr>";
echo "<td>";
//echo "<label for='name' id='label_name'>Your Name*</label>";
echo "Your Name*";
echo "</td>";

echo "<td>";
echo "<input type='text' name='name' id='name' placeholder='Your Name' required></input> <br/>";
echo "</td>";
echo "</tr>";

echo "<tr>";
echo "<td></td>";
echo "<td>";
echo "<textarea id='msg' name='msg' rows='4' placeholder='Enter your Log message' cols='50'></textarea>";
echo "</td>";
echo "</tr>";

echo "<tr></tr>";

echo "<tr>";
echo "<td>";
echo "Temperature <br> Pressure 
<input type='checkbox' id='tempPresHumi' name='tempPresHumi'/>
<br/> Humidity";
echo "</td>";
echo "<td>";
echo "<div id='temp-pres-humi' name='temp-pres-humi'></div>";
echo "</td>";
echo "</tr>";

echo "<tr>";
echo "<td></td>";
echo "<td>";
echo "<input type='submit' id='submit'></input>";
echo "</td>";
echo "</tr>";

echo "</table>";
echo "</form>";
?>
<body>
</html>
