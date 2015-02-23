<?php foreach ($leaderships as $eid => $leadership): ?>
    <?php
    if(!empty($error['new']) && isset($leadership['new'])) {
        $error = $error['new'];
    }
    $datePresent = false;
    if (empty($leadership['end_mounth']) && empty($leadership['end_year'])) {
        $datePresent = true;
    }
    ?>
    <div class="row-fluid  <?php print isset($leadership['new'])?'new-leadership new-leadership-'.$eid:'sortable'; ?> leadership leadership-<?php print $eid; ?>" data-eid="<?php print $eid; ?>">
        <div class="span1">
            <div class="icon remove-icon  remove-leadership"></div>
            <?php if(!isset($leadership['new'])): ?>
            <div class="prior-reduce" title="<?php print t('Move Item Up'); ?>"></div>
            <div class="prior-add" title="<?php print t('Move Item Down'); ?>"></div>
            <?php endif; ?>
        </div>
        <div class="span11">
            <div class="dotted-border">
                <div class="row-fluid">
                    <div class="span12">
                        <label><?php print t('Name of Organization'); ?><span class="clr-red">*</span></label>
                        <input type="text" name="leadership<?php print isset($leadership['new'])?'[new]':''; ?>[<?php print $eid; ?>][organization]"
                               value="<?php print $leadership['organization']; ?>"
                               class="input-xxlarge <?php isset($error[$eid]['organization'])?print 'error':''?>" required required spellcheck="true" />
                    </div>
                </div>
                <div class="row-fluid">
                    <div class="span12">
                        <label><?php print t('Title'); ?></label>
                        <input type="text" name="leadership<?php print isset($leadership['new'])?'[new]':''; ?>[<?php print $eid; ?>][designationtitle]"
                               value="<?php print $leadership['designationtitle']; ?>"
                               class="input-xxlarge <?php isset($error[$eid]['designationtitle'])?print 'error':''?>" spellcheck="true" />
                    </div>
                </div>
                <div class="row-fluid">
                    <div class="span4">
                        <label><?php print t('City'); ?></label>
                        <input type="text" name="leadership<?php print isset($leadership['new'])?'[new]':''; ?>[<?php print $eid; ?>][city]"
                               value="<?php print $leadership['city']; ?>"
                               class="input-medium <?php isset($error[$eid]['city'])?print 'error':''?>" spellcheck="true" />
                    </div>
                    <div class="span4">
                        <label><?php print t('State'); ?></label>
                        <input type="text" name="leadership<?php print isset($leadership['new'])?'[new]':''; ?>[<?php print $eid; ?>][state]"
                               value="<?php print $leadership['state']; ?>"
                               class="input-medium <?php isset($error[$eid]['state'])?print 'error':''?>" spellcheck="true" />
                    </div>
                    <div class="span4">
                        <label><?php print t('Country'); ?></label>
                        <input type="text" name="leadership<?php print isset($leadership['new'])?'[new]':''; ?>[<?php print $eid; ?>][country]"
                               value="<?php print $leadership['country']; ?>"
                               class="input-medium <?php isset($error[$eid]['country'])?print 'error':''?>" spellcheck="true" />
                    </div>
                </div>
                <div class="row-fluid">
                    <div class="span5">
                        <label><?php print t('Time Period Worked / Involved With'); ?></label>
                    </div>
                    <div class="span4 offset3">
                        <input type="checkbox" name="none" class="date-type-select input-small <?php isset($error[$eid]['date_type'])?print 'error':''?>" value="1"
                            <?php print $leadership['date_type'] == 1?'checked="checked"':''?> /> Single Date
                        <input type="hidden" name="leadership<?php print isset($leadership['new'])?'[new]':''; ?>[<?php print $eid; ?>][date_type]"
                               value="<?php print $leadership['date_type']; ?>" />
                    </div>
                </div>
                <div class="row-fluid" id="time-period">
                    <div class="span4">
                        <label><?php print t('From'); ?><span class="clr-red">*</span></label>
                        <select name="leadership<?php print isset($leadership['new'])?'[new]':''; ?>[<?php print $eid; ?>][start_year]"
                                class="input-small <?php isset($error[$eid]['start_year'])?print 'error':''?>">
                            <?php foreach ($years as $item): ?>
                                <option value="<?php print $item; ?>" <?php print ($item == $leadership['start_year'])?'selected="selected"':''?> ><?php print $item; ?></option>
                            <?php endforeach; ?>
                        </select>
                        <select name="leadership<?php print isset($leadership['new'])?'[new]':''; ?>[<?php print $eid; ?>][start_mounth]"
                                class="input-small <?php isset($error[$eid]['start_mounth'])?print 'error':''?>">
                            <?php foreach ($months as $key => $item): ?>
                                <option <?php print ($key==12)?'class="m-group"':''; ?> value="<?php print $key; ?>" <?php print ($key == $leadership['start_mounth'])?'selected="selected"':''?> ><?php print $item; ?></option>
                            <?php endforeach; ?>
                        </select>
                    </div>
                    <div class="span4 <?php print $leadership['date_type'] == 1?' hide':'' ?>">
                        <label><?php print t('To'); ?><span class="clr-red">*</span></label>
                        <span class="date-block <?php print $datePresent?'hide':''; ?>">
                            <select name="leadership<?php print isset($leadership['new'])?'[new]':''; ?>[<?php print $eid; ?>][end_year]"
                                    class="input-small end-year <?php isset($error[$eid]['end_year'])?print 'error':''?>">
                                <?php foreach ($years as $item): ?>
                                    <option value="<?php print $item; ?>" <?php print ($item == $leadership['end_year'])?'selected="selected"':''?> ><?php print $item; ?></option>
                                <?php endforeach; ?>
                                <?php if ($datePresent): ?>
                                    <option value="0" selected="selected">0</option>
                                <?php endif; ?>
                            </select>
                            <select name="leadership<?php print isset($leadership['new'])?'[new]':''; ?>[<?php print $eid; ?>][end_mounth]"
                                    class="input-small end-mounth <?php isset($error[$eid]['end_mounth'])?print 'error':''?>">
                                <?php foreach ($months as $key => $item): ?>
                                    <option <?php print ($key==12)?'class="m-group"':''; ?> value="<?php print $key; ?>" <?php print ($key == $leadership['end_mounth'])?'selected="selected"':''?> ><?php print $item; ?></option>
                                <?php endforeach; ?>
                                <?php if ($datePresent): ?>
                                    <option value="0" selected="selected">0</option>
                                <?php endif; ?>
                            </select>
                        </span>
                        <span class="date-block-text <?php print $datePresent?'':'hide'; ?>"><?php print t('Present'); ?></span>
                    </div>
                    <div class="span4 <?php print $leadership['date_type'] == 1?' hide':'' ?>">
                        <input type="checkbox" name="on_off" value="0" class="on-off-date" <?php print $datePresent?'checked="checked"':''; ?> />
                        <?php print t('Currently Involved'); ?>
                    </div>
                </div>
                <div class="row-fluid">
                    <div class="span12 address">
                        <label><?php print t('Details'); ?></label>
                        <textarea name="leadership<?php print isset($leadership['new'])?'[new]':''; ?>[<?php print $eid; ?>][details]"
                                 class="autowraps <?php isset($error[$eid]['details'])?print 'error':''?>" rows="2" spellcheck="true"><?php print $leadership['details']; ?></textarea>
                    </div>
                </div>

                <?php
                    if (!isset($leadership['responsibility']))
                        $leadership['responsibility'] = array();
                    print zportfolio_theme_leadership_responsibility($leadership, $eid, $error);
                ?>
            </div>
        </div>
    </div>
<?php endforeach; ?>