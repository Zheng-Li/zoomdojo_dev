(function($){
    Drupal.behaviors.zoomdojo_zportfolio = {
        attach : function(context, settings) {
            $(document).ready(function(){
                var oldname = '';

                var ZMyResumes = Backbone.View.extend({
                    el: $('#z-my-resumes'),
                    datetime: null,
                    initialize: function() {

                    },
                    events: {
                        'click .z-delete-resume': 'deleteResume',
                        'click .z-edit-resume': 'editResume',
                        'click .btn-z-cancel': 'cancelResumeEdit',
                        'click .btn-z-save': 'saveResumeEdit'
                    },
                    deleteResume: function(e) {
                        if (confirm('Are you sure you want to delete this résumé?')) {
                            var rid = $(e.currentTarget).parent().data('rid');
                            var url = '/z-delete-resume';
                            $.post(url, {rid: rid}, function(data){
                                if (data != null) {
                                    var resp = JSON.parse(data);
                                    if (resp.status == 'OK') {
                                        window.location.reload();
                                    } else {
                                        App.showMessage(resp.data);
                                    }
                                }
                            });
                        }
                    },
                    editResume: function(e) {
                        var rid = $(e.currentTarget).parent().data('rid');
                        this.changeResumeMode(true, rid, false);
                    },
                    saveResumeEdit: function(e) {
                        var selfObject = this;
                        var rid = $(e.currentTarget).data('rid');
                        var name = App.trim($('#z-edit-name-' + rid).val());
                        var note = App.trim($('#z-edit-note-' + rid).val());

                        var myResumes = Drupal.settings.zportfolio.myResumes || [];
                        myResumes = JSON.parse(myResumes);
                        var isDuplicate = false;
                        _.each(myResumes, function(rname){
                            if (rname.toUpperCase() == name.toUpperCase() && rname.toUpperCase() != oldname.toUpperCase()) {
                                isDuplicate = true;
                            }
                        });
                        var msg = 'You have duplicate resume name. ';
                        if (isDuplicate) {
                            if (jQuery.browser.version == 8.0) {
                                alert(msg);
                            } else {
                                App.showMessage(msg);
                            }
                            return false;
                        }

                        var url = '/z-edit-resume';
                        $.post(url, {rid: rid, name: name, note: note}, function(data){
                            if (data != null) {
                                var resp = JSON.parse(data);
                                if (resp.status == 'OK') {
                                    selfObject.datetime = resp.data;
                                    selfObject.changeResumeMode(false, rid, false);
                                } else {
                                    App.showMessage(resp.data);
                                }
                            }
                        });
                    },
                    cancelResumeEdit: function(e) {
                        var rid = $(e.currentTarget).data('rid');
                        this.changeResumeMode(false, rid, true);
                    },
                    changeResumeMode: function(editMode, rid, cancel) {
                        var emptyNote = 'No notes';
                        if (editMode) {
                            $('#z-edit-name-' + rid).val(App.trim($('#z-view-name-' + rid).text()));
                            oldname = App.trim($('#z-view-name-' + rid).text());
                            var note = App.trim($('#z-view-note-' + rid).text());
                            if (note != emptyNote)
                                $('#z-edit-note-' + rid).val(note);
                            $('#z-view-name-' + rid).hide();
                            $('.z-view-time-' + rid).hide();
                            $('#z-view-note-' + rid).hide();
                            $('#z-edit-name-' + rid).show();
                            $('#z-edit-note-' + rid).show();
                            $('#z-edit-btn-save-' + rid).show();
                            $('#z-edit-btn-cancel-' + rid).show();
                            $('#z-view-note-' + rid).parent().parent().addClass('in').css('height', 'auto');
                        } else {
                            if (!cancel) {
                                $('#z-view-name-' + rid).text($('#z-edit-name-' + rid).val());
                                var note = App.trim($('#z-edit-note-' + rid).val());
                                if (note == '')
                                    note = emptyNote;
                                $('#z-view-note-' + rid).text(note);
                            }
                            $('#z-view-updated-'+rid).text(this.datetime).prev().text(' / ');
                            $('#z-view-name-' + rid).show();
                            $('.z-view-time-' + rid).show();
                            $('#z-view-note-' + rid).show();
                            $('#z-edit-name-' + rid).hide();
                            $('#z-edit-note-' + rid).hide();
                            $('#z-edit-btn-save-' + rid).hide();
                            $('#z-edit-btn-cancel-' + rid).hide();
                        }
                    }
                });

                var zmyresumes = new ZMyResumes();
            });
        }
    };
})(jQuery);