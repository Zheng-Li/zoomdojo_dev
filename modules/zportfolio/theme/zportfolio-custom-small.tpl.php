<?php if (empty($js)): ?>
<?php foreach($items as $iid=>$item):
  $datePresent = false;
  if (empty($item['end_mounth']) && empty($item['end_year'])) {
      $datePresent = true;
  }
  if(!empty($error['new']) && isset($item['new'])) {
        $error = $error['new'];
  }
  ?>

<div class="row-fluid sortable <?php print isset($item['new'])?'new-custom-item new-custom-item-'.$sid:''; ?> custom-item custom-item-<?php print $sid; ?>" data-iid="<?php print $sid; ?>">
        <div class="span1">
            <div class="icon remove-icon remove-custom-item" data-new="<?php print isset($item['new'])?'1':'0'; ?>" data-sid="<?php print $sid; ?>" data-iid="<?php print $iid; ?>"></div>
            <div class="prior-reduce" title="<?php print t('Move Item Up'); ?>"></div>
            <div class="prior-add" title="<?php print t('Move Item Down'); ?>"></div>
        </div>
        <div class="span11">
            <div class="dotted-border">
                <div class="row-fluid">
                    <div class="span12">
                        <label><?php print t('Title'); ?><span class="clr-red">*</span></label>
                        <input type="text" name="custom<?php print $new; ?>[<?php print $sid; ?>][items]<?php print isset($item['new'])?'[new]':''; ?>[<?php print $iid; ?>][title]"
                               value="<?php print $item['title']; ?>"
                               class="input-xxlarge <?php isset($error[$iid]['title'])?print 'error':''?>" required spellcheck="true" />
                    </div>
                </div>

                <div class="row-fluid">
                    <div class="span4">
                        <label><?php print t('Time Period'); ?></label>
                    </div>
                    <div class="span4 offset4">
                        <input type="checkbox" name="none" class="date-type-select input-small <?php isset($error[$iid]['date_type'])?print 'error':''?>" value="1"
                               <?php print $item['date_type'] == 1?'checked="checked"':''?> /> Single Date
                        <input type="hidden" name="custom<?php print $new; ?>[<?php print $sid; ?>][items]<?php print isset($item['new'])?'[new]':''; ?>[<?php print $iid; ?>][date_type]" value="<?php print $item['date_type']; ?>" />
                    </div>
                </div>
              
                <div class="row-fluid" id="time-period">
                    <div class="span4">
                        <label><?php print t('From'); ?><span class="clr-red">*</span></label>
                        <select name="custom<?php print $new; ?>[<?php print $sid; ?>][items]<?php print isset($item['new'])?'[new]':''; ?>[<?php print $iid; ?>][start_year]"
                                class="input-small <?php isset($error[$iid]['start_year'])?print 'error':''?>">
                            <?php foreach ($years as $year): ?>
                                <option value="<?php print $year; ?>" <?php print ($year == $item['start_year'])?'selected="selected"':''?> ><?php print $year; ?></option>
                            <?php endforeach; ?>
                        </select>
                        <select name="custom<?php print $new; ?>[<?php print $sid; ?>][items]<?php print isset($item['new'])?'[new]':''; ?>[<?php print $iid; ?>][start_mounth]"
                                class="input-small <?php isset($error[$iid]['start_mounth'])?print 'error':''?>">
                            <?php foreach ($months as $key => $month): ?>
                                <option <?php print ($key==12)?'class="m-group"':''; ?> value="<?php print $key; ?>" <?php print ($key == $item['start_mounth'])?'selected="selected"':''?> ><?php print $month; ?></option>
                            <?php endforeach; ?>
                        </select>
                    </div>
                    <div class="span4 <?php print $item['date_type'] == 1?' hide':'' ?>">
                        <label><?php print t('To'); ?><span class="clr-red">*</span></label>
                        <span class="date-block <?php print $datePresent?'hide':''; ?>">
                            <select name="custom<?php print $new; ?>[<?php print $sid; ?>][items]<?php print isset($item['new'])?'[new]':''; ?>[<?php print $iid; ?>][end_year]"
                                    class="input-small end-year <?php isset($error[$iid]['end_year'])?print 'error':''?>">
                                <?php foreach ($years_to as $year): ?>
                                    <option value="<?php print $year; ?>" <?php print ($year == $item['end_year'])?'selected="selected"':''?> ><?php print $year; ?></option>
                                <?php endforeach; ?>
                                <?php if ($datePresent): ?>
                                    <option value="0" selected="selected">0</option>
                                <?php endif; ?>
                            </select>
                            <select name="custom<?php print $new; ?>[<?php print $sid; ?>][items]<?php print isset($item['new'])?'[new]':''; ?>[<?php print $iid; ?>][end_mounth]"
                                    class="input-small end-mounth <?php isset($error[$iid]['end_mounth'])?print 'error':''?>">
                                <?php foreach ($months as $key => $month): ?>
                                    <option <?php print ($key==12)?'class="m-group"':''; ?> value="<?php print $key; ?>" <?php print ($key == $item['end_mounth'])?'selected="selected"':''?> ><?php print $month; ?></option>
                                <?php endforeach; ?>
                                <?php if ($datePresent): ?>
                                    <option value="0" selected="selected">0</option>
                                <?php endif; ?>
                            </select>
                        </span>
                        <span class="date-block-text <?php print $datePresent?'':'hide'; ?>"><?php print t('Present'); ?></span>
                    </div>
                    <div class="span4 <?php print $item['date_type'] == 1?' hide':'' ?>">
                        <input type="checkbox" name="on_off" value="0" class="on-off-date" <?php print $datePresent?'checked="checked"':''; ?> />
                        <?php print t('Currently Working'); ?>
                    </div>
                </div>
                <div class="row-fluid">
                    <div class="span12 address">
                        <label><?php print t('Description'); ?></label>
                        <textarea name="custom<?php print $new; ?>[<?php print $sid; ?>][items]<?php print isset($item['new'])?'[new]':''; ?>[<?php print $iid; ?>][description]"
                                 class="autowraps <?php isset($error[$iid]['details'])?print 'error':''?>" rows="2" spellcheck="true"><?php print $item['description']; ?></textarea>
                    </div>
                </div>
            </div>
        </div>
    </div>
<?php endforeach; ?>
<?php else: ?>
<div class="row-fluid new-custom-item new-custom-item-<%= sid %> new-custom-item-<%= sid %>-<%= iid %> custom-item custom-item-<%= sid %>" data-iid="<%= sid %>">
        <div class="span1">
            <div class="icon remove-icon remove-custom-item new" data-sid="<%= sid %>"></div>
        </div>
        <div class="span11">
            <div class="dotted-border">
                <div class="row-fluid">
                    <div class="span12">
                        <label><?php print t('Title'); ?><span class="clr-red">*</span></label>
                        <input type="text" name="custom<% if (isNew) {%>[new]<%} %>[<%= sid %>][items][new][<%= iid %>][title]" value="" class="input-xxlarge" required spellcheck="true" />
                    </div>
                </div>

                <div class="row-fluid">
                    <div class="span4">
                        <label><?php print t('Time Period'); ?></label>
                    </div>
                    <div class="span4 offset4">
                        <input type="checkbox" name="none" class="date-type-select input-small value="1" /> Single Date
                        <input type="hidden" name="custom<% if (isNew) {%>[new]<%} %>[<%= sid %>][items][new][<%= iid %>][date_type]" value="0" />
                    </div>
                </div>
              
                <div class="row-fluid" id="time-period">
                    <div class="span4">
                        <label><?php print t('From'); ?><span class="clr-red">*</span></label>
                        <select name="custom<% if (isNew) {%>[new]<%} %>[<%= sid %>][items][new][<%= iid %>][start_year]"
                                class="input-small">
                            <?php foreach ($years as $year): ?>
                                <option value="<?php print $year; ?>"><?php print $year; ?></option>
                            <?php endforeach; ?>
                        </select>
                        <select name="custom<% if (isNew) {%>[new]<%} %>[<%= sid %>][items][new][<%= iid %>][start_mounth]"
                                class="input-small ">
                            <?php foreach ($months as $key => $month): ?>
                                <option <?php print ($key==12)?'class="m-group"':''; ?> value="<?php print $key; ?>"><?php print $month; ?></option>
                            <?php endforeach; ?>
                        </select>
                    </div>
                    <div class="span4">
                        <label><?php print t('To'); ?><span class="clr-red">*</span></label>
                        <span class="date-block">
                            <select name="custom<% if (isNew) {%>[new]<%} %>[<%= sid %>][items][new][<%= iid %>][end_year]"
                                    class="input-small end-year">
                                <?php foreach ($years_to as $year): ?>
                                    <option value="<?php print $year; ?>" <?php print $year == date('Y')?'selected':'';?>><?php print $year; ?></option>
                                <?php endforeach; ?>
                            </select>
                            <select name="custom<% if (isNew) {%>[new]<%} %>[<%= sid %>][items][new][<%= iid %>][end_mounth]"
                                    class="input-small end-mounth">
                                <?php foreach ($months as $key => $month): ?>
                                    <option <?php print ($key==12)?'class="m-group"':''; ?> value="<?php print $key; ?>"><?php print $month; ?></option>
                                <?php endforeach; ?>
                            </select>
                        </span>
                        <span class="date-block-text hide"><?php print t('Present'); ?></span>
                    </div>
                    <div class="span4">
                        <input type="checkbox" name="on_off" value="0" class="on-off-date" />
                        <?php print t('Currently Working'); ?>
                    </div>
                </div>
                <div class="row-fluid">
                    <div class="span12 address">
                        <label><?php print t('Description'); ?></label>
                        <textarea name="custom<% if (isNew) {%>[new]<%} %>[<%= sid %>][items][new][<%= iid %>][description]" rows="2" spellcheck="true"></textarea>
                    </div>
                </div>
            </div>
        </div>
    </div>
<?php endif; ?>
