// global object
function MainApp() {
    return this;
} 
MainApp.prototype.singInPopup = function() { 
    jQuery('.modal').modal('hide');
    jQuery('#sing-in-popup').modal('show');
    trackAjaxRequest("Sign In", "/user/login");
    return false;
}
MainApp.prototype.singUpPopup = function() {
    jQuery('.modal').modal('hide');
    jQuery('#sing-up-popup').modal('show');
    trackAjaxRequest("Sign Up", "/user/register");
    return false;
}
MainApp.prototype.forgotPassPopup = function() {
    jQuery('.modal').modal('hide');
    jQuery('#sing-forgon-pass-popup').modal('show');
    trackAjaxRequest("Forgot your password?", "/user/password");
    return false;
}
MainApp.prototype.sharePageForEmailPopup = function() {
    jQuery('.modal').modal('hide');
    jQuery('#share-for-email-popup').modal('show');
    trackAjaxRequest("Get Our Latest Updates", "/#get-our-latest-updates");
    return false;
}
MainApp.prototype.showMessage = function(message) {
    jQuery('#view-message-popup .info-text-msg').html(message);
    jQuery('#view-message-popup').modal();
}
MainApp.prototype.trim = function(text) {
    if(typeof String.prototype.trim !== 'function') {
        return text.replace(/^\s+|\s+$/g, '');
    } else {
        return jQuery.trim(text);
    }
}

var App = new MainApp();

function findJobsPopup() {
    jQuery('#findJobsPopup').modal();
    trackAjaxRequest("Search for jobs (Modal)", "/find-jobs");
    return void(0);
}

function findNewJobsPopup() {
    jQuery('#findNewJobsPopup').modal();
    trackAjaxRequest("Search for jobs (Modal)", "/find-jobs");
    return void(0);
}

function trackAjaxRequest(title, url) {
    // Google analytics
    if (typeof ga != "undefined") {
        ga('send', 'pageview', {'page': url,'title': title});
    }
    // Piwik analytics
    if (typeof _gaq != "undefined") {
        _paq.push(["setCustomUrl", "http://" + document.domain + url]);
        _paq.push(['trackPageView', title]);
    }
    return false;
}

(function($) {
    var methods = {
        init : function( options ) {
            return this.each(function(){
                $(this).on( "click", $(this), methods.viewSharewindow);
            });
        },
        viewSharewindow: function(e) {
            var title = $(this).data('title');
            var url   = $(this).attr('href');
            var desc  = $(this).data('desc');
            var img   = $(this).data('img');

            if (!$(this).attr('disabled')) {
                var html = methods.getWindow(url, title, desc, img);
                $(this).parent('.share-view').append(html);
                $(this).attr('disabled', true);
                $(this).parent().find('.social-share-window a').bind('click', methods.clickOnIcon);
                $(this).parent().find('.social-share-window a.close-w').bind('click', methods.closeWindow);
                $(this).parent().find('.social-share-window a.icn-share-email').bind('click', methods.shareForEmail);
            }
            return false;
        },
        getFacebookUrl: function(url, title, desc, img) {
            var pageUrl = 'http://www.facebook.com/sharer.php?s=100'
                + '&p[url]='+encodeURIComponent(url)
                + '&p[images][0]=' + encodeURIComponent(img)
                + '&p[title]=' + title
                + '&p[summary]=' + desc;
            return pageUrl;
        },
        getTwiterUrl: function(url, title, desc, img) {
            url = url.replace(/\s/gi, '%20');
            encodeUrl  = encodeURIComponent(url);
            if (desc.length > 110) {
                encodeDesc = encodeURIComponent(desc.substring(0, 110) + ' ...');
            } else {
                encodeDesc = encodeURIComponent(desc);
            }
            var pageUrl = 'https://twitter.com/intent/tweet'
                + '?url=' + encodeUrl
                + '&text=' + encodeDesc;
            return pageUrl;
        },
        getGPlusUrl: function(url, title, desc, img) {
            var pageUrl = 'https://plus.google.com/share'
                + '?url='+encodeURIComponent(url);
            return pageUrl;
        },
        getPitItUrl: function(url, title, desc, img) {
            var pageUrl = 'http://pinterest.com/pin/create/button/'
                + '?url='+encodeURIComponent(url)
                + '&media=' + encodeURIComponent(img)
                + '&description=' + desc;
            return pageUrl;
        },
        getEmailUrl: function(url, title, desc, img) {
            $('#organization-manager-shareemailform .messages').remove();
            desc += '\n\n Share Page: '+url.replace(' ', '+');
            $('#zd-share-massage').val(desc);
            return '#';
        },
        getIcon: function(url, type, cl, title){
            return '<a href="'+url+'" class="'+cl+'" title="'+title+'">'
                        +'<img src="'+this.getIconSrc(type)+'" width="25px" height="25px" />'
                    +'</a>';
        },
        getIconSrc: function(type) {
            switch (type) {
                case 'fb':
                    return '/sites/all/themes/zoomdojo/img/icon/fb.jpg';
                    break;
                case 'tw':
                    return '/sites/all/themes/zoomdojo/img/icon/tw.png';
                    break;
                case 'gp':
                    return '/sites/all/themes/zoomdojo/img/icon/gp.jpg';
                    break;
                case 'pi':
                    return '/sites/all/themes/zoomdojo/img/icon/pi.png';
                    break;
                case 'ml':
                    return '/sites/all/themes/zoomdojo/img/icon/ml.jpg';
                    break;
                default:
                    return '/sites/all/themes/zoomdojo/img/icon/close.png';
            }
        },
        getWindow: function(url, title, desc, img) {
            var html = '<div class="social-share-window">';
            html += this.getIcon(this.getFacebookUrl(url, title, desc, img), 'fb', '', 'Share via Facebook');
            html += this.getIcon(this.getTwiterUrl(url, title, desc, img), 'tw', '', 'Share via Twitter');
            html += this.getIcon(this.getGPlusUrl(url, title, desc, img), 'gp', '', 'Share via Google Plus');
            html += this.getIcon('#', 'ml', 'icn-share-email', 'Share via Email');
            html += this.getIcon(this.getPitItUrl(url, title, desc, img), 'pi', '', 'Share via Pinterest');
            html += this.getIcon(this.getEmailUrl(url, title, desc, img), 'close', 'close-w', 'close');
            html += '</div>';
            return html;
        },
        clickOnIcon: function(e) {
            var href = $(e.currentTarget).attr('href');
            if (href != '#') {
                window.open(href, '', 'toolbar=no ,location=0,status=no,titlebar=no,menubar=no,width=500,height=300');
            }
            return false;
        },
        closeWindow: function(e) {
            $(e.currentTarget).parent().parent().find('.btn-share').attr('disabled', false);
            $(e.currentTarget).parent().remove();
            return false;
        },
        shareForEmail: function() {
            App.sharePageForEmailPopup();
            return false;
        }
    };

    $.fn.share = function(method) {
        if ( methods[method] ) {
            return methods[method].apply( this, Array.prototype.slice.call( arguments, 1 ));
        } else if ( typeof method === 'object' || ! method ) {
            return methods.init.apply( this, arguments );
        } else {
            $.error('No method ' +  method + ' ! ');
        }
    };
})(jQuery);


jQuery(document).ready(function($) {
    
    // Search Form validation -- [[
    $('#findJobsForm, #findNewJobsForm').submit(function(){
        if($(this).find('input[name=company_name]').length > 0 && $(this).find('input[name=company_name]').val() != ""){
            $(this).find('select').val('');
            $(this).find('select, input').filter(function() { return $(this).val() == ""; }).attr('disabled','disabled');
            return true;
        }

        if($(this).find('.check-choose').filter(function() { return $(this).val() != ""; }).length < 1){
            var msg = ($(this).find('input[name=company_name]').length > 0)?'Please fill in two or more fields!':'Please fill in both fields and click Go to find jobs';
            if (jQuery.browser.version == 8.0) {
                alert(msg);
            } else {
                ShowAlert(msg);
            }
            return false;
        }
        $(this).find('select, input').filter(function() { return $(this).val() == ""; }).attr('disabled','disabled');
    });
    // ]] --

    $('#findJobsForm input[name=company_name], #findNewJobsForm input[name=company_name]').on('change', function(e){
        $(e.currentTarget).parents('form').find('select').val('');
    });
    $('#findJobsForm select, #findNewJobsForm select').on('change', function(e){
        $(e.currentTarget).parents('form').find('input[name=company_name]').val('');
    });

    // open external links on new tab
    $('a').not('a.zd-url').click(function(e){
        if ($(this)[0].hostname && $(this)[0].hostname !== location.hostname) {
            window.open($(this).attr('href'), '_blank');
            return false;
        }
    });


    // Login form popup
    $('.menu-680 a').on('click', function(){
        App.singInPopup();
        return false;
    });

    // Registration form popup
    $('.menu-681 a').on('click', function(){
        App.singUpPopup();
        return false;
    });

    $('.share-view .btn-share').share();

});

function ShowAlert(msg, title) {
    var title = title ? title : 'Error';
    jQuery('<div id="errorAlert" class="modal hide fade"><div class="modal-header"><button type="button" class="close" data-dismiss="modal" aria-hidden="true">×</button><h3 id="myModalLabel">' + title + '</h3></div><div class="modal-body"><p>' + msg + '</p></div></div>').modal()
    .on('hidden', function() {
        jQuery('#errorAlert').remove();
    });
}

window.onload = function() {

    var i,L=document.images.length;
    for(i=0;i<L;++i){

        var width =document.images[i].clientWidth;
        var height=document.images[i].clientHeight;

        document.images[i].setAttribute('height', height);
        document.images[i].setAttribute('width', width);

    }
};
