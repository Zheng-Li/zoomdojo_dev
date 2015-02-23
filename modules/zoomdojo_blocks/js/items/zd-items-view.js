(function($){
    Drupal.behaviors.zoomdojo_blocks = {
        attach : function(context, settings) {
            $(document).ready(function(){
                $('.zd-toogle-items').toggle(function() {
                    var cid = $(this).data('cid');
                    $(this).html('<span>Hide</span>');
                    $('#zd-toogle-items-'+cid).slideToggle('slow');
                }, function() {
                    var cid = $(this).data('cid');
                    $(this).html('<span>Read More</span>');
                    $('#zd-toogle-items-'+cid).slideToggle('slow');
                });
            });
        }
    };
})(jQuery);