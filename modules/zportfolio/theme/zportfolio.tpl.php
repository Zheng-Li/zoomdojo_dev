<div class="z-portfolio-wrapper" id="z-portfolio-control">
    <div class="row-fluid">
        <div class="span12 text-center">
            <a href="/z-portfolio-resume-edit" class="create-resume-btn"><?php print t('Create Résumé'); ?></a> |
            <a href="/all-my-resumes"><?php print t('View All Résumés'); ?></a>
            <!--<a href="#" class="z-get-hint"><?php print t('Help Tips'); ?></a> |-->
        </div>
    </div>
    <form method="POST" action="z-portfolio"  id="z-portfolio-form" parsley-validate >
        <div class="row-fluid">
            <div class="span2 offset10 text-center submit-portfolio-top-btn">
                <?php print theme('zportfolio_submit_btn', array('text'=>'Save', 'class'=> 'top-save-btn-section standard', 'isTop'=> true, 'hideSaveBtn'=>false)); ?>
            </div>
        </div>
        <div class="accordion" id="z-portfolio-control-group">
            <div class="accordion-group" data-type="0">
                <div class="accordion-heading">
                    <a class="accordion-toggle" data-toggle="collapse" data-parent="#z-portfolio-control-group" href="#personal-details">
                        <?php print t('PERSONAL DETAILS'); ?>
                    </a>
                </div>
                <div id="personal-details" class="accordion-body collapse in">
                    <div class="accordion-inner">
                        <?php print $personalDetails; ?>
                    </div>
                </div>
            </div>
            <div class="accordion-group" data-type="1">
                <div class="accordion-heading">
                    <a class="accordion-toggle collapsed" data-toggle="collapse" data-parent="#z-portfolio-control-group" href="#education">
                        <?php print t('EDUCATION'); ?>
                    </a>
                </div>
                <div id="education" class="accordion-body collapse">
                    <div class="accordion-inner">
                        <?php print $educations; ?>
                    </div>
                </div>
            </div>
            <div class="accordion-group" data-type="2">
                <div class="accordion-heading">
                    <a class="accordion-toggle collapsed" data-toggle="collapse" data-parent="#z-portfolio-control-group" href="#experience">
                        <?php print t('EXPERIENCE'); ?>
                    </a>
                </div>
                <div id="experience" class="accordion-body collapse">
                    <div class="accordion-inner">
                        <?php print $experience; ?>
                    </div>
                </div>
            </div>
            <div class="accordion-group" data-type="3">
                <div class="accordion-heading">
                    <a class="accordion-toggle collapsed" data-toggle="collapse" data-parent="#z-portfolio-control-group" href="#leadership">
                        <?php print t('LEADERSHIP'); ?>
                    </a>
                </div>
                <div id="leadership" class="accordion-body collapse">
                    <div class="accordion-inner">
                        <?php print $leadership; ?>
                    </div>
                </div>
            </div>
            <div class="accordion-group" data-type="4">
                <div class="accordion-heading">
                    <a class="accordion-toggle collapsed" data-toggle="collapse" data-parent="#z-portfolio-control-group" href="#volunteer">
                        <?php print t('VOLUNTEER WORK'); ?>
                    </a>
                </div>
                <div id="volunteer" class="accordion-body collapse">
                    <div class="accordion-inner">
                        <?php print $volunteer; ?>
                    </div>
                </div>
            </div>
            <?php print $custom; ?>
            <div class="accordion-group" data-type="5">
                <div class="accordion-heading">
                    <a class="accordion-toggle collapsed" data-toggle="collapse" data-parent="#z-portfolio-control-group" href="#others">
                        <?php print t('SKILLS & INTERESTS'); ?>
                    </a>
                </div>
                <div id="others" class="accordion-body collapse">
                    <div class="accordion-inner">
                        <?php print $skill; ?>
                    </div>
                </div>
            </div>
            <?php print $addCustomSection; ?>
            <?php print theme('zportfolio_submit_btn', array('text'=>'Save', 'class'=> 'top-save-btn-section standard', 'isTop'=> true, 'hideSaveBtn'=>false)); ?>
            <input type="button" class="btn btn-danger standard" name="clear" id="zportfolio-clear-form" value="<?php print t('Clear'); ?>" />
            <a class="btn btn-danger standard create-resume-btn" id="create-resume-btn" href="/z-portfolio-resume-edit" ><?php print t('Create Résumé'); ?></a>
        </div>
    </form>
    <div class="row-fluid">
        <div class="span12 text-center">
            <a class="create-resume-btn" href="/z-portfolio-resume-edit"><?php print t('Create Résumé '); ?></a> |
            <a href="/all-my-resumes"><?php print t('View All Résumés'); ?></a>
            <!--<a href="#" class="z-get-hint"><?php print t('Help Tips'); ?></a> |-->
        </div>
    </div>
  <!--    modal window for creating new custom section -->
<div id="add-section-popup" class="modal fade hide in">
    <div class="modal-header">
        <button aria-hidden="true" data-dismiss="modal" class="close" type="button">×</button>
        <h3>
            <?php print t('New Section'); ?>
        </h3>
    </div>
    <div class="modal-body">
        <label><?php print t('Enter Section Name:'); ?></label>
        <input type="text" id="add-section-popup-title" value="" />
    </div>
    <div class="modal-footer">
        <a href="#" onclick="return false;" class="btn btn-danger btn-small no-opacity" data-type="new"  id="add-section-popup-submit" ><?php print t('Ok'); ?></a>
        <a href="#" onclick="return false;" data-dismiss="modal" class="btn btn-danger btn-small close no-opacity"><?php print t('Close'); ?></a>
    </div>
</div>
</div>

<?php print $hint; ?>
