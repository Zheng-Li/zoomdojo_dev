<?php

function organization_manager_jobs_list()
{
    $organizationId = arg(3);
    $header         = array(
        array('data'  => t('ID'), 'field' => 'id'),
        array('data'  => t('Title'), 'field' => 'title'),
        array('data'  => t('Created'), 'field' => 'created'),
        array('data'  => t('Last update'), 'field' => 'updated'),
        array('data'  => t('Operations'), 'colspan' => 3)
    );

    $query  = db_select('zd_jobs', 'j');
    $query->fields('j', array('id', 'title', 'created', 'updated'));
    $query->where('organizationId = :organizationId', array(':organizationId' => $organizationId));
//    $query->extend('PagerDefault')->limit(25);
    $query  = $query
        ->extend('TableSort')
        ->orderByHeader($header)
        ->extend('PagerDefault')
        ->limit(20);
    $result = $query->execute();
    $rows   = array();
    foreach ($result as $item) {
        $rows[] = array(
            $item->id,
            $item->title,
            $item->created,
            $item->updated,
            l(t('Edit'), 'admin/organization-manager/job/edit/' . $item->id),
            l(t('Delete'), 'admin/organization-manager/job/delete/' . $item->id),
        );
    }
    $build['pager_top']      = array(
        '#theme'  => 'pager',
        '#weight' => 1
    );
    $build['category_table'] = array(
        '#theme'  => 'table',
        '#header' => $header,
        '#rows'   => $rows,
        '#weight' => 2,
    );
    $build['pager_bottom']   = array(
        '#theme'  => 'pager',
        '#weight' => 3
    );
    return $build;
}

function organization_manager_job_edit()
{
    $id = intval(arg(4));

    if ($id) {
        $job = db_select('zd_jobs', 'o')
            ->fields('o', array('organizationId', 'title', 'description', 'url'))
            ->condition('id', $id)
            ->execute()
            ->fetch();

        $orgIndustriesData = db_select('zd_jobs_industries', 'i')
            ->fields('i', array('industryId'))
            ->condition('jobId', $id)
            ->execute()
            ->fetchAll();
        $orgIndustries     = array();
        foreach ($orgIndustriesData as $item)
            $orgIndustries[]   = $item->industryId;

        $orgTypesData = db_select('zd_jobs_job_types', 't')
            ->fields('t', array('typeId'))
            ->condition('jobId', $id)
            ->execute()
            ->fetchAll();
        $orgTypes     = array();
        foreach ($orgTypesData as $item)
            $orgTypes[]   = $item->typeId;

        $orgLocationsData = db_select('zd_jobs_locations', 'l')
            ->fields('l', array('locationId'))
            ->condition('jobId', $id)
            ->execute()
            ->fetchAll();
        $orgLocations     = array();
        foreach ($orgLocationsData as $item)
            $orgLocations[]   = $item->locationId;
    }

    drupal_add_css(drupal_get_path('module', 'organization_manager') . '/css/select2.css');
    drupal_add_css(drupal_get_path('module', 'organization_manager') . '/css/organization_manager.css');
    drupal_add_js(drupal_get_path('module', 'organization_manager') . '/js/organization_manager.js');
    drupal_add_js(drupal_get_path('module', 'organization_manager') . '/js/select2.min.js');

    $form['id'] = array(
        '#type'          => 'hidden',
        '#default_value' => $id ? $id : ''
    );

    $form['organizationId'] = array(
        '#type'          => 'hidden',
        '#default_value' => $id ? $job->organizationId : arg(3)
    );

    $form['title']       = array(
        '#type'          => 'textfield',
        '#title'         => t('Job Title'),
        '#size'          => 60,
        '#maxlength'     => 255,
        '#required'      => TRUE,
        '#default_value' => $id ? $job->title : ''
    );
    $form['description'] = array(
        '#type'          => 'textarea',
        '#title'         => t('Description'),
        '#cols'          => 30,
        '#rows'          => 5,
        '#required'      => FALSE,
        '#default_value' => $id ? $job->description : ''
    );
    $form['url']       = array(
        '#type'          => 'textfield',
        '#title'         => t('Job apply url'),
        '#size'          => 60,
        '#maxlength'     => 255,
        '#default_value' => $id ? $job->url : ''
    );

    $job_types = array();
    foreach (organization_manager_job_types_get_data() as $item) {
        $job_types[$item->id] = $item->title;
    }

    $industry_types = array();
    foreach (organization_manager_job_industries_get_data() as $item) {
        $industry_types[$item->id] = $item->title;
    }

    $locations = array();
    foreach (organization_manager_locations_get_data() as $item) {
        $locations[$item->id] = $item->title;
    }

    $form['industry_types'] = array(
        '#title'         => 'Industry Types',
        '#type'          => 'select',
        '#options'       => $industry_types,
        '#multiple'      => TRUE,
        '#attributes'    => array(
            'class' => array('select2'),
            'style' => 'width:400px;'
        ),
        '#default_value' => $id ? $orgIndustries : array()
    );
    $form['job_types']      = array(
        '#title'         => 'Job Types',
        '#type'          => 'select',
        '#options'       => $job_types,
        '#multiple'      => TRUE,
        '#attributes'    => array(
            'class' => array('select2'),
            'style' => 'width:400px;'
        ),
        '#default_value' => $id ? $orgTypes : array()
    );

    $form['locations'] = array(
        '#title'         => 'Locations',
        '#type'          => 'select',
        '#options'       => $locations,
        '#multiple'      => TRUE,
        '#attributes'    => array(
            'class' => array('select2'),
            'style' => 'width:400px;'
        ),
        '#default_value' => $id ? $orgLocations : array()
    );


    $form['save'] = array(
        '#type'  => 'submit',
        '#value' => 'save'
    );

    return $form;
}

/**
 * Add & Edit form for Organization Jobs
 */
function organization_manager_job_addEditForm($orgId, $id = 0)
{
    if (isset($_POST['op'])) {
        organization_manager_job_edit_submit($_POST);
    }
    drupal_add_css(drupal_get_path('module', 'organization_manager') . '/css/select2.css');
    drupal_add_css(drupal_get_path('module', 'organization_manager') . '/css/organization_manager.css');

    drupal_add_js('/sites/all/libraries/tinymce/jscripts/tiny_mce/tiny_mce.js', 'external');
    drupal_add_js(drupal_get_path('module', 'organization_manager') . '/js/select2.min.js');
    drupal_add_js(drupal_get_path('module', 'organization_manager') . '/js/underscore-min.js');
    drupal_add_js(drupal_get_path('module', 'organization_manager') . '/js/backbone-min.js');
    drupal_add_js(drupal_get_path('module', 'organization_manager') . '/js/organization_manager.js');

    $job = new stdClass();
    $job->id          = 0;
    $job->title       = '';
    $job->description = '';
    $job->url         = '';
    $orgIndustries    = array();
    $orgTypes         = array();
    $locations        = array();
    
    if($id){
        $job = db_select('zd_jobs', 'o')
            ->fields('o', array('id', 'organizationId', 'title', 'description', 'url'))
            ->condition('id', $id)
            ->execute()
            ->fetch();

        $orgIndustriesData = db_select('zd_jobs_industries', 'i')
            ->fields('i', array('industryId'))
            ->condition('jobId', $id)
            ->execute()
            ->fetchAll();
        $orgIndustries     = array();
        foreach ($orgIndustriesData as $item)
            $orgIndustries[]   = $item->industryId;

        $orgTypesData = db_select('zd_jobs_job_types', 't')
            ->fields('t', array('typeId'))
            ->condition('jobId', $id)
            ->execute()
            ->fetchAll();
        $orgTypes     = array();
        foreach ($orgTypesData as $item)
            $orgTypes[]   = $item->typeId;

        $query = db_select('zd_jobs_locations', 'l');
        $query->fields('l', array('countryId', 'stateId', 'cityId'));
        $locations = $query->condition('l.jobId', $id)
            ->execute()
            ->fetchAll();
    }

    if (!is_numeric($orgId)) {
        $orgId = $job->organizationId;
    }
    
    $countries = _ajax_organization_manager_getCountriesOptions(true);
    $states    = _ajax_organization_manager_getStatesOptions($countries[0]->id);
    $cities    = _ajax_organization_manager_getCitiesOptions($states[0]->id);

    $variables = array(
        'job'            => $job,
        'orgId'          => $orgId,
        'orgIndustries'  => $orgIndustries,
        'orgTypes'       => $orgTypes,
        'locations'      => $locations,
        'countries'      => $countries,
        'states'         => $states,
        'cities'         => $cities,
        'industry_types' => organization_manager_job_industries_get_data(),
        'job_types'      => organization_manager_job_types_get_data(true),
    );
    return theme('organization_manager_edit_organization_job', $variables);
}

function organization_manager_job_edit_submit($val)
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
        'title'          => $val['title'],
        'organizationId' => $val['organizationId'],
        'description'    => $val['description'],
        'url'            => $val['url'],
        'updated'        => date('Y-m-d h:i:s'),
    );

    $status = db_merge('zd_jobs')
        ->key(array('id' => $val['id'] ? $val['id'] : null))
        ->fields($fields)
        ->execute();

    if ($status == MergeQuery::STATUS_INSERT) {
        $lastId = db_query("SELECT LAST_INSERT_ID()")->fetchField();
    } else {
        $lastId = $val['id'];
    }

    if ($val['id'] && $lastId) {
        db_delete('zd_jobs_locations')
            ->condition('jobId', $lastId)
            ->execute();
        db_delete('zd_jobs_job_types')
            ->condition('jobId', $lastId)
            ->execute();
        db_delete('zd_jobs_industries')
            ->condition('jobId', $lastId)
            ->execute();
    }

    if (sizeof($val['location'])) {
        $query = db_insert('zd_jobs_locations')->fields(array('jobId', 'countryId', 'stateId', 'cityId'));
        foreach ($val['location'] as $v){
            $query->values(
                array(
                    'jobId'     => $lastId,
                    'countryId' => $v->countryId,
                    'stateId'   => $v->stateId,
                    'cityId'    => $v->cityId,
                )
            );
            
            $itemExists = db_query("SELECT count(*) FROM zd_org_loc WHERE organizationId = {$fields['organizationId']} AND countryId = {$v->countryId} AND stateId = {$v->stateId} AND cityId = {$v->cityId}")->fetchField();
            if(!$itemExists){
                db_insert('zd_org_loc')
                    ->fields(
                        array(
                            'organizationId' => $fields['organizationId'],
                            'countryId'      => $v->countryId,
                            'stateId'        => $v->stateId,
                            'cityId'         => $v->cityId,
                        )
                    )
                    ->execute();
            }
        }
        $query->execute();
    }

    if (sizeof($val['industry_types'])) {
        $query = db_insert('zd_jobs_industries')->fields(array('jobId', 'industryId'));
        foreach ($val['industry_types'] as $v){
            $query->values(
                array(
                    'jobId'      => $lastId,
                    'industryId' => $v
                )
            );
            $itemExists = db_query("SELECT count(*) FROM zd_org_industries WHERE organizationId = {$fields['organizationId']} AND industryId = {$v}")->fetchField();
            if(!$itemExists){
                db_query("INSERT INTO zd_org_industries (organizationId, industryId) VALUES ({$fields['organizationId']}, {$v})")->execute();
            }
        }
        $query->execute();
    }

    if (sizeof($val['job_types'])) {
        $query = db_insert('zd_jobs_job_types')->fields(array('jobId', 'typeId'));
        foreach ($val['job_types'] as $v){
            $query->values(
                array(
                    'jobId'  => $lastId,
                    'typeId' => $v
                )
            );
            $itemExists = db_query("SELECT count(*) FROM zd_org_job_types WHERE organizationId = {$fields['organizationId']} AND typeId = {$v}")->fetchField();
            if(!$itemExists){
                db_query("INSERT INTO zd_org_job_types (organizationId, typeId) VALUES ({$fields['organizationId']}, {$v})")->execute();
            }
        }
        $query->execute();
    }

    drupal_goto('admin/organization-manager/organization/'.$fields['organizationId'].'/jobs');
}

function organization_manager_job_delete()
{
    $id = intval(arg(4));
    $organizationId = db_query("SELECT organizationId FROM zd_jobs WHERE id = '{$id}'")->fetchField();
    db_delete('zd_jobs')
        ->condition('id', $id)
        ->execute();
    
    drupal_goto("admin/organization-manager/organization/{$organizationId}/jobs");
}
