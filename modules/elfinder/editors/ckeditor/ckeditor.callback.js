// $Id$

function elfinder_ckeditor_callback(url) {
          funcNum = window.location.search.replace(/^.*CKEditorFuncNum=(\d+).*$/, "$1");
          window.opener.CKEDITOR.tools.callFunction(funcNum, url);
          window.close();
}