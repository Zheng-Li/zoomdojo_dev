<?php
include_once 'organization_manager_find_jobs.inc';



/**
 * $items['find-positions'] get jobs from new database
 */
function organization_manager_positions()
{   
    
    global $user;
    drupal_add_css(drupal_get_path('module', 'organization_manager') . '/css/find-jobs.css');
    drupal_add_js(drupal_get_path('module', 'organization_manager')  . '/js/typeahead.min.js');
    drupal_add_js(drupal_get_path('module', 'organization_manager')  . '/js/find-position.js');
    drupal_add_js(drupal_get_path('module', 'organization_manager')  . '/js/position_popup.js');


    $variables = organization_manager_find_jobs_getPositionsData($_GET);
    $variables['path'] = drupal_get_path('module', 'organization_manager');
    $variables['user'] = $user;

    drupal_add_js(
        array(
        'location'      => $variables['location'],
        'page'          => $variables['currentPage'],
        'keywords'      => $variables['keywords'],
        'display'       => $variables['limit'],
        'requestedLimit'=> $variables['requestedLimit'],
        'requestedPage' => $variables['requestedPage'],
        'needLogIn'     => $variables['needLogIn'],
        ), 'setting'
    );

    return theme('organization_manager_positions', $variables);
}


/**
 * main function to get data from database
 */
function organization_manager_find_jobs_getPositionsData($get)
{
    
    global $user, $base_url;
    $dotted       = 3;
    $url          = array();
    $where        = array();
    $jobsWhere    = array();
    $join         = array();
    $jobsJoin     = array();
    $params       = array();
    $allJobString = array();
    $jobType      = 0;
    $limit        = $requested_limit = 5;
    $currentPage  = $requested_page  = 0;
    $needLogIn    = 0;
    $displayArray = array(5, 10, 20);
    
    if (!empty($get['display'])) {
        $limit = $get['display'];
    }
    if (!empty($get['page'])) {
        $currentPage = intval($get['page']);
    }

    if (!empty($get['keywords'])){
        $keywords = $get['keywords'];
    }

    if (!empty($get['location'])){
        $location  = trim($get['location']);
    }
    else{
        $location = "USA";
    }

    if ( !$user->uid && ($limit > 5 || $currentPage > 0)) {
        $requested_limit = $limit;
        $requested_page = $currentPage;
        $limit = 5;
        $currentPage = 0;
        $needLogIn = 1;
    }

    $url['keywords']     = $keywords;
    $url['location']     = $location;
    $url['display']      = $limit;

    if(!empty($get['type']) && $get['type'] == 'featured_tags'){
        $location = "";
        $fined_keywords =array();
        $fined_keywords[0] = $keywords;
    }

    else{
    $keyword_list = preg_split("/[\s,]+/", $keywords);
    $fined_keywords = organization_manager_find_jobs_keywordPreprocess($keyword_list);
        }

    $numOfKeywords = count($fined_keywords);

    if($numOfKeywords>0 and $numOfKeywords<4){

        /////keywords string process///////

        $params = array();    
        for($i=0;$i<$numOfKeywords;$i++){
            $tempName = ":kw".$i;
            $params[$tempName] = '%'.$fined_keywords[$i].'%';

        }

        $sql = "
            SELECT SQL_CALC_FOUND_ROWS distinct zdj.ID, Title, Snippet, zo.name
                FROM zd_dev_jobs AS zdj
                LEFT JOIN zd_dev_jobs_tags AS zdjt
                ON zdj.ID = zdjt.ID
                LEFT JOIN zd_organization AS zo
                ON zdj.Org_id = zo.id
                WHERE ( CONCAT(IFNULL(zdjt.Tag, zdj.Title),',',zdj.Title,',',zdj.Snippet,',',zo.name) like :kw0
        ";
        
        $sql_keyword = "";
        for($i=1;$i<$numOfKeywords;$i++){
            
            $tempKeyword = ":kw".$i;
            $sql_keyword=$sql_keyword." ";
            $sql_keyword = $sql_keyword."AND CONCAT(IFNULL(zdjt.Tag, zdj.Title),',',zdj.Title,',',zdj.Snippet,',',zo.name) like ".$tempKeyword;
        }

        $sql=$sql.$sql_keyword.")";

        ///location string process
        if($location != ""){
        
        $location_id_res = db_query('
            SELECT id 
            FROM zd_dev_location_city
            WHERE Name = :Name'
        , array(':Name' => $location))->fetchAll();

        $location_pos = ' City_id = ';

        if(empty($location_id_res)){
            $location_id_res = db_query('
            SELECT id 
            FROM zd_dev_location_district
            WHERE Name = :Name'
        , array(':Name' => $location))->fetchAll();
            $location_pos = ' District_id = ';
        }

        if(empty($location_id_res)){
            $location_id_res = db_query('
            SELECT id 
            FROM zd_dev_location_country
            WHERE Name = :Name'
        , array(':Name' => $location))->fetchAll();
            $location_pos = ' Country_id = ';
        }
        
        if(empty($location_id_res)){
            $loc_id = 0;
        }
        else{
        $loc_id = $location_id_res[0]->id;}

        $sql_loc = " AND ".$location_pos.$loc_id;

        $sql = $sql.$sql_loc;
        }
        
        //////location string process end///////////
        
        $sql_condition = " AND zdj.Status = '1'
                    AND (zdj.Url_status < '300' or  zdj.Url_status = '304')
                    ORDER BY Job_weight ASC, Created_on DESC";

        $sql=$sql.$sql_condition;
        
        $sql = $sql." LIMIT ". ($currentPage * $limit) . ", " . $limit;


        $results = db_query($sql,$params);

        $positions = array();
        
        foreach ($results as $record) {
            $record->encodeName = urlencode($record->Title);
            $record->Url = 'detailed-job-page/'.$record->ID;
            $positions[] = $record;
        }

    ///////////////////////////////////////////////////////////////
        $countRows = db_query('SELECT FOUND_ROWS();')->fetchField();

    /////////////process tags////////////////
        /*
        $sql_temp = str_replace("SELECT SQL_CALC_FOUND_ROWS distinct zdj.ID, Title, Snippet, Url, zo.name","SELECT distinct zdj.ID",$sql);

        $sql_temp = str_replace("ORDER BY Job_weight ASC, Created_on DESC","ORDER BY ID",$sql_temp);

        $sql_tags="select ID, tag 
                   from zd_dev_jobs_tags
                   where ID in ( ".$sql_temp." )";
       
        $results = db_query($sql_tags);

        $db_tags = array();

        foreach ($results as $key => $value) {
            echo $key.": ".$value;
        }
    */
    ///////////////////////////////////////////////////////////////
    }

    else{
        $positions = array();
        $countRows = 0;}

    if ($countRows < $limit) {
        $limit = $countRows;
    }

    $countPage = 0;
    if ($countRows > $limit) {
        $countPage = ceil($countRows / $limit);
    }
    

    $featuredJobs = false;

    if (!empty($get['type']) && $get['type'] == 'featured_tags') {
        $url = '/jobs-by-keywords/' . $get['urlAlias'] . '/page/';
        $featuredJobs = true;
    } else {
        $url = '/find-positions?' . http_build_query($url) . '&page=';
    }

    foreach ($allJobString as $key => $item) {
        if (empty($item)) {
            unset($allJobString[$key]);
        }
    }
    $userCanEdit = false;

    if ($router_item = menu_get_item('admin/organization-manager/organizations/edit/%')) {
      $userCanEdit = $router_item['access'];
    }

    return array(
        'positions'     => $positions,
        'limit'         => $limit,
        'countRows'     => $countRows,
        'countPage'     => $countPage,
        'currentPage'   => $currentPage,
        'url'           => $url,
        'dotted'        => $dotted,
        'location'      => $location,
        'keywords'      => $keywords,
        'featuredJobs'  => $featuredJobs,
        'home'          => $base_url,
        'displayArray'  => $displayArray,
        'userCanEdit'   => $userCanEdit,
        'requestedLimit'=> $requested_limit,
        'requestedPage' => $requested_page,
        'needLogIn'     => $needLogIn
    );
}

/*
function organization_manager_find_jobs_getDatabyKeyword($keyword){

    if($keyword == ""){
        $keyword = ".";
    }

    $params = array();

    //$params[':keyword'] = '%' . db_like($keyword) . '%';
    $params[':keyword'] = $keyword;
    print_r($keyword);

    $sqltest="select zd_position.id,jobTitle,url,snippet from zd_position where jobTitle REGEXP :keyword 
    or tags REGEXP :keyword or snippet REGEXP :keyword";

    $results = db_query($sqltest,$params);

    return $results;

}
*/


/**
 * preprocess the keywords
 */
function organization_manager_find_jobs_keywordPreprocess($keywords){
    
    $res = array();

    foreach ($keywords as $keyword) {
        if (trim($keyword) != ''){
        
        $res[] = trim($keyword);
        
        }
    }

    return $res;

}

/**
 *  $items['get-keywords'] data source for position typeahead
 */
function organization_manager_find_jobs_getPositions()
{
    ignore_user_abort(false);
    $response = array(
        'status' => 'ERROR',
        'data'   => 'No result',
    );
    if (!empty($_GET['keywords'])) {
        //$keywords = $_GET['keywords'];
        $params[':keyword'] = '%'.$_GET['keywords'].'%';
        
        $sql = "SELECT Tag as result
                FROM zd_dev_jobs_tags
                WHERE Tag like :keyword
                UNION
                SELECT Title as result
                FROM zd_dev_jobs
                WHERE Title like :keyword
        ";

        $results = db_query($sql,$params);
        $query = array();
        foreach ($results as $res) {
            $query[] = $res;
        }


        if (!empty($query)) {
            if (count($query) > 1) { //add you typed string into choice box
                //array_unshift($query, (object) array('result' => $keywords));
            }
            $response = array(
                'status' => 'OK',
                'data'   => $query,
            );
        }
    }

    print json_encode($response);
    exit();
}


/**
 * $items['get-location'] data source for location typeahead
 */
function organization_manager_find_jobs_getLocation()
{
    ignore_user_abort(false);
    $response = array(
        'status' => 'ERROR',
        'data'   => 'No result',
    );
    if (!empty($_GET['location'])) {
        $location = $_GET['location'];
        $query = db_select('zd_dev_location_city', 'zdlc');
        //$query->addField('zdlc', 'Name', 'locationName');
        $query = $query->fields('zdlc', array('Name'))
            ->condition('Name', '%' . db_like($location) . '%', 'LIKE');

        
        $query_district = db_select('zd_dev_location_district', 'zdld');
        $query_district = $query_district->fields('zdld', array('Name'))
            ->condition('Name', '%' . db_like($location) . '%', 'LIKE');

        $query->union($query_district, 'UNION');

        $query_country = db_select('zd_dev_location_country', 'zdlco');
        $query_country = $query_country->fields('zdlco', array('Name'))
            ->condition('Name', '%' . db_like($location) . '%', 'LIKE');

        $query->union($query_country, 'UNION');

        //$query->condition('zo.status', 1);
        $query = $query->range(0, 20)
            //->groupBy('zo.id')
            ->execute()
            ->fetchAll();

        //To be cleared

        if (!empty($query)) {
            /*
            if (count($query) > 1) { //add you typed string into choice box
                array_unshift($query, (object) array('Name' => $location));
            }
            */
            $response = array(
                'status' => 'OK',
                'data'   => $query,
            );
        }
    }

    print json_encode($response);
    exit();
}

/**
 * $items['jobs-by-keywords'] featured jobs by keywords
 */
function organization_manager_jobs_by_keywords()
{
    // seo
    drupal_add_html_head(array(
        '#tag' => 'meta',
        '#attributes' => array(
            'name' => 'description',
            'content' => "Zoomdojo's listings of the featured and new jobs and internships for young professionals",
        ),
    ), 'description');
    drupal_add_html_head(array(
        '#tag' => 'meta',
        '#attributes' => array(
            'name' => 'keywords',
            'content' => "internships, entry level jobs, seasonal jobs, seasonal work, best internships",
        ),
    ), 'keywords');

    drupal_add_css(drupal_get_path('module', 'organization_manager') . '/css/find-jobs.css');
    
    ////ting new query
    
    $new_limit = 3;
    $new_query = db_select('zd_job_tags', 'zjt');
    $new_query->leftJoin('file_managed', 'fm', 'fm.fid = zjt.fid');//
    $new_query->fields('zjt', array('id', 'title', 'fid'))
        ->fields('fm', array('uri'));

    $new_results = $new_query->orderBy('weight')
        ->extend('PagerDefault')
        ->limit($new_limit)
        ->groupBy('zjt.id')
        ->execute();

    $tagged_jobs = array();

    foreach ($new_results as $new_res) {
        
        $new_res->url = drupal_get_path_alias('jobs-by-keywords/' . $new_res->id);
        
        if (!empty($new_res->uri)) {
            $new_res->image = file_create_url($new_res->uri);
        } else {
            $new_res->image = '/sites/default/files/slider_images/feature-4.jpg';
        }
        $tagged_jobs[] = $new_res;
    }

    $variables = array(
        'tagged_jobs' => $tagged_jobs,
        'pager'      => theme('pager', array('tags' => array()))
    );


    return theme('organization_manager_jobs_by_keywords', $variables);
}



/**
 * $items['jobs-by-keywords/%']
 */
function organization_manager_jobs_by_keywords_List($tagsId, $page = 0)
{
    drupal_add_css(drupal_get_path('module', 'organization_manager') . '/css/find-jobs.css');
    drupal_add_js(drupal_get_path('module', 'organization_manager') . '/js/underscore-min.js');
    drupal_add_js(drupal_get_path('module', 'organization_manager') . '/js/backbone-min.js');
    drupal_add_js(drupal_get_path('module', 'organization_manager') . '/js/find-position.js');
    
    $params = organization_manager_getTagsQueryParams($tagsId);
    
    //error
    $tagsId = $params->tagsId;
    
    $urlString = $params->urlString;

    $tags_general = organization_manager_getTagsInfoById($tagsId);

    // seo
    if (!empty($tags_general->pageDescription))
        drupal_add_html_head(array(
            '#tag' => 'meta',
            '#attributes' => array(
                'name' => 'description',
                'content' => $tags_general->pageDescription,
            ),
        ), 'description');
    if (!empty($tags_general->pageKeywords))
        drupal_add_html_head(array(
            '#tag' => 'meta',
            '#attributes' => array(
                'name' => 'keywords',
                'content' => $tags_general->pageKeywords,
            ),
        ), 'keywords');

    $get = array(
        'type'         => 'featured_tags',
        'keywords'     => $tags_general->keywords,
        'page'         => $page,
        'urlAlias'     => $urlString,
        'limit'        => 5,
    );

    $variables = organization_manager_find_jobs_getPositionsData($get);
    $variables['path'] = drupal_get_path('module', 'organization_manager');
    $variables['tags'] = $tags_general->title;
    
    drupal_add_js(
        array(
        'location'    => $variables['location'],
        'page'        => $variables['currentPage'],
        'keywords'      => $variables['keywords'],
        'tags' => $variables['tags'],
        'urlAlias'    => $urlString,
        ), 'setting'
    );

    return theme('organization_manager_positions', $variables);
}

/**
 *  get url from database
 */
function organization_manager_getTagsQueryParams($tagsId = 0)
{

    if (arg(0) != 'jobs-by-keywords' || !is_numeric(arg(1))) {
        $alias = arg(0) . '/' . arg(1);
        $url = drupal_lookup_path('source', $alias);
        $tagsId = intval(str_replace('jobs-by-keywords/', '', $url));
        $urlString  = arg(1);//mark might cause problems 01282015
    } else {
        $tagsId = arg(1);
        $url = drupal_get_path_alias('jobs-by-keywords/' . $tagsId);
        $urlString  = str_replace('jobs-by-keywords/', '', $url);
    }
    return (object) array(
        'tagsId' => $tagsId,
        'urlString'  => $urlString,
    );
}


/**
 *  get meta content for featured jobs category
 */

function organization_manager_getTagsInfoById($id)
{
    if (!empty($id))
        return db_select('zd_job_tags', 'zjt')
                ->fields('zjt', array('title', 'pageTitle', 'pageDescription', 'pageKeywords','keywords'))
                ->condition('id', $id)
                ->execute()
                ->fetch();
    return null;
}

/**
 * 
 */
function organization_manager_getPositions()
{
    $post = (array) json_decode(file_get_contents("php://input"));
    if (!empty($post)) {
        $variables = organization_manager_find_jobs_getPositionsData($post);
        print json_encode($variables);
    }
    exit();
}

/**
 * 
 */
function organization_manager_jobs_keyword_getAjaxjobsList()
{
    $post = (array) json_decode(file_get_contents("php://input"));
    if (!empty($post)) {
        $post['type'] = 'featured_tags';
        $variables = organization_manager_find_jobs_getPositionsData($post);
        print json_encode($variables);
    }
    exit();
}


function organization_manager_jobDetails($jobId)
{
    global $user, $base_url;
    drupal_add_css(drupal_get_path('module', 'organization_manager') . '/css/find-jobs.css');
    drupal_add_js(drupal_get_path('module', 'organization_manager') . '/js/underscore-min.js');
    drupal_add_js(drupal_get_path('module', 'organization_manager') . '/js/backbone-min.js');
    //drupal_add_js(drupal_get_path('module', 'organization_manager') . '/js/job-detail-page.js');

    ///////////////////start query/////////////////
    /*
    $params[':jobId'] = $jobId

    $sql = " SELECT 
            FROM zd_dev_jobs as zdj
            LEFT JOIN zd_dev_location_city as zdlc
            ON zdj.City_id = zdlc.ID
            LEFT JOIN zd_dev_location_district as zdld
            ON zdj.District_id = zdld.ID
            LEFT JOIN zd_dev_location_country as zdlco
            ON zdj.Country_id = zdlco.ID
            LEFT JOIN zd_organization as zo
            ON zdj.Org_id = zo.id
            WHERE zdj.ID = :$jobId
    " 
    */

    $query = db_select('zd_dev_jobs','zdj');
    $query->leftJoin('zd_dev_location_city','zdlc','zdj.City_id = zdlc.ID');
    $query->leftJoin('zd_dev_location_district','zdld','zdj.District_id = zdld.ID');
    $query->leftJoin('zd_dev_location_country','zdlco','zdj.Country_id = zdlco.ID');
    $query->leftJoin('zd_organization','zo','zdj.Org_id = zo.id');
    $query = $query->fields('zdj')
                ->fields('zdlc',array('Name'))
                ->fields('zdld',array('Name'))
                ->fields('zdlco',array('Name'))
                ->fields('zo',array('name'))
                ->condition('zdj.ID',$jobId)
                ->execute()
                ->fetch();

    $query->location = "";
    if ($query->Name != ""){$query->location.= " ".$query->Name;}
    if ($query->zdld_Name != ""){$query->location.=" ".$query->zdld_Name;}
    if ($query->zdlco_Name != ""){$query->location.= " ".$query->zdlco_Name;}

    $tag_query = db_select('zd_dev_jobs_tags','zdjt');
    $tag_query = $tag_query->fields('zdjt',array('Tag'))
                condition('zdjt.ID',$jobId)
                ->execute()
                ->fetch();
    //////////////////////////////////////////////
    /*
    $query = db_select('zd_jobs', 'zj');
    $query->leftJoin('zd_save_entity', 'zde', 'zde.uid = '.$user->uid.' AND zde.entity_type = 1 AND zde.entity_id = zj.id');
    $query->leftJoin('zd_jobs_locations', 'zjl', 'zjl.jobId=zj.id');
    $query->leftJoin('zd_organization', 'zo', 'zo.id=zj.organizationId');
    $query->fields('zjl');
    $query->addExpression('IF(zde.uid IS NULL, 0, 1)', 'saved');
    $query = $query->fields('zj', array('id', 'title', 'description', 'url', 'updated'))
        ->fields('zo', array('name', 'homePageUrl'))
        ->condition('zj.id', $jobId)
        ->execute()
        ->fetch();
    

    if (empty($query->url)) {
        $query->url = $query->homePageUrl;
    }

    $query->date = date('d/m/Y', strtotime($query->updated));
    $query->location = organization_manager_getOrganizationLocationById(
        array(
            'country' => $query->countryId,
            'state'   => $query->stateId,
            'city'    => $query->cityId,
        )
    );
    */

    $variables = array(
        'job'  => $query,
        'user' => $user,
        'home' => $base_url,
    );
    return theme('organization_manager_jobDetails', $variables);
}


