<div id="zd-job-page-<?php print $job->id; ?>" class="zd-job-page-wrapper">
    <div class="container-fluid">
        <div class="row-fluid job-top-block">
            <!-- <div class="span2 text-left job-logo">
                <img src="http://placehold.it/120x90&text=Company Logo" />
            </div> -->
            <div class="span12">
                <div class="row-fluid">
                    <div class="span8 text-left job-title">
                        <?php print $job->title; ?>
                    </div>
                    <div class="span4 text-right job-price">

                    </div>
                </div>
                <div class="row-fluid">
                    <div class="span8 text-left company-info">
                        <div class="company-name"><?php print $job->name; ?></div>
                        <div class="company-location"><?php print $job->location; ?></div>
                    </div>
                    <div class="span4 text-right job-btns share-view">
                        <?php if(!empty($job->url)): ?>
                            <?php if ($user->uid > 0): ?>
                                <a href="<?php print $job->url; ?>" target="_blank" class="btn btn-danger btn-apply"><?php print t('Apply'); ?></a>
                            <?php else: ?>
                                <a href="#" onclick="App.singInPopup(); return false;" class="btn btn-danger btn-apply"><?php print t('Apply'); ?></a>
                            <?php endif; ?>
                        <?php endif; ?>
                        <a href="<?php print $home; ?>/job-details/<?php print $job->id; ?>" 
                            class="btn btn-danger btn-share" 
                            data-img="http://placehold.it/120x90&text=Logo"
                            data-id="<?php print $job->id; ?>"
                            data-title="ZoomDojo - cracking the Job Search Code for You"
                            data-desc="Click here to see a job opportunity <?php print $job->title; ?>">
                            <?php print t('Share'); ?>
                            <i id="share-btn"></i>
                        </a>
                        <?php if($job->saved): ?>
                            <a href="#" class="btn btn-danger btn-save btn-saved" data-id="<?php print $job->id; ?>" data-uid="<?php print $user->uid; ?>"><span class="saved-text-for-replace"><?php print t('Saved'); ?></span> <i id="save-btn"></i> </a>
                        <?php else: ?>
                            <a href="#" class="btn btn-danger btn-save tooltips" data-tooltips-text="<?php print t('Save this employer in your account for future reference'); ?>" data-id="<?php print $job->id; ?>" data-uid="<?php print $user->uid; ?>"><span class="saved-text-for-replace"><?php print t('Save'); ?></span> <i id="save-btn"></i> </a>
                        <?php endif; ?>
                    </div>
                </div>
            </div>
        </div>
        <div class="row-fluid job-bottom-block">
            <div class="span10 job-status">
                <h3 class="job-info-text"><?php print t('Job Details'); ?></h3>
            </div>
            <div class="span2 job-status text-right">
                <div class="posted">Posted <?php print $job->date; ?> </div>
            </div>
            <div class="span12 job-info">
                <div class="job-description"><?php print $job->description; ?></div>
            </div>
        </div>
    </div>
</div>
