<?php

    /*
     *Show job details classified by the job itself
     */
    function organization_manager_jobs() {  
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
            '#attributes'=>variable_get('location')?array('placeholder' => variable_get('location')):array(),
            '#name' => 'location',
            '#size' => 35,           
            );

        $form['filters']['fieldset']['organization'] = array (
            '#type' => 'textfield',
            '#title' => t('Organization filter'),
            '#attributes'=>variable_get('organization')?array('placeholder' => variable_get('organization')):array(),
            '#name' => 'organization',
            '#size' => 35,           
            );

        $form['filters']['fieldset']['tag'] = array (
            '#type' => 'textfield',
            '#title' => t('Tag filter'),
            '#attributes'=>variable_get('tag')?array('placeholder' => variable_get('tag')):array(),
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
            array('data' => 'Title', 'field' => 'title'),
            array('data' => 'Snippet', 'field' => 'snippet'),
            array('data' => 'Url', 'field' => 'url'),
            array('data' => 'Url Status', 'field' => 'url_status'),
            array('data' => 'Organization', 'field' => 'org_name'),
            array('data' => 'City', 'field' => 'city'),
            array('data' => 'District', 'field' => 'district'),
            array('data' => 'Country', 'field' => 'country'),
            array('data' => 'Created On', 'field' => 'date_created'),
            array('data' => 'Expired On', 'field' => 'date_expired'),
            array('data' => 'Counter 1', 'field' => 'counter_1'),
            array('data' => 'Counter 2', 'field' => 'counter_2'), 
            array('data' => 'Delete Flag', 'field' => 'delete_flag'),
            array('data' => t('Operations'), 'colspan' => 2),
        );

        $query = db_select('zd_dev_jobs', 'j');
        $query -> leftjoin('zd_dev_organizations', 'o', 'j.Org_id = o.ID');
        $query -> join('zd_dev_location_city', 'c', 'j.City_id = c.ID');
        $query -> join('zd_dev_location_district', 'd', 'j.District_id = d.ID');
        $query -> join('zd_dev_location_country', 't', 'j.Country_id = t.ID');
        $query -> fields('j', array('ID', 'Title', 'Snippet', 'Url', 'Url_status'));
        $query -> fields('o', array('Name'));
        $query -> fields('c', array('Name'));
        $query -> fields('d', array('Name'));
        $query -> fields('t', array('Name'));
        $query -> fields('j', array('Created_on', 'Expired_on','Counter_1', 'Counter_2', 'Delete_flag'));

        // Apply the filter for the sql query
        if(variable_get('location') != "") {
            $or = db_or()
                -> condition('c.Name', '%'.db_like(variable_get('location')).'%', 'LIKE')
                -> condition('d.Name', '%'.db_like(variable_get('location')).'%', 'LIKE')
                -> condition('t.Name', '%'.db_like(variable_get('location')).'%', 'LIKE');
            $query -> condition($or);
        }

        if(variable_get('organization') != "") {
            $query -> condition('o.Name', '%'.db_like(variable_get('organization')).'%', 'LIKE');
        }

        if(variable_get('tag') != "") {
            $query -> join('zd_dev_jobs_tags', 's', 'j.ID = s.ID');
            $query -> condition('s.Tag', '%'.db_like(variable_get('tag')).'%', 'LIKE');
        }

        if(arg(3) != null) {
            $query -> condition('o.ID', arg(3));
        }

        $query = $query
            ->extend('TableSort')
            ->orderByHeader($header)
            ->extend('PagerDefault')
            ->limit(10);
        $result = $query->execute();
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
                $item->c_Name,
                $item->d_Name,
                $item->t_Name,
                $item->Created_on,
                $item->Expired_on,
                $item->Counter_1,
                $item->Counter_2,
                $status = $item->Delete_flag ? "Deleted" : "Undeleted",
                l(t('Edit'), 'admin/organization-manager/jobs/edit/'. $item->ID,array('query' => drupal_get_destination())),
                l(t('Change Flag'), 'admin/organization-manager/jobs/flag-delete/' . $item->ID . '/' . $item->Delete_flag, array(
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
    function organization_manager_jobs_edit($id = 0) {
        if (isset($_POST['op'])) {
            organization_manager_job_edit_submit($_POST);
        }

        drupal_add_css(drupal_get_path('module', 'organization_manager') . '/css/select2.css');
        drupal_add_css(drupal_get_path('module', 'organization_manager') . '/css/organization_manager.css');

        drupal_add_js(drupal_get_path('module', 'organization_manager') . '/js/select2.min.js');
        drupal_add_js(drupal_get_path('module', 'organization_manager') . '/js/underscore-min.js');
        drupal_add_js(drupal_get_path('module', 'organization_manager') . '/js/backbone-min.js');
        drupal_add_js(drupal_get_path('module', 'organization_manager') . '/js/organization_manager.js');

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
        $job->district         = '';
        $job->country          = '';
        $job->weight           = 0;
        $job->job_tags         = '';
        
        if($id) {
            $job_query = db_select('zd_dev_jobs', 'j');
            $job_query -> leftJoin('zd_dev_jobs_tags', 't', 'j.ID = t.ID');
            $job_query -> join('zd_dev_location_city', 'c', 'j.City_id = c.ID');
            $job_query -> join('zd_dev_location_district', 'd', 'j.District_id = d.ID');
            $job_query -> join('zd_dev_location_country', 'cc', 'j.Country_id = cc.ID');
            $job_query -> fields('j', array('ID', 'Title', 'Url', 'Url_status', 'Org_id', 'Job_weight', 'Created_on', 'Expired_on', 'Updated_on', 'Snippet'));
            $job_query -> fields('t', array('Tag'));
            $job_query -> fields('c', array('Name'));
            $job_query -> fields('d', array('Name', 'Alias'));
            $job_query -> fields('cc', array('Name'));
            $job_query -> condition('j.ID', $id);
            $job_query -> addExpression('GROUP_CONCAT(DISTINCT Tag)', 'Tag_list');
            $job_query -> groupBy('j.ID');
            $job_result = $job_query -> execute();

            foreach($job_result as $item) {
                $job->job_id = $item->ID;
                $job->job_title = $item->Title;
                $job->job_tags = $item->Tag_list;
                $job->job_url = $item->Url;
                $job->job_url_status = $item->Url_status;
                $job->org_id = $item->Org_id;
                $job->job_snippet = $item->Snippet;
                $job->weight = $item->Job_weight;
                $job->date_created = $item->Created_on;
                $job->date_updated = $item->Updated_on;
                $job->date_expired = $item->Expired_on;
                $job->city = $item->Name;
                if($item->Alias) {
                    $job->district = $item->d_Name.', '.$item->Alias;
                } else {
                    $job->district = $item->d_name;
                }
                $job->country = $item->cc_Name;
            }

            $org_query = db_select('zd_dev_organizations', 'o');
            $org_query -> leftJoin('zd_dev_organizations_tags', 't', 'o.ID = t.ID');
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
            'district'      => $job->district,
            'country'       => $job->country,
            );

        return theme('organization_manager_edit_job', $variables);
    }

    /*
     * Apply the filter by button
     */
    function organization_manager_organizations_list_filters_submit($form) {
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
    function organization_manager_job_edit_submit($var) {  
        $org_fields = array(
            'ID'        => $var['org-id'],
            'Name'      => $var['org-name'],
            'Url'       => $var['org-url'],
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
            'Expired_on'    => $var['date-expired'],  
            'Updated_on'    => date("Y-m-d"),
            'City_id'       => 0,
            'District_id'   => 0,
            'Country_id'    => 0,
            );

        $job_tags = array(
            'ID'        => $var['job-id'],
            'Tag'           => explode(",", $var['job-tags']),
            );

        $location = array(
            'City'          => $var['city'],
            'District'      => $var['district'],
            'Country'       => $var['country'],
            );

        if($var['city'] == "" && $var['district'] == "" && $var['country'] == "") {
            var_dump('WTF!!!');   
        }

        $loc_query = db_select('zd_dev_location_city', 'c')
            ->fields('c', array('ID'))
            ->condition('Name', $location['City'])
            ->execute();
        $num = $loc_query->rowCount();
        if($num == 1) {
            $job_fields['City_id'] = $loc_query->fetchField();
        } 
        if($num == 0) {
            $insert = db_insert('zd_dev_location_city')
                        ->fields(array('Name' => $var['city'],))
                        ->execute();
            $job_fields['City_id'] = db_query("SELECT LAST_INSERT_ID()")->fetchField();
        }

        $or = db_or()
            ->condition('Name', '%'.db_like($location['District']).'%', 'LIKE')
            ->condition('Alias', '%'.db_like($location['District']).'%', 'LIKE');
        $loc_query = db_select('zd_dev_location_district', 'd')
            ->fields('d', array('ID'))
            ->condition($or)
            ->execute();
        $num = $loc_query -> rowCount();
        if($num == 1) {
            $job_fields['District_id'] = $loc_query -> fetchField();
        } 
        if($num == 0) {
            $insert = db_insert('zd_dev_location_district')
                -> fields(array(
                    'Name' => $location['District'],))
                -> execute();
            $job_fields['District_id'] = db_query("SELECT LAST_INSERT_ID()")->fetchField(); 
        }

        $loc_query = db_select('zd_dev_location_country', 'c')
            ->fields('c', array('ID'))
            ->condition('Name', $location['Country'])
            ->execute();
        $num = $loc_query->rowCount();
        if($num == 1) {
            $job_fields['Country_id'] = $loc_query->fetchField();
        } 
        if($num == 0) {
            $insert = db_insert('zd_dev_location_country')
                        ->fields(array('Name' => $var['country'],))
                        ->execute();
            $job_fields['Country_id'] = db_query("SELECT LAST_INSERT_ID()")->fetchField();
        }

        $org_status = db_merge('zd_dev_organizations')
            ->key(array('ID' => $var['org-id']?$var['org-id']:null))
            ->fields($org_fields)
            ->execute();
        if($org_status == MergeQuery::STATUS_INSERT) {
            $job_fields['org_id'] = db_query("SELECT LAST_INSERT_ID()")->fetchField();
        } 
        if($num == 0) {
            $job_fields['org_id'] = $var['org-id'];
        }

        $org_query = db_delete('zd_dev_organizations_tags')
            ->condition('ID', $org_tags['ID'])
            ->execute();
        $org_query = db_insert('zd_dev_organizations_tags')
            ->fields(array('ID', 'Tag'));
        foreach ($org_tags['Tag'] as $t) {
            $org_query->values(array($org_tags['ID'], $t));
        }
        $org_query->execute();

        $job_status = db_merge('zd_dev_jobs')
            ->key(array('ID' => $var['job-id']?$var['job-id']:null))
            ->fields($job_fields)
            ->execute();
        if($job_status == MergeQuery::STATUS_INSERT) {
            $last_id = db_query("SELECT LAST_INSERT_ID()")->fetchField();
        } 
        if($num == 0) {
            $last_id = $var['job-id'];
        }

        $job_query = db_delete('zd_dev_jobs_tags')
            ->condition('ID', $job_tags['ID'])
            ->execute();
        $job_query = db_insert('zd_dev_jobs_tags')
            ->fields(array('ID', 'Tag'));
        foreach ($job_tags['Tag'] as $t) {
            $job_query->values(array($job_tags['ID'], $t));
        }
        $job_query->execute();

        // drupal_goto();
    }


//     drupal_goto('admin/organization-manager/organization/'.$fields['organizationId'].'/jobs');

?>
