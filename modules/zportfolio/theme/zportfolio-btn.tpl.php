<div class="row-fluid">
    <?php if (!empty($double)): ?>
        <div class="span6 text-left">
            <?php print theme('zportfolio_submit_btn', array('text'=>'Save', 'class'=> 'top-save-btn-section', 'isTop'=> isset($isTop)?$isTop:false, 'hideSaveBtn'=>$hideSaveBtn)); ?>
        </div>
    <?php endif; ?>
    <div class="span<?php  print (empty($double))?12:6; ?> text-center">
        <div class="btn btn-danger standard head-btn <?php print $class; ?>" id="<?php print $idName; ?>"
             data-eid="<?php print $eid; ?>">
            <?php print t($text); ?>
        </div>
    </div>
</div>