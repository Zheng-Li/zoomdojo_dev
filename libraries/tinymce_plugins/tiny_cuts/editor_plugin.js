(function() {
        tinymce.create('tinymce.plugins.TinyCuts', {
                /**
                 * Initializes the plugin, this will be executed after the plugin has been created.
                 * This call is done before the editor instance has finished it's initialization so use the onInit event
                 * of the editor instance to intercept that event.
                 *
                 * @param {tinymce.Editor} ed Editor instance that the plugin is initialized in.
                 * @param {string} url Absolute URL to where the plugin is located.
                 */
                init : function(ed, url) {
                        // Let's invoke the Link dialog on Ctrl+L
                        // addShortcut() can take various other arguments, see
                        // http://www.tinymce.com/wiki.php/API3:method.tinymce.Editor.addShortcut
                        // as well as lines with addCommand() in plugin sources and the advanced theme.
                        ed.onKeyDown.add(function(ed, e) {
                         
                            if (e.keyCode == 13 && e.ctrlKey) {
                               e.preventDefault()
                          e.stopPropagation()
                              var selected_text = ed.selection.getContent(),
                              $node = jQuery(ed.selection.getStart()),
                              return_text = '';

                              return_text = '<p>' + selected_text + '</p>';
                              ed.execCommand('mceInsertContent', 0, return_text);
                            }
                        });
                },
                /**
                 * Returns information about the plugin as a name/value array.
                 * The current keys are longname, author, authorurl, infourl and version.
                 *
                 * @return {Object} Name/value array containing information about the plugin.
                 */
                getInfo : function() {
                        return {
                                longname : 'TinyMCE Shortcuts',
                                author : 'Henrik "TwoD" Danielsson', // Note: EXAMPLE! I do not claim any copyright on this code!
                                authorurl : '',
                                infourl : '',
                                version : "1.0"
                        };
                }
        });
        // Register plugin
        tinymce.PluginManager.add('tiny_cuts', tinymce.plugins.TinyCuts);
})();