(function($){
    Drupal.behaviors.organization_manager = {
        attach : function(context, settings) {
            $(document).ready(function(){
                
                var JobDetailPageView = Backbone.View.extend({
                    el: $('.zd-job-page-wrapper'),
                    initialize: function() {
                        return this;
                    },
                    events: {
                        "click .btn-save":  "clickSave",
                        "click .btn-share": "clickShare",
                    },
                    clickSave: function(e) {
                        var selfObject = this;
                        var id  = $(e.currentTarget).data('id');
                        var uid = $(e.currentTarget).data('uid');
                        if (uid == 0) {
                            App.singInPopup();
                        } else {
                            if (!$(e.currentTarget).hasClass('btn-saved')) {
                                $.ajax({
                                    type: "GET",
                                    url:  '/save-entity/' + id + '/type/1',
                                    success: function(data) {
                                        if (data.length > 0) {
                                            var resp = JSON.parse(data);
                                            if (resp.status === 'OK') {
                                                $(e.currentTarget).find('.saved-text-for-replace').text('Saved');
                                                $(e.currentTarget).addClass('btn-saved');
                                            }
                                        }
                                    }
                                });
                            } else {
                                $.ajax({
                                    type: "GET",
                                    url:  '/delete-entity/' + id + '/type/1',
                                    success: function(data) {
                                        if (data.length > 0) {
                                            var resp = JSON.parse(data);
                                            if (resp.status === 'OK') {
                                                $(e.currentTarget).find('.saved-text-for-replace').text('Save');
                                                $(e.currentTarget).removeClass('btn-saved');
                                            }
                                        }
                                    }
                                });
                            }
                        }
                        return false;
                    },
                    clickShare: function(e) {
                        var id = $(e.currentTarget).data('jid');
                        alert('Click share - organization id = ' + id);
                        return false;
                    }
                });

                window.jobDetailPage = new JobDetailPageView();

            });
        }
    };
})(jQuery);