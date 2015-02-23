(function($){
    Drupal.behaviors.zoomdojo_zportfolio = {
        attach : function(context, settings) {
            $(document).ready(function(){

                var not = [
                    '#z-portfolio-form a',
                    '.accordion-heading a',
                    '#secondary-menu a.greetings',
                    '.navbar-inner button',
                    '#findJobsPopup .modal-footer a',
                    '#findJobsPopup .close',
                    '#btn-footer-sing-up',
                    '.modal-header .close',
                    '#view-message-popup .modal-footer a',
                    '#add-section-popup a',
                    '#add-section-popup .close',
                    '.zportfolio-submit'
                ];
                var isPortfolioModify = false;

                $('a, button, input[type=submit]').not(not.join()).click(function(e){
                    if (isPortfolioModify) {
                        if (!confirm('Are you sure you want to leave this page without saving?')){
                            return false;
                        }
                    }
                });
                $(document).on('keypress', '#z-portfolio-form input[type=text], #z-portfolio-form textarea, #add-section-popup input[type=text]', function(){
                    isPortfolioModify = true;
                });
                $(document).on('change', '#z-portfolio-form input[type=checkbox], #z-portfolio-form select', function(){
                    isPortfolioModify = true;
                });

                var Zportfolio = Backbone.View.extend({
                    el: $('#z-portfolio-control'),
                    parsley: $('#z-portfolio-form'),
                    initialize: function() {
                        this.parsley.parsley();
                    },
                    events: {
                        'click #add-new-education-row': 'addNewEducation',
                        'click #add-new-education-row-top': 'addNewEducationTop',
                        'click .remove-education': 'removeEducation',
                        'click .add-coursework': 'addNewEducationCoursework',
                        'click .remove-education-coursework': 'removeEducationCoursework',
                        'click #add-new-experience-row': 'addNewExperience',
                        'click #add-new-experience-row-top': 'addNewExperienceTop',
                        'click .remove-experience': 'removeExperience',
                        'click .add-responsibility': 'addNewExperienceResponsibility',
                        'click .remove-experience-responsibility': 'removeExperienceResponsibility',
                        'click #add-new-volunteer-row': 'addNewVolunteer',
                        'click #add-new-volunteer-row-top': 'addNewVolunteerTop',
                        'click .remove-volunteer': 'removeVolunteer',
                        'click .add-volunteer-responsibility': 'addNewVolunteerResponsibility',
                        'click .remove-volunteer-responsibility': 'removeVolunteerResponsibility',
                        'change .on-off-date': 'onOffDate',
                        'change .on-off-date-single': 'onOffSingleDate',
                        'click #add-new-leadership-row': 'addNewLeadership',
                        'click #add-new-leadership-row-top': 'addNewLeadershipTop',
                        'click .remove-leadership': 'removeLeadership',
                        'click .add-leadership-responsibility': 'addNewLeadershipResponsibility',
                        'click .remove-leadership-responsibility': 'removeLeadershipResponsibility',
                        'click #add-new-custom-section':'addNewCustomSectionPopup',
                        'click #add-section-popup-submit':'createNewCustomSection',
                        'click .custom-rename':'renameCustomSectionPopup',
                        'click .custom-delete':'deleteCustomSection',
                        'click .add-custom': 'addNewCustomItem',
                        'click .add-custom-top': 'addNewCustomItemTop',
                        'change .date-type-select': 'changeDateTypeForCustomItem',
                        'click .remove-custom-item': 'removeCustomItem',
                        'click .add-skills': 'addNewSkills',
                        'click .remove-skills-other': 'removeSkillOther',
                        'click #add-new-language-row': 'addNewSkillLanguage',
                        'click .remove-skills-language': 'removeSkillLanguage',
                        'change .zp-language-select': 'changeLanguage',
                        'click .zportfolio-submit': 'submit',
                        'click #zportfolio-clear-form': 'clearForm',
                        'click .z-get-hint': 'getHint',
                        'click #z-portfolio-control-group>.accordion-group>.accordion-heading':'showTipsSection',
                        'click .prior-reduce':'priorReduce',
                        'click .prior-add':'priorAdd',
                        'click .create-resume-btn': 'createResume'
                    },
                    createResume: function() {
                        if (!confirm('Have you saved all the data in your Z-Portfolio? \n If not, click Cancel and then save your data. \n  Click OK if you have already saved your data.')){
                            return false;
                        }
                    },
                    deleteElement: function(replace, type, value) {
                        $(replace).replaceWith($('<input/>', {
                              'type':  'hidden',
                              'name':  type + '[delete][]',
                              'value': value
                        }));
                    },
                    getHtmlTemplate: function(elemId, index) {
                        return _.template($('#'+ elemId).html(), {index:index});
                    },
                    addSkillFieldsValidate: function(elem, selectClass) {
                        var selfObject = this;
                        elem.parent().parent().parent().parent().parent().parent().find('.insert-item ' + selectClass + ' *[required]').each(function(){
                            selfObject.parsley.parsley( 'addItem', $(this) );
                        });
                    },
                    addFieldsValidate: function(elem, selectClass) {
                        var selfObject = this;
                        elem.parent().parent().parent().find(selectClass + ' *[required]').each(function(){
                            selfObject.parsley.parsley( 'addItem', $(this) );
                        });
                    },
                    removeFialdsValidate: function(elem) {
                        var selfObject = this;
                        elem.find('*[required]').each(function(){
                            selfObject.parsley.parsley( 'removeItem', $(this) );
                        });
                    },
                    checkItemCount: function(el, btn){
                        if ($('#'+el +' .'+el).size() == 0) {
                            $('#'+btn).hide();
                            $('#'+el + ' .top-save-btn-section').hide();
                        } else {
                            $('#'+btn).show();
                            $('#'+el + ' .top-save-btn-section').show();
                        }
                    },
                    checkCustomItemCount: function(elId, elClass, btn, isNew){
                        if ($(elClass).size() == 0) {
                            $('#'+btn).hide();
                            $(elId + ' .top-save-btn-section').hide();
                        } else {
                            $('#'+btn).show();
                            $(elId + ' .top-save-btn-section').show();
                        }
                    },
                    addNewEducation: function(e) {
                        var index = $('#z-portfolio-control .education').size() + 1;
                        var html = this.getHtmlTemplate('education-js-template', index);
                        $(e.currentTarget).parent().parent().before(html);
                        this.addFieldsValidate($(e.currentTarget), '.new-education-'+index);
                        this.checkItemCount('education', 'add-new-education-row-top');
                    },
                    addNewEducationTop: function() {
                        $('#add-new-education-row').click();
                    },
                    removeEducation: function(e) {
                        if (confirm('Do you really want to delete this?')) {
                            this.removeEducationScript(e);
                        }
                    },
                    removeEducationScript: function(e) {
                        var education = $(e.currentTarget).parent().parent();
                        if (education.hasClass('new-education')) {
                            this.removeFialdsValidate(education);
                            education.remove();
                        } else {
                            this.deleteElement(education, 'education', education.data('eid'));
                        }
                        this.checkItemCount('education', 'add-new-education-row-top');
                    },
                    addNewEducationCoursework: function(e){
                        var eid = $(e.currentTarget).data('eid');
                        var rid = $('#z-portfolio-control .education-coursework-' + eid).size() + 1;
                        var isNew = false;
                        if ($('#z-portfolio-control .education-' + eid).hasClass('new-education')) {
                            isNew = true;
                        }
                        console.info(eid,rid,isNew);
                        var html = _.template($('#education-small-js-template').html(), {eid:eid, rid:rid, isNew:isNew});
                        $(e.currentTarget).parent().parent().before(html);
                        console.info(html);
                        this.addFieldsValidate($(e.currentTarget), '.education-'+eid+'-coursework-'+rid);
                    },
                    removeEducationCoursework: function(e) {
                        var responsibility = $(e.currentTarget).parent().parent();
                        var eid = responsibility.data('eid');
                        if (responsibility.hasClass('education-coursework-new')) {
                            this.removeFialdsValidate(responsibility);
                            responsibility.remove();
                        } else {
                            responsibility.replaceWith($('<input/>', {
                                'type':  'hidden',
                                'name':  'education['+eid+'][coursework][delete][]',
                                'value': responsibility.data('rid')
                            }));
                        }
                    },
                    addNewExperience: function(e) {
                        var index = $('#z-portfolio-control .experience').size() + 1;
                        var html = this.getHtmlTemplate('experience-js-template', index);
                        $(e.currentTarget).parent().parent().before(html);
                        this.addFieldsValidate($(e.currentTarget), '.new-experience-'+index);
                        this.checkItemCount('experience', 'add-new-experience-row-top');
                    },
                    addNewExperienceTop: function() {
                        $('#add-new-experience-row').click();
                    },
                    removeExperience: function(e) {
                        if (confirm('Do you really want to delete this?')) {
                            this.removeExperienceScript(e);
                        }
                    },
                    removeExperienceScript: function(e) {
                        var experience = $(e.currentTarget).parent().parent();
                        if (experience.hasClass('new-experience')) {
                            this.removeFialdsValidate(experience);
                            experience.remove();
                        } else {
                            this.deleteElement(experience, 'experience', experience.data('eid'));
                        }
                        this.checkItemCount('experience', 'add-new-experience-row-top');
                    },
                    addNewExperienceResponsibility: function(e) {
                        var eid = $(e.currentTarget).data('eid');
                        var rid = $('#z-portfolio-control .experience-responsibility-' + eid).size() + 1;
                        var isNew = false;
                        if ($('#z-portfolio-control .experience-' + eid).hasClass('new-experience')) {
                            isNew = true;
                        }
                        var html = _.template($('#experience-small-js-template').html(), {eid:eid, rid:rid, isNew:isNew});
                        $(e.currentTarget).parent().parent().before(html);
                        this.addFieldsValidate($(e.currentTarget), '.experience-'+eid+'-responsibility-'+rid);
                    },
                    removeExperienceResponsibility: function(e) {
                        var responsibility = $(e.currentTarget).parent().parent();
                        var eid = responsibility.data('eid');
                        if (responsibility.hasClass('experience-responsibility-new')) {
                            this.removeFialdsValidate(responsibility);
                            responsibility.remove();
                        } else {
                            responsibility.replaceWith($('<input/>', {
                                'type':  'hidden',
                                'name':  'experience['+eid+'][responsibility][delete][]',
                                'value': responsibility.data('rid')
                            }));
                        }
                    },
                    addNewVolunteer: function(e) {
                        var index = $('#z-portfolio-control .volunteer').size() + 1;
                        var html = this.getHtmlTemplate('volunteer-js-template', index);
                        $(e.currentTarget).parent().parent().before(html);
                        this.addFieldsValidate($(e.currentTarget), '.new-volunteer-'+index);
                        this.checkItemCount('volunteer', 'add-new-volunteer-row-top');
                    },
                    addNewVolunteerTop: function() {
                        $('#add-new-volunteer-row').click();
                    },
                    removeVolunteer: function(e) {
                        if (confirm('Do you really want to delete this?')) {
                            this.removeVolunteerScript(e);
                        }
                    },
                    removeVolunteerScript: function(e) {
                        var volunteer = $(e.currentTarget).parent().parent();
                        if (volunteer.hasClass('new-volunteer')) {
                            this.removeFialdsValidate(volunteer);
                            volunteer.remove();
                        } else {
                            this.deleteElement(volunteer, 'volunteer', volunteer.data('eid'));
                        }
                        this.checkItemCount('volunteer', 'add-new-volunteer-row-top');
                    },
                    onOffDate: function(e) {
                        var selfObject = this;
                        var row = $(e.currentTarget).parent().parent();
                        if ($(e.currentTarget).is(':checked')) {
                            selfObject.setSelectNull(row.find('.end-year'));
                            selfObject.setSelectNull(row.find('.end-mounth'));
                            row.find('.date-block').hide();
                            row.find('.date-block-text').show();
                        } else {
                            selfObject.removeSelectNull(row.find('.end-year'));
                            selfObject.removeSelectNull(row.find('.end-mounth'));
                            row.find('.date-block-text').hide();
                            row.find('.date-block').show();
                        }
                    },
                    onOffSingleDate: function(e) {
                        var selfObject = this;
                        var row = $(e.currentTarget).parent().parent();
                        if ($(e.currentTarget).is(':checked')) {
                            $(e.currentTarget).next().val(1);
                            row.find('.date-block').hide();
                        } else {
                            $(e.currentTarget).next().val(0);
                            row.find('.date-block').show();
                        }
                    },
                    setSelectNull: function(elem) {
                        elem.append($('<option/>', {
                            'text':  '0',
                            'value': '0'
                        }));
                        elem.find('option')
                            .removeAttr('selected')
                            .filter('[value=0]')
                            .attr('selected', true);
                    },
                    removeSelectNull: function(elem) {
                        elem.find('option')
                            .removeAttr('selected')
                            //.filter('[value=0]')
                            .last()
                            .remove();
                    },
                    addNewLeadership: function(e) {
                        var index = $('#z-portfolio-control .leadership').size() + 1;
                        var html = this.getHtmlTemplate('leadership-js-template', index);
                        $(e.currentTarget).parent().parent().before(html);
                        this.addFieldsValidate($(e.currentTarget), '.new-leadership-'+index);
                        this.checkItemCount('leadership', 'add-new-leadership-row-top');
                    },
                    addNewLeadershipTop: function() {
                        $('#add-new-leadership-row').click();
                    },
                    removeLeadership: function(e) {
                        if (confirm('Do you really want to delete this?')) {
                            this.removeLeadershipScript(e);
                        }
                    },
                    removeLeadershipScript: function(e) {
                        var leadership = $(e.currentTarget).parent().parent();
                        if (leadership.hasClass('new-leadership')) {
                            this.removeFialdsValidate(leadership);
                            leadership.remove();
                        } else {
                            this.deleteElement(leadership, 'leadership', leadership.data('eid'));
                        }
                        this.checkItemCount('leadership', 'add-new-leadership-row-top');
                    },
                    addNewLeadershipResponsibility: function(e) {
                        var eid = $(e.currentTarget).data('eid');
                        var rid = $('#z-portfolio-control .leadership-responsibility-' + eid).size() + 1;
                        var isNew = false;
                        if ($('#z-portfolio-control .leadership-' + eid).hasClass('new-leadership')) {
                            isNew = true;
                        }
                        var html = _.template($('#leadership-small-js-template').html(), {eid:eid, rid:rid, isNew:isNew});
                        $(e.currentTarget).parent().parent().before(html);
                        this.addFieldsValidate($(e.currentTarget), '.leadership-'+eid+'-responsibility-'+rid);
                    },
                    removeLeadershipResponsibility: function(e) {
                        var responsibility = $(e.currentTarget).parent().parent();
                        var eid = responsibility.data('eid');
                        if (responsibility.hasClass('leadership-responsibility-new')) {
                            this.removeFialdsValidate(responsibility);
                            responsibility.remove();
                        } else {
                            responsibility.replaceWith($('<input/>', {
                                'type':  'hidden',
                                'name':  'leadership['+eid+'][responsibility][delete][]',
                                'value': responsibility.data('rid')
                            }));
                        }
                    },
                    addNewVolunteerResponsibility: function(e) {
                        var eid = $(e.currentTarget).data('eid');
                        var rid = $('#z-portfolio-control .volunteer-responsibility-' + eid).size() + 1;
                        var isNew = false;
                        if ($('#z-portfolio-control .volunteer-' + eid).hasClass('new-volunteer')) {
                            isNew = true;
                        }
                        var html = _.template($('#volunteer-small-js-template').html(), {eid:eid, rid:rid, isNew:isNew});
                        $(e.currentTarget).parent().parent().before(html);
                        this.addFieldsValidate($(e.currentTarget), '.volunteer-'+eid+'-responsibility-'+rid);
                    },
                    removeVolunteerResponsibility: function(e) {
                        var responsibility = $(e.currentTarget).parent().parent();
                        var eid = responsibility.data('eid');
                        if (responsibility.hasClass('volunteer-responsibility-new')) {
                            this.removeFialdsValidate(responsibility);
                            responsibility.remove();
                        } else {
                            responsibility.replaceWith($('<input/>', {
                                'type':  'hidden',
                                'name':  'volunteer['+eid+'][responsibility][delete][]',
                                'value': responsibility.data('rid')
                            }));
                        }
                    },
                    addNewCustomSectionPopup: function(e){
                        $('#add-section-popup-title').val('');
                        $('#add-section-popup-submit').data('type','new');
                        jQuery('#add-section-popup').modal({
                          show:true,
                          keyboard: false
                        });
                        $('#add-section-popup-title').keyup(function(e){
                          if(e.keyCode == 13) {
                            e.preventDefault();
                            e.stopPropagation();
                            return false;
                          }
                        })
                        return false;
                    },
                    createNewCustomSection: function(e){
                      if($('#add-section-popup-title').val() == ''){
                        var _lbl = '';
                        if($('#add-section-popup-submit').data('type') == 'new'){
                          var _lbl = 'New ';
                        }
                        _lbl += 'Resume Name is empty!';
                        if (jQuery.browser.version == 8.0) {
                            alert(_lbl);
                        } else {
                            App.showMessage(_lbl);
                        }
                        $('#add-section-popup-title').addClass('error').keyup(function(e){
                          $(this).removeClass('error').next('ul').remove();
                        });
                        return;
                      }
                      if($('#add-section-popup-submit').data('type') == 'new'){
                        var html = _.template($('#custom-js-template').html(), {sid:$('.accordion-group-custom').length, title:$('#add-section-popup-title').val().toUpperCase()});
                        if($('.accordion-group-custom:last').length){
                          $('.accordion-group-custom:last').after(html);
                        }else{
                          $('.accordion-group:eq(4)').after(html);
                        }
                        // new sections alert
                        _lbl = 'New section added. Look above Skills & Interests.';
                        if (jQuery.browser.version == 8.0) {
                          alert(_lbl);
                        } else {
                          App.showMessage(_lbl);
                        }
                      }else{
                        var _target  = $('#add-section-popup-submit').data('rename');
                        _target.parent().next().text($('#add-section-popup-title').val().toUpperCase());
                        _target.parent().next().next().val($('#add-section-popup-title').val().toUpperCase());
                      }
                      
                      $('#add-section-popup-title').val('');
                      jQuery('#add-section-popup').modal('hide');
                    },
                    renameCustomSectionPopup: function(e){
                      e.stopPropagation();
                      $('#add-section-popup-title').val($(e.currentTarget).parent().next().text().trim());
                      $('#add-section-popup-submit')
                              .data('type','old')
                              .data('rename',$(e.currentTarget));
                      jQuery('#add-section-popup').modal('show');
                      
                      return false;
                    },
                    deleteCustomSection: function(e){
                      e.stopPropagation();
                      if (confirm('Are you sure you want to delete this section?')) {
                        this.deleteCustomSectionScript(e);
                      }
                    },
                    deleteCustomSectionScript: function(e) {
                        var _trashButton = $(e.currentTarget);
                        var _parent = _trashButton.parent().parent();
                        this.removeFialdsValidate($('.custom-item-'+_parent.parent().data('id')));
                        if(_parent.hasClass('new')){
                            _parent.parent().remove();
                        }else{
                            _parent.parent().replaceWith('<input type="hidden" name="custom[delete][]" value="'+_parent.parent().data('id')+'" />');
                        }
                    },
                    addNewCustomItem: function(e){
                        var sid = $(e.currentTarget).data('eid');
                        var iid = $('#z-portfolio-control .custom-item-' + sid).size() + 1;
                        var isNew = $(e.currentTarget).hasClass('new');
                        var html = _.template($('#custom-small-js-template').html(), {sid:sid, iid:iid, isNew:isNew});
                        $(e.currentTarget).parent().parent().before(html);
                        this.addFieldsValidate($(e.currentTarget), '.new-custom-item-'+sid+'-'+iid);
                        console.log($(e.currentTarget).parent().parent().parent().parent().parent());
                        if ($(e.currentTarget).parent().parent().parent().parent().parent().hasClass('new')) {
                            this.checkCustomItemCount('#custom-new-'+sid, '.custom-item-'+sid, 'add-custom-top-'+sid, true);
                        } else {
                            this.checkCustomItemCount('#custom-'+sid, '.custom-item-'+sid, 'add-custom-top-'+sid, false);
                        }
                    },
                    addNewCustomItemTop: function(e) {
                        var eid = $(e.currentTarget).data('eid');
                        $('#add-custom-'+eid).click();
                    },
                    changeDateTypeForCustomItem: function(e){
                      var _check = $(e.currentTarget);
                      var _type = _check.attr('checked');
                      var _present = _check.parent().parent().next().find('.on-off-date');
                      if(_type == 'checked'){
                        _check.closest('.sortable').find('.hide-type-1').addClass('hide');
                        _check.closest('.sortable').find('.hide-type-1 select').each(function(){
                          el = $(this)
                          console.log(el)
                          el.data('name',el.attr('name'))
                          el.removeAttr('name')
                        })
                        _check.closest('.sortable').find('.hide-type-0').removeClass('hide');
                        _check.closest('.sortable').find('.hide-type-0 select').each(function(){
                          el = $(this)
                          el.attr('name',el.data('name'))
                        })
                        _check.next().val(1);
                        if (_present.attr('checked') != 'checked') {
                          _present.click();
                        }
                        _check.parent().parent().next().find('div:gt(0):not(.hide-type-1,.hide-type-0)').addClass('hide');
                      }else{
                        _check.next().val(0);
                        _check.closest('.sortable').find('.hide-type-0').addClass('hide');
                        _check.closest('.sortable').find('.hide-type-0 select').each(function(){
                          el = $(this)
                          el.data('name',el.attr('name'))
                          el.removeAttr('name')
                        })
                        _check.closest('.sortable').find('.hide-type-1').removeClass('hide');
                        _check.closest('.sortable').find('.hide-type-1 select').each(function(){
                          el = $(this)
                          el.attr('name',el.data('name'))
                        })
                        
                        if (_present.attr('checked') == 'checked') {
                          _present.click();
                        }
                        _check.parent().parent().next().find('div:gt(0):not(.hide-type-1,.hide-type-0)').removeClass('hide');
                      }
                    },
                    removeCustomItem: function(e){
                        if (confirm('Do you really want to delete this?')) {
                            this.removeCustomItemScript(e);
                        }
                    },
                    removeCustomItemScript: function(e){
                        var trashButton = $(e.currentTarget);
                        var itemBlock = trashButton.parent().parent();
                        var isNew = $(e.currentTarget).parent().parent().parent().parent().parent().hasClass('new');
                        this.removeFialdsValidate(itemBlock);
                        if (trashButton.hasClass('new')) {
                            itemBlock.remove();
                        } else {
                            itemBlock.replaceWith($('<input/>', {
                                'type':  'hidden',
                                'name':  'custom['+trashButton.data('sid')+'][items][delete][]',
                                'value': trashButton.data('iid')
                            }));
                        }
                        var sid = $(e.currentTarget).data('sid');
                        if (isNew) {
                            this.checkCustomItemCount('#custom-new-'+sid, '.custom-item-'+sid, 'add-custom-top-'+sid);
                        } else {
                            this.checkCustomItemCount('#custom-'+sid, '.custom-item-'+sid, 'add-custom-top-'+sid);
                        }
                    },
                    addNewSkills: function(e) {
                        var skillType = $(e.currentTarget).data('eid');
                        var index = $('#z-portfolio-control .skill-type-' + skillType).size() + 1;
                        var html = _.template($('#skill-js-template').html(), {index: index, type: skillType});
                        $(e.currentTarget).parent().parent().parent().parent().parent().parent().find('.insert-item').append(html);
                        this.addSkillFieldsValidate($(e.currentTarget), '.new-skill-other-'+index);
                    },
                    removeSkillOther: function(e) {
                        var eid = $(e.currentTarget).data('eid');
                        var skillOther = $(e.currentTarget).parent();
                        if (skillOther.hasClass('new-skill-other')) {
                            this.removeFialdsValidate(skillOther);
                            skillOther.remove();
                        } else {
                            this.deleteElement(skillOther, 'skills', eid);
                        }
                    },
                    addNewSkillLanguage: function(e) {
                        var index = $('#z-portfolio-control .skill-language').size() + 1;
                        var html = this.getHtmlTemplate('language-js-template', index);
                        $(e.currentTarget).parent().parent().parent().parent().parent().parent().find('.insert-item').append(html);
                    },
                    removeSkillLanguage: function(e) {
                        var skillOther = $(e.currentTarget).parent().parent().parent();
                        if (skillOther.hasClass('new-skill-language')) {
                            skillOther.remove();
                        } else {
                            this.deleteElement(skillOther, 'skills', skillOther.data('eid'));
                        }
                    },
                    changeLanguage: function(e) {
                        var otherValue = 6;
                        var eid = $(e.currentTarget).data('eid');
                        if ($(e.currentTarget).val() == otherValue) {
                            $(e.currentTarget).parent().find('#other-language-'+eid).attr('disabled', false).show();
                        } else {
                            $(e.currentTarget).parent().find('#other-language-'+eid).attr('disabled', true).hide();
                        }
                    },
                    validate: function() {
                        return this.parsley.parsley('validate');
                    },
                    submit: function() {
                        if (!this.validate()) {
                            $('.accordion-body').removeClass('in').css('height', '0');
                            $('.accordion-body').prev().find('a:not(.custom-delete,.custom-rename)').addClass('collapsed');
                            $('.parsley-error-list').parents('.accordion-body').addClass('in').css('height', 'auto');
                            $('.parsley-error-list').parents('.accordion-body').prev().find('a:not(.custom-delete,.custom-rename)').removeClass('collapsed');
                            var rhs = $('#zportfolio-tips .accordion-group').filter(function(){
                                return !$(this).hasClass('hidden');
                            }).last();
                            rhs.find('.accordion-heading a').removeClass('collapsed');
                            rhs.find('.accordion-body').addClass('in').css('height', 'auto');
                            return false;
                        }
                        return true;
                    },
                    clearForm: function(e) {
                        var selfObject = this;
                        if (confirm('Are you sure you want to clear all the information in your Z-Portfolio?')) {
                            $('#z-name').val('');
                            $('#z-phone').val('');
                            $('#z-email').val('');
                            $('#z-address').val('');
                            $('#z-other').val('');
                            $('#education .remove-education').each(function(){
                                var e = {currentTarget:$(this)[0]};
                                selfObject.removeEducationScript(e);
                            });
                            $('#experience .remove-experience').each(function(){
                                var e = {currentTarget:$(this)[0]};
                                selfObject.removeExperienceScript(e);
                            });
                            $('#leadership .remove-leadership').each(function(){
                                var e = {currentTarget:$(this)[0]};
                                selfObject.removeLeadershipScript(e);
                            });
                            $('#volunteer .remove-volunteer').each(function(){
                                var e = {currentTarget:$(this)[0]};
                                selfObject.removeVolunteerScript(e);
                            });
                            $('.custom-delete').each(function(){
                                var e = {currentTarget:$(this)[0]};
                                selfObject.deleteCustomSectionScript(e);
                            });
                            $('#others .remove-skills-language').each(function(){
                                $(this).click();
                            });
                            $('#others .remove-skills-other').each(function(){
                                $(this).click();
                            });
                        }
                        return false;
                    },
                    getHint: function (e) {
                        jQuery('#z-portfolio-hint-popup').modal('show');
                        return false;
                    },
                    showTipsSection: function(e){
                      // scroll to opened tab
                      var el = $(e.currentTarget);
                      if (!el.next().hasClass('in')) {
                        setTimeout(function() {
                          jQuery.scrollTo( el.parent(), 800, {offset:-180});
                        }, 800);
                      }

                      $('#zportfolio-tips>.accordion-group:not(.section-0)').addClass('hidden');
                      var _that = $(e.currentTarget).parent();
                      if(_that.data('type')!=0 || (_that.data('type')==0 && !$('#zportfolio-tips>.accordion-group.section-0').find('.accordion-heading>a:not(.custom-delete,.custom-rename)').hasClass('collapse'))){
                        $('#zportfolio-tips>.accordion-group.section-0').find('.accordion-body').css('height','0').removeClass('in');
                        $('#zportfolio-tips>.accordion-group.section-0').find('.accordion-heading>a:not(.custom-delete,.custom-rename)').addClass('collapsed');
                      }else{
                        $('#zportfolio-tips>.accordion-group.section-0').find('.accordion-body').css('height','auto').addClass('in');
                        $('#zportfolio-tips>.accordion-group.section-0').find('.accordion-heading>a:not(.custom-delete,.custom-rename)').removeClass('collapsed');
                      }

                      if(!$('>.accordion-body',_that).height()){
                        var _header = $('#zportfolio-tips>.section-'+_that.data('type')).removeClass('hidden');
                        _header.find('.accordion-body').css('height','auto').addClass('in');
                        _header.find('.accordion-heading>a:not(.custom-delete,.custom-rename)').removeClass('collapsed');
                      }
                    },
                    priorReduce : function(e){
                      isPortfolioModify =true;
                      this.priorMod(e,false);
                    },
                    priorAdd: function(e){
                      isPortfolioModify =true;
                      this.priorMod(e,true);
                    },
                    priorMod: function(e,_direction){
                      var _row = $(e.currentTarget).closest('.sortable');
                      if(_direction){
                        _row.insertAfter(_row.nextAll('.sortable:first'))
                      }else{
                        _row.insertBefore(_row.prevAll('.sortable:first'))
                      }
                    }
                });

                var zportfolio = new Zportfolio();
            });
            jQuery("#zportfolio-tips .tip-url").click(function(event) {
              jQuery('.modal.tip-'+$(event.currentTarget).data('url')).modal('show');
            });
            jQuery('.autowraps').each(function(){
              var lines = jQuery.countLines(this,{recalculateCharWidth:true});
              var curRows = $(this).attr('rows');
              $(this).attr('rows',curRows>lines.visual?curRows:lines.visual)
            })
        }
    };
    
})(jQuery);