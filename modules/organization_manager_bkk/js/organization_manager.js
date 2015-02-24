(function($){
    Drupal.behaviors.organization_manager = {
        attach : function(context, settings) {
            $(document).ready(function(){

                var OrganizationView = Backbone.View.extend({
                    el: $('#organization-manager-organization-edit'),
                    initialize: function() {
                        $('.select2').select2();
                        if ($(this.el).hasClass('edit-job-wrapper')) {
                            tinymce.init({
                                selector: ".edit-job-wrapper #edit-description",
                                toolbar: "insertfile undo redo | styleselect | bold italic | alignleft aligncenter alignright alignjustify | bullist numlist outdent indent | link image"
                            });
                        }
                        return this;
                    },
                    events: {
                        'change .edit-location-country': 'changeCountry',
                        'change .edit-location-state': 'changeState',
                        'click #add-new-location-row': 'addLocationRow',
                        'click .btn-delete': 'deleteLocationRow'
                    },
                    changeCountry: function(e) {
                        var selfObject  = this;
                        var val         = $(e.currentTarget).val();
                        var stateSelect = $(e.currentTarget).parent().next().find('.edit-location-state');
                        var url         = '/get-states-admin/' + val;
                        selfObject.sendAjaxRequest('GET', url, null, function(resp){
                            selfObject.renderSelect(stateSelect, resp.data);
                        });
                        // clean city select
                        var citySelect = $(e.currentTarget).parent().next().next().find('.edit-location-city');
                        var locations = {
                            0: {
                                'id': 0,
                                'title': 'All cities'
                            }
                        };
                        selfObject.renderSelect(citySelect, locations);
                    },
                    changeState: function(e) {
                        var selfObject  = this;
                        var val         = $(e.currentTarget).val();
                        var citySelect  = $(e.currentTarget).parent().next().find('.edit-location-city');
                        var url         = '/get-cities-admin/' + val;
                        selfObject.sendAjaxRequest('GET', url, null, function(resp){
                            selfObject.renderSelect(citySelect, resp.data);
                        });
                    },
                    addLocationRow: function() {
                        var row = $('#location-row-template').html();
                        $('#insert-location-row').append(row);
                        return false;
                    },
                    deleteLocationRow: function(e) {
                        var count = $('#insert-location-row .btn-delete').size();
                        if(count > 1) {
                            $(e.currentTarget).parent().parent().remove();
                        } else {
                            alert('Entity must to have one and more locations');
                        }
                    },
                    sendAjaxRequest: function(method, url, params, callback, error) {
                        $.ajax({
                            type: method,
                            url:  url,
                            data: params,
                            success: function(data) {
                                if (data.length > 0) {
                                    var resp = JSON.parse(data);
                                    if (resp.status === 'OK') {
                                        callback(resp);
                                    } else {
                                        error(resp);
                                    }
                                }
                            }
                        });
                    },
                    renderSelect: function(selector, locations) {
                        var html = '';
                        _.each(locations, function(location){
                            html += '<option value="'+location.id+'">'+location.title+'</option>';
                        });
                        selector.html(html);
                    }
                });

                window.org = new OrganizationView();
            });
        }
    };
})(jQuery);
