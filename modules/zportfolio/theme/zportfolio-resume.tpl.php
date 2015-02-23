<div class="z-resume-wrapper" id="z-resume">
    <div class="row-fluid">
        <div class="span12">
            <form method="POST" id="z-resume-form">
                <?php if (!empty($resume['id'])): ?>
                    <a onclick="jQuery('#view-resume-download-type').modal('show');" class="btn btn-danger standard"><?php print t('Download'); ?></a>
                    <a href="/z-portfolio-resume-preview/<?php print $resume['id']; ?>" class="btn btn-danger standard preview-pdf"><?php print t('Preview Résumé'); ?></a>
                    <a class="btn btn-danger btn-delete-wrapper zresume-delete"><i class="icon remove-icon remove-education"></i></a>
                <?php else: ?>
                    <input type="submit" class="btn btn-danger standard zresume-submit-download" name="save-resume" value="<?php print t('Download'); ?>" />
                    <input type="submit" class="btn btn-danger standard zresume-submit-preview" name="save-resume" value="<?php print t('Preview Résumé'); ?>" />
                <?php endif; ?>
                <input type="submit" class="btn btn-danger standard zresume-as-submit" name="save-as-resume" value="<?php print t('Save as'); ?>" />
                <?php if (!empty($resume['id'])): ?>
                    <input type="submit" class="btn btn-danger standard zresume-submit" name="save-resume" value="<?php print t('Save'); ?>" />
                <?php endif; ?>
                <div class="clear"></div>
                <div><h3><?php print t('Click anywhere on this Résumé to edit'); ?></h3></div>
                <div class="z-item z-editor" data-valueid="0" contenteditable="true" >

                        <?php print $resume['text']; ?>
                </div>
                <textarea name="text" id="z-value-0" class="hide-textarea"><?php print $resume['text']; ?></textarea>
                <input type="hidden" name="name" value="<?php print $resume['name']; ?>" id="z-name-insert" />
                <input type="hidden" name="rid" value="<?php print $resume['id']; ?>" id="z-rid-insert" />
                <?php if (!empty($resume['id'])): ?>
                    <a onclick="jQuery('#view-resume-download-type').modal('show');" id="portfolio-resume-download" class="btn btn-danger standard"><?php print t('Download'); ?></a>
                    <a href="/z-portfolio-resume-preview/<?php print $resume['id']; ?>" class="btn btn-danger standard  preview-pdf"><?php print t('Preview Résumé'); ?></a>
                    <a class="btn btn-danger btn-delete-wrapper zresume-delete"><i class="icon remove-icon remove-education"></i></a>
                <?php else: ?>
                    <input type="submit" class="btn btn-danger standard zresume-submit-download" name="save-resume" value="<?php print t('Download'); ?>" />
                    <input type="submit" class="btn btn-danger standard zresume-submit-preview" name="save-resume" value="<?php print t('Preview Résumé'); ?>" />
                <?php endif; ?>
                <input type="submit" class="btn btn-danger standard zresume-as-submit" name="save-as-resume" value="<?php print t('Save as'); ?>" />
                <?php if (!empty($resume['id'])): ?>
                    <input type="submit" class="btn btn-danger standard zresume-submit" name="save-resume" value="<?php print t('Save'); ?>" />
                <?php endif; ?>
            </form>
        </div>
    </div>

    <!--    model window for resume name -->
    <div id="view-resume-name-popup" class="modal fade hide in">
        <div class="modal-header">
            <button aria-hidden="true" data-dismiss="modal" class="close" type="button">×</button>
            <h3>
                <?php print t('Save as Resume'); ?>
            </h3>
        </div>
        <div class="modal-body">
            <label><?php print t('Enter Resume Name:'); ?></label>
            <input type="text" name="name" id="z-resume-name" value="" />
        </div>
        <div class="modal-footer">
            <a href="#" onclick="return false;" class="btn btn-danger btn-small no-opacity"  id="zresume-popup-submit" ><?php print t('Ok'); ?></a>
            <a href="#" onclick="return false;" data-dismiss="modal" class="btn btn-danger btn-small close no-opacity"><?php print t('Close'); ?></a>
        </div>
    </div>
    
    <!--    model window for resume preview -->
    <div id="view-resume-preview-popup" class="modal fade hide in">
        <div class="modal-header">
            <button aria-hidden="true" data-dismiss="modal" class="close" type="button">×</button>
            <h3></h3>
        </div>
        <div class="modal-body" style="max-height:540px;padding:0;"></div>
        <div class="modal-footer">
        </div>
    </div>
    
    <!--    model window for resume dowsnload type -->
    <div id="view-resume-download-type" class="modal fade hide in">
        <div class="modal-header">
            <button aria-hidden="true" data-dismiss="modal" class="close" type="button">×</button>
            <h3><?php print t('Please select format'); ?></h3>
        </div>
        <div class="modal-body" style="max-height:540px;">
          <a href="/z-portfolio-resume-download/<?php print $resume['id']; ?>">pdf</a> or <a href="/z-portfolio-resume-download/<?php print $resume['id']; ?>/docx">docx</a>
        </div>
    </div>
</div>
