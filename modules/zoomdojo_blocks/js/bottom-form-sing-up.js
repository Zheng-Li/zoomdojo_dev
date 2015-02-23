(function($){
    $(document).ready(function(){
        $('#form-inline-sing-up').submit(function(){
            var email = $.trim($('#email-footer-input').val());
            if (email != '') {
                if (!Drupal.settings.loggedIn) {
                    $('#user-register-form .form-item-mail #edit-mail').val(email);
                    App.singUpPopup();
                } else {
                    App.showMessage('Thanks, we will send you our latest updates.');
                }
            } else {
                App.showMessage('Email is empty!');
            }
            $('#email-footer-input').val('');
            $('#email-footer-input').blur();
            return false;
        });
    });
})(jQuery);