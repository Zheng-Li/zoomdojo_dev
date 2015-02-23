<?php foreach ($educations as $eid => $education): ?>
    <?php
        if(!empty($error['new']) && isset($education['new'])) {
            $error = $error['new'];
        }
        $datePresent = false;
        if (empty($education['end_mounth']) && empty($education['end_year'])) {
            $datePresent = true;
        }
    ?>
    <div class="row-fluid sortable <?php print isset($education['new'])?'new-education new-education-'.$eid:'sortable'; ?> education education-<?php print $eid; ?>" data-eid="<?php print $eid; ?>">
        <div class="span1">
            <div class="icon remove-icon remove-education"></div>
            <?php if(!isset($education['new'])): ?>
            <div class="prior-reduce" title="<?php print t('Move Item Up'); ?>"></div>
            <div class="prior-add" title="<?php print t('Move Item Down'); ?>"></div>
            <?php endif; ?>
        </div>
        <div class="span11">
            <div class="dotted-border">
                <div class="row-fluid">
                    <div class="span12">
                        <label><?php print t('Name of Institution'); ?><span class="clr-red">*</span></label>
                        <input type="text" name="education<?php print isset($education['new'])?'[new]':''; ?>[<?php print $eid; ?>][institution]"
                               value="<?php print $education['institution']; ?>"
                               class="input-xxlarge <?php isset($error[$eid]['institution'])?print 'error':''?>" required spellcheck="true" />
                    </div>
                </div>
                <div class="row-fluid">
                    <div class="span5">
                        <label><?php print t('Years Attended'); ?></label>
                    </div>
                    <div class="span4 offset3">
                        <input type="checkbox" name="none" class="date-type-select input-small <?php isset($error[$eid]['currently_studying'])?print 'error':''?>" value="1"
                            <?php print isset($education['currently_studying']) && $education['currently_studying'] == 1?'checked="checked"':''?> /> Currently Studying
                        <input type="hidden" name="education<?php print isset($education['new'])?'[new]':''; ?>[<?php print $eid; ?>][currently_studying]"
                               value="<?php print isset($education['currently_studying'])?$education['currently_studying']:0; ?>" />
                    </div>
                </div>
                <div class="row-fluid">
                    <div class="span4 hide-type-1 <?php print isset($education['currently_studying']) && $education['currently_studying'] == 1?' hide':'' ?>">
                        <label><?php print t('From'); ?><span class="clr-red">*</span></label>
                        <select <?php print isset($education['currently_studying']) && $education['currently_studying'] == 1?'data-name':'name' ?>="education<?php print isset($education['new'])?'[new]':''; ?>[<?php print $eid; ?>][start_year]"
                                class="input-small <?php isset($error[$eid]['start_year'])?print 'error':''?>">
                            <?php foreach ($years as $item): ?>
                                <option value="<?php print $item; ?>" <?php print ($item == $education['start_year'])?'selected="selected"':''?> ><?php print $item; ?></option>
                            <?php endforeach; ?>
                        </select>
                        <select <?php print isset($education['currently_studying']) && $education['currently_studying'] == 1?'data-name':'name' ?>="education<?php print isset($education['new'])?'[new]':''; ?>[<?php print $eid; ?>][start_mounth]"
                                class="input-small <?php isset($error[$eid]['start_mounth'])?print 'error':''?>">
                            <?php foreach ($months as $key => $item): ?>
                                <option <?php print ($key==12)?'class="m-group"':''; ?> value="<?php print $key; ?>" <?php print ($key == $education['start_mounth'])?'selected="selected"':''?> ><?php print $item; ?></option>
                            <?php endforeach; ?>
                        </select>
                    </div>
                    <div class="span6 hide-type-0 <?php print (isset($education['currently_studying']) && $education['currently_studying'] == 0) || !isset($education['currently_studying'])?' hide':'' ?>">
                        <label><?php print t('Expected Date'); ?><span class="clr-red">*</span></label>
                        <select <?php print (isset($education['currently_studying']) && $education['currently_studying'] == 0) || !isset($education['currently_studying'])?'data-name':'name' ?>="education<?php print isset($education['new'])?'[new]':''; ?>[<?php print $eid; ?>][start_year]"
                                class="input-small <?php isset($error[$eid]['start_year'])?print 'error':''?>">
                            <?php foreach ($years_expected as $item): ?>
                                <option value="<?php print $item; ?>" <?php print ($item == $education['start_year'])?'selected="selected"':''?> ><?php print $item; ?></option>
                            <?php endforeach; ?>
                        </select>
                        <select <?php print (isset($education['currently_studying']) && $education['currently_studying'] == 0) || !isset($education['currently_studying'])?'data-name':'name' ?>="education<?php print isset($education['new'])?'[new]':''; ?>[<?php print $eid; ?>][start_mounth]"
                                class="input-small <?php isset($error[$eid]['start_mounth'])?print 'error':''?>">
                            <?php foreach ($months as $key => $item): ?>
                                <option <?php print ($key==12)?'class="m-group"':''; ?> value="<?php print $key; ?>" <?php print ($key == $education['start_mounth'])?'selected="selected"':''?> ><?php print $item; ?></option>
                            <?php endforeach; ?>
                        </select>
                    </div>
                    <div class="span4  <?php print isset($education['currently_studying']) && $education['currently_studying'] == 1?' hide':'' ?>">
                        <span class="date-block <?php print $education['date_type']==1?'hide':''; ?>">
                            <label><?php print t('To'); ?><span class="clr-red">*</span></label>
                            <select name="education<?php print isset($education['new'])?'[new]':''; ?>[<?php print $eid; ?>][end_year]"
                                    class="end-year input-small <?php isset($error[$eid]['end_year'])?print 'error':''?>">
                                <?php foreach ($years_to as $item): ?>
                                    <option value="<?php print $item; ?>" <?php print ($item == $education['end_year'])?'selected="selected"':''?> ><?php print $item; ?></option>
                                <?php endforeach; ?>
                            </select>
                            <select name="education<?php print isset($education['new'])?'[new]':''; ?>[<?php print $eid; ?>][end_mounth]"
                                    class="end-mounth input-small <?php isset($error[$eid]['end_mounth'])?print 'error':''?>">
                                <?php foreach ($months as $key => $item): ?>
                                    <option <?php print ($key==12)?'class="m-group"':''; ?> value="<?php print $key; ?>" <?php print ($key == $education['end_mounth'])?'selected="selected"':''?> ><?php print $item; ?></option>
                                <?php endforeach; ?>
                            </select>
                        </span>
                    </div>
                    <div class="span4 hide-type-1 <?php print isset($education['currently_studying']) && $education['currently_studying'] == 1?' hide':'' ?>">
                        <input type="checkbox" name="on_off" value="0" class="on-off-date-single" <?php print $education['date_type']==1?'checked="checked"':''; ?> />
                        <input type="hidden" name="education<?php print isset($education['new'])?'[new]':''; ?>[<?php print $eid; ?>][date_type]"
                               value="<?php print $education['date_type']; ?>" />
                        <b><?php print t('Single Date'); ?></b>
                    </div>
                </div>

                <div class="row-fluid">
                    <div class="span4">
                        <label><?php print t('City'); ?></label>
                        <input type="text" name="education<?php print isset($education['new'])?'[new]':''; ?>[<?php print $eid; ?>][city]"
                               value="<?php print $education['city']; ?>"
                               class="input-medium <?php isset($error[$eid]['city'])?print 'error':''?>" spellcheck="true" />
                    </div>
                    <div class="span4">
                        <label><?php print t('State'); ?></label>
                        <input type="text" name="education<?php print isset($education['new'])?'[new]':''; ?>[<?php print $eid; ?>][state]"
                               value="<?php print $education['state']; ?>"
                               class="input-medium <?php isset($error[$eid]['state'])?print 'error':''?>" spellcheck="true" />
                    </div>
                    <div class="span4">
                        <label><?php print t('Country'); ?></label>
                        <input type="text" name="education<?php print isset($education['new'])?'[new]':''; ?>[<?php print $eid; ?>][country]"
                               value="<?php print $education['country']; ?>"
                               class="input-medium <?php isset($error[$eid]['country'])?print 'error':''?>" spellcheck="true" />
                    </div>
                </div>
              
                <div class="row-fluid">
                    <div class="span12">
                        <label><?php print t('Degree / Name of Course'); ?></label>
                        <input type="text" name="education<?php print isset($education['new'])?'[new]':''; ?>[<?php print $eid; ?>][course]"
                               value="<?php print $education['course']; ?>"
                               class=" <?php isset($error[$eid]['course'])?print 'error':''?>" spellcheck="true" />
                    </div>
                </div>

                <div class="row-fluid" id="gpa">
                    <div class="span4">
                        <label><?php print t('Major GPA'); ?></label>
                        <input type="text" name="education<?php print isset($education['new'])?'[new]':''; ?>[<?php print $eid; ?>][major]"
                               value="<?php print $education['major']; ?>"
                               class="input-medium <?php isset($error[$eid]['major'])?print 'error':''?>" spellcheck="true" />
                    </div>
                    <div class="span4">
                        <label><?php print t('Minor (s)'); ?></label>
                        <input type="text" name="education<?php print isset($education['new'])?'[new]':''; ?>[<?php print $eid; ?>][minor]"
                               value="<?php print $education['minor']; ?>"
                               class="input-medium <?php isset($error[$eid]['minor'])?print 'error':''?>" spellcheck="true" />
                    </div>
                    <div class="span4">
                        <label><?php print t('Cumulative GPA'); ?></label>
                        <input type="text" name="education<?php print isset($education['new'])?'[new]':''; ?>[<?php print $eid; ?>][cumulativegpa]"
                               value="<?php print $education['cumulativegpa']; ?>"
                               class="input-small <?php isset($error[$eid]['cumulativegpa'])?print 'error':''?>" spellcheck="true" />
                    </div>
                </div>
                <div class="row-fluid">
                    <div class="span12">
                        <label class="for-textarea"><?php print t('Honors / Awards'); ?></label>
                        <textarea rows="1" name="education<?php print isset($education['new'])?'[new]':''; ?>[<?php print $eid; ?>][honors]"
                               class="autowraps input-medium <?php isset($error[$eid]['honors'])?print 'error':''?>" spellcheck="true"><?php print $education['honors']; ?></textarea>
                    </div>
                </div>
                <div class="row-fluid">
                    <div class="span12">
                        <label><?php print t('Relevant Coursework'); ?></label>
                    </div>
                </div>
                <?php
                    if (!isset($education['coursework']))
                        $education['coursework'] = array();
                    print zportfolio_theme_education_coursework($education, $eid, $error);
                ?>
            </div>
        </div>
    </div>
<?php endforeach; ?>
