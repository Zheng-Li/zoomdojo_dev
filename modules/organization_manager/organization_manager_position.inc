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
    else{$keywords = '%';}

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

    if($numOfKeywords>0 and $numOfKeywords<10){

        /////keywords string process///////
 
        $params = array();    
        for($i=0;$i<$numOfKeywords;$i++){
            $tempName = ":kw".$i;
            $params[$tempName] = '%'.$fined_keywords[$i].'%';

        }

        $sql = "
            SELECT SQL_CALC_FOUND_ROWS distinct znj.ID, Title, znj.Snippet, Updated_on, zo.Name, znl.City as city_name,
                znl.State as District, znl.Country as country_name, x.Tags
                FROM zd_new_job AS znj
                LEFT JOIN zd_new_job_tag AS znjt
                ON znj.ID = znjt.ID
                LEFT JOIN zd_new_organization AS zo
                ON znj.Org_id = zo.ID
                LEFT JOIN zd_new_location AS znl
                ON znj.Loc_id = znl.ID
                LEFT JOIN (
                select zd_new_job_tag.ID, group_concat(Tag separator ',') as Tags from zd_new_job_tag GROUP BY zd_new_job_tag.ID
                ) x
                ON x.ID = znj.ID
                WHERE ( CONCAT(IFNULL(x.Tags, znj.Title),',',znj.Title,',',znj.Snippet,',',zo.Name) like :kw0
        ";
        
        $sql_keyword = "";
        for($i=1;$i<$numOfKeywords;$i++){
            
            $tempKeyword = ":kw".$i;
            $sql_keyword=$sql_keyword." ";
            $sql_keyword = $sql_keyword."AND CONCAT(IFNULL(x.Tags, znj.Title),',',znj.Title,',',znj.Snippet,',',zo.Name) like ".$tempKeyword;
        }

        $sql=$sql.$sql_keyword.")";

        ///location string process
         if($location != ""){
        $params[':loc'] = $location;

            $sql_loc = " AND Loc_id in (
                SELECT ID FROM zd_new_location WHERE City = :loc
                UNION 
                SELECT ID FROM zd_new_location WHERE State = :loc
                UNION 
                SELECT ID FROM zd_new_location WHERE Country = :loc
                )
            ";
        $sql=$sql.$sql_loc;

         }
        
        //////location string process end///////////
        


        $sql_condition = " AND znj.Status = '1'
                    AND (znj.Url_status < '300' or znj.Url_status = '304')
                    ORDER BY Job_weight ASC, city_name = :loc DESC, District = :loc DESC, country_name = :loc DESC, Updated_on DESC";

        $sql=$sql.$sql_condition;
        
        $sql = $sql." LIMIT ". ($currentPage * $limit) . ", " . $limit;


        $results = db_query($sql,$params);

        $now=strtotime(date("y-m-d H:i:s"));

        $positions = array();
        
        $pos_ids = array();

        foreach ($results as $record) {
            $record->encodeName = urlencode($record->Title);
            $record->Url = 'detailed-job-page/'.$record->ID;
            if(strlen($record->Snippet)>255){
                $record->Snippet = substr($record->Snippet,0,255)."...";
            }
            $record->location = "";
            if ($record->city_name != ""){$record->location.= " ".$record->city_name;}
            //if ($record->district_name != ""){$record->location.=" ".$record->district_name;}
            if ($record->country_name != ""){$record->location.= " ".$record->country_name;}

            $postTime = (int)ceil(($now - strtotime($record->Updated_on))/3600);
            
            
            if($postTime >= 24){
                $postTime = (int)($postTime/24);
                
                if($postTime == 1){$postFormat = strval($postTime)." day";}
                else{
                    if($postTime > 30){
                        $postTime = 30;
                        $postFormat=strval($postTime)."+ days";}
                    else{$postFormat=strval($postTime)." days";}
                    }
                
            }
            
            else{
                if($postTime <= 1){$postFormat = strval($postTime)." hour";}
                else{{$postFormat = strval($postTime)." hours";}}
            }
            $record->post = $postFormat;
            
            $record->Tags = array();
            $positions[$record->ID] = $record;
            $pos_ids[] = $record->ID;
        }

    ///////////////////////////////////////////////////////////////
        $countRows = db_query('SELECT FOUND_ROWS();')->fetchField();

    /////////////process tags////////////////

        if(!empty($positions)){

        $results_tag = db_select("zd_new_job_tag","znjt")
            ->fields("znjt")
            ->condition("ID", $pos_ids, "IN")
            ->execute();

        foreach ($results_tag as $result_tag) {
           $positions[$result_tag->ID]->Tags[]=$result_tag->Tag;
        }

        }

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
    if($keywords == '%'){$keywords = '';}
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
                FROM zd_new_job_tag
                WHERE Tag like :keyword
                UNION
                SELECT Title as result
                FROM zd_new_job
                WHERE Title like :keyword
                UNION
                SELECT Name as result
                FROM zd_new_organization
                WHERE Name like :keyword
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
        $location = trim($_GET['location']);
        //$params = array();
        $params[':loc'] = '%'.$location.'%';
        $sql = "
         SELECT City as Name 
         From zd_new_location
         Where City LIKE :loc
         UNION
         SELECT State as Name 
         From zd_new_location
         Where State LIKE :loc
         UNION
         SELECT Country as Name 
         From zd_new_location
         Where Country LIKE :loc
        ";
        $results = db_query($sql,$params);
        
        foreach ($results as $res) {
            $query[] = $res;
        }

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
    drupal_add_js(drupal_get_path('module', 'organization_manager') . '/js/new-job-page.js');

    if($user->uid != 1){
    db_update('zd_new_job')
    ->expression('Counter_1', 'Counter_1 + 1')
    ->condition('ID', $jobId)
    ->execute();
    }
    ///////////////////start query/////////////////
    
    $query = db_select('zd_new_job','znj');
    $query->leftJoin('zd_new_location','znl','znj.Loc_id = znl.ID');
    $query->leftJoin('zd_new_organization','zo','znj.Org_id = zo.ID');
    $query = $query->fields('znj')
                ->fields('znl',array('City','State','Country'))
                ->fields('zo',array('Name'))
                ->condition('znj.ID',$jobId)
                ->execute()
                ->fetch();

    $query->location = "";
    if ($query->City != ""){$query->location.= " ".$query->City;}
    
    if ($query->Country != ""){$query->location.= " ".$query->Country;}

    $tags_query = db_select('zd_new_job_tag','znjt');
    $tags_query = $tags_query->fields('znjt',array('Tag'))
                ->condition('znjt.ID',$jobId)
                ->execute()
                ->fetchAll();

    $query->Tags = array();
    foreach ($tags_query as $tag_query) {
        $query->Tags[]=$tag_query->Tag;
    }
    
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

    drupal_add_js(
        array(
        'jobId'    => $jobId,
        'jobUrl'   => $query->Url,
        'userId'   => $user->uid,
        ), 'setting'
    );

    return theme('organization_manager_jobDetails', $variables);
}

function organization_manager_find_counter_increasement(){
        $jobId = $_GET['jobId'];
        db_update('zd_new_job')
        ->expression('Counter_2', 'Counter_2 + 1')
        ->condition('ID', $jobId)
        ->execute();          
}
