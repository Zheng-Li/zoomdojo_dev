<?php
    $picture = $user_profile['user_picture'];
    $uid = $user->uid;
    if (arg(0) == 'user' && is_numeric(arg(1))) {
        $uid = intval(arg(1));
    }
    $user_profile = user_load($uid);
    $lang = 'und';
?>

<div class="user-profile-wrapper">
    <div class="container-fluid">
        <div class="user-profile-<?php print $user->uid; ?>">
            <div class="field-picture row-fluid">
                <div class="span6 text-left">
                    <?php if (!empty($picture)): ?>
                        <?php print render($picture); ?>
                    <?php endif; ?>
                </div>
                <div class="span6 text-right">
                    <a href="/user/<?php print $uid; ?>/edit" class="btn btn-danger"><?php print t('Edit My Account'); ?></a>
                </div>
            </div>
            <div class="field-first-name row-fluid">
                <div class="f-title span6">
                    <?php print t('First Name'); ?>:
                </div>
                <div class="f-value span6">
                    <?php if (!empty($user_profile->field_first_name[$lang][0])): ?>
                
                        <?php 
                            $firstName = field_view_value('user', $user_profile, 'field_first_name', $user_profile->field_first_name[$lang][0]);
                            print render($firstName);
                        ?>
                    <?php endif; ?>
                </div>
            </div>
            <div class="field-last-name row-fluid">
                <div class="f-title span6">
                    <?php print t('Last Name'); ?>:
                </div>
                <div class="f-value span6">
                    <?php if (!empty($user_profile->field_last_name[$lang][0])): ?>
                        <?php 
                            $lastName=field_view_value('user', $user_profile, 'field_last_name', $user_profile->field_last_name[$lang][0]);
                            print render($lastName);
                        ?>
                    <?php endif; ?>
                </div>
            </div>
            <div class="field-email-address row-fluid">
                <div class="f-title span6">
                    <?php print t('Email Address'); ?>:
                </div>
                <div class="f-value span6">
                    <?php if (!empty($user_profile->mail)): ?>
                        <?php print $user_profile->mail; ?>
                    <?php endif; ?>
                </div>
            </div>
            <div class="field-mobile-number row-fluid">
                <div class="f-title span6">
                    <?php print t('Mobile Number'); ?>:
                </div>
                <div class="f-value span6">
                    <?php if (!empty($user_profile->field_mobile[$lang][0])): ?>
                
                        <?php 
                            $mobile = field_view_value('user', $user_profile, 'field_mobile', $user_profile->field_mobile[$lang][0]);
                            print render($mobile);
                        ?>
                    <?php endif; ?>
                </div>
            </div>
            <div class="field-college-university row-fluid">
                <div class="f-title span6">
                    <?php print t('College/University'); ?>:
                </div>
                <div class="f-value span6">
                    <?php if (!empty($user_profile->field_college_university[$lang][0])): ?>
                
                        <?php 
                            $collegeUniversity = field_view_value('user', $user_profile, 'field_college_university', $user_profile->field_college_university[$lang][0]);
                            print render($collegeUniversity);
                        ?>
                    <?php endif; ?>
                </div>
            </div>
            <div class="field-degree row-fluid">
                <div class="f-title span6">
                    <?php print t('Degree you are studying for'); ?>:
                </div>
                <div class="f-value span6">
                    <?php if (!empty($user_profile->field_degree_you_are_studying_fo[$lang][0])): ?>
                
                        <?php 
                            $degree = field_view_value('user', $user_profile, 'field_degree_you_are_studying_fo', $user_profile->field_degree_you_are_studying_fo[$lang][0]);
                            print render($degree);
                        ?>
                    <?php endif; ?>
                </div>
            </div>
            <div class="field-year-you-expert row-fluid">
                <div class="f-title span6">
                    <?php print t('Year you are studying for'); ?>:
                </div>
                <div class="f-value span6">
                    <?php if (!empty($user_profile->field_year_you_are_studying_for[$lang][0])): ?>
                
                        <?php 
                            $yearStudying = field_view_value('user', $user_profile, 'field_year_you_are_studying_for', $user_profile->field_year_you_are_studying_for[$lang][0]);
                            print render($yearStudying);
                        ?>
                    <?php endif; ?>
                </div>
            </div>
            <div class="field-sing-up row-fluid">
                <div class="f-title span6">
                    <?php print t('Sign Up date'); ?>:
                </div>
                <div class="f-value span6">
                    <?php print date('D, j F Y', $user_profile->created); ?>
                </div>
            </div>
            <div class="field-last-visited row-fluid">
                <div class="f-title span6">
                    <?php print t('Last visited date'); ?>:
                </div>
                <div class="f-value span6">
                    <?php if (!empty($user_profile->login)): ?>
                        <?php print date('D, j F Y', $user_profile->login); ?>
                    <?php else: ?>
                        <?php print t('Never'); ?>
                    <?php endif; ?>
                </div>
            </div>
        </div>
    </div>
</div>

  
