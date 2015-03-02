(function($){
	$(document).ready(function () {
		$('#character_count').text('500 characters left');
		$('#job_snippet').keyup(function () {
			var max = 500;
			var len = $(this).val().length;
			if (len >= max) {
				$('#character_count').text('You\'ve reached the limit');
			} else {
				var ch = max - len;
				$('#character_count').text(ch + ' characters left');
			}
		});
	});
})(jQuery);

