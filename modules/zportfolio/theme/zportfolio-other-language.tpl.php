<?php foreach ($items as $eid => $item): ?>
    <div class="skill-language <?php print isset($item['new'])?'new-skill-language':''; ?>" data-eid="<?php print $eid; ?>">
        <div class="row-fluid">
            <div class="span6">
                <div class="small-icon icon-minus remove-skills-language"></div>
                <select name="skills[1]<?php print isset($item['new'])?'[new]':''; ?>[<?php print $eid; ?>][val1]"
                        class="input-medium zp-language-select <?php isset($error[$eid]['val1'])?print 'error':''?>"
                        data-eid="<?php print $eid; ?>" >
                    <?php foreach ($langs as $k => $row): ?>
                        <option value="<?php print $k; ?>" <?php print ($k == $item['val1'] || (!is_numeric($item['val1']) && $k == 6) )?'selected="selected"':''?> ><?php print $row; ?></option>
                    <?php endforeach; ?>
                </select>
                <?php
                    $class = 'hide';
                    $attr  = 'disabled="disabled"';
                    $val   = '';
                    if (!is_numeric($item['val1'])) {
                        $class = '';
                        $attr  = '';
                        $val   = $item['val1'];
                    }
                ?>
                <input type="text" name="skills[1]<?php print isset($item['new'])?'[new]':''; ?>[<?php print $eid; ?>][val1]"
                       value="<?php print $val; ?>" class="input-small <?php print $class; ?> <?php isset($error[$eid]['val1'])?print 'error':''?>"
                       id="other-language-<?php print $eid; ?>" <?php print $attr; ?> spellcheck="true" />
            </div>
            <div class="span6">
                <label class="checkbox inline">
                    <input type="checkbox" name="skills[1]<?php print isset($item['new'])?'[new]':''; ?>[<?php print $eid; ?>][val3]"
                           value="1" <?php print $item['val3']?'checked="checked"':''; ?> />
                    <?php print t('Speak'); ?>
                </label>
                <label class="checkbox inline">
                    <input type="checkbox" name="skills[1]<?php print isset($item['new'])?'[new]':''; ?>[<?php print $eid; ?>][val4]"
                           value="1" <?php print $item['val4']?'checked="checked"':''; ?> />
                    <?php print t('Read'); ?>
                </label>
                <label class="checkbox inline">
                    <input type="checkbox" name="skills[1]<?php print isset($item['new'])?'[new]':''; ?>[<?php print $eid; ?>][val5]"
                           value="1" <?php print $item['val5']?'checked="checked"':''; ?> />
                    <?php print t('Write'); ?>
                </label>
            </div>
        </div>
        <div class="row-fluid">
            <div class="span6">
                <select name="skills[1]<?php print isset($item['new'])?'[new]':''; ?>[<?php print $eid; ?>][val2]"
                        class="input-large <?php isset($error[$eid]['val2'])?print 'error':''?>" >
                    <?php foreach ($langLevels as $k => $row): ?>
                        <option value="<?php print $k; ?>" <?php print ($k == $item['val2'])?'selected="selected"':''?> ><?php print $row; ?></option>
                    <?php endforeach; ?>
                </select>
            </div>
            <div class="span6">
                <?php print t('Fluency level'); ?>
            </div>
        </div>
    </div>
<?php endforeach; ?>