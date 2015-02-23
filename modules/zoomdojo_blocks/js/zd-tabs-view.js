(function($){
    Drupal.behaviors.zoomdojo_block = {
        attach : function(context, settings) {
            $(document).ready(function(){

                $('#myTab a:first').tab('show');
                
                $('.zd-url').click(function() {
                    var nw   = $(this).data('nw');
                    var href = $(this).attr('href');
                    if (nw) {
                        window.open(href, '', 'toolbar=no,location=no,status=no,menubar=no,scrollbars=yes,resizable=yes,width=780,height=550');
                    } else {
                        window.location.href = href;
                    }
                    return false;
                });
            });
        }
    };
})(jQuery);