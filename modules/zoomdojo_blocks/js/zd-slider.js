(function($){
    Drupal.behaviors.zoomdojo_block = {
        attach : function(context, settings) {
            $(document).ready(function(){
                
                $('.bxslider').bxSlider({
                    slideWidth: 1026,
                    minSlides: 1,
                    maxSlides: 3,
                    moveSlides: 1,
                    speed: 1000,
                    slideMargin: 0,
                    auto: false,
                    autoHover: true,
                    pager: false,
                    onSlideBefore: function (currentSlideNumber, totalSlideQty, currentSlideHtmlObject) {
                        $('.bxslider div').removeClass('active');
                        $('.bxslider div').eq(currentSlideHtmlObject+3).addClass('active');
                    }
                });

            });
        }
    };
})(jQuery);