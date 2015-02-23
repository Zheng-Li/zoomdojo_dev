<?php

define('SAVED_ORGANIZATION_TYPE', 0);

define('SAVED_JOB_TYPE', 1);

/**
 * Implementation hook_submit
 * Redirect on current page
 */
function organization_manager_user_login(&$edit, $account) {
    $edit['redirect'] = current_path();
}

/**
 * Callback function for save entity (ajax)
 * @param $type: 0 - organization
 *               1 - job
 */
function organization_manager_user_save_entity($id, $type)
{
    global $user;
    $response = array(
        'status' => 'ERROR',
    );

    $res = organization_manager_saveEntity($id, $user->uid, $type);
    if ($res) {
        $response['status'] = 'OK';
    }

    print json_encode($response);
    exit();
}

/**
 * Callback function for delete entity (ajax)
 * @param $type: 0 - organization
 *               1 - job
 */
function organization_manager_user_delete_entity($id, $type)
{
    global $user;
    $response = array(
        'status' => 'ERROR',
    );

    if ($user->uid > 0) {
        $res = organization_manager_deleteEntity($id, $user->uid, $type);
        if ($res) {
            $response['status'] = 'OK';
        }
    }

    print json_encode($response);
    exit();
}

/**
 * Save entity
 */
function organization_manager_saveEntity($id, $uid, $type)
{
    return db_merge('zd_save_entity')
        ->key(array(
                'uid'         => $uid,
                'entity_type' => $type,
                'entity_id'   => $id,
            )
        )
        ->fields(
            array(
                'uid'         => $uid,
                'entity_type' => $type,
                'entity_id'   => $id,
            )
        )->execute();
}

/**
 * Save entity
 */
function organization_manager_deleteEntity($id, $uid, $type)
{
    return db_delete('zd_save_entity')
        ->condition('uid', $uid)
        ->condition('entity_type', $type)
        ->condition('entity_id', $id)
        ->execute();
}

/**
 * Get user saved organizations
 */
function organization_manager_user_userSavedOrganizations()
{
    global $user, $base_url;
    drupal_add_css(drupal_get_path('module', 'organization_manager') . '/css/find-jobs.css');
    drupal_add_js(drupal_get_path('module', 'organization_manager') . '/js/underscore-min.js');
    drupal_add_js(drupal_get_path('module', 'organization_manager') . '/js/backbone-min.js');
    drupal_add_js(drupal_get_path('module', 'organization_manager') . '/js/find-jobs.js');

    $variables = organization_manager_user_currentUserSavedOrganizationData($_GET);
    $variables['path'] = drupal_get_path('module', 'organization_manager');
    $variables['user'] = $user;
    $variables['home'] = $base_url;

    drupal_add_js(
        array(
            'page'    => $variables['currentPage'],
            'display' => $variables['display'],
        ), 'setting'
    );

    return theme('organization_manager_user_saved_organizations', $variables);
}

/**
 * Get user saved organizations ajax
 */
function organization_manager_user_userSavedOrganizationsAjax() 
{
    $post = (array) json_decode(file_get_contents("php://input"));
    if (!empty($post)) {
        $variables = organization_manager_user_currentUserSavedOrganizationData($post);
        print json_encode($variables);
    }
    exit();
}

/**
 * Get user saved data
 */
function organization_manager_user_currentUserSavedOrganizationData($get)
{
    global $user;

    $dotted       = 3;
    $currentPage  = 0;
    $displayArray = array(5, 10, 20, 50, 100);
    if (!empty($get['page'])) {
        $currentPage = $get['page'];
    }

    $limit = 5;
    if (!empty($get['display'])) {
        $limit = $get['display'];
    }

    $url = '/saved-organizations?display='.$limit.'&page=';

    $sql = "SELECT SQL_CALC_FOUND_ROWS zo.id, zo.name, zo.status, zo.homePageUrl, zo.internLink,
                zo.graduateLink, zo.veteranLink, zo.careerLink, zo.mbaLink, zo.experiencedLink,
                COUNT(zj.id) AS jobsCount, zu.title AS metaTitle, zu.description AS metaDesc
            FROM zd_organization zo 
            LEFT OUTER JOIN zd_save_entity zse ON zse.entity_id = zo.id 
            LEFT OUTER JOIN zd_jobs zj ON zj.organizationId = zo.id
            LEFT JOIN `zd_organization_urls` `zu` ON `zu`.`organizationId` = `zo`.`id` AND `zu`.`type` = 'home'
            WHERE zse.uid = :uid AND zse.entity_type = :entity_type 
            GROUP BY zo.id 
            ORDER BY zo.name ASC 
            LIMIT " . ($currentPage * $limit) . ", " . $limit;
    $params = array(
        ':uid'         => $user->uid,
        ':entity_type' => SAVED_ORGANIZATION_TYPE,
    );
    $results = db_query($sql, $params);

    $countRows = db_query('SELECT FOUND_ROWS();')->fetchField();
    if ($countRows < $limit) {
        $limit = $countRows;
    }

    $countPage = 0;
    if ($countRows > $limit) {
        $countPage = ceil($countRows / $limit);
    }

    $organizations = array();
    foreach ($results as $record) {
        $organizations[] = $record;
    }
    $organizations = organization_manager_setOrganizationsUrlByJobType($organizations, 0);

    return array(
        'organizations' => $organizations,
        'limit'         => $limit,
        'countRows'     => $countRows,
        'countPage'     => $countPage,
        'currentPage'   => $currentPage,
        'url'           => $url,
        'dotted'        => $dotted,
        'displayArray'  => $displayArray,
        'display'       => $limit,
    );
}

/**
 * Get user saved jobs
 */
function organization_manager_user_userSavedJobs()
{
    global $user, $base_url;
    drupal_add_css(drupal_get_path('module', 'organization_manager') . '/css/find-jobs.css');
    drupal_add_js(drupal_get_path('module', 'organization_manager') . '/js/underscore-min.js');
    drupal_add_js(drupal_get_path('module', 'organization_manager') . '/js/backbone-min.js');
    drupal_add_js(drupal_get_path('module', 'organization_manager') . '/js/find-jobs.js');

    $get = array();
    if (!empty($_GET['page'])) {
        $get['page'] = $_GET['page'];
    }

    $variables = organization_manager_user_currentUserSavedJobData($get);
    $variables['path'] = drupal_get_path('module', 'organization_manager');
    $variables['user'] = $user;
    $variables['home'] = $base_url;

    drupal_add_js(
        array(
            'page'    => $variables['currentPage'],
            'display' => $variables['display'],
        ), 'setting'
    );

    return theme('organization_manager_user_saved_jobs', $variables);
}

/**
 * Get user saved jobs Ajax
 */
function organization_manager_user_userSavedJobsAjax()
{
    $post = (array) json_decode(file_get_contents("php://input"));
    if (!empty($post)) {
        $variables = organization_manager_user_currentUserSavedJobData($post);
        print json_encode($variables);
    }
    exit();
}

/**
 * Get user saved data
 */
function organization_manager_user_currentUserSavedJobData($get)
{
    global $user;

    $dotted      = 3;
    $currentPage = 0;
    if (!empty($get['page'])) {
        $currentPage = $get['page'];
    }

    $limit = 5;
    if (!empty($get['limit'])) {
        $limit = $get['limit'];
    }
    $url = '/saved-jobs?page=';

    $sql = "SELECT SQL_CALC_FOUND_ROWS zj.id, zj.title, zj.description, zo.careerLink, zo.homePageUrl, zo.name, zo.description AS orgDesc
            FROM zd_jobs zj 
            LEFT OUTER JOIN zd_save_entity zse ON zse.entity_id = zj.id 
            LEFT OUTER JOIN zd_organization zo ON zo.id = zj.organizationId 
            WHERE zse.uid = :uid AND zse.entity_type = :entity_type 
            ORDER BY zj.title ASC 
            LIMIT " . ($currentPage * $limit) . ", " . $limit;
    $params = array(
        ':uid'         => $user->uid,
        ':entity_type' => SAVED_JOB_TYPE,
    );
    $results = db_query($sql, $params);

    $countRows = db_query('SELECT FOUND_ROWS();')->fetchField();
    if ($countRows < $limit) {
        $limit = $countRows;
    }

    $countPage = 0;
    if ($countRows > $limit) {
        $countPage = ceil($countRows / $limit);
    }

    $jobs = array();
    foreach ($results as $record) {
        $record->status = 1;
        $record->url    = drupal_get_path_alias('job-details/' . $record->id);
        $record->orgUrl = organization_manager_chooseOrganizationsUrl('', $record->careerLink, $record->homePageUrl);
        $jobs[] = $record;
    }

    return array(
        'organizations' => $jobs,
        'limit'         => $limit,
        'countRows'     => $countRows,
        'countPage'     => $countPage,
        'currentPage'   => $currentPage,
        'url'           => $url,
        'dotted'        => $dotted,
        'display'       => $limit,
    );
}

/**
 * Form for share email modal window
 */
function organization_manager_shareEmailForm($form, $form_state)
{
    global $user;
    $form = array();

    $form['from_email'] = array(
        '#type'       => 'textfield', 
        '#title'      => t('My email'), 
        '#size'       => 60,
        '#maxlength'  => 255,
        '#attributes' => array(
            'id' => 'zd-share-from-email'
        ),
    );
    if (!empty($user->uid)) {
        $form['from_email']['#default_value'] = $user->mail;
    }

    $form['to_email'] = array(
        '#type'       => 'textfield', 
        '#title'      => t('Friend\'s email'),
        '#size'       => 60,
        '#maxlength'  => 255,
        '#attributes' => array(
            'id' => 'zd-share-to-email'
        ),
    );

    $form['message'] = array(
        '#type'          => 'text_format', 
        '#title'         => t('Message'),
        '#format'        => 'filtered_html',
        '#default_value' => '',
        '#attributes'    => array(
            'id' => 'zd-share-massage',
        ),
    );

    $form['submit'] = array(
        '#type'  => 'submit',
        '#value' => t('Share'),
        '#ajax'  => array(
            'callback' => 'organization_manager_shareEmailFormSubmit',
            'wrapper'  => 'organization-manager-shareemailform',
            'method'   => 'replace',
            'effect'   => 'fade',
        ),
    );

    return $form;
}

function organization_manager_shareEmailForm_validate($form, $formState)
{
    $fromEmail = $formState['values']['from_email'];
    $toEmail   = $formState['values']['to_email'];
    $message   = $formState['values']['message']['value'];
    if (!valid_email_address($fromEmail)) {
        form_set_error('from_email', t('Wrong email'));
    }
    if (!valid_email_address($toEmail)) {
        form_set_error('to_email', t('Wrong email!'));
    }
    if (empty($message)) {
        form_set_error('message', t('Message is empty!'));
    }
}

/**
 * Ajax submit form for send share email
 */
function organization_manager_shareEmailFormSubmit($form, $formState)
{
    global $base_url;
    $fromEmail = $formState['values']['from_email'];
    $toEmail   = $formState['values']['to_email'];
    $message   = $formState['values']['message']['value'];
    $error     = 0;
    if (!valid_email_address($fromEmail)) {
        $error = 1;
    }
    if (!valid_email_address($toEmail)) {
        $error = 1;
    }
    if (empty($message)) {
        $error = 1;
    }
    if (!$error) {
        $message = str_replace('Share Page', '<br/>Share Page', $message);
        //send email
        $body = theme('organization_manager_share_email_template', 
            array(
                'message' => $message,
                'email'   => $fromEmail,
                'home'    => $base_url,
            )
        );

        $module = 'organization_manager';
        $key = 'default';
        $language = language_default();
        $params = array();
        $email = $toEmail;
        $from = $fromEmail;
        $send = FALSE;
        $message = drupal_mail($module, $key, $email, $language, $params, $from, $send);

        $message['headers']['Content-Type'] = 'text/html; charset=UTF-8;';
        $message['subject'] = 'Zoomdojo - Cracking the Job Search Code for You';
        $message['body'] = array();
        $message['body'][] = $body;

        // Retrieve the responsible implementation for this message.
        $system = drupal_mail_system($module, $key);
        // Format the message body.
        $message = $system->format($message);
        // Send e-mail.
        $message['result'] = $system->mail($message);

        if ($message['result']) {
            drupal_set_message(t('Message already was sent'), 'status');
            $form["wrapper"] = array("#markup" => "<script>window.setTimeout(jQuery('.modal').modal('hide'), '5000')</script>");
        }
        
    }
    return $form;
}


/**
 * Implementation hook_user_view - replace user name
 */
function organization_manager_user_view($account, $view_mode, $langcode)
{
    $account->name = organization_manager_user_getViewName();
}

/**
 * Get string name for view current user name on site
 */
function organization_manager_user_getViewName()
{
    global $user;
    $query = db_select('users', 'u');
    $query->leftJoin('field_data_field_first_name', 'fdffn', 'fdffn.entity_id=u.uid');
    $query->leftJoin('field_data_field_last_name', 'fdfln', 'fdfln.entity_id=u.uid');
    $query->addExpression("CONCAT(fdffn.field_first_name_value, ' ', fdfln.field_last_name_value)", 'welcom');
    $query = $query->condition('u.uid', $user->uid)
        ->condition('fdffn.bundle', 'user')
        ->condition('fdffn.entity_type', 'user')
        ->condition('fdfln.bundle', 'user')
        ->condition('fdfln.entity_type', 'user')
        ->execute()
        ->fetchColumn();

    if (!empty($query)) {
        return $query;
    }

    return !empty($user->uid)?$user->name:'';
}