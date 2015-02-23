(function($){
	Drupal.behaviors.zoomdojo_experts = {
		attach : function(context, settings) {
			$(document).ready(function(){
				$('#zd-expert-select select').change(function(){
                    var selected = $(this).find('option:selected');
                    var cid = selected.data('cid');
                    var type = selected.data('type');
                    $('#zd-expert-cid input').val(cid);
                    $('#zd-expert-type input').val(type);
                });
			});
		}
	};
})(jQuery);