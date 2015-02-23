(function($){
    $(document).ready(function(){
        var EventsView = Backbone.View.extend({
            el: $('#zd-events-view'),
            calendar: null,
            initialize: function() {
                var selfObject = this;

                selfObject.calendar = $(".data-picker-pagin").datepicker({
                    'format': 'yyyy-mm-dd'
                }).on('changeDate', function(e) {
                    selfObject.calendar.hide();
                    selfObject.selectDate(e);
                }).data('datepicker');
            },
            events: {
                "click .date .icon-calendar": "showCalendar",
                "click .btn-pager": "changePage",
            },
            showCalendar: function() {
                var selfObject = this;
                if (selfObject.calendar != null) {
                    selfObject.calendar.show();
                }
            },
            changePage: function(e) {
                var val = $(e.currentTarget).data('date');
                this.changeDate(val);
                return false;
            },
            selectDate: function(e) {
                var val = $(e.currentTarget).val();
                this.changeDate(val);
                return false;
            },
            changeDate: function(date) {
                var selfObject = this;
                var url = '/get-events';
                this.sendAjaxRequest('GET', url, {'date':date}, function(resp){
                    //OK status
                    selfObject.renderEvents(resp.data.events);
                    selfObject.changeControlData(resp.data);
                },
                function(resp){
                    //No data
                    var html = $('#events-empty-tmp').html();
                    $('#zd-events-content-body').html(html);
                    selfObject.changeControlData(resp.data);
                });
            },
            sendAjaxRequest: function(method, url, params, callback, error) {
                var selfObject = this;
                selfObject.loadingBig(true);
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
                            selfObject.loadingBig(false);
                        }
                    }
                });
            },
            renderEvents: function(events) {
                var tmp = $('#one-event-template').html();
                var html = '';
                _.each(events, function(event){
                    html += _.template(tmp, event);
                });
                $('#zd-events-content-body').html(html);
            },
            changeControlData: function(data) {
                var url = data.url + data.date;
                window.history.pushState('', '', url);
                var prev = data.prevDay;
                var date = data.date;
                var next = data.nextDay;
                $('.btn-pager-prev').data('date', prev);
                $('.data-picker-pagin').val(date);
                $('.btn-pager-next').data('date', next);
                $('#week-info-str').text(data.info);
            },
            loadingBig: function(show) {
                if (show) {
                    $('#zd-big-loading-image').show();
                } else {
                    $('#zd-big-loading-image').hide();
                }
            }
        });

        window.events  = new EventsView();
    });
})(jQuery);