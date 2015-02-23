<div class="z-my-resumes-wrapper" id="z-my-resumes">
    <?php if (!empty($resumes)): ?>
        <?php if (!empty($pager)): ?>
            <div class="row-fluid">
                <div class="span12 resumes-pager">
                    <?php print $pager; ?>
                </div>
            </div>
        <?php endif; ?>
        <div class="row-fluid">
            <div class="span12">
                <?php foreach ($resumes as $resume): ?>
                    <div class="z-one-resume">
                        <div class="row-fluid">
                            <div class="span10">
                                <a href="/z-portfolio-resume-edit/<?php print $resume->id; ?>"
                                   id="z-view-name-<?php print $resume->id; ?>">
                                    <?php print $resume->name; ?>
                                </a>
                                <time class="z-view-time-<?php print $resume->id; ?>" datetime="<?php print $resume->created; ?>" title="<?php print t('Created'); ?>"><?php print $resume->created; ?></time>
                                <i class="z-view-time-<?php print $resume->id; ?>"><?php print $resume->updated?' / ':''; ?></i>
                                <time class="z-view-time-<?php print $resume->id; ?>" id="z-view-updated-<?php print $resume->id; ?>" datetime="<?php print $resume->updated; ?>" title="<?php print t('Edited'); ?>"><?php print $resume->updated; ?></time>
                                <input type="text" value="<?php print $resume->name; ?>" class="edit-resume-name hide"
                                       id="z-edit-name-<?php print $resume->id; ?>" />
                            </div>
                            <div class="span2 text-right" data-rid="<?php print $resume->id; ?>">
                                <div class="z-ico z-view-note" data-toggle="collapse" title="View Notes"
                                     data-target="#z-note-<?php print $resume->id; ?>"></div>
                                <div class="z-ico z-edit-resume" title="Edit Notes"></div>
                                <div class="z-ico z-delete-resume" title="Delete Résumé"></div>
                                <div class="clearfix"></div>
                            </div>
                        </div>
                        <div class="row-fluid collapse" id="z-note-<?php print $resume->id; ?>">
                            <div class="span12 note-wrapper">
                                <div class="view-resume-note" id="z-view-note-<?php print $resume->id; ?>">
                                    <?php if (!empty($resume->notes)): ?>
                                        <?php print $resume->notes; ?>
                                    <?php else: ?>
                                        <?php print t('No notes'); ?>
                                    <?php endif; ?>
                                </div>
                                <textarea class="resume-edit-note hide" id="z-edit-note-<?php print $resume->id; ?>" ><?php print $resume->notes; ?></textarea>
                                <input type="button" class="btn btn-danger standard btn-mini btn-z-save hide" value="Save"
                                       id="z-edit-btn-save-<?php print $resume->id; ?>" data-rid="<?php print $resume->id; ?>" />
                                <input type="button" class="btn btn-danger standard btn-mini btn-z-cancel hide" value="Cancel"
                                       id="z-edit-btn-cancel-<?php print $resume->id; ?>" data-rid="<?php print $resume->id; ?>" />
                            </div>
                        </div>
                    </div>
                <?php endforeach; ?>
            </div>
        </div>
        <?php if (!empty($pager)): ?>
            <div class="row-fluid">
                <div class="span12 resumes-pager">
                    <?php print $pager; ?>
                </div>
            </div>
        <?php endif; ?>
    <?php else: ?>
        <div class="row-fluid">
            <div class="span12 empty-results">
                <?php print t('You haven\'t any résumés. Please click Back to set up your Z-Portfolio and create a résumé.'); ?>
            </div>
        </div>
    <?php endif; ?>
</div>
