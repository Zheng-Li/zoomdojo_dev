<?php
include_once 'organization_manager_job_types.inc';
include_once 'organization_manager_job_inustries.inc';
include_once 'organization_manager_locations.inc';

function organization_manager_organization_edit($id = 0)
{
    if (isset($_POST['op'])) {
        organization_manager_organization_edit_submit($_POST);
    }
    drupal_add_css(drupal_get_path('module', 'organization_manager') . '/css/select2.css');
    drupal_add_css(drupal_get_path('module', 'organization_manager') . '/css/organization_manager.css');

    drupal_add_js(drupal_get_path('module', 'organization_manager') . '/js/select2.min.js');
    drupal_add_js(drupal_get_path('module', 'organization_manager') . '/js/underscore-min.js');
    drupal_add_js(drupal_get_path('module', 'organization_manager') . '/js/backbone-min.js');
    drupal_add_js(drupal_get_path('module', 'organization_manager') . '/js/organization_manager.js');

    $organization = new stdClass();
    $organization->id              = 0;
    $organization->name            = '';
    $organization->description     = '';
    $organization->internLink      = '';
    $organization->graduateLink    = '';
    $organization->veteranLink     = '';
    $organization->careerLink      = '';
    $organization->homePageUrl     = '';
    $organization->mbaLink         = '';
    $organization->experiencedLink = '';
    $organization->delete_flag     = 0;
    $organization->status          = 1;
    $orgIndustries = array();
    $orgTypes      = array();
    $locations     = array();
    
    if($id){
        $organization = db_select('zd_organization', 'o')
            ->fields('o', array('id', 'name', 'description', 'internLink', 'graduateLink', 'veteranLink', 'careerLink', 'homePageUrl', 'mbaLink', 'experiencedLink', 'status','delete_flag'))
            ->condition('id', $id)
            ->execute()
            ->fetch();
        
        $orgIndustriesData = db_select('zd_org_industries', 'i')
            ->fields('i', array('industryId'))
            ->condition('organizationId', $id)
            ->execute()
            ->fetchAll();
        $orgIndustries = array();
        foreach($orgIndustriesData as $item)
            $orgIndustries[] = $item->industryId;
        
        $orgTypesData = db_select('zd_org_job_types', 't')
            ->fields('t', array('typeId'))
            ->condition('organizationId', $id)
            ->execute()
            ->fetchAll();
        $orgTypes = array();
        foreach($orgTypesData as $item)
            $orgTypes[] = $item->typeId;

        $query = db_select('zd_org_loc', 'l');
        $query->fields('l', array('countryId', 'stateId', 'cityId'));
        $locations = $query->condition('l.organizationId', $id)
            ->execute()
            ->fetchAll();
    }
    
    $countries = _ajax_organization_manager_getCountriesOptions(true);
    $states    = _ajax_organization_manager_getStatesOptions($countries[0]->id);
    $cities    = _ajax_organization_manager_getCitiesOptions($states[0]->id);

    $variables = array(
        'organization'   => $organization,
        'orgIndustries'  => $orgIndustries,
        'orgTypes'       => $orgTypes,
        'locations'      => $locations,
        'countries'      => $countries,
        'states'         => $states,
        'cities'         => $cities,
        'industry_types' => organization_manager_job_industries_get_data(),
        'job_types'      => organization_manager_job_types_get_data(true),
        'flag_delete_button' => organization_manager_flagDeleteButton($id,$organization->delete_flag),
        'status_button' => organization_manager_statusButton($id,$organization->status)
    );
    return theme('organization_manager_edit_organization', $variables);
}

function organization_manager_ajax_getStates($countryId)
{
    $resp = array(
        'status' => 'OK',
        'data'   => _ajax_organization_manager_getStatesOptions($countryId),
    );
    print json_encode($resp);
    exit();
}

function organization_manager_ajax_getCities($stateId)
{
    $resp = array(
        'status' => 'OK',
        'data'   => _ajax_organization_manager_getCitiesOptions($stateId),
    );
    print json_encode($resp);
    exit();
}

function organization_manager_ajax_getAdminStates($countryId)
{
    $resp = array(
        'status' => 'OK',
        'data'   => _ajax_organization_manager_getAdminStatesOptions($countryId),
    );
    print json_encode($resp);
    exit();
}

function organization_manager_ajax_getAdminCities($stateId)
{
    $resp = array(
        'status' => 'OK',
        'data'   => _ajax_organization_manager_getAdminCitiesOptions($stateId),
    );
    print json_encode($resp);
    exit();
}

function organization_manager_organization_edit_submit($val)
{
    $location = array();
    foreach ($val['location']['country'] as $k => $v) {
        $location[] = (object) array(
            'countryId' => $v,
            'stateId'   => $val['location']['state'][$k],
            'cityId'    => $val['location']['city'][$k],
        );
    }
    $val['location'] = $location;

    $fields = array(
        'name'            => $val['name'],
        'description'     => $val['description'],
        'homePageUrl'     => $val['home_link'],
        'internLink'      => $val['intern_link'],
        'graduateLink'    => $val['graduate_link'],
        'veteranLink'     => $val['veteran_link'],
        //'careerLink'      => $val['carrer_link'],
        'mbaLink'         => $val['mba_link'],
        'experiencedLink' => $val['experienced_link'],
        'updated'         => date('Y-m-d h:i:s'),
    );
    
    $status = db_merge('zd_organization')
        ->key(array('id' => $val['id']?$val['id']:null))
        ->fields($fields)
        ->execute();
    
    if( $status == MergeQuery::STATUS_INSERT ) {
        $lastId = db_query("SELECT LAST_INSERT_ID()")->fetchField();
    } else {
        $lastId = $val['id'];
    }
    
    if($val['id'] && $lastId){
        db_delete('zd_org_loc')
            ->condition('organizationId', $lastId)
            ->execute();
        db_delete('zd_org_job_types')
            ->condition('organizationId', $lastId)
            ->execute();
        db_delete('zd_org_industries')
            ->condition('organizationId', $lastId)
            ->execute();
    }
    
    if(sizeof($val['location'])){
        $query = db_insert('zd_org_loc')->fields(array('organizationId', 'countryId', 'stateId', 'cityId'));
        foreach($val['location'] as $v)
            $query->values(
                array(
                    'organizationId' => $lastId,
                    'countryId'      => $v->countryId,
                    'stateId'        => $v->stateId,
                    'cityId'         => $v->cityId,
                )
            );
        $query->execute();
    }
    
    if(!empty($val['industry_types']) && sizeof($val['industry_types'])){
        $query = db_insert('zd_org_industries')->fields(array('organizationId', 'industryId'));
        foreach($val['industry_types'] as $v)
            $query->values(
                array(
                    'organizationId' => $lastId,
                    'industryId'     => $v
                )
            );
        $query->execute();
    }
    
    if(!empty($val['job_types']) && sizeof($val['job_types'])){
        $query = db_insert('zd_org_job_types')->fields(array('organizationId', 'typeId'));
        foreach($val['job_types'] as $v)
            $query->values(
                array(
                    'organizationId' => $lastId,
                    'typeId'         => $v
                )
            );
        $query->execute();
    }
    drupal_goto();
}

function organization_manager_organization_delete()
{
//    $id = arg(4);
//    db_delete('zd_organization')
//        ->condition('id', $id)
//        ->execute();
    
    drupal_goto($_SERVER['HTTP_REFERER']);
}

/**
 * change status for organization
 */
function organization_manager_organization_change_status($orgId, $status)
{
    $st = 0;
    if ($status == 0) {
        $st = 1;
    }
    db_update('zd_organization')
        ->fields(
            array(
                'status' => $st,
            )
        )
        ->condition('id', $orgId)
        ->execute();

    drupal_goto($_SERVER['HTTP_REFERER']);
}

function organization_manager_organizations_list()
{
    if(isset($_POST['op']) && $_POST['op'] == 'Apply the filters'){
        organization_manager_organizations_list_filters_submit($_POST);
    }
    $header = array(
        array('data' => t('ID'), 'field' => 'id'),
        array('data' => t('Name'), 'field' => 'name'),
        array('data' => t('Rank'), 'field' => 'rank'),
        array('data' => t('Created'), 'field' => 'created'),
        array('data' => t('Last update'), 'field' => 'updated'),
        array('data' => t('Status'), 'field' => 'status'),
        array('data' => t('Flagged'), 'field' => 'delete_flag'),
        array('data' => t('Operations'), 'colspan' => 3)
    );
    
    $query = db_select('zd_organization', 'o');
    $query->fields('o', array('id', 'name', 'rank', 'status', 'created', 'updated','delete_flag'));
    $query = $query
        ->extend('TableSort')
        ->orderByHeader($header)
        ->extend('PagerDefault')
        ->limit(20);
    if(variable_get('hide_deleted_organizations',0) == 1){
      $query->condition('o.status',1);
    }
    $result = $query->execute();
    $rows = array();
    $deleteText = array(
        'undeleted' => 'Are you sure you want to delete this row?',
        'deleted' => 'Are you sure you want to undelete this row?',
    );
    foreach($result as $item){
        $status = $item->status?'undeleted':'deleted';
        $delete_flag = $item->delete_flag?t('Flagged for delete'):'-';
        $jobsCount = db_query("SELECT count(*) FROM zd_dev_jobs WHERE Org_id = {$item->id}")->fetchField();
        $rows[] = array(
            $item->id,
            $item->name,
            $item->rank,
            $item->created,
            $item->updated,
            $status,
            $delete_flag,
            l(t("Jobs ({$jobsCount})"), 'admin/organization-manager/organization/' . $item->id . '/jobs/'),
            l(t('Edit'), 'admin/organization-manager/organizations/edit/' . $item->id,array('query' => drupal_get_destination())),
            //l(t('Real delete'), 'admin/organization-manager/organizations/change-status/' . $item->id . '/' . $item->status),
            l(t('Change status'), 'admin/organization-manager/organizations/change-status/' . $item->id . '/' . $item->status, array(
                    'attributes' => array(
                        'onClick' => 'if (!confirm("'.$deleteText[$status].'")) {return false;}'
                    )
                )
            ),
        );
    }
    
    $build['filters'] = array(  
      '#type'   => 'form',
    );
    
    $build['filters']['fieldset'] = array(  
      '#type'   => 'fieldset', 
      '#collapsible'=>TRUE,
      '#title' => t('Filters'),
    );
    $build['filters']['fieldset']['organization'] = array(
      '#type' => 'checkbox', 
      '#name' => 'hide_deleted_organizations',
      '#attributes'=>variable_get('hide_deleted_organizations',0) == 1?array('checked'=>'checked'):array(),
      '#title' => t('Hide deleted organizations'), 
    );
    $build['filters']['fieldset']['submit'] = array( '#type' => 'submit', '#value' => 'Apply the filters', '#submit' => array('apply_filter') );
    
    
    $build['pager_top'] = array(
        '#theme' => 'pager',
        '#weight' => 1
    );
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

function organization_manager_organizations_list_filters_submit($data)
{
  variable_set('hide_deleted_organizations',0);
  if(isset($data['hide_deleted_organizations']) && $data['hide_deleted_organizations'] == 1){
    variable_set('hide_deleted_organizations',1);
  }
  drupal_goto($_SERVER['HTTP_REFERER']);
}

/**
 * Organization broken url links
 */
function organization_manager_getOrganizationBrokenLinks()
{
    drupal_set_title('Organization broken links - Http Error');
    $variables = organization_manager_getOrganizationDataBrokenLinks(0, '<>');
    return theme('organization_manager_list_broken_links', $variables);
}

function organization_manager_getOrganizationDataBrokenLinks($error, $sym = '=')
{
    $limit = 20;

    $query = db_select('zd_organization', 'zo')
        ->fields('zo', array('id', 'name'))
        ->fields('zou', array('url', 'type', 'status'));
    $query->leftJoin('zd_organization_urls', 'zou', 'zou.organizationId = zo.id');
    $query->leftJoin('zd_organization', 'zdo', 'zdo.id = zo.id');
    $query = $query->extend('PagerDefault')->limit($limit);
    $results = $query->condition('zou.status', 200, '<>')
        ->condition('zou.status', $error, $sym)
        ->condition('zo.status', 1)
        ->where('zdo.homePageUrl = zou.url')
        ->orderBy('zo.name')
        ->orderBy('zou.status')
        ->execute();
    
    $errorType = organization_manager_getHttpCode();

    $organizations = array();
    foreach ($results as $item) {
        $organizations[$item->id]['name'] = $item->name;
        $organizations[$item->id]['urls'][] = (object) array(
            'url'    => $item->url,
            'type'   => $item->type,
            'status' => isset($errorType[$item->status])?$errorType[$item->status]:'Undefined error (' . $item->status . ')',
        );
    }

    return  array(
        'organizations' => $organizations,
        'pager'         => theme('pager', array('tags' => array())),
    );
}

function organization_manager_getOrganizationBrokenLinksUnknownError()
{
    drupal_set_title('Organization broken links - Unknown Error');
    $variables = organization_manager_getOrganizationDataBrokenLinks(0, '=');
    return theme('organization_manager_list_broken_links', $variables);
}

function organization_manager_getHttpCode()
{
    return  array(
        0   => 'Unknown error',
        1   => 'Unknown error',
        100 => 'Continue',
        101 => 'Switching Protocols',
        102 => 'Processing',
        200 => 'OK',
        201 => 'Created',
        202 => 'Accepted',
        203 => 'Non-Authoritative Information',
        204 => 'No Content',
        205 => 'Reset Content',
        206 => 'Partial Content',
        207 => 'Multi-Status',
        300 => 'Redirect',
        301 => 'Redirect',
        302 => 'Redirect',
        303 => 'Redirect',
        304 => 'Redirect',
        305 => 'Redirect',
        306 => 'Redirect',
        307 => 'Redirect',
        400 => 'Bad Request',
        401 => 'Unauthorized',
        402 => 'Payment Required',
        403 => 'Forbidden',
        404 => 'Not Found',
        405 => 'Method Not Allowed',
        406 => 'Not Acceptable',
        407 => 'Proxy Authentication Required',
        408 => 'Request Timeout',
        409 => 'Conflict',
        410 => 'Gone',
        411 => 'Length Required',
        412 => 'Precondition Failed',
        413 => 'Request Entity Too Large',
        414 => 'Request-URI Too Long',
        415 => 'Unsupported Media Type',
        416 => 'Requested Range Not Satisfiable',
        417 => 'Expectation Failed',
        418 => 'I\'m a teapot',
        422 => 'Unprocessable Entity',
        423 => 'Locked',
        424 => 'Failed Dependency',
        425 => 'Unordered Collection',
        426 => 'Upgrade Required',
        449 => 'Retry With',
        450 => 'Blocked by Windows Parental Controls',
        500 => 'Internal Server Error',
        501 => 'Not Implemented',
        502 => 'Bad Gateway',
        503 => 'Service Unavailable',
        504 => 'Gateway Timeout',
        505 => 'HTTP Version Not Supported',
        506 => 'Variant Also Negotiates',
        507 => 'Insufficient Storage',
        509 => 'Bandwidth Limit Exceeded',
        510 => 'Not Extended',
    );
}

/**
 * Logic for "Flag delete" button
 * 
 * return string "Delete button" HTML code
 */
function organization_manager_flagDeleteButton($id = 0, $delete_flag = 0){
  
  global $user;
  
  /*
   * show "Flag delete" button only for user with "editing_bad_links" permissions
   */
  if($id == 0 || !user_access('editing_bad_links', $user)){
    return;
  }
  
  $button = array(
		'#type'	=> 'button',
		'#value' => t($delete_flag?'Unflag':'Flag for Delete'),
    '#attributes'=>
      array(
        'id' => array('organization-manager-flag-delete'),
        'class' => array($delete_flag?'green':'red'),
        'data-flag'=>array($delete_flag)
      )
  );
  
  $js = 'jQuery(document).ready(function () {'
      . 'jQuery("#organization-manager-flag-delete").click(function(){'
      . 'var status = confirm(jQuery("#organization-manager-flag-delete").data("flag")?"'.
      t('Are you sure you want to unflag this company?').'":"'.t('Are you sure you want to flag this company?').'"'
      .');'
      . 'if(status){'
      . 'jQuery.ajax({
                            "url": "/admin/organization-manager/organizations/flag/'.$id.'",
                            "success": function(res) {
                                res = JSON.parse(res);
                                if (res.status === "OK") {
                                    jQuery("#organization-manager-flag-delete").toggleClass("red green");
                                    jQuery("#organization-manager-flag-delete").data("flag",1-jQuery("#organization-manager-flag-delete").data("flag"))
                                    if(!jQuery("#organization-manager-flag-delete").data("flag")){
                                      jQuery("#organization-manager-flag-delete").val("'.t('Flag for Delete').'");
                                    } else{
                                      jQuery("#organization-manager-flag-delete").val("'.t('Unflag').'");
                                    }
                                } else {
                                    alert("Error!");
                                }
                            }
                        });'
      . '}'
      . 'return false;'
      . '});});';
  drupal_add_js($js, 'inline');
  
	return drupal_render($button);
}

function organization_manager_flagDeleteButton_flag_action($id){
  $response = array(
        'status' => 'FAIL',
    );
    $id = intval($id);
    if (!empty($id)) {
        $res = db_update('zd_organization')
            ->expression('delete_flag','1 - delete_flag')
            ->condition('id', $id)
            ->execute();
        if ($res) {
            $response['status'] = 'OK';
        }
    }
    print json_encode($response);
    exit();
}

/**
 * Logic for "Change status" button
 * 
 * return string "Change status" HTML code
 */
function organization_manager_statusButton($id = 0, $status = 1){
  global $user;
  
  /*
   * show "Flag delete" button only for user with "editing_bad_links" permissions
   */
  if($id == 0 || !user_access('administer site configuration', $user)){
    return;
  }
  
  $button = array(
		'#type'	=> 'button',
		'#value' => t(!$status?'Undelete':'Delete'),
    '#attributes'=>
      array(
        'id' => array('organization-manager-change-status'),
        'class' => array(!$status?'green':'red'),
        'data-status'=>array($status)
      )
  );
  
  $js = 'jQuery(document).ready(function () {'
      . 'jQuery("#organization-manager-change-status").click(function(){'
      . 'var status = confirm(!jQuery("#organization-manager-change-status").data("status")?"'.
      t('Are you sure you want to undelete this company?').'":"'.t('Are you sure you want to delete this company?').'"'
      .');'
      . 'if(status){'
      . 'jQuery.ajax({
                            "url": "/admin/organization-manager/organizations/change-status/'.$id.'",
                            "success": function(res) {
                                res = JSON.parse(res);
                                if (res.status === "OK") {
                                    jQuery("#organization-manager-change-status").toggleClass("red green");
                                    jQuery("#organization-manager-change-status").data("status",1-jQuery("#organization-manager-change-status").data("status"))
                                    if(jQuery("#organization-manager-change-status").data("status")){
                                      jQuery("#organization-manager-change-status").val("'.t('Delete').'");
                                    } else{
                                      jQuery("#organization-manager-change-status").val("'.t('Undelete').'");
                                    }
                                } else {
                                    alert("Error!");
                                }
                            }
                        });'
      . '}'
      . 'return false;'
      . '});});';
  drupal_add_js($js, 'inline');
  
	return drupal_render($button);
}

function organization_manager_statusButton_action($id){
  $response = array(
        'status' => 'FAIL',
    );
    $id = intval($id);
    if (!empty($id)) {
        $res = db_update('zd_organization')
            ->expression('status','1 - status')
            ->condition('id', $id)
            ->execute();
        if ($res) {
            $response['status'] = 'OK';
        }
    }
    print json_encode($response);
    exit();
}
