<?php
header('Content-type: text/html');
echo "<html><head><title>Ismran Data Status</title>
<script src='js/jquery.js'></script>
<script src='js/helpers.js'></script>
<script>

</script>
</head>
<body>";
echo "<center><h2>Data Status</h2>";
echo "<center> <h3>The current file is shown in <font color='red'>Red Color</font></h3></center><br/>";
echo "<input type='date' name='searchText' id='searchText'> ";
echo "<input type='button' name='searchButton' id='searchButton' value='Search'/>";
echo "</center><br/>";
echo "<div id='queriedData' name='queriedData'/>";

?>
