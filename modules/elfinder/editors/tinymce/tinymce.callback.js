var elfinder_tinymce_callback = function(url) {
 window.opener.tinymceFileWin.document.forms[0].elements[window.opener.tinymceFileField].value = url;
 window.opener.tinymceFileWin.focus();
 window.close();
}