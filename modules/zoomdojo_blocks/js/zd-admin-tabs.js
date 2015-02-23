(function($){
    Drupal.behaviors.zoomdojo_block = {
        attach : function(context, settings) {
            $(document).ready(function(){
                var addFormView = Backbone.View.extend({
                    el: $('#edit-tab-bck-view'),
                    tabs:     null,
                    dialog:   null,
                    initialize: function() {
                        var selfObject = this;

                        //init
                        selfObject.tabs = $("#tabs").tabs();
                        selfObject.dialog = $("#dialog").dialog({
                            autoOpen: false,
                            modal: true,
                            buttons: {
                                Add: function() {
                                    selfObject.addNewTab($(this));
                                },
                                Cancel: function() {
                                    $(this).dialog("close");
                                }
                            }
                        });

                        // close icon: removing the tab on click
                        selfObject.tabs.delegate("span.ui-icon-close", "click", function() {
                              var panelId = $(this).closest("li").remove().attr("aria-controls");
                              $("#" + panelId).remove();
                              selfObject.tabs.tabs("refresh");
                        });
                    },
                    events: {
                        "click #add_tab":            "openDialogForNewTab",
                        "click .add-item-btn":       "addNewRowToTab",
                        "click .delete-current-row": "deleteRowOfTab",
                        "change .nw":                "changeNewWindow",
                        "click #submit-form":        "submitForm",
                    },
                    openDialogForNewTab: function() {
                        this.dialog.dialog("open");
                    },
                    addNewTab: function(dialog) {
                        var selfObject = this;
                        var val = parseInt($('.category-radios:checked').val());
                        if (val == 0) {
                            var cid = $('#select-category option:selected').val();
                            var is = 0;
                            $('.ui-tabs-nav li a').each(function(i, item){
                                if ($(this).attr('href').replace("#tabs-","") == cid) {
                                    is = 1;
                                }
                            });
                            if (!is) {
                                var tabTemplate = "<li><a href='#{href}'>#{label}</a><span class='ui-icon ui-icon-close' role='presentation'>Remove Tab</span></li>";

                                var label = $('#select-category option:selected').text(),
                                    id    = "tabs-" + cid,
                                    li    = $(tabTemplate.replace( /#\{href\}/g, "#" + id ).replace( /#\{label\}/g, label )),
                                    tabContentHtml = _.template($('#tab-new-content').html(), {'cid': cid});
                                    selfObject.tabs.find(".ui-tabs-nav").append(li);
                                    selfObject.tabs.append("<div id='" + id + "'>" + tabContentHtml + "</div>");
                                    selfObject.tabs.tabs("refresh");
                                    $('#tabs ul li:last-child a').click();
                            }
                            dialog.dialog("close");
                        } else if (val == 1) {
                            var categName = $('#new-categ-name').val();
                            if ($.trim(categName) == '') {
                                alert('Category name is empty!');
                                return false;
                            }
                            var url = '/admin/zoomdojo/tablet-panel/categories/add-new-ajax';

                            selfObject.sendAjaxRequest('GET', url, {name:categName}, function(data){
                                var cid = data.id;
                                if (cid > 0) {
                                    console.log(cid);
                                    // create tab
                                    var is = 0;
                                    $('.ui-tabs-nav li a').each(function(i, item){
                                        if ($(this).attr('href').replace("#tabs-","") == cid) {
                                            is = 1;
                                        }
                                    });
                                    if (!is) {
                                        var tabTemplate = "<li><a href='#{href}'>#{label}</a><span class='ui-icon ui-icon-close' role='presentation'>Remove Tab</span></li>";

                                        var label = categName,
                                            id    = "tabs-" + cid,
                                            li    = $(tabTemplate.replace( /#\{href\}/g, "#" + id ).replace( /#\{label\}/g, label )),
                                            tabContentHtml = _.template($('#tab-new-content').html(), {'cid': cid});
                                        selfObject.tabs.find(".ui-tabs-nav").append(li);
                                        selfObject.tabs.append("<div id='" + id + "'>" + tabContentHtml + "</div>");
                                        selfObject.tabs.tabs("refresh");
                                        $('#tabs ul li:last-child a').click();
                                    }
                                    dialog.dialog("close");
                                } else {
                                    alert('Category already exists');
                                }
                            }, function(data){
                                alert(data.text);
                            });
                        }
                        return false;
                    },
                    addNewRowToTab: function(e) {
                        var cid = $(e.currentTarget).data('cid');
                        var rowHtml = _.template($('#tab-new-row').html(), {'cid':cid}); 
                        $('#tabs-'+cid).append(rowHtml);
                        return false;
                    },
                    deleteRowOfTab: function (e) {
                        $(e.currentTarget).parent().remove();
                    },
                    changeNewWindow: function(e) {
                        if ($(e.currentTarget).attr('checked')) {
                            $(e.currentTarget).next().val(0);
                            $(e.currentTarget).attr('checked', false);
                        } else {
                            $(e.currentTarget).next().val(1);
                            $(e.currentTarget).attr('checked', true);
                        }
                    },
                    submitForm: function() {
                        $('#form-tabbbled-block').submit();
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
                });

                window.addFormView  = new addFormView();
            });
        }
    };
})(jQuery);