<?php

/**
 * Event list
 */
function zoomdojo_blocks_eventList()
{
    drupal_add_js(drupal_get_path('module', 'zoomdojo_blocks') . '/js/zd-admin-tabled-categ.js');

    $limit = 50;
    $header = array(
        array('data' => t('Title'), 'field' => 'title'),
        array('data' => t('Upcoming'), 'field' => 'Upcoming'),
        array('data' => t('Start Date'), 'field' => 'dateStart'),
        array('data' => t('End Date'), 'field' => 'dateEnd'),
        array('data' => t('Created'), 'field' => 'created'),
        array('data' => t('Last update'), 'field' => 'updated'),
        array('data' => t('Operations'), 'colspan' => 2)
    );

    $categories = db_select('zd_events', 'ze')
        ->fields('ze');
    $categories = $categories->extend('TableSort')
        ->orderByHeader($header)
        ->extend('PagerDefault')
        ->limit($limit)
        ->execute();

    $rows = array();
    foreach ($categories as $item) {
        $rows[] = array(
            l($item->title, 'events/'.$item->id),
            $item->upcoming?'&#10003;':'&#10008;',
            $item->dateStart,
            $item->dateEnd,
            $item->created,
            $item->updated,
            l(t('Edit'), 'admin/zoomdojo/event/'.$item->id.'/edit'),
            l(
                t('Delete'), 'admin/zoomdojo/event/'.$item->id.'/delete', array(
                    'attributes' => array(
                        'class' => 'zd-delete-tab-category'
                    )
                )
            ),
        );
    }
    $build['category_table'] = array(
        '#theme'  => 'table',
        '#header' => $header,
        '#rows'   => $rows,
        '#weight' => 2,
    );
    $build['pager_bottom'] = array(
        '#theme' => 'pager',
        '#weight' => 3
    );
    return $build;
}

/**
 * Fast Edit (Redirect function)
 */
function zoomdojo_blocks_eventFastEdit($id)
{
    drupal_goto('admin/zoomdojo/event/'.$id.'/edit');
}

/**
 * Add & Edit event Form
 */
function zoomdojo_blocks_addEditEventForm($formId, $formState, $eid = 0)
{
    drupal_add_css(drupal_get_path('module', 'zoomdojo_blocks') . '/css/jquery-ui-1.10.3.custom.min.css');
    drupal_add_css(drupal_get_path('module', 'zoomdojo_blocks') . '/css/jquery-ui-timepicker-addon.css');
    drupal_add_js(drupal_get_path('module', 'zoomdojo_blocks')  . '/js/jquery-ui-1.10.3.custom.min.js');
    drupal_add_js(drupal_get_path('module', 'zoomdojo_blocks')  . '/js/jquery-ui-timepicker-addon.js');
    drupal_add_js("
        jQuery(document).ready(function(){
            jQuery('#date-picker input').datetimepicker({
                showOtherMonths: true,
                selectOtherMonths: true,
                dateFormat: 'yy-mm-dd',
                timeFormat: 'HH:mm:00'
            });
        });", "inline");
    $edit = intval($eid)?true:false;
    $def = new stdClass();
    $def->id          = 0;
    $def->title       = '';
    $def->description = '';
    $def->dateStart   = date('Y-m-d 00:00:00');
    $def->dateEnd     = date('Y-m-d 23:59:00', strtotime('+1 day', time()));
    $def->upcoming    = true;
    $def->url         = '';

    if ($edit) {
        $def = zoomdojo_blocks_getEvent($eid);
    }

    $form = array();
    $form['title'] = array(
        '#type'          => 'textfield', 
        '#title'         => t('Event title'), 
        '#size'          => 60,
        '#maxlength'     => 255, 
        '#required'      => TRUE,
        '#default_value' => $def->title,
    );
    $form['description'] = array(
        '#type'          => 'text_format',
        '#title'         => t('Description'),
        '#default_value' => $def->description,
        '#format'        => 'full_html',
        '#required'      => TRUE,
        '#rows'          => 20,
    );

    $form['date'] = array(
        '#title' => t('Event time'),
        '#type'  => 'fieldset',
    );
    $form['date']['date_start'] = array(
        '#type'          => 'textfield', 
        '#title'         => t('Event start date'), 
        '#size'          => 60,
        '#maxlength'     => 255, 
        '#prefix'        => '<div id="date-picker">',
        '#suffix'        => '</div>',
        '#required'      => TRUE,
        '#default_value' => $def->dateStart,
    );
    $form['date']['date_end'] = array(
        '#type'          => 'textfield', 
        '#title'         => t('Event end date'), 
        '#size'          => 60,
        '#maxlength'     => 255, 
        '#prefix'        => '<div id="date-picker">',
        '#suffix'        => '</div>',
        '#required'      => TRUE,
        '#default_value' => $def->dateEnd,
    );

    $form['upcoming_up'] = array(
        '#title' => t('Upcoming fieldset'),
        '#type'  => 'fieldset',
    );
    $form['upcoming_up']['upcoming'] = array(
        '#type'          => 'checkbox',
        '#title'         => t('Upcoming'),
        '#default_value' => $def->upcoming,
        '#ajax'          => array(
            'callback' => 'ajax_zoomdojo_check_disable_callback',
            'wrapper'  => 'upcoming-wrapper',
        ),
    );
    $form['upcoming_up']['insert'] = array(
        '#type'   => 'item',
        '#prefix' => '<div id="upcoming-wrapper">',
        '#suffix' => '</div>',
    );
    $form['upcoming_up']['insert']['url'] = array(
        '#type'          => 'textfield', 
        '#title'         => t('Event URL'), 
        '#size'          => 60,
        '#maxlength'     => 255,
        '#required'      => TRUE,
        '#default_value' => isset($formState['values']['url'])?$formState['values']['url']:$def->url,
    );
    if (empty($formState['values']['upcoming'])) {
        $form['upcoming_up']['insert']['url']['#disabled'] = true;
        $form['upcoming_up']['insert']['url']['#description'] = t('Check back later for details');
    } else {
        $form['upcoming_up']['insert']['url']['#disabled'] = false;
        $form['upcoming_up']['insert']['url']['#description'] = t('Click here for more details');
    }
    if (!isset($formState['values']['upcoming']) && $def->upcoming) {
        $form['upcoming_up']['insert']['url']['#disabled'] = false;
        $form['upcoming_up']['insert']['url']['#description'] = t('Click here for more details');
    } elseif (!isset($formState['values']['upcoming']) && !$def->upcoming) {
        $form['upcoming_up']['insert']['url']['#disabled'] = true;
        $form['upcoming_up']['insert']['url']['#description'] = t('Check back later for details');
    }

    $form['eid'] = array(
        '#type'          => 'hidden', 
        '#default_value' => $eid,
    );
    $form['save'] = array(
        '#type'  => 'submit', 
        '#value' => t(!$edit?'Save and add next':'Save'),
    );
    if (!$edit) {
        $form['save_end_exit'] = array(
            '#type'  => 'submit', 
            '#value' => t('Save and exit'),
        );
    }
    $form['actions']['cancel'] = array(
        '#markup' => l(t('Cancel'), 'admin/zoomdojo/event/list', 
            array(
                'attributes' => array(
                    'class' => 'button'
                )
            )
        ),
    );

    return $form;
}

function ajax_zoomdojo_check_disable_callback($form, $forState)
{
    return $form['upcoming_up']['insert'];
}

/**
 * Implementation hook_submit
 */
function zoomdojo_blocks_addEditEventForm_submit($formId, $formValue)
{
    $title       = $formValue['values']['title'];
    $description = $formValue['values']['description']['value'];
    $dateStart   = $formValue['values']['date_start'];
    $dateEnd     = $formValue['values']['date_end'];
    $upcoming    = $formValue['values']['upcoming'];
    $url         = $formValue['values']['url'];
    $eid         = $formValue['values']['eid'];
    $op          = $formValue['values']['op'];

    $fields = array(
        'title'       => $title,
        'description' => $description,
        'upcoming'    => $upcoming,
        'url'         => $url,
        'dateStart'   => $dateStart,
        'dateEnd'     => $dateEnd,
        'updated'     => date('Y-m-d h:i:s'),
    );

    $status = db_merge('zd_events')
        ->key(array('id' => $eid))
        ->fields($fields)
        ->execute();

    $lastId = $eid;
    if( $status == MergeQuery::STATUS_INSERT ) {
        $lastId = db_query("SELECT LAST_INSERT_ID()")->fetchField();
    }

    zoomdojo_blocks_createEventPath($lastId, $title);

    if ($op === 'Save and add next') {

    } elseif ($op === 'Save and exit') {
        drupal_goto('/admin/zoomdojo/event/list');
    } else {
        drupal_goto('/admin/zoomdojo/event/list');
    }
}

/**
 * Delete Event
 */
function zoomdojo_blocks_deleteEvent($eid)
{
    $response = array(
        'status' => 'FAIL',
    );
    $eid = intval($eid);
    if (!empty($eid)) {
        $res = db_delete('zd_events')
            ->condition('id', $eid)
            ->execute();
        if ($res) {
            db_delete('url_alias')
                ->condition('source', db_like('events/'.$eid))
                ->execute();
            $response['status'] = 'OK';
        }
    }
    print json_encode($response);
    exit();
}

/**
 * Get event data
 */
function zoomdojo_blocks_getEvent($id = 0, $order = 'title')
{
    $event = db_select('zd_events', 'ze')
        ->fields('ze')
        ->orderBy($order);
    if (!empty($id)) {
        $event = $event->condition('id', $id)
            ->execute()
            ->fetch();
    } else {
        $event = $event->execute()
            ->fetchAll();
    }
    return $event;
}

/**
 * Config api keys
 */
function zoomdojo_blocks_configEventbriteAccount()
{
    include_once "lib/eventbrite.php"; 
    $authenticationTokens = array(
        'app_key'  => variable_get('zd_eventbrite_app_key', ''),
        'user_key' => variable_get('zd_eventbrite_user_key', '')
    );
    if (!empty($authenticationTokens['app_key']) && !empty($authenticationTokens['user_key'])) {
        $ebClient = new Eventbrite($authenticationTokens);
        try {
            $ebUser = $ebClient->user_get();
            if (!empty($ebUser->user->email)) {
                $form = array();
                $form['info'] = array(
                    '#markup' => "<h1>".$ebUser->user->email."</h1>",
                );
            }
        } catch (Exception $e) {
            //
        }
    }

    $form['app_key'] = array(
        '#type'          => 'textfield', 
        '#title'         => t('App key:'), 
        '#size'          => 60,
        '#maxlength'     => 255, 
        '#required'      => TRUE,
        '#default_value' => $authenticationTokens['app_key'],
    );
    $form['user_key'] = array(
        '#type'          => 'textfield', 
        '#title'         => t('User key:'), 
        '#size'          => 60,
        '#maxlength'     => 255, 
        '#required'      => TRUE,
        '#default_value' => $authenticationTokens['user_key'],
    );
    $form['save'] = array(
        '#type'  => 'submit', 
        '#value' => t('Save'),
    );
    $form['actions']['cancel'] = array(
        '#markup' => l(t('Cancel'), 'admin/zoomdojo/event', 
            array(
                'attributes' => array(
                    'class' => 'button'
                )
            )
        ),
    );
    return $form;
}

/**
 * Implementation hook_submit
 */
function zoomdojo_blocks_configEventbriteAccount_validate($formId, $formState)
{
    include_once "lib/eventbrite.php"; 
    $authenticationTokens = array(
        'app_key'  => $formState['values']['app_key'],
        'user_key' => $formState['values']['user_key']
    );
    if (!empty($authenticationTokens['app_key']) && !empty($authenticationTokens['user_key'])) {
        $ebClient = new Eventbrite($authenticationTokens);
        try {
            $ebUser = $ebClient->user_get();
        } catch (Exception $e) {
            form_set_error('app_key', 'Wrong user data!');
            form_set_error('user_key', 'Wrong "app key" or "user key"!');
        }
    }
}

/**
 * Implementation hook_submit
 */
function zoomdojo_blocks_configEventbriteAccount_submit($formId, $formState)
{
    variable_set('zd_eventbrite_app_key', $formState['values']['app_key']);
    variable_set('zd_eventbrite_user_key', $formState['values']['user_key']);
}

/**
 * Import events with Eventbrite
 */
function zoomdojo_blocks_configEventbriteImport()
{
    $form = array();
    $form['save'] = array(
        '#type'  => 'submit', 
        '#value' => t('Run events import'),
    );
    $form['actions']['cancel'] = array(
        '#markup' => l(t('Cancel'), 'admin/zoomdojo/event', 
            array(
                'attributes' => array(
                    'class' => 'button'
                )
            )
        ),
    );
    return $form;
}

/**
 * Implementation hook_submit
 */
function zoomdojo_blocks_configEventbriteImport_submit($formId, $formState)
{
    if (isset($formState['values']['op'])) {
        include_once "lib/eventbrite.php"; 
        $authenticationTokens = array(
            'app_key'  => variable_get('zd_eventbrite_app_key', ''),
            'user_key' => variable_get('zd_eventbrite_user_key', '')
        );
        if (!empty($authenticationTokens['app_key']) && !empty($authenticationTokens['user_key'])) {
            $events   = array();
            $results  = array();
            $ebClient = new Eventbrite($authenticationTokens);
            try {
                $results = $ebClient->user_list_events();
            } catch (Exception $e) {
                drupal_set_message(t('Wrong "app key" or "user key"!'), 'error');
            }
            $count = 0;
            $is    = 0;
            $error = 0;
            if (!empty($results)) {
                foreach ($results->events as $item) {
                    if ($item->event->status === 'Live' || $item->event->status === 'Completed') {
                        $fields = array(
                            'title'       => $item->event->title,
                            'description' => $item->event->description,
                            'dateStart'   => $item->event->start_date,
                            'dateEnd'     => $item->event->end_date,
                            'eid'         => $item->event->id,
                            'upcoming'    => 1,
                            'url'         => $item->event->url,
                            'updated'     => date('Y-m-d h:i:s'),
                        );
                        $events[] = $fields;

                        $res = db_merge('zd_events')
                            ->key(array('eid' => $item->event->id))
                            ->fields($fields)
                            ->execute();
                        if ($res == MergeQuery::STATUS_INSERT) {
                            $eid = db_query("SELECT LAST_INSERT_ID()")->fetchField();
                            zoomdojo_blocks_createEventPath($eid, $item->event->title);
                            $count++;
                        } elseif ($res == 2) {
                            $is++;
                        } elseif ($res == 0) {
                            $error++;
                        }
                    }
                }
                drupal_set_message(t('Imported @count events, Existing @is, Error @error', array('@count' => $count, '@is' => $is, '@error' => $error)), 'status');
            }
        }
    }
}

/**
 * Create event path alias
 */
function zoomdojo_blocks_createEventPath($eid, $title)
{
    $urlAlias = drupal_lookup_path("alias", "events/" . $eid);
    if(empty($urlAlias)){
        $alternateUrl = "events/" . cleanEventString($title);
        $path = array(
            "source" => "events/" . $eid, 
            "alias"  => $alternateUrl,
        );
        path_save($path);
    }
}

/**
 * Clean title for alias
 */
function cleanEventString($string, $separator = '-'){
    $accents = array('Š' => 'S', 'š' => 's', 'Ð' => 'Dj','Ž' => 'Z', 'ž' => 'z', 'À' => 'A', 'Á' => 'A', 'Â' => 'A', 'Ã' => 'A', 'Ä' => 'A', 'Å' => 'A', 'Æ' => 'A', 'Ç' => 'C', 'È' => 'E', 'É' => 'E', 'Ê' => 'E', 'Ë' => 'E', 'Ì' => 'I', 'Í' => 'I', 'Î' => 'I', 'Ï' => 'I', 'Ñ' => 'N', 'Ò' => 'O', 'Ó' => 'O', 'Ô' => 'O', 'Õ' => 'O', 'Ö' => 'O', 'Ø' => 'O', 'Ù' => 'U', 'Ú' => 'U', 'Û' => 'U', 'Ü' => 'U', 'Ý' => 'Y', 'Þ' => 'B', 'ß' => 'Ss','à' => 'a', 'á' => 'a', 'â' => 'a', 'ã' => 'a', 'ä' => 'a', 'å' => 'a', 'æ' => 'a', 'ç' => 'c', 'è' => 'e', 'é' => 'e', 'ê' => 'e', 'ë' => 'e', 'ì' => 'i', 'í' => 'i', 'î' => 'i', 'ï' => 'i', 'ð' => 'o', 'ñ' => 'n', 'ò' => 'o', 'ó' => 'o', 'ô' => 'o', 'õ' => 'o', 'ö' => 'o', 'ø' => 'o', 'ù' => 'u', 'ú' => 'u', 'û' => 'u', 'ý' => 'y', 'ý' => 'y', 'þ' => 'b', 'ÿ' => 'y', 'ƒ' => 'f');
    $string = strtr($string, $accents);
    $string = strtolower($string);
    $string = preg_replace('/[^a-zA-Z0-9\s]/', '', $string);
    $string = preg_replace('{ +}', ' ', $string);
    $string = trim($string);
    $string = str_replace(' ', $separator, $string);
    return $string;
}

/**
 * Fix date first day for php (sunday)
 */
function zoomdojo_blocks_getCurrentYearAndWeek($date = null) {
    if (empty($date)) {
        $date = date('Y-m-d');
    }
    $isDate = DateTime::createFromFormat('Y-m-d', $date);
    if ($isDate === false) {
        $date = date('Y-m-d');
    }
    $currentWeek = null;
    $m = strtotime($date); 
    $today =   date('l', $m);  
    $customDate = strtotime( date('d-m-Y', $m) );
    if ($today == 'Sunday') {
        $currentWeek = $m;
    } else {
        $currentWeek = strtotime('this week last sunday', $customDate);
    }
    return $currentWeek;
}

/**
 * return string current week of days
 */
function zoomdojo_blocks_eventsWeekInfoString($date)
{
    $resp = '';
    $patern = 'M d, Y';
    if (date('l', $date) == 'Sunday') {
        $resp = date($patern, $date);
    } else {
        $resp = date($patern, strtotime('last sunday', $date));
    }
    if (date('l', $date) == 'Saturday') {
        $resp .= ' - ' . date($patern, $date);
    } else {
        $resp .= ' - ' . date($patern, strtotime('first saturday', $date));
    }
    return $resp;
}

/**
 * Get events data 
 */
function zoomdojo_blocks_getEventsData($get = array())
{
    $firstDay  = zoomdojo_blocks_getCurrentYearAndWeek();
    $date         = time();
    if (!empty($get['date'])) {
        $firstDay = zoomdojo_blocks_getCurrentYearAndWeek($get['date']);
        $date = strtotime($get['date']);
    }
    $lastDay = strtotime('+6 day', $firstDay);

    $query = db_select('zd_events', 'ze')
        ->fields('ze', array('id', 'title', 'description', 'upcoming', 'url', 'dateStart', 'dateEnd', 'eid'));
    $query->addExpression("unix_timestamp(dateStart)", "weekStart");
    $query->addExpression("unix_timestamp(dateEnd)", "weekEnd");
    $results = $query
        ->having($firstDay." BETWEEN weekStart AND weekEnd OR ".$lastDay." BETWEEN weekStart AND weekEnd")
        ->orderBy('dateStart', 'ASC')
        ->orderBy('title', 'ASC')
        ->execute();

    $url = '/events?date=';
    
    $events = array();
    foreach ($results as $record) {
        $record->druUrl = drupal_get_path_alias('events/' . $record->id);
        $record->dateStart = date('d M Y \a\t H:i', strtotime($record->dateStart));
        $record->dateEnd = date('d M Y \a\t H:i', strtotime($record->dateEnd));
        $events[] = $record;
    }

    return array(
        'events'  => $events,
        'date'    => date('M d, Y', $date),
        'nextDay' => date('Y-m-d', strtotime('+1 week', $date)),
        'prevDay' => date('Y-m-d', strtotime('-1 week', $date)),
        'url'     => $url,
        'info'    => zoomdojo_blocks_eventsWeekInfoString($date),
    );
}

/**
 * Events page /events
 */
function zoomdojo_blocks_eventsPage()
{
    // seo
    drupal_add_html_head(array(
        '#tag' => 'meta',
        '#attributes' => array(
            'name' => 'description',
            'content' => "Meet real-life young professionals working in the events industry and find out what people do in event management fields.",
        ),
    ), 'description');
    drupal_add_html_head(array(
        '#tag' => 'meta',
        '#attributes' => array(
            'name' => 'keywords',
            'content' => "events industry, what does an event manager do, event manager interview",
        ),
    ), 'keywords');

    drupal_add_css(drupal_get_path('module', 'zoomdojo_blocks') . '/css/zd-events.css');
    $variables['path'] = drupal_get_path('module', 'zoomdojo_blocks');

    $events = array();
    foreach (zoomdojo_blocks_getLeftEvents(10) as $event) {
        $event->druUrl = drupal_get_path_alias('events/' . $event->id);
        $event->dateStart = date('M d, Y', strtotime($event->dateStart));
        $events[] = $event;
    }
    $variables['leftEvents']  = $events;

    $events = array();
    foreach (zoomdojo_blocks_getRightEvents('all') as $event) {
        $event->druUrl = drupal_get_path_alias('events/' . $event->id);
        $event->dateStart = date('M d, Y', strtotime($event->dateStart));
        $events[] = $event;
    }
    $variables['rightEvents'] = $events;

    return theme('zoomdojo_blocks_events_page_simple', $variables);
}

/**
 * Get all past events page
 */
function zoomdojo_blocks_eventsPageAllPast()
{
    drupal_add_css(drupal_get_path('module', 'zoomdojo_blocks') . '/css/zd-events.css');
    $results = zoomdojo_blocks_getLeftEvents('all');
    $events = array();
    foreach ($results as $event) {
        $event->druUrl = drupal_get_path_alias('events/' . $event->id);
        $event->dateStart = date('M d, Y', strtotime($event->dateStart));
        //$event->dateStart = date('M d, Y \a\t H:i', strtotime($event->dateStart));
        $event->dateEnd = date('M d, Y \a\t H:i', strtotime($event->dateEnd));
        $events[] = $event;
    }
    $variables = array(
        'events' => $events,
    );
    return theme('zoomdojo_blocks_events_page_past_events', $variables);
}

/**
 * Events page /events New (in future)
 */
function zoomdojo_blocks_eventsPageFuture()
{
    // seo
    drupal_add_html_head(array(
        '#tag' => 'meta',
        '#attributes' => array(
            'name' => 'description',
            'content' => "Meet real-life young professionals working in the events industry and find out what people do in event management fields.",
        ),
    ), 'description');
    drupal_add_html_head(array(
        '#tag' => 'meta',
        '#attributes' => array(
            'name' => 'keywords',
            'content' => "events industry, what does an event manager do, event manager interview",
        ),
    ), 'keywords');

    drupal_add_css(drupal_get_path('module', 'zoomdojo_blocks') . '/css/zd-events.css');
    drupal_add_css(drupal_get_path('module', 'zoomdojo_blocks') . '/css/datepicker.css');
    drupal_add_js(drupal_get_path('module', 'zoomdojo_blocks') . '/js/bootstrap-datepicker.js');
    drupal_add_js(drupal_get_path('module', 'zoomdojo_blocks') . '/js/zd-events.js');

    $variables = zoomdojo_blocks_getEventsData($_GET);
    $variables['path'] = drupal_get_path('module', 'zoomdojo_blocks');

    $variables['leftEvents']  = zoomdojo_blocks_getLeftEvents();
    $variables['rightEvents'] = zoomdojo_blocks_getRightEvents();

    return theme('zoomdojo_blocks_events_page', $variables);
}

/**
 * Get left events
 */
function zoomdojo_blocks_getLeftEvents($count = 3)
{
    $query = db_select('zd_events', 'ze')
        ->fields('ze', array('id', 'title', 'dateStart', 'dateEnd', 'eid', 'description'));
    $query->addExpression("UNIX_TIMESTAMP(dateStart)", "date");
    $query->addExpression("UNIX_TIMESTAMP(CURRENT_DATE())", "today");
    if ($count != 'all') {
        $query->range(0, $count);
    }
    $results = $query->having('date < today')
        ->orderBy('dateStart', 'DESC')
        ->orderBy('title', 'ASC')
        ->execute()
        ->fetchAll();
    return $results;
}

/**
 * Get right events
 */
function zoomdojo_blocks_getRightEvents($count = 3)
{
    $query = db_select('zd_events', 'ze')
        ->fields('ze', array('id', 'title', 'dateStart', 'dateEnd', 'eid'));
    $query->addExpression("UNIX_TIMESTAMP(dateStart)", "date");
    $query->addExpression("UNIX_TIMESTAMP(CURRENT_DATE())", "today");
    if ($count != 'all') {
        $query->range(0, $count);
    }
    $results = $query->having('date > today')
        ->orderBy('dateStart', 'ASC')
        ->orderBy('title', 'ASC')
        ->execute()
        ->fetchAll();
    return $results;
}

/**
 * Get events ajax
 */
function zoomdojo_blocks_getEventsAjax()
{
    $resp = array(
        'status' => 'ERROR',
        'data'   => null,
    );
    if (!empty($_GET['date'])) {
        $variables = zoomdojo_blocks_getEventsData($_GET);
        if (!empty($variables['events'])) {
            $resp = array(
                'status' => 'OK',
                'data'   => $variables,
            );
        } else {
            $resp['data'] = $variables;
        }
        print json_encode($resp);
    }
    exit();
}

/**
 * One event page /events/%eid
 */
function zoomdojo_blocks_oneEventsPage($eid, $detail = false)
{
    drupal_add_css(drupal_get_path('module', 'zoomdojo_blocks') . '/css/zd-events.css');

    if ($detail) {
        $alias = arg(0) . '/' . arg(1);
        $url = drupal_lookup_path('source', $alias);
        if (!empty($url)) {
            $eid = intval(str_replace('events/', '', $url));
        } else {
            $eid = arg(1);
        }
    }

    $event = zoomdojo_blocks_getEvent($eid);
    if (empty($event)) {
        drupal_not_found();
    }

    $event->old = false;
    if (strtotime($event->dateStart) < time())
    {
        $event->old = true;
    }

    if (!$event->old) {
        //$event->dateStart = date('M d, Y \a\t H:i', strtotime($event->dateStart));
        $event->dateStart = date('M d, Y', strtotime($event->dateStart));
        $event->dateEnd = date('M d, Y \a\t H:i', strtotime($event->dateEnd));
    } else {
        $event->dateStart = date('M d, Y', strtotime($event->dateStart));
        $event->dateEnd = date('M d, Y', strtotime($event->dateEnd));
    }

    drupal_set_title($event->title);
    $them = false;
    $widgetContent = null;

    if (!empty($event->eid)) {
        include "lib/eventbrite.php"; 
        $authenticationTokens = array(
            'app_key'  => variable_get('zd_eventbrite_app_key', ''),
            'user_key' => variable_get('zd_eventbrite_user_key', '')
        );
        if (!empty($authenticationTokens['app_key']) && !empty($authenticationTokens['user_key'])) {
            $ebClient = new Eventbrite($authenticationTokens);
            $event->druUrl = drupal_get_path_alias('events/' . $event->id);
            $event->id = $event->eid;
            $widgetContent = $ebClient->registrationWidget($event);
            $them = true;
        }
    }

    $variables = array(
        'event'         => $event,
        'them'          => $them,
        'detail'        => $detail,
        'widgetContent' => $widgetContent,
    );
    return theme('zoomdojo_blocks_one_events_page', $variables);
}

/**
 * View home link template
 */
function zoomdojo_blocks_homePageLinkView()
{
    //$homePageLink = variable_get('zd_homepage_link', '/events');
    $homePageLink = '/featured-jobs/internships';
    return '<div class="interships-2013">
                <p><a class="btn btn-danger btn-large" href="'.$homePageLink.'">'.t('Click here').'</a></p>
                 <span>'.t('Just posted! Exclusive Jobs and Internship Opportunities and new International Internships!').'</span>
           </div>';
}
