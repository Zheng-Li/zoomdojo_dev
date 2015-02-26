(function($){
    Drupal.behaviors.organization_manager = {
        attach : function(context, settings) {
            $(document).ready(function(){
                /*
                var FindJobModel = Backbone.Model.extend({
                    defaults: {

                    }
                });
                */
                var DetailedJobPageView = Backbone.View.extend({

                    el: $('.zd-job-page-wrapper'),
                    initialize: function() {
                        return this;
                    },
                    events: {
                        "click .btn-save":  "clickSave",
                        "click .btn-share": "clickShare",
                        "click .btn-apply": "clickApply",
                    },
                    clickApply: function(){
                        if(Drupal.settings.userId > 1){                    
                            $.ajax({
                                type: "GET",
                                url:  '/counter_increasement',
                                data: {"jobId":Drupal.settings.jobId},
                                    });
                        //window.open(Drupal.settings.jobUrl, "_blank");
                        //window.location.href=Drupal.settings.jobUrl;
                        }
                        else{
                            if(Drupal.settings.userId == 1){
                                //window.open(Drupal.settings.jobUrl, "_blank");
                                window.location.href=Drupal.settings.jobUrl;
                            }
                        }
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

                window.DetailedJobPage = new DetailedJobPageView();

            });
        }
    };
})(jQuery);