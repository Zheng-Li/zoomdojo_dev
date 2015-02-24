<?php
include_once 'organization_manager_find_jobs.inc';

function organization_manager_positions()
{   
    
    global $user;
    drupal_add_css(drupal_get_path('module', 'organization_manager') . '/css/find-jobs.css');
    drupal_add_js(drupal_get_path('module', 'organization_manager')  . '/js/typeahead.min.js');
    drupal_add_js(drupal_get_path('module', 'organization_manager')  . '/js/find-position.js');

    #$variables = organization_manager_find_jobs_getOrganizationsData($_GET);
    $variables = organization_manager_find_jobs_getPositionsData($_GET);
    #$variables = array();
    #var_dump($variables);
    $variables['path'] = drupal_get_path('module', 'organization_manager');
    $variables['user'] = $user;

    drupal_add_js(
        array(
        //'location'      => $variables['location'],
        'page'          => $variables['currentPage'],
        //'jobType'       => $variables['jobType'],
        //'jobIndustry'   => $variables['jobIndustry'],
        //'companyName'   => $variables['companyName'],
        'display'       => $variables['limit'],
        'requestedLimit'=> $variables['requestedLimit'],
        'requestedPage' => $variables['requestedPage'],
        'needLogIn'     => $variables['needLogIn'],
        ), 'setting'
    );
    //var_dump($_GET);
    file_put_contents('/Users/Justin/Desktop/for_url.txt', print_r($variables, true));
    return theme('organization_manager_positions', $variables);
}

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
    $displayArray = array(5, 10, 20, 50, 100);
    
    if (!empty($get['display'])) {
        $limit = $get['display'];
    }
    if (!empty($get['page'])) {
        $currentPage = intval($get['page']);
    }

    if (!empty($get['keywords'])){
        $keywords = $get['keywords'];
    }
    else{
        $keywords = "software";
    }

    if ( !$user->uid && ($limit > 5 || $currentPage > 0)) {
        $requested_limit = $limit;
        $requested_page = $currentPage;
        $limit = 5;
        $currentPage = 0;
        $needLogIn = 1;
    }

    $url['keywords']     = $keywords;
    $url['location']     = 'New York';
    $url['display']      = $limit;


    //$keywords = $get['keywords'];

    $keyword_list = preg_split("/[\s,]+/", $keywords);

    //$keyword_list = explode(" ", $keywords);
    /*
    foreach ($keyword_list as $keyword) {
        echo $keyword;
        echo "|";
    }
    */
    #echo count($keyword_list);

    //$sqltest="select id,jobTitle,url,snippet from zd_position";

    
    #$results = db_query($sqltest);

    //file_put_contents('/Users/Justin/Desktop/stdout_pos.txt', print_r($results, true));
    //print $sql;
    //$result = db_query($sql, $params);


    //trim
    $fined_keywords = organization_manager_find_jobs_keywordPreprocess($keyword_list);



    

    //echo count($fined_keywords);

    //$result = array();

    $cat_keywords = join("|", $fined_keywords);
    //print_r($cat_keywords);
    

    //$results = organization_manager_find_jobs_getDatabyKeyword($cat_keywords);

    ////////////////////////GET DATA/////////////////////////////
    if($cat_keywords == ""){
        $cat_keywords = ".";
    }

    $params = array();

    //$params[':keyword'] = '%' . db_like($keyword) . '%';
    $params[':keyword'] = $cat_keywords;
    //$params[':limit'] = $limit;
    //$params[':offset'] = $limit * $currentPage;
    //print_r($cat_keywords);

    $sqltest="select SQL_CALC_FOUND_ROWS zd_position.id,jobTitle,url,snippet from zd_position where jobTitle REGEXP :keyword 
    or tags REGEXP :keyword or snippet REGEXP :keyword LIMIT " . ($currentPage * $limit) . ", " . $limit;

    $results = db_query($sqltest,$params);


    ///////////////////////////////////////////////////////////////



    $countRows = db_query('SELECT FOUND_ROWS();')->fetchField();
    print_r($countRows);

    
    if ($countRows < $limit) {
        $limit = $countRows;
    }

    $countPage = 0;
    if ($countRows > $limit) {
        $countPage = ceil($countRows / $limit);
    }
    
    $positions = array();
    foreach ($results as $record) {
        //$record[encodeName] = urlencode($record->name);
        $positions[] = $record;
    }

    //$countRows = count($positions);


    file_put_contents('/Users/Justin/Desktop/stdout_pos.txt', print_r($positions, true));

    $featuredJobs = false;

    print_r($url);
    //marked ting
    if (!empty($get['type']) && $get['type'] == 'featured_jobs') {
        $url = '/featured-jobs/internships/' . $get['urlAlias'] . '/page/';
        $featuredJobs = true;
    } else {
        $url = '/find-positions?' . http_build_query($url) . '&page=';
    }

    //$positions = organization_manager_setOrganizationsUrlByJobType($positions, $jobType);

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
        //'allJobString'  => implode('<br/>', $allJobString),
        //'location'      => $location,
        //'jobType'       => $jobType,
        //'jobIndustry'   => $jobIndustry,
        //'companyName'   => $companyName,
        'featuredJobs'  => $featuredJobs,
        //'locationStr'   => $locationStr,
        //'typeStr'       => $typeStr,
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

function organization_manager_find_jobs_keywordPreprocess($keywords){
    
    $res = array();

    foreach ($keywords as $keyword) {
        if (trim($keyword) != ''){
        
        $res[] = trim($keyword);
        
        }
    }

    return $res;

}


function organization_manager_find_jobs_getPositions()
{
    ignore_user_abort(false);
    $response = array(
        'status' => 'ERROR',
        'data'   => 'No result',
    );
    if (!empty($_GET['keywords'])) {
        $keywords = $_GET['keywords'];

        //start query
        $query = db_select('zd_position', 'zp');
        $query->leftJoin('zd_new_org', 'zno', 'zp.organizationId = zno.id');
        $query->leftJoin('zd_pos_tags', 'zpt', 'zpt.organizationId = zo.id');
        $query->leftJoin('zd_org_loc', 'zol', 'zol.organizationId = zo.id');
        
        $query = $query->fields('zo', array('name'))
            ->condition('name', '%' . db_like($companyName) . '%', 'LIKE');
        /*
        // is location country
        if (!empty($_GET['location']['country'])) {
            $query->condition('zol.countryId', $_GET['location']['country']);
        }
        // is location state
        if (!empty($_GET['location']['state'])) {
            $query->condition('zol.stateId', $_GET['location']['state']);
        }
        // is location city
        if (!empty($_GET['location']['city'])) {
            $query->condition('zol.cityId', $_GET['location']['city']);
        }
        // is job type
        if (!empty($_GET['job_type'])) {
            $query->condition('zojt.typeId', $_GET['job_type']);
        }
        // is job industry
        if (!empty($_GET['job_industry'])) {
            $query->condition('zoi.industryId', $_GET['job_industry']);
        }
        */

        $query->condition('zo.status', 1);
        $query = $query->range(0, 20)
            ->groupBy('zo.id')
            ->execute()
            ->fetchAll();


        //To be cleared

        if (!empty($query)) {
            if (count($query) > 1) { //add you typed string into choice box
                array_unshift($query, (object) array('name' => $companyName));
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
    
    ///////
    /*
    $internshipId = 1;
    $limit = 20;
    $query = db_select('zd_job_industries', 'zji');
    $query->join('zd_org_industries', 'zoi', 'zoi.industryId = zji.id');
    $query->join('zd_organization', 'zo', 'zo.id = zoi.organizationId');
    $query->join('zd_org_job_types', 'zojt', 'zojt.organizationId = zo.id');
    $query->leftJoin('file_managed', 'fm', 'fm.fid = zji.fid');//
    $query->fields('zji', array('id', 'title', 'fid'))
        ->fields('fm', array('uri'))
        ->fields('zo', array('internLink'));
    $results = $query->orderBy('weight')
        ->condition('zojt.typeId', $internshipId)
        ->condition('zo.internLink', '', '<>')
        ->extend('PagerDefault')
        ->limit($limit)
        ->groupBy('zji.id')
        ->execute();
    */
    //file_put_contents('/Users/Justin/Desktop/res.txt', print_r($results, true));

    $industries_url_overload = array(
        /*
        "36" => "internships-jobs-accounting-spring-summer-2015",//Accounting
        "2" => "spring-summer-2015-internships-aerospace-defense",//Aerospace & Defense
        "47" => "internships-spring-summer-2015-aaeid",//Architecture, Architectural Engineering, Interior Design
        "16" => "spring-summer-2015-internships-arts-culture-dance-museums-music",//Art
        "6" => "spring-summer-2015-internships-conglomerates",//conglomerates
        "7" => "spring-summer-internships-2015-consulting",//consulting
        "26" => "spring-summer-2015-internships-environment-non-profits",//environment-non-profits
        "5" => "spring-summer-fall-internships-jobs-2015-finance",//finance
        "17" => "spring-summer-fall-internships-2015-petroleum-energy-industry",//petroleum-energy-industry
        "1" => "spring-summer-2015-internships-entry-level-jobs-marketing-communications",//marketing
        "4" => "spring-summer-internships-2015-automotive",//automotive
        "29" => "public-broadcasting-internships-2015",//public-broadcasting-internships
        "3" => "spring-summer-2015-internships-airlines-air-couriers-transportation-logistics",//airline...
        "56" => "2015-internships-entry-level-jobs-agribusiness",//agribusiness
        "24" => "internships-2015-–-not-profits-development-relief-social-need",//
        "21" => "internships-2015-–-chemicals-paper",//
        "8" => "internships-2015-–-consumer-goods",//
        "23" => "internships-2015-–-media-entertainment-consumer-electronics",//
        "28" => "internships-2015-–-not-profits-policy",//
        "9" => "engineering-construction-machinery",//
        "10" => "fashion-apparel",//
        "11" => "food-beverages",//
        "41" => "internships-2015-–-forestry",//
        "40" => "internships-2015-–-general-trading",//
        */


        );
    $title_overload = array(
        "36" => "Accounting",
        "7"  => "Consulting",
        "5"  => "Finance",
        "26" => "Environment",
        "1"  => "Marketing & Communications",
        "2"  => "Aerospace & Defence",
        "29" => "Public Broadcasting",
        "17" => "Petroleum & Energy",
    );

    $tagged_jobs = array();

    /*
    foreach ($results as $res) {
        if (isset($industries_url_overload[$res->id])){
            $res->url = $industries_url_overload[$res->id];
        }
        else{
        $res->url = drupal_get_path_alias('jobs-by-keywords/' . $res->id);
        }   
        if (!empty($res->uri)) {
            $res->image = file_create_url($res->uri);
        } else {
            $res->image = '/sites/default/files/slider_images/feature-4.jpg';
        }

        if (isset($title_overload[$res->id])){
            $res->title = $title_overload[$res->id];
        }
        $tagged_jobs[] = $res;
    }
    */
    ///ting
    
    foreach ($new_results as $new_res) {
        
        $new_res->url = drupal_get_path_alias('jobs-by-keywords/' . $new_res->id);
           
        if (!empty($new_res->uri)) {
            $new_res->image = file_create_url($new_res->uri);
        } else {
            $new_res->image = '/sites/default/files/slider_images/feature-4.jpg';
        }
        $tagged_jobs[] = $new_res;
    }
    
    ///



    //print_r($tagged_jobs);
    $variables = array(
        'tagged_jobs' => $tagged_jobs,
        'pager'      => theme('pager', array('tags' => array()))
    );
    file_put_contents('/Users/Justin/Desktop/stdout_pos.txt', print_r($variables, true));
    //ting
    /*
    $query = db_select('zd_position','zp');
    $result = $query->fields('zp',array('jobTitle','url','snippet'))
          ->execute()
          ->fetch();

    foreach ($result as $record){
        echo $result->jobTitle;
        echo $result->url;
        echo $result->snippet;
    } 
    */

    return theme('organization_manager_jobs_by_keywords', $variables);
}


function organization_manager_jobs_by_keywords_List($tagsId, $page = 0)
{
    drupal_add_css(drupal_get_path('module', 'organization_manager') . '/css/find-jobs.css');
    drupal_add_js(drupal_get_path('module', 'organization_manager') . '/js/underscore-min.js');
    drupal_add_js(drupal_get_path('module', 'organization_manager') . '/js/backbone-min.js');
    drupal_add_js(drupal_get_path('module', 'organization_manager') . '/js/find-jobs.js');
    

    //$internshipId = 1;

    //$params = organization_manager_getFeaturedJobsQueryParams($industryId);
    $params = organization_manager_getTagsQueryParams($tagsId);

    $tagsId = $params->$tagsId;
    $urlString = $params->urlString;


    $tags_general = organization_manager_getTagsInfoById($tagsId);

    // seo
    if (!empty($industryType->pageDescription))
        drupal_add_html_head(array(
            '#tag' => 'meta',
            '#attributes' => array(
                'name' => 'description',
                'content' => $industryType->pageDescription,
            ),
        ), 'description');
    if (!empty($industryType->pageKeywords))
        drupal_add_html_head(array(
            '#tag' => 'meta',
            '#attributes' => array(
                'name' => 'keywords',
                'content' => $industryType->pageKeywords,
            ),
        ), 'keywords');
    //


    $get = array(
        //'job_type'     => $internshipId,
        //'job_industry' => $industryId,
        //'location'     => 0,
        //'type'         => 'featured_jobs',
        'keywords'     => $tags_general->keywords,
        'page'         => $page,
        'urlAlias'     => $urlString,
        'limit'        => 5,
    );

    $variables = organization_manager_find_jobs_getPositionsData($get);
    //ting
    //$variables = organization_manager_find_jobs_getPositionData($get);
    /*
    $testquery = db_select('zd_position','zp');
    $testresult = $testquery->fields('zp',array('id','jobTitle','url','snippet'))
          ->execute()
          ->fetch();
    file_put_contents('/Users/Justin/Desktop/stdout.txt', print_r($testresult, true));
    echo "OK";
    */


    $variables['path'] = drupal_get_path('module', 'organization_manager');
    $variables['tags'] = $industryType->title;
    
    //var_dump($variables);

    drupal_add_js(
        array(
        //'location'    => $variables['location'],
        'page'        => $variables['currentPage'],
        //'jobType'     => $variables['jobType'],
        //'jobIndustry' => $variables['jobIndustry'],
        //'companyName' => $variables['companyName'],
        'tags' => $variables['tags'],
        'urlAlias'    => $urlString,
        ), 'setting'
    );

    //file_put_contents('/Users/Justin/Desktop/stdout.txt', print_r($variables, true));
    //echo "OK";
    return theme('organization_manager_positions', $variables);
}


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