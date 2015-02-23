(function($){
    Drupal.behaviors.organization_manager = {
        attach : function(context, settings) {
            $(document).ready(function(){

                var FindPositionsFiltersModel = Backbone.Model.extend({
                    defaults: {
                        page:         Drupal.settings.page,
                        location:     Drupal.settings.location,
                        keywords:     Drupal.settings.keywords,
                        keyword:      0,
                        urlAlias:     Drupal.settings.urlAlias,
                        display:      Drupal.settings.display
                        
                    },
                    url: function() {
                        return $('#zd-find-jobs-common-view').data('url');
                    },
                    isNew: function() {
                        return true;
                    }
                });

                var FindPositionsCommonView = Backbone.View.extend({
                    el: $('#zd-find-jobs-common-view'),
                    template: $('#one-organization-template'),
                    //templateJobs: $('#jobs-template'),
                    contentBody: $('#zd-jobs-content-body'),
                    getEmployersAjax: null,
                    availableTags: new Array(),
                    initialize: function() {
                        var selfObject = this;
                        _.bindAll(this, "sendServerRequestbyting");
                        this.model.bind('change:page', this.sendServerRequestbyting);
                        this.model.bind('change:company_name', this.sendServerRequestbyting);
                        
                        var availableTags = new Array();
                        $('#search-keyword').typeahead({
                            items:20,
                            minLength:2,
                            updater: function (item) {
                                 selfObject.selectEmployer(item, 1);
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
                        //selfObject.contentBody.find('.tooltips').each(function(){
                        //      $(this).tooltip({title:$(this).data('tooltips-text')});
                        //});
                        return this;
                    },
                    events: {
                        "click .pagination a"      : "changePage",
                        "change #dispalay-ctl"     : "changeDisplayBy"
                    },

                    
                    selectText: function(e) {
                        $(e.currentTarget).select();
                    },

                    sendAjaxRequest: function(method, url, params, callback, error) {
                        if (this.getEmployersAjax !== null) {
                            this.getEmployersAjax.abort();
                        }
                        this.getEmployersAjax = $.ajax({
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
                    loadingBig: function(show) {
                        if (show) {
                            $('#zd-big-loading-image').show();
                        } else {
                            $('#zd-big-loading-image').hide();
                        }
                    },
                    loadingLittle: function(id) {
                        var html = $('#zd-loadding-little').html();
                        $('#organization-job-content-'+id).html(html);
                    },
                    sendServerRequestbyting: function() {
                        var selfObject = this;
                        selfObject.loadingBig(true);
                        
                        this.model.save({id:0}, {
                            success: function(modal, resp) {

                                if (typeof resp.needLogIn !== 'undefined' && resp.needLogIn) {
                                    var _url = resp.url.replace(/&display=\d+/,'&display='+resp.requestedLimit) + resp.requestedPage;
                                    App.singInPopup();
                                    if (!($.browser.msie  && parseInt($.browser.version, 10) === 8)) {
                                        window.history.pushState('', '', _url);
                                        trackAjaxRequest("Zoomdojo - Job Search Results", _url);
                                    }
                                    selfObject.loadingBig(false);
                                }else{
                                    selfObject.renderPositions(resp.positions, resp);
                                    selfObject.changeToolPanel(resp);
                                }
                            },
                            
                            error: function(XMLHttpRequest){
                                alert("error");
                                selfObject.loadingBig(false);
                            }
                            
                        });
                    },
                    
                    changePage: function(e) {
                        var page = $(e.currentTarget).data('page');
                        this.model.set('page', page);
                        return false;
                    },

                    changeDisplayBy: function(e) {
                        
                        var display = $(e.currentTarget).val();
                        this.model.set('display', display);
                        if (this.model.get('page') == 0) {
                            this.sendServerRequestbyting();
                        } else {
                            this.model.set('page', 0);
                        }
                        return false;    
                    },

                    renderPositions: function(positions, options) {
                        var selfObject = this;
                        selfObject.contentBody.html('');
                        _.each(positions, function(position){
                            positions.opt = {
                                'location': options.location,
                            };
                            selfObject.contentBody.append(selfObject.renderPosition(position));
                           // selfObject.contentBody.find('.tooltips').each(function(){
                           //   $(this).tooltip({title:$(this).data('tooltips-text')});
                           // });
                        });
                        $('.share-view .btn-share').share();
                        selfObject.loadingBig(false);
                    },
                    renderPosition: function(position) {
                        return _.template(this.template.html(), position);
                    },
                    changeToolPanel: function(options) {
                        var pagin = _.template($('#pagin-template').html(), options);
                        var url = options.url + options.currentPage;
                        if (!($.browser.msie  && parseInt($.browser.version, 10) === 8)) {
                            window.history.pushState('', '', url);
                            trackAjaxRequest("Zoomdojo - Job Search Results", url);
                        }
                        $('#zd-find-jobs-common-view .pagination').html(pagin);
                        var limit = options.limit * options.currentPage + 1;
                        var endLimit = options.limit * options.currentPage + parseInt(options.limit);
                        if (endLimit > options.countRows) {
                            endLimit = options.countRows;
                        }
                        $('#zd-limit-row').text(limit);
                        $('#zd-end-limit-row').text(endLimit);
                        $('#zd-count-row').text(options.countRows);
                        $('#zd-location').html(options.allJobString);
                        //clear input
                        $('#search-keyword').val('');
                        this.model.set('limit', 0);
                    },
                });

                window.findJobs = new FindPositionsCommonView({model: new FindPositionsFiltersModel()});

            });
        }
    };   
})(jQuery);