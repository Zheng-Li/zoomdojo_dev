<div id="<?php print $zId; ?>" class="modal fade hide in">
    <div class="modal-header">
        <button aria-hidden="true" data-dismiss="modal" class="close" type="button">×</button>
        <h3>
            <?php print t($title); ?>
        </h3>
    </div>
    <div class="modal-body">
        <?php print $body; ?>
    </div>
    <div class="modal-footer">
        <a href="#" onclick="return false;" data-dismiss="modal" class="btn btn-danger btn-small close no-opacity"><?php print t('Close'); ?></a>
    </div>
</div>