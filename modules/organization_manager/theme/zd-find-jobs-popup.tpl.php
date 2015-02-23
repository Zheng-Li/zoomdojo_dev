<div id="findJobsPopup" class="modal hide fade">
    <div class="modal-header">
        <button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
        <h3>Create your job search</h3>
    </div>
    <div class="modal-body">
        <form id="findJobsForm" method="get" action="/find-jobs">
        <div class="row-fluid">
            <div class="span7 leftpart">
                <!-- <h3>Create your job search</h3> -->
                <p>Fill in two or more fields</p>
                <label>I am looking at opportunities for</label>
                <select name="job_type" class="fullwidth">
                    <option value="0">All jobs</option>
                    <?php foreach($jobTypes as $key=>$val) { ?>
                        <option value="<?php echo $key; ?>" ><?php echo $val; ?></option>
                    <?php } ?>
                </select>
                <label>The industry I am interested in is</label>
                <select name="job_industry" class="fullwidth check-choose">
                    <option value="">Choose from dropdown menu</option>
                    <?php foreach($industryTypes as $key=>$val) { ?>
                        <option value="<?php echo $key; ?>" ><?php echo $val; ?></option>
                    <?php } ?>
                </select>
                <label>The location I have in mind is</label>
                <select name="location[country]" class="fullwidth check-choose" id="zd-pop-country">
                    <option value="">Choose from dropdown menu</option>
                    <?php foreach($country = _ajax_organization_manager_getCountriesOptions() as $val): ?>
                        <?php
                            if ($val->title == 'Global') {
                                $val->id = 0;
                            }
                        ?>
                        <?php if (isset($_GET['location']['country']) && $_GET['location']['country'] == $val->id): ?>
                            <?php $countryId = $_GET['location']['country']; ?>
                            <option value="<?php echo $val->id; ?>"><?php echo $val->title; ?></option>
                        <?php else: ?>
                            <option value="<?php echo $val->id; ?>" ><?php echo $val->title; ?></option>
                        <?php endif; ?>
                    <?php endforeach; ?>
                </select>
                <select name="location[state]" id="zd-pop-state" class="hide">
                    <?php
                        if (empty($_GET['location']['country'])) {
                            $countryId = $country[0]->id;
                        }
                    ?>
                    <?php foreach($state = _ajax_organization_manager_getStatesOptions($countryId) as $val): ?>
                        <?php if(!empty($_GET['location']['state']) && $_GET['location']['state'] === $val->id): ?>
                            <?php $stateId = $_GET['location']['state']; ?>
                            <option value="<?php echo $val->id; ?>"><?php echo $val->title; ?></option>
                        <?php else: ?>
                            <option value="<?php echo $val->id; ?>" ><?php echo $val->title; ?></option>
                        <?php endif; ?>
                    <?php endforeach; ?>
                </select>
                <select name="location[city]" id="zd-pop-city" class="hide">
                    <?php
                        $stateId = 0;
                        if (empty($_GET['location']['state'])) {
                            $stateId = $state[0]->id;
                        }
                    ?>
                    <?php foreach(_ajax_organization_manager_getCitiesOptions($stateId) as $val): ?>
                        <?php if (!empty($_GET['location']['city']) && $_GET['location']['city'] === $val->id): ?>
                            <option value="<?php echo $val->id; ?>"><?php echo $val->title; ?></option>
                        <?php else: ?>
                            <option value="<?php echo $val->id; ?>" ><?php echo $val->title; ?></option>
                        <?php endif; ?>
                    <?php endforeach; ?>
                </select>
            </div>
            <div class="span5 rightpart">
                <h3>I know the employer<br/>I want to search</h3>
                <label>Enter the desired employer name</label>
                <input name="company_name" value="" id="employer-autocomplete" type="text" autocomplete="off" placeholder="Type employer name" class="fullwidth employer-autocomplete"/>
            </div>
        </div>
        </form>
    </div>
    <div class="modal-footer">
        <a href="#" onclick="jQuery('#findJobsForm').submit(); return false;" class="btn btn-danger btn-lg">Start my job search now</a>
    </div>
</div>

<div id="findNewJobsPopup" class="modal hide fade">
    <div class="modal-header">
        <button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
        <h3>Where the jobs are</h3>
    </div>
    <div class="modal-body">
        <form id="findNewJobsForm" method="get" action="/find-jobs">
            <div class="row-fluid">
                <div class="span7 leftpart">
                    <h3>Create your job search</h3>
                    <p>Fill in two or more fields</p>
                    <label>I am looking at opportunities for</label>
                    <select name="job_type" class="fullwidth">
                        <option value="0">All jobs</option>
                        <?php foreach($jobTypes as $key=>$val) { ?>
                            <option value="<?php echo $key; ?>" <?php echo (isset($_GET['job_type']) && $_GET['job_type'] == $key)?'selected="selected"':''?>><?php echo $val; ?></option>
                        <?php } ?>
                    </select>
                    <label>The industry I am interested in is</label>
                    <select name="job_industry" class="fullwidth check-choose">
                        <option value="">Choose from dropdown menu</option>
                        <?php foreach($industryTypes as $key=>$val) { ?>
                            <option value="<?php echo $key; ?>" <?php echo (isset($_GET['job_industry']) && $_GET['job_industry'] == $key)?'selected="selected"':''?>><?php echo $val; ?></option>
                        <?php } ?>
                    </select>
                    <label>The location I have in mind is</label>
                    <select name="location[country]" class="fullwidth check-choose" id="zd-pop-country">
                        <option value="">Choose from dropdown menu</option>
                        <?php foreach($country = _ajax_organization_manager_getCountriesOptions() as $val): ?>
                            <?php
                            if ($val->title == 'Global') {
                                $val->id = 0;
                            }
                            ?>
                            <?php if (isset($_GET['location']['country']) && $_GET['location']['country'] == $val->id): ?>
                                <?php $countryId = $_GET['location']['country']; ?>
                                <option value="<?php echo $val->id; ?>" selected="selected"><?php echo $val->title; ?></option>
                            <?php else: ?>
                                <option value="<?php echo $val->id; ?>" ><?php echo $val->title; ?></option>
                            <?php endif; ?>
                        <?php endforeach; ?>
                    </select>
                    <select name="location[state]" id="zd-pop-state" class="<?php print empty($_GET['location']['state'])?'hide':'show'; ?>">
                        <?php
                        if (empty($_GET['location']['country'])) {
                            $countryId = $country[0]->id;
                        }
                        ?>
                        <?php foreach($state = _ajax_organization_manager_getStatesOptions($countryId) as $val): ?>
                            <?php if(!empty($_GET['location']['state']) && $_GET['location']['state'] === $val->id): ?>
                                <?php $stateId = $_GET['location']['state']; ?>
                                <option value="<?php echo $val->id; ?>" selected="selected"><?php echo $val->title; ?></option>
                            <?php else: ?>
                                <option value="<?php echo $val->id; ?>" ><?php echo $val->title; ?></option>
                            <?php endif; ?>
                        <?php endforeach; ?>
                    </select>
                    <select name="location[city]" id="zd-pop-city" class="<?php print empty($_GET['location']['city'])?'hide':'show'; ?>">
                        <?php
                        if (empty($_GET['location']['state'])) {
                            $stateId = $state[0]->id;
                        }
                        ?>
                        <?php foreach(_ajax_organization_manager_getCitiesOptions($stateId) as $val): ?>
                            <?php if (!empty($_GET['location']['city']) && $_GET['location']['city'] === $val->id): ?>
                                <option value="<?php echo $val->id; ?>" selected="selected"><?php echo $val->title; ?></option>
                            <?php else: ?>
                                <option value="<?php echo $val->id; ?>" ><?php echo $val->title; ?></option>
                            <?php endif; ?>
                        <?php endforeach; ?>
                    </select>
                </div>
                <div class="span5 rightpart">
                    <h3>I know the employer<br/>I want to search</h3>
                    <label>Enter the desired employer name</label>
                    <input name="company_name" value="<?php echo (isset($_GET['company_name']))?$_GET['company_name']:''; ?>" type="text" placeholder="Type employer name" class="fullwidth employer-autocomplete"/>
                </div>
            </div>
        </form>
    </div>
    <div class="modal-footer">
        <a href="#" onclick="jQuery('#findNewJobsForm').submit(); return false;" class="btn btn-danger btn-lg">Start my job search now</a>
    </div>
</div>

<?php if (empty($user->uid)): ?>
    <div id="sing-in-popup" class="modal hide fade in">
        <div class="modal-header">
            <button aria-hidden="true" data-dismiss="modal" class="close" type="button">×</button>
            <h3>
                <?php print t('Sign In'); ?>
            </h3>
        </div>
        <div class="modal-body">
            <?php 
                $loginForm = drupal_get_form("user_login");
                print drupal_render($loginForm); 
            ?>
            <div class="forgont-pass">
                <a href="#" onclick="App.forgotPassPopup();"><?php print t('Forgot your password?'); ?></a><br/>
                <?php print t("Don't have an account yet?"); ?> <a href="#" onclick="App.singUpPopup();"><?php print t('Sign Up'); ?></a> <?php print t('now'); ?>
            </div>

        </div>
    </div>
<?php endif; ?>

<?php if (empty($user->uid)): ?>
    <div id="sing-up-popup" class="modal hide fade in">
        <div class="modal-header">
            <button aria-hidden="true" data-dismiss="modal" class="close" type="button">×</button>
            <h3>
                <?php print t('Sign Up'); ?>
            </h3>
        </div>
        <div class="modal-body">
            <div style="font-weight:bold;color:red;font-size:12px;">
                After you sign up, a welcome message with further instructions will be sent to your e-mail address.<br/>
                If you do not receive an email within 5 minutes, please check your SPAM folder.
            </div>
            <?php 
                $registerForm = drupal_get_form("user_register_form");
                print drupal_render($registerForm); 
            ?>
            <div class="conf-text">
                By clicking Sign Up, I agree to Zoomdojo's
                <a href="/terms-use">Terms of Use</a> and <a href="/privacy-policy">Privacy Policy</a>.<br/>
                <?php print t("If you already have an account,"); ?> <a href="#" onclick="App.singInPopup();"><?php print t('Sign In'); ?></a> <?php print t('now'); ?> ?
            </div>
        </div>
    </div>
<?php endif; ?>

<?php if (empty($user->uid)): ?>
    <div id="sing-forgon-pass-popup" class="modal hide fade in">
        <div class="modal-header">
            <button aria-hidden="true" data-dismiss="modal" class="close" type="button">×</button>
            <h3>
                <?php print t('Forgot your password?'); ?> 
            </h3>
        </div>
        <div class="modal-body">
            <?php 
                module_load_include('inc', 'user', 'user.pages');
                $forgotForm = drupal_get_form("user_pass");
                print drupal_render($forgotForm); 
            ?>
        </div>
    </div>
<?php endif; ?>

<div id="share-for-email-popup" class="modal hide fade in">
    <div class="modal-header">
        <button aria-hidden="true" data-dismiss="modal" class="close" type="button">×</button>
        <h3>
            <?php print t('Email This Job'); ?>
        </h3>
    </div>
    <div class="modal-body">
        <?php 
            $forgotForm = drupal_get_form("organization_manager_shareEmailForm");
            print drupal_render($forgotForm); 
        ?>
    </div>
</div>

<div id="view-message-popup" class="modal hide fade in">
    <div class="modal-header">
        <button aria-hidden="true" data-dismiss="modal" class="close" type="button">×</button>
        <h3>
            <?php print t('Message'); ?>
        </h3>
    </div>
    <div class="modal-body">
        <div class="info-text-msg"></div>
    </div>
    <div class="modal-footer">
        <a href="#" onclick="return false;" data-dismiss="modal" class="btn btn-danger btn-small close no-opacity">Close</a>
    </div>
</div>