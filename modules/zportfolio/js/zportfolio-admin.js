(function($){
    Drupal.behaviors.zoomdojo_block = {
        attach : function(context, settings) {
            $(document).ready(function(){
                $('.delete-row').click(function(){
                    var selfObject = $(this);
                    if (confirm('Are you sure you want delete this row?')) {
                        var url = $(this).attr('href');
                        $.ajax({
                            'url': url,
                            'success': function(res) {
                                res = JSON.parse(res);
                                if (res.status === 'OK') {
                                    selfObject.parent().parent().remove();
                                } else {
                                    alert('Error delete!');
                                }
                            }
                        });
                    }
                    return false;
                });

            });
        }
    };
})(jQuery);