(function($){
    Drupal.behaviors.zoomdojo_zportfolio = {
        attach : function(context, settings) {
            $(document).ready(function(){
                var Zresume = Backbone.View.extend({
                    el: $('#z-resume'),
                    initialize: function() {
                        CKEDITOR.on( 'instanceCreated', function( event ) {
                            var editor = event.editor,
                                element = editor.element;

                            // Customize editors for headers and tag list.
                            // These editors don't need features like smileys, templates, iframes etc.
                            if ( element.is( 'h1', 'h2', 'h3' ) || element.getAttribute( 'id' ) == 'taglist' ) {
                                // Customize the editor configurations on "configLoaded" event,
                                // which is fired after the configuration file loading and
                                // execution. This makes it possible to change the
                                // configurations before the editor initialization takes place.
                                editor.on( 'configLoaded', function() {

                                    // Remove unnecessary plugins to make the editor simpler.
                                    editor.config.removePlugins = 'colorbutton,find,flash,font,' +
                                        'forms,iframe,image,newpage,removeformat,' +
                                        'specialchar,stylescombo,templates';
                                        
                                    // Rearrange the layout of the toolbar.
                                    editor.config.toolbarGroups = [
                                        { name: 'editing',		groups: [ 'basicstyles', 'links' ] },
                                        { name: 'paragraph'},
                                        { name: 'undo' },
                                        { name: 'clipboard',	groups: [ 'selection', 'clipboard' ] }
                                    ];
                                });
                            }
                            editor.on( 'doubleclick', function( evt )
                            {
                               var element = CKEDITOR.plugins.link.getSelectedLink( editor ) || evt.data.element;
                               

                               if ( !element.isReadOnly() )
                               {
                                  if ( element.is( 'a' ) )
                                  {
                                     evt.data.dialog = ( element.getAttribute( 'name' ) && ( !element.getAttribute( 'href' ) || !element.getChildCount() ) ) ? 'anchor' : 'link';
                                     editor.getSelection().selectElement( element );
                                     if(evt.data.dialog == 'link'){
                                       window.open(element.getAttribute('href'), '_blank');
                                       return false;
                                     }
                                  }
                                  else if ( CKEDITOR.plugins.link.tryRestoreFakeAnchor( editor, element ) )
                                     evt.data.dialog = 'anchor';
                               }
                            });
                        });
                    },
                    events: {
                        'submit #z-resume-form': 'changeValues',
                        'click .zresume-submit-download': 'downloadAfterSubmit',
                        'click .zresume-submit-preview': 'previewAfterSubmit',
                        'click #zresume-popup-submit': 'setResumeTitle',
                        'click .zresume-as-submit': 'getResumeTitleForm',
                        'click .zresume-delete': 'deleteResume',
                        'click .preview-pdf': 'previewPDF',
                        'contextmenu #view-resume-preview-popup' : 'previewPDFblocker',
                        'click .z-edit-btn': 'editZitem'
                    },
                    changeValues: function () {
                        $('.z-editor').each(function(){
                            var vid = $(this).data('valueid');
                            var val = $(this).html();
                            $('#z-value-' + vid).val(val);
                        });
                    },
                    setResumeTitle: function() {
                        var msg = 'Resume Name is empty!';
                        var name = App.trim($('#z-resume-name').val());
                        if (name == '') {
                            if (jQuery.browser.version == 8.0) {
                                alert(msg);
                            } else {
                                App.showMessage(msg);
                            }
                            return false;
                        }
                        var myResumes = Drupal.settings.zportfolio.myResumes || [];
                        myResumes = JSON.parse(myResumes);
                        var isDuplicate = false;
                        _.each(myResumes, function(item){
                            if (item.toUpperCase() == name.toUpperCase()) {
                                msg = 'You have duplicate resume name. ';
                                if (jQuery.browser.version == 8.0) {
                                    alert(msg);
                                } else {
                                    App.showMessage(msg);
                                }
                                isDuplicate = true;
                            }
                        });
                        if (isDuplicate) {
                            return false;
                        }

                        $('#z-name-insert').val(name);
                        $('#z-rid-insert').val('');
                        $('#z-resume-form').submit();
                    },
                    getResumeTitleForm: function() {
                        jQuery('#view-resume-name-popup').modal('show');
                        $('#z-resume-form input[name=download-after-submit]').remove();
                        $('#z-resume-form input[name=preview-after-submit]').remove();
                        return false;
                    },
                    downloadAfterSubmit: function(){
                      $('#z-resume-form input[name=download-after-submit]').remove();
                      $('#z-resume-form').append('<input type=hidden name=download-after-submit value=1/>');
                      jQuery('#view-resume-name-popup').modal('show');
                      return false;
                    },
                    previewAfterSubmit: function(){
                      $('#z-resume-form input[name=preview-after-submit]').remove();
                      $('#z-resume-form').append('<input type=hidden name=preview-after-submit value=1/>');
                      jQuery('#view-resume-name-popup').modal('show');
                      return false;
                    },
                    deleteResume: function() {
                        if (confirm('Are you sure you want to delete this résumé?')) {
                            $('#z-resume-form').append('<input type=hidden name=delete-resume value=1/>').submit();
                            return true;
                        }
                        return false;
                    },
                    previewPDF: function(e){
                      $btn = $(e.currentTarget);
                      $btn.prepend('<i class="loading"/>');
                      jQuery('#view-resume-preview-popup h3').text(jQuery('#page-title').text());
                      jQuery.ajax($btn.attr('href')).done(function(data){
                        jQuery('#view-resume-preview-popup .modal-body').html(data);
                        var _images = jQuery('#view-resume-preview-popup .modal-body img');
                        _images.filter(':gt(0)').hide()
                        var _footer = jQuery('#view-resume-preview-popup .modal-footer');
                        _footer.html('').css('text-align','center');
                        for(i=0;i<_images.length;i++){
                          _footer.append('<a data-id="'+i+'" class="btn btn-danger btn-small">'+(i+1)+'</a>')
                        }
                        $('a:first',_footer).addClass('active');
                        $('a',_footer).click(function(){
                          $('a',_footer).removeClass('active')
                          $(this).addClass('active')
                          jQuery('#view-resume-preview-popup .modal-body img').hide();
                          $('#view-resume-preview-popup .modal-body img:eq('+$(this).data('id')+')').show();
                        });
                        jQuery('#view-resume-preview-popup').modal('show');
                        $btn.find('i').remove();
                      })
                      return false;
                    },
                    previewPDFblocker: function(e){
                      e.preventDefault();
                      e.stopPropagation();
                    },
                    editZitem: function(e) {
                        $(e.currentTarget).next().focus();
                    }
                });

                var zresume = new Zresume();
            });
        }
    };
})(jQuery);