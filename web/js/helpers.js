function GetTodaysDate(){
	var date = new Date();
	var day = date.getDate();
	var month = date.getMonth() + 1;
	var year = date.getFullYear();
	if (month < 10) month = '0' + month;
	if (day < 10) day = '0' + day;
	var today = year + '-' + month + '-' + day;
	return today;
}
function GetMonthName(monthNumber) {

		var months = ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun', 'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec'];
		return months[monthNumber - 1];

}

function GetDataOnClick(){
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
                }
$(document).ready(function(){
	
		$('#searchButton').click(function(){
				GetDataOnClick();
		});

		$('#loggedMessages').load("GetLoggedMessages.php");
		
		$('#loadElog').click(function(event){
			event.preventDefault();
			$('#newMessage').show();
			$('#newMessage').load("elog.php");
			$('#loggedMessages').hide();
		});

}); 
