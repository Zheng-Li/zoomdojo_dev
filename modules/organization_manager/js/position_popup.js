(function($){
    $(document).ready(function(){

        var FindJobPopupView = Backbone.View.extend({
            el: $('#findJobsFormMini'),
            initialize: function() {
                var selfObject = this;

                $('.keywords-autocomplete').typeahead({
                    items:10,
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
                            var url = '/get-keywords';
                            availableTags = [];
                            var params = {
                                keywords: query
                            };

                            selfObject.sendAjaxRequest('GET', url, params, function(resp){
                                _.each(resp.data, function(item){
                                    availableTags.push(item.result); 
                                });
                                
                                return process(availableTags);
                            }, 

                            function(resp){
                                return process(availableTags);
                            });
                        }, '300');
                    }
                });
                // get-locations///////////////////////////////////////
                $('.location-autocomplete').typeahead({
                    items:10,
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
                            var url = '/get-location';
                            availableTags = [];
                            var params = {
                                location: query
                            };
                            selfObject.sendAjaxRequest('GET', url, params, function(resp){
                                _.each(resp.data, function(item){
                                    availableTags.push(item.Name); 
                                });
                                return process(availableTags);
                            }, 

                            function(resp){
                                return process(availableTags);
                            });
                        }, '300');
                    }
                });

                return this;
            },
            events: {
                //'change #zd-pop-country': 'changeCountry',
                //'change #zd-pop-state':   'changeState',
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
        });

        window.findJobPopup = new FindJobPopupView();
    });
})(jQuery);
