(function($){
    Drupal.behaviors.zoomdojo_block = {
        attach : function(context, settings) {
            $(document).ready(function(){
                $('.delete-items-category, .delete-items-block').click(function(){
                    var selfObject = $(this);
                    if (confirm('Are you sure you want delete this row?')) {
                        var url = $(this).attr('href');
                        $.ajax({
                            'url': url,
                            'success': function(res) {
                                res = JSON.parse(res);
                                if (res.status === 'OK') {
                                    selfObject.parent().parent().remove();
                                } else {
                                    alert('Error delete!');
                                }
                            }
                        });
                    }
                    return false;
                });

                var ItemsBlockTabView = Backbone.View.extend({
                    el: $('#items-wrapper'),
                    tabs: null,
                    dialog: null,
                    initialize: function() {
                        var selfObject = this;

                        //init
                        selfObject.tabs = $("#tabs").tabs();
                        selfObject.dialog = $("#dialog").dialog({
                            autoOpen: false,
                            modal: true,
                            buttons: {
                                Add: function() {
                                    selfObject.addNewTab();
                                    $(this).dialog("close");
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

                        // Initialise the first table (as before)
                        selfObject.initDragTable();
                    },
                    events: {
                        "click #add_tab":            "openDialogForNewTab",
                        "click .add-item-btn":       "addNewRowToTab",
                        "click .delete-current-row": "deleteRowOfTab",
                        "click #submit-form":        "sendForm"
                    },
                    initDragTable: function() {
                        $(".table-items").tableDnD({
                            onDragClass: "tableDragClass",
                            onDrop: function(table, row) {
                                $(table).find('.weight-input').each(function(i){
                                    $(this).val(i);
                                });

                            }
                        });
                    },
                    openDialogForNewTab: function() {
                        this.dialog.dialog("open");
                        return false;
                    },
                    addNewTab: function() {
                        var selfObject = this;
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
                        selfObject.initDragTable();
                        return false;
                    },
                    addNewRowToTab: function(e) {
                        var cid  = $(e.currentTarget).data('cid');
                        var weight = parseInt($('#tabs-table-'+cid+' tbody').find('.weight-input').last().val()) + 1;
                        var rowHtml = _.template($('#tab-new-row').html(), {'cid':cid, 'weight':weight}); 
                        $('#tabs-table-'+cid+' tbody').append(rowHtml);
                        this.initDragTable();
                        return false;
                    },
                    deleteRowOfTab: function (e) {
                        $(e.currentTarget).parent().parent().remove();
                    },
                    sendForm: function(e) {
                      e.preventDefault();
                      e.stopPropagation();
                      $('#send-items-data-form').submit();
                    }
                });

                window.itemsBlockTabView = new ItemsBlockTabView();
            });
        }
    };
})(jQuery);