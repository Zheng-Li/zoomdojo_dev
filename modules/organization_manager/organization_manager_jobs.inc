<?php

    /*
     *Show job details classified by the job itself
     */
    function organization_manager_jobs() {  # Done
        if(isset($_POST['op']) && $_POST['op'] == 'Apply the filters'){
            organization_manager_organizations_list_filters_submit($_POST);
        }

        //Building the structure of the form
        $form['filters'] = array(
            '#type'   => 'form',
            );
    
        $form['filters']['fieldset'] = array(
            '#type'   => 'fieldset',
            '#collapsible'=>TRUE,
            '#collapsed'=>TRUE,
            '#title' => t('Filters'),
            );

        $form['filters']['fieldset']['location'] = array (
            '#type' => 'textfield',
            '#title' => t('Location filter'),
            '#attributes'=>variable_get('location')?array('placeholder' => variable_get('location')):array('placeholder' => 'Any location name...'),
            '#name' => 'location',
            '#size' => 35,           
            );

        $form['filters']['fieldset']['organization'] = array (
            '#type' => 'textfield',
            '#title' => t('Organization Name Filter'),
            '#attributes'=>variable_get('organization')?array('placeholder' => variable_get('organization')):array('placeholder' => 'Any organization name...'),
            '#name' => 'organization',
            '#size' => 35,           
            );

        $form['filters']['fieldset']['tag'] = array (
            '#type' => 'textfield',
            '#title' => t('Job/Organization Tag Filter'),
            '#attributes'=>variable_get('tag')?array('placeholder' => variable_get('tag')):array('placeholder' => 'Any tags for job or organization...'),
            '#name' => 'tag',
            '#size' => 35,           
            );

        $form['filters']['fieldset']['submit'] = array( 
            '#type' => 'submit', 
            '#value' => 'Apply the filters', 
            '#submit' => array('apply_filter'), 
            );

        //Fetch the content of the form
        $header = array(
            array('data' => 'ID', 'field' => 'id'),
            array('data' => 'Job Title', 'field' => 'title'),
            array('data' => 'Job Snippet', 'field' => 'snippet'),
            array('data' => 'Job Url', 'field' => 'url'),
            array('data' => 'Url Status (read only)', 'field' => 'url_status'),
            array('data' => 'Organization Name (read only)', 'field' => 'name'),
            array('data' => 'Created On (read only)', 'field' => 'created_on'),
            array('data' => 'Expired On (read only)', 'field' => 'expired_on'),
            array('data' => 'City', 'field' => 'city'),
            array('data' => 'State', 'field' => 'state'),
            array('data' => 'Country', 'field' => 'country'),
            array('data' => 'Counter 1', 'field' => 'counter_1'),
            array('data' => 'Counter 2', 'field' => 'counter_2'), 
            array('data' => 'Delete Flag', 'field' => 'delete_flag'),
            array('data' => t('Operations'), 'colspan' => 2),
        );

        $query = db_select('zd_new_job', 'j');
        $query -> leftjoin('zd_new_organization', 'o', 'j.Org_id = o.ID');
        // ------------------------- NOT IN USE ---------------------------
        // $query -> join('zd_dev_location_city', 'c', 'j.City_id = c.ID');
        // $query -> join('zd_dev_location_district', 'd', 'j.District_id = d.ID');
        // $query -> join('zd_dev_location_country', 't', 'j.Country_id = t.ID');
        // ------------------------- NOT IN USE ---------------------------
        $query -> join('zd_new_location', 'l', 'j.Loc_id = l.ID');
        $query -> fields('j', array('ID', 'Title', 'Snippet', 'Url', 'Url_status'));
        $query -> fields('o', array('Name'));
        // ------------------------- NOT IN USE ---------------------------
        // $query -> fields('c', array('Name'));
        // $query -> fields('d', array('Name'));
        // $query -> fields('t', array('Name'));
        // ------------------------- NOT IN USE ---------------------------
        $query -> fields('l', array('City', 'State', 'Country'));
        $query -> fields('j', array('Created_on', 'Expired_on','Counter_1', 'Counter_2', 'Delete_flag'));

        // Apply the filter for the sql query
        if(variable_get('location') != "") {
            $or = db_or()
                -> condition('City', '%'.db_like(variable_get('location')).'%', 'LIKE')
                -> condition('State', '%'.db_like(variable_get('location')).'%', 'LIKE')
                -> condition('Country', '%'.db_like(variable_get('location')).'%', 'LIKE');
            $query -> condition($or);
        }

        if(variable_get('organization') != "") {
            $query -> condition('Name', '%'.db_like(variable_get('organization')).'%', 'LIKE');
        }

        // +++++++++++++++++++ Tag table disabled +++++++++++++++++++
        // if(variable_get('tag') != "") {
        //     $query -> join('zd_new_job_tag', 'jt', 'j.ID = jt.ID');
        //     $query -> join('zd_new_organization_tag', 'ot', 'o.ID = ot.ID');
        //     $or = db_or()
        //         -> condition('jt.Tag', '%'.db_like(variable_get('tag')).'%', 'LIKE')
        //         -> condition('ot.Tag', '%'.db_like(variable_get('tag')).'%', 'LIKE');
        //     $query -> condition($or);
        // }

        // Alternative
            if(variable_get('tag') != "") {
                $query -> join('zd_new_organization_tag', 'ot', 'o.ID = ot.ID');
                $or = db_or()
                    -> condition('j.tags', '%'.db_like(variable_get('tag')).'%', 'LIKE')
                    -> condition('ot.Tag', '%'.db_like(variable_get('tag')).'%', 'LIKE');
                $query -> condition($or);
            }
        // +++++++++++++++++++ Tag table disabled +++++++++++++++++++

        if(arg(3) != null) {
            $query -> condition('o.ID', arg(3));
        }

        $query = $query
            ->extend('TableSort')
            ->orderByHeader($header)
            ->extend('PagerDefault')
            ->limit(10);
        $result = $query->distinct()->execute();
        $deleteText = array(
            'Undeleted' => 'Are you sure you want to delete this record?',
            'Deleted' => 'Are you sure you want to undelete this row?',
        );
        $rows = array();
        foreach ($result as $item) {
            $rows[] = array(
                $item->ID,
                $item->Title,
                strlen($item->Snippet) > 50 ? substr($item->Snippet,0,20)."..." : $item->Snippet,
                strlen($item->Url) > 25 ? substr($item->Url,0,16)."..." : $item->Url,
                $item->Url_status,
                $item->Name,
                $item->Created_on,
                $item->Expired_on,
                $item->City,
                $item->State,
                $item->Country,
                $item->Counter_1,
                $item->Counter_2,
                $status = $item->Delete_flag ? "Deleted" : "Undeleted",
                l(t('Edit'), 'admin/organization-manager/job/edit/'. $item->ID,array('query' => drupal_get_destination())),
                l(t('Change Flag'), 'admin/organization-manager/job/flag-delete/' . $item->ID . '/' . $item->Delete_flag, array(
                    'attributes' => array(
                        'onClick' => 'if (!confirm("'.$deleteText[$status].'")) {return false;}'
                    ))
                ),
            );
        }

        $form['pager_top'] = array(
            '#theme' => 'pager',
            '#weight' => 1,
        );

        $form['job_urls'] = array(
            '#theme' => 'table',
            '#header' => $header,
            '#rows' => $rows,
            '#weight' => 2,
            '#empty' => t('No matching result in the database.'),
        );

        $form['pager_bottom'] = array(
            '#theme' => 'pager',
            '#weight' => 3,
        );

        // $form['actions']           = array('#type' => 'actions');
        // $form['actions']['submit'] = array('#type'  => 'submit', '#value' => t('Save Changes'));
        return $form;
    }

    /*
     * Job editing page with pre-defined organization
     */
    function organization_manager_job_edit($id = 0) { # Done
        if (isset($_POST['op'])) {
            organization_manager_job_edit_submit($_POST);
        }

        drupal_add_css(drupal_get_path('module', 'organization_manager') . '/css/select2.css');
        drupal_add_css(drupal_get_path('module', 'organization_manager') . '/css/organization_manager.css');

        drupal_add_js(drupal_get_path('module', 'organization_manager') . '/js/select2.min.js');
        drupal_add_js(drupal_get_path('module', 'organization_manager') . '/js/underscore-min.js');
        drupal_add_js(drupal_get_path('module', 'organization_manager') . '/js/backbone-min.js');
        drupal_add_js(drupal_get_path('module', 'organization_manager') . '/js/organization_manager.js');
        drupal_add_js(drupal_get_path('module', 'organization_manager') . '/js/character-count.js');

        $job = new stdClass();
        $job->org_id           = 0;
        $job->org_name         = '';
        $job->org_url          = '';
        $job->org_tags         = '';
        $job->job_id           = 0;
        $job->job_title        = '';
        $job->job_snippet      = '';
        $job->job_url          = '';
        $job->job_url_status   = 200;
        $job->date_created     = '';
        $job->date_expired     = '';
        $job->city             = '';
        $job->state            = '';
        $job->country          = '';
        $job->weight           = 0;
        $job->job_tags         = '';
        
        if($id) {
            // ------------------- NOT IN USE ----------------------
            // $job_query -> join('zd_dev_location_city', 'c', 'j.City_id = c.ID');
            // $job_query -> join('zd_dev_location_district', 'd', 'j.District_id = d.ID');
            // $job_query -> join('zd_dev_location_country', 'cc', 'j.Country_id = cc.ID');
            // $job_query -> fields('c', array('Name'));
            // $job_query -> fields('d', array('Name', 'Alias'));
            // $job_query -> fields('cc', array('Name'));
            // ------------------- NOT IN USE ----------------------
            $job_query = db_select('zd_new_job', 'j');

            // +++++++++++++++++++ Tag table disabled +++++++++++++++++++
            // $job_query -> leftJoin('zd_new_job_tag', 't', 'j.ID = t.ID');
            // $job_query -> fields('t', array('Tag'));
            // $job_query -> addExpression('GROUP_CONCAT(DISTINCT Tag)', 'Tag_list');

            $job_query -> join('zd_new_location', 'l', 'j.Loc_id = l.ID');
            $job_query -> fields('j', array('ID', 'Title', 'Url', 'Url_status', 'Org_id', 'Job_weight', 'Created_on', 'Expired_on', 'Updated_on', 'Snippet', 'tags'));
            $job_query -> fields('l', array('City', 'State', 'Country'));
            $job_query -> condition('j.ID', $id);
            $job_query -> groupBy('j.ID');
            $job_result = $job_query -> execute();
            // +++++++++++++++++++ Tag table disabled +++++++++++++++++++

            foreach($job_result as $item) {
                $job->job_id = $item->ID;
                $job->job_title = $item->Title;

                // +++++++++++++++++++ Tag table disabled +++++++++++++++++++
                // $job->job_tags = $item->Tag_list;
                $job ->job_tags = $item->tags; // Alternative 
                // +++++++++++++++++++ Tag table disabled +++++++++++++++++++

                $job->job_url = $item->Url;
                $job->job_url_status = $item->Url_status;
                $job->org_id = $item->Org_id;
                $job->job_snippet = $item->Snippet;
                $job->weight = $item->Job_weight;
                $job->date_created = $item->Created_on;
                $job->date_updated = date('Y-m-d', strtotime($item->Updated_on));
                $job->date_expired = $item->Expired_on;
                $job->city = $item->City;
                $job->state = $item->State;
                $job->country = $item->Country;
            }

            $org_query = db_select('zd_new_organization', 'o');
            $org_query -> leftJoin('zd_new_organization_tag', 't', 'o.ID = t.ID');
            $org_query -> fields('o', array('ID', 'Name', 'Url'));
            $org_query -> fields('t', array('Tag'));
            $org_query -> condition('o.ID', $job->org_id);
            $org_query -> addExpression('GROUP_CONCAT(DISTINCT Tag)', 'Tag_list');
            $org_query -> groupBy('o.ID');
            $org_result = $org_query -> execute();

            foreach ($org_result as $item) {
                $job->org_name = $item->Name;
                $job->org_url = $item->Url;
                $job->org_tags = $item->Tag_list;
            }
        }

        $variables = array(
            'org_id'        => $job->org_id,
            'org_name'      => $job->org_name,
            'org_url'       => $job->org_url,
            'org_tags'      => $job->org_tags,
            'job_id'        => $job->job_id,
            'job_title'     => $job->job_title,
            'job_tags'      => $job->job_tags,
            'job_url'       => $job->job_url,
            'job_url_status'=> $job->job_url_status,
            'job_snippet'   => $job->job_snippet,
            'date_created'  => $job->date_created,
            'date_expired'  => $job->date_expired,
            'date_updated'  => $job->date_updated,
            'weight'        => $job->weight,
            'city'          => $job->city,
            'state'         => $job->state,
            'country'       => $job->country,
            );

        return theme('organization_manager_edit_job', $variables);
    }

    /*
     * Apply the filter by button
     */
    function organization_manager_organizations_list_filters_submit($form) { # Done
        variable_set($form['location'], '');
        variable_set($form['organization'], '');
        variable_set($form['tag'], '');
        // Apply the filter for the sql query
        if(isset($form['location'])) {
            variable_set('location', $form['location']);
        }
        if(isset($form['organization'])) {
            variable_set('organization', $form['organization']);
        }
        if(isset($form['tag'])) {
            variable_set('tag', $form['tag']);
        }

        drupal_goto($_SERVER['HTTP_REFERER']);
    }

    /*
     * Adding or Editing job with pre-defined organization
     */
    function organization_manager_job_edit_submit($var) {  # Done
        $org_fields = array(
            'ID'        => $var['org-id'],
            'Name'      => $var['org-name'],
            );

        $org_tags = array(
            'ID'        => $var['org-id'],
            'Tag'           => explode(",", $var['org-tags']),       
            );

        $job_fields = array(
            'ID'            => $var['job-id'],
            'Org_id'        => $var['org-id'],
            'Title'         => $var['job-title'],
            'Job_weight'    => $var['job-weight'],
            'Url'           => $var['job-url'],
            'Url_status'    => $var['url-status'],
            'Snippet'       => $var['job-snippet'],
            'Created_on'    => $var['date-created'],
            'Expired_on'    => $var['date-expired']?$var['date-expired']:date('Y-m-d', strtotime("+2 months")), # Defualt expire date is 2 month from now
            'Loc_id'        => 0,
            // +++++++++++++++++++ Tag table disabled +++++++++++++++++++
            'tags'          => $var['job-tags'],
            // +++++++++++++++++++ Tag table disabled +++++++++++++++++++

            //------- NOT IN USE ----------
            // 'Updated_on'    => date("Y-m-d"),
            // 'City_id'       => 0,
            // 'District_id'   => 0,
            // 'Country_id'    => 0,
            //------- NOT IN USE ----------
            );

        // +++++++++++++++++++ Tag table disabled +++++++++++++++++++
        $job_tags = array(
            'ID'        => $var['job-id'],
            'Tag'       => explode(",", $var['job-tags']),
            );
        // +++++++++++++++++++ Tag table disabled +++++++++++++++++++

        $location_fields = array(
            'City'       => $var['city'],
            'State'      => $var['state'],
            'Country'    => $var['country']?$var['country']:'USA',
            );

        // -------------------- NOT IN USE -------------------------- 
        // $loc_query = db_select('zd_dev_location_city', 'c')
        //     ->fields('c', array('ID'))
        //     ->condition('Name', $location['City'])
        //     ->execute();
        // $num = $loc_query->rowCount();
        // if($num == 1) {
        //     $job_fields['City_id'] = $loc_query->fetchField();
        // } 
        // if($num == 0) {
        //     $insert = db_insert('zd_dev_location_city')
        //                 ->fields(array('Name' => $var['city'],))
        //                 ->execute();
        //     $job_fields['City_id'] = db_query("SELECT LAST_INSERT_ID()")->fetchField();
        // }

        // $or = db_or()
        //     ->condition('Name', '%'.db_like($location['District']).'%', 'LIKE')
        //     ->condition('Alias', '%'.db_like($location['District']).'%', 'LIKE');
        // $loc_query = db_select('zd_dev_location_district', 'd')
        //     ->fields('d', array('ID'))
        //     ->condition($or)
        //     ->execute();
        // $num = $loc_query -> rowCount();
        // if($num == 1) {
        //     $job_fields['District_id'] = $loc_query -> fetchField();
        // } 
        // if($num == 0) {
        //     $insert = db_insert('zd_dev_location_district')
        //         -> fields(array(
        //             'Name' => $location['District'],))
        //         -> execute();
        //     $job_fields['District_id'] = db_query("SELECT LAST_INSERT_ID()")->fetchField(); 
        // }

        // $loc_query = db_select('zd_dev_location_country', 'c')
        //     ->fields('c', array('ID'))
        //     ->condition('Name', $location['Country'])
        //     ->execute();
        // $num = $loc_query->rowCount();
        // if($num == 1) {
        //     $job_fields['Country_id'] = $loc_query->fetchField();
        // } 
        // if($num == 0) {
        //     $insert = db_insert('zd_dev_location_country')
        //                 ->fields(array('Name' => $var['country'],))
        //                 ->execute();
        //     $job_fields['Country_id'] = db_query("SELECT LAST_INSERT_ID()")->fetchField();
        // }
        // -------------------- NOT IN USE -------------------------- 
        $or = db_or()
            ->condition('State', $location_fields['State'], 'LIKE')
            ->condition('Abbreviation', $location_fields['State'], 'LIKE');
        $loc_query = db_select ('zd_new_location', 'l')
            ->fields('l', array('ID'))
            ->condition('City', $location_fields['City'])
            ->condition('Country', $location_fields['Country'])
            ->condition($or)
            ->execute();
        $num = $loc_query->rowCount();
        if($num) {
            $job_fields['Loc_id'] = $loc_query->fetchField();
        } else {
            $insert = db_insert('zd_new_location')
                ->fields($location_fields)
                ->execute();
            $job_fields['Loc_id'] = db_query("SELECT LAST_INSERT_ID()")->fetchField();
        }

        $org_query = db_merge('zd_new_organization')
            ->key(array('ID' => $var['org-id']?$var['org-id']:null))
            ->fields($org_fields)
            ->execute();
        if($org_query == MergeQuery::STATUS_INSERT) {
            $job_fields['org_id'] = db_query("SELECT LAST_INSERT_ID()")->fetchField();
        } else {
            $job_fields['org_id'] = $var['org-id'];
        }

        $org_tag_query = db_delete('zd_new_organization_tag')
            ->condition('ID', $org_tags['ID'])
            ->execute();
        $org_tag_query = db_insert('zd_new_organization_tag')
            ->fields(array('ID', 'Tag'));
        foreach ($org_tags['Tag'] as $t) {
            $org_tag_query->values(array($org_tags['ID'], $t));
        }
        $org_tag_query->execute();

        $job_query = db_merge('zd_new_job')
            ->key(array('ID' => $var['job-id']?$var['job-id']:null))
            ->fields($job_fields)
            ->execute();
        if($job_query == MergeQuery::STATUS_INSERT) {
            $last_id = db_query("SELECT LAST_INSERT_ID()")->fetchField();
        } else {
            $last_id = $var['job-id'];
        }

        // +++++++++++++++++++ Tag table disabled +++++++++++++++++++
        $job_tag_query = db_delete('zd_new_job_tag')
            ->condition('ID', $job_tags['ID'])
            ->execute();
        $job_tag_query = db_insert('zd_new_job_tag')
            ->fields(array('ID', 'Tag'));
        foreach ($job_tags['Tag'] as $t) {
            $job_tag_query->values(array($job_tags['ID'], $t));
        }
        $job_tag_query->execute();
        // +++++++++++++++++++ Tag table disabled +++++++++++++++++++

        drupal_goto();
    }

    /*
     *Change delete flag of the job
     */
    function organization_manager_job_change_status($id, $status) { # Done
        $st = 0;
        if ($status == 0) {
            $st = 1;
        }
        db_update('zd_new_job')
            ->fields(array('Delete_flag' => $st))
            ->condition('id', $id)
            ->execute();

        drupal_goto($_SERVER['HTTP_REFERER']);
    }

?>
