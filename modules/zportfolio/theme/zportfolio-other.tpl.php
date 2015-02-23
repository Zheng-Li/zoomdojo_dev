<div class="skills-wrapper">
    <div class="row-fluid">
        <div class="inner-space">
            <div class="span2">
                <label><?php print t('Languages:'); ?></label>
            </div>
            <div class="span10 insert-item">
                <?php print $languages; ?>
            </div>
            <div class="span12 margin0">
                <div class="row-fluid">
                    <div class="span6 text-left">
                        <?php print theme('zportfolio_submit_btn', array('text'=>'Save', 'class'=> 'top-save-btn-section', 'isTop'=> false, 'hideSaveBtn'=>false)); ?>
                    </div>
                    <div class="span6 text-right">
                        <?php print zportfolio_theme_btn('add-new-language-row', 'btn-mini'); ?>
                    </div>
                </div>
            </div>
        </div>
    </div>
    <div class="row-fluid">
        <div class="inner-space">
            <div class="span2">
                <label><?php print t('Computer Skills:'); ?></label>
            </div>
            <div class="span10 insert-item">
                <?php print $computer; ?>
            </div>
            <div class="span12 margin0">
                <div class="row-fluid">
                    <div class="span6 text-left">
                        <?php print theme('zportfolio_submit_btn', array('text'=>'Save', 'class'=> 'top-save-btn-section', 'isTop'=> false, 'hideSaveBtn'=>false)); ?>
                    </div>
                    <div class="span6 text-right">
                        <?php print zportfolio_theme_btn('add-new-skill-'.SKILL_TYPE_COMPUTER.'-row', 'add-skills btn-mini', 'Add new', SKILL_TYPE_COMPUTER); ?>
                    </div>
                </div>
            </div>
        </div>
    </div>
    <div class="row-fluid">
        <div class="inner-space">
            <div class="span2">
                <label><?php print t('Other Skills /'); ?><br/><?php print t(' Activities /'); ?><br/><?php print t(' Interests:'); ?></label>
            </div>
            <div class="span10 insert-item">
                <?php print $otherSkills; ?>
            </div>
            <div class="span12 margin0">
                <div class="row-fluid">
                    <div class="span6 text-left">
                        <?php print theme('zportfolio_submit_btn', array('text'=>'Save', 'class'=> 'top-save-btn-section', 'isTop'=> false, 'hideSaveBtn'=>false)); ?>
                    </div>
                    <div class="span6 text-right">
                        <?php print zportfolio_theme_btn('add-new-skill-'.SKILL_TYPE_OTHER.'-row', 'add-skills btn-mini', 'Add new', SKILL_TYPE_OTHER); ?>
                    </div>
                </div>
            </div>
        </div>
    </div>
    <div class="row-fluid">
        <div class="inner-space">
            <div class="span2">
                <label><?php print t('Other'); ?><br/><?php print t('Awards &'); ?><br/><?php print t('Honors:'); ?></label>
            </div>
            <div class="span10 insert-item">
                <?php print $award; ?>
            </div>
            <div class="span12 margin0">
                <div class="row-fluid">
                    <div class="span6 text-left">
                        <?php print theme('zportfolio_submit_btn', array('text'=>'Save', 'class'=> 'top-save-btn-section', 'isTop'=> false, 'hideSaveBtn'=>false)); ?>
                    </div>
                    <div class="span6 text-right">
                        <?php print zportfolio_theme_btn('add-new-skill-'.SKILL_TYPE_AWARDS.'-row', 'add-skills btn-mini', 'Add new', SKILL_TYPE_AWARDS); ?>
                    </div>
                </div>
            </div>
        </div>
    </div>
    <div class="row-fluid">
        <div class="inner-space">
            <div class="span2">
                <label><?php print t('Others:'); ?></label>
            </div>
            <div class="span10">
                <textarea rows="2" name="other" class="autowraps other" id="z-other"><?php print $other; ?></textarea>
            </div>
            <div class="span12 margin0">
                <?php print theme('zportfolio_submit_btn', array('text'=>'Save', 'class'=> 'top-save-btn-section', 'isTop'=> false, 'hideSaveBtn'=>false)); ?>
            </div>
        </div>
    </div>
</div>