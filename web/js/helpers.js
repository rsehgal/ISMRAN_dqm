$(document).ready(function(){
		$('#searchButton').click(function(){
				alert($('#searchText').val());
				});


		$('#searchButton').click(function(){
				var urlLink = 'GetQueriedData.php';
				$.ajax({url: urlLink, success: function(result){
						$('#queriedData').html(result)
						//$.getScript('js/custom.js');
						}}
				      );
				});

		}); 
