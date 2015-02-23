(function($){
    $(document).ready(function(){

        var FindJobPopupView = Backbone.View.extend({
            el: $('#findJobsForm, #findNewJobsForm'),
            initialize: function() {
                var selfObject = this;

                $('.employer-autocomplete').typeahead({
                    items:5,
                    minLength:2,
                    updater: function (item) {
                        return item;
                    },
                    highlighter: function (item) {
                        var regex = new RegExp( '(' + this.query + ')', 'gi' );
                        return item.replace( regex, "<strong>$1</strong>" );
                    },
                    source: function (query, process) {
                        selfObject.delay(function(){
                            var url = '/get-employers';
                            availableTags = [];
                            var params = {
                                location:     0,
                                job_type:     0,
                                job_industry: 0,
                                company_name: query
                            };
                            selfObject.sendAjaxRequest('GET', url, params, function(resp){
                                _.each(resp.data, function(item){
                                    availableTags.push(item.name);
                                });
                                return process(availableTags);
                            }, function(resp){
                                return process(availableTags);
                            });
                        }, '300');
                    }
                });

                return this;
            },
            events: {
                'change #zd-pop-country': 'changeCountry',
                'change #zd-pop-state':   'changeState',
            },
            changeCountry: function(e) {
                var selfObject  = this;
                var val         = parseInt($(e.currentTarget).val());
                if (val >= 0) {
                    var stateSelect = $(e.currentTarget).parents('form').find('#zd-pop-state');
                    var url         = '/get-states/' + val;
                    selfObject.sendAjaxRequest('GET', url, null, function(resp){
                        selfObject.renderSelect(stateSelect, resp.data);
                    });
                    // clean city select
                    var citySelect = $(e.currentTarget).parents('form').find('#zd-pop-city');
                    var locations = {
                        0: {
                            'id': 0,
                            'title': 'All cities'
                        }
                    };
                    selfObject.renderSelect(citySelect, locations);
                }
            },
            changeState: function(e) {
                var selfObject  = this;
                var val         = $(e.currentTarget).val();
                var citySelect  = $(e.currentTarget).parents('form').find('#zd-pop-city');
                var url         = '/get-cities/' + val;
                selfObject.sendAjaxRequest('GET', url, null, function(resp){
                    selfObject.renderSelect(citySelect, resp.data);
                });
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
            delay: (function(){
                var timer = 0;
                return function(callback, ms){
                    clearTimeout (timer);
                    timer = setTimeout(callback, ms);
                };
            })(),
            renderSelect: function(selector, locations) {
                var count = parseInt(locations.length);
                if (count > 1) {
                    selector.show();
                } else {
                    selector.hide();
                }
                var html = '';
                _.each(locations, function(location){
                    html += '<option value="'+location.id+'">'+location.title+'</option>';
                });
                selector.html(html);
            }
        });

        window.findJobPopup = new FindJobPopupView();
    });
})(jQuery);
