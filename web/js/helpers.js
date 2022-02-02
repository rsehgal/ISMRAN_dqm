$(document).ready(function(){

		function GetMonthName(monthNumber) {

		var months = ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun', 'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec'];
		return months[monthNumber - 1];

		}

		/*$('#searchButton').click(function(){
				//alert($('#searchText').val());
				var date = new Date($('#searchText').val());
				var day = date.getDate();
				var month = date.getMonth() + 1;
				var year = date.getFullYear();
				//alert([day, GetMonthName(month), year].join('/'));
				});*/


		$('#searchButton').click(function(){

				var date = new Date($('#searchText').val());
				var day = date.getDate();
				var month = date.getMonth() + 1;
				var year = date.getFullYear();
				var monthName = GetMonthName(month);

				var form_data = new FormData();
				form_data.append("day",day);
				form_data.append("month",monthName);
				form_data.append("year",year);

				var urlLink = 'GetQueriedData.php';
				$.ajax({url: urlLink, 
						cache:false,
						type:'post',
						data:form_data,
						processData: false,
						contentType: false,
						success: function(result){
						$('#queriedData').html(result)
						//console.log(result);
						//$.getScript('js/custom.js');
						}}
				      );
		});

		$('#loggedMessages').load("GetLoggedMessages.php");
		
		$('#loadElog').click(function(event){
			event.preventDefault();
			$('#newMessage').show();
			$('#newMessage').load("elog.php");
			$('#loggedMessages').hide();
		});

		/*$("form").submit(function (event) {
		    event.preventDefault();
		    var formData = {
		      name: $("#name").val(),
		      msg: $("#msg").val(),
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

		  });*/

}); 
