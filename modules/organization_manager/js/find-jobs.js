(function($){
    Drupal.behaviors.organization_manager = {
        attach : function(context, settings) {
            $(document).ready(function(){

                var FindJobsFiltersModel = Backbone.Model.extend({
                    defaults: {
                        page:         Drupal.settings.page,
                        location:     Drupal.settings.location,
                        job_type:     Drupal.settings.jobType,
                        job_industry: Drupal.settings.jobIndustry,
                        company_name: Drupal.settings.companyName,
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

                var FindJobsCommonView = Backbone.View.extend({
                    el: $('#zd-find-jobs-common-view'),
                    template: $('#one-organization-template'),
                    templateJobs: $('#jobs-template'),
                    contentBody: $('#zd-jobs-content-body'),
                    getEmployersAjax: null,
                    availableTags: new Array(),
                    initialize: function() {
                        var selfObject = this;
                        _.bindAll(this, "sendServerRequest");
                        this.model.bind('change:page', this.sendServerRequest);
                        this.model.bind('change:company_name', this.sendServerRequest);
                        
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
                                        location:     selfObject.model.get('location'),
                                        job_type:     selfObject.model.get('job_type'),
                                        job_industry: selfObject.model.get('job_industry'),
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
                        selfObject.contentBody.find('.tooltips').each(function(){
                              $(this).tooltip({title:$(this).data('tooltips-text')});
                        });
                        return this;
                    },
                    events: {
                        "click .btn-save"          : "clickSave",
                        "click .open-job"          : "openJobs",
                        "click .pagination a"      : "changePage",
                        "click .zd-jobs-pagination": "changeJobsPage",
                        "click .btn-delete"        : "deleteMySavedEntity",
                        "click #search-keyword"    : "selectText",
                        "click  #btn-find-keyword" : "selectEmployer",
                        "change #dispalay-ctl"     : "changeDisplayBy"
                    },
                    selectEmployer: function(item, select) {
                        var selfObject = this;
                        var val = $.trim($('#search-keyword').val().replace(/[^A-Za-z0-9\s]/g, ""));
                        if (select) {
                            val = item;
                        }
                        selfObject.model.set('keyword', 1);
                        selfObject.model.set('company_name', val);
                        selfObject.model.set('page', 0);

                        $('#search-keyword').blur();
                        return false;
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
                    sendServerRequest: function() {
                        var selfObject = this;
                        selfObject.loadingBig(true);
                        //console.log(this.model.url);
                        //alert('url before send :');
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
                                    selfObject.renderOrganizations(resp.organizations, resp);
                                    selfObject.changeToolPanel(resp);
                                }
                            },
                            error: function(){
                                alert('error');
                                selfObject.loadingBig(false);
                            }
                        });
                    },
                    clickSave: function(e) {
                        var selfObject = this;
                        var id  = $(e.currentTarget).data('id');
                        var uid = $(e.currentTarget).data('uid');
                        if (uid == 0) {
                            App.singInPopup();
                        } else {
                            if (!$(e.currentTarget).hasClass('btn-saved')) {
                                var  url = '/save-entity/' + id + '/type/0';
                                selfObject.sendAjaxRequest('GET', url, '', function(resp){
                                    $(e.currentTarget).find('.saved-text-for-replace').text('Saved');
                                    $(e.currentTarget).addClass('btn-saved');
                                });
                                $(e.currentTarget).tooltip('destroy');
                            } else {
                                var  url = '/delete-entity/' + id + '/type/0';
                                selfObject.sendAjaxRequest('GET', url, '', function(resp){
                                    $(e.currentTarget).find('.saved-text-for-replace').text('Save');
                                    $(e.currentTarget).removeClass('btn-saved');
                                });
                                $(e.currentTarget).tooltip({title:$(e.currentTarget).data('tooltips-text')});
                            }
                        }
                        return false;
                    },
                    changeJobsPage: function(e) {
                        var selfObject = this;
                        var params     = {
                            'organizationId': $(e.currentTarget).data('id'), 
                            'jobType':        $(e.currentTarget).data('jtid'), 
                            'industryType':   $(e.currentTarget).data('jiid'), 
                            'location':       {
                                'country': $(e.currentTarget).data('location-c'),
                                'state':   $(e.currentTarget).data('location-s'),
                                'city':    $(e.currentTarget).data('location-t')
                            }, 
                            'page':           $(e.currentTarget).data('page'),
                        };
                        selfObject.sendJobsServerRequest(params, false);
                    },
                    openJobs: function(e) {
                        var selfObject = this;
                        var id         = $(e.currentTarget).data('id');
                        var jtid       = $(e.currentTarget).data('jtid');
                        var count      = $(e.currentTarget).data('count');
                        var params     = {
                            'organizationId': id, 
                            'jobType':        jtid, 
                            'industryType':   selfObject.model.get('job_industry'), 
                            'location':       selfObject.model.get('location'), 
                            'page':           0,
                        };
                        if (count > 0) {
                            if ($('#organization-job-content-'+id).hasClass('zd-first')) { 
                                selfObject.sendJobsServerRequest(params, true);
                                $('#organization-job-content-'+id).removeClass('zd-first');
                            } else {
                                selfObject.toggleJobs(id);
                            }
                        } else {
                            // no jobs
                            var msg = $('<div/>', {
                                'class': 'empty-job-result',
                                'html': 'Please click on organisation name for more info.'
                            });
                            $('#organization-job-content-'+id).html(msg);
                            selfObject.toggleJobs(id);
                        }
                        return false;
                    },
                    sendJobsServerRequest: function(params, toggle) {
                        var selfObject = this;
                        var url = '/find-jobs-get-jobs';
                        selfObject.loadingLittle(params.organizationId);
                        if (toggle)
                            selfObject.toggleJobs(params.organizationId);

                        $.ajax({
                            type: "GET",
                            url:  url,
                            data: params,
                            success: function(data) {
                                if (data.length > 0) {
                                    var jobs = JSON.parse(data);
                                    selfObject.renderOrganizationJobs(params.organizationId, jobs);
                                }
                            }
                        });
                    },
                    renderOrganizationJobs: function(id, jobs) {
                        var selfObject = this;
                        $('#org-count-job-'+id).text(jobs.countRows);
                        var htmlJobs = _.template(selfObject.templateJobs.html(), jobs);
                        $('#organization-job-content-'+id).html(htmlJobs);
                    },
                    toggleJobs: function(id) {
                        if ($('#organization-job-content-'+id).hasClass('zd-hide')) {
                            $('#organization-job-content-'+id).collapse('show');
                            $('#org-jobs-bottom-text-'+id).hide();
                            $('#organization-job-content-'+id).removeClass('zd-hide');
                            $('#organization-job-icon-'+id).removeClass('zd-arrow-down');
                            $('#organization-job-icon-'+id).addClass('zd-arrow-up');
                        } else {
                            $('#organization-job-content-'+id).collapse('hide');
                            $('#org-jobs-bottom-text-'+id).show();
                            $('#organization-job-content-'+id).addClass('zd-hide');
                            $('#organization-job-icon-'+id).removeClass('zd-arrow-up');
                            $('#organization-job-icon-'+id).addClass('zd-arrow-down');
                        }
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
                            this.sendServerRequest();
                        } else {
                            this.model.set('page', 0);
                        }
                        return false;
                    },
                    renderOrganizations: function(organizations, options) {
                        var selfObject = this;
                        selfObject.contentBody.html('');
                        _.each(organizations, function(organization){
                            organization.opt = {
                                'locationStr': options.locationStr,
                                'location': options.location,
                                'typeStr': options.typeStr,
                                'jobIndustry': options.jobIndustry,
                                'jobType': options.jobType,
                            };
                            organization.globalJobType = selfObject.model.get('job_type');
                            selfObject.contentBody.append(selfObject.renderOrganization(organization));
                            selfObject.contentBody.find('.tooltips').each(function(){
                              $(this).tooltip({title:$(this).data('tooltips-text')});
                            });
                        });
                        $('.share-view .btn-share').share();
                        selfObject.loadingBig(false);
                    },
                    renderOrganization: function(organization) {
                        return _.template(this.template.html(), organization);
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
                    deleteMySavedEntity: function (e) {
                        if (confirm('Are you sure you want to delete this row?')) {
                            var selfObject = this;
                            var id   = $(e.currentTarget).data('id');
                            var type = $(e.currentTarget).data('type');
                            $.ajax({
                                type: "GET",
                                url:  '/delete-entity/' + id + '/type/' + type,
                                success: function(data) {
                                    if (data.length > 0) {
                                        var resp = JSON.parse(data);
                                        if (resp.status === 'OK') {
                                            selfObject.sendServerRequest();
                                        }
                                    }
                                }
                            });
                        }
                    }
                });

                window.findJobs = new FindJobsCommonView({model: new FindJobsFiltersModel()});

            });
        }
    };
})(jQuery);