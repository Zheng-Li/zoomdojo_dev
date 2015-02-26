 <?php
include_once 'organization_manager_job_types.inc';
include_once 'organization_manager_job_inustries.inc';
include_once 'organization_manager_locations.inc';
include_once 'organization_manager_user.inc';

function organization_manager_find_jobs_jobDetails($jobId)
{
    global $user, $base_url;
    drupal_add_css(drupal_get_path('module', 'organization_manager') . '/css/find-jobs.css');
    drupal_add_js(drupal_get_path('module', 'organization_manager') . '/js/underscore-min.js');
    drupal_add_js(drupal_get_path('module', 'organization_manager') . '/js/backbone-min.js');
    drupal_add_js(drupal_get_path('module', 'organization_manager') . '/js/job-detail-page.js');

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

    $variables = array(
        'job'  => $query,
        'user' => $user,
        'home' => $base_url,
    );
    return theme('organization_manager_find_jobs_jobDetails', $variables);
}

function organization_manager_find_jobs_popup()
{
    drupal_add_js(drupal_get_path('module', 'organization_manager') . '/js/typeahead.min.js');
    drupal_add_js(drupal_get_path('module', 'organization_manager') . '/js/popup.js');

    global $user;
    $job_types = array();
    foreach (organization_manager_job_types_get_data() as $item) {
        $job_types[$item->id] = $item->title;
    }

    $industry_types = array();
    foreach (organization_manager_job_industries_get_data() as $item) {
        $industry_types[$item->id] = $item->title;
    }

    return theme('organization_manager_find_jobs_popup', array(
        'jobTypes'      => $job_types,
        'industryTypes' => $industry_types,
        'user'          => $user,
    ));
}

function organization_manager_find_jobs_header_form()
{
    drupal_add_css(drupal_get_path('module', 'organization_manager') . '/css/find-jobs.css');
    drupal_add_js(drupal_get_path('module', 'organization_manager') . '/js/typeahead.min.js');
    drupal_add_js(drupal_get_path('module', 'organization_manager') . '/js/position_popup.js');
    /*
    $job_types = array();
    foreach (organization_manager_job_types_get_data() as $item) {
        $job_types[$item->id] = $item->title;
    }

    $industry_types = array();
    foreach (organization_manager_job_industries_get_data() as $item) {
        $industry_types[$item->id] = $item->title;
    }

    $locations = _ajax_organization_manager_getCountriesOptions();
    */
    $keywords='';
    $location='';

    return theme('organization_manager_find_jobs_header_form');
}

function organization_manager_find_jobs_getOrganizationsData($get)
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

    if ( !$user->uid && ($limit > 5 || $currentPage > 0)) {
        
        //the information can be more protected here

        $requested_limit = $limit;
        $requested_page = $currentPage;
        $limit = 5;
        $currentPage = 0;
        $needLogIn = 1;
    }
    $sqlSave = ' 0 AS `saved`, ';
    if (!empty($user->uid)) {
        $params[':uid'] = $user->uid;
        $join[]         = " LEFT JOIN `zd_save_entity` `zde` ON `zde`.`uid` = :uid AND `zde`.`entity_type` = 0 AND `zde`.entity_id = `zo`.`id`";
        $sqlSave        = " IF(zde.uid IS NULL, 0, 1) as saved, ";
        $params[':uid'] = $user->uid;
    }
    $typeStr = "All jobs";
    $isAllJobAlias = true;
    if (!empty($get['job_type']) && $get['job_type'] != 0) {
        $jobType            = intval($get['job_type']);
        $organizationJobType = organization_manager_getOrganizationJobTypeById($jobType);
        $typeStr            = $organizationJobType[0]->title;
        if($organizationJobType[0]->alias_all != 1){
            $isAllJobAlias = false;
            $where[]            = '`zojt`.`typeId` = :jobType';
        }
        $join[]             = " LEFT JOIN `zd_org_job_types` `zojt` ON `zo`.`id` = `zojt`.`organizationId` ";
        // if featured jobs
        if (empty($get['type']) || (!empty($get['type']) && $get['type'] != 'featured_jobs')) {
            //$jobsWhere[]        = '`jobsjt`.`typeId` = :jobType';
            $jobsJoin[]         = " LEFT JOIN `zd_jobs_job_types` `jobsjt` ON `zd_jobs`.`id` = `jobsjt`.`jobId` AND `jobsjt`.`typeId` = :jobType ";
        }
        $params[':jobType'] = $jobType;
        
        $allJobString[]     = $typeStr;
    } else {
        $allJobString[] = "All jobs";
    }

    $jobTypeJoinUrl = organization_manager_getUrlJobTypeNameById($isAllJobAlias?0:$jobType);
    $jobIndustry = 0;
    if (!empty($get['job_industry'])) {
        $jobIndustry            = intval($get['job_industry']);
        $where[]                = '`zoi`.`industryId` = :jobIndustry';
        $join[]                 = " LEFT JOIN `zd_org_industries` `zoi` ON `zo`.`id` = `zoi`.`organizationId` ";
        // if featured jobs
        if (empty($get['type']) || (!empty($get['type']) && $get['type'] != 'featured_jobs')) {
            //$jobsWhere[]            = '`jobsi`.`industryId` = :jobIndustry';
            $jobsJoin[]             = " LEFT JOIN `zd_jobs_industries` `jobsi` ON `zd_jobs`.`id` = `jobsi`.`jobId` AND `jobsi`.`industryId` = :jobIndustry ";
        }
        $params[':jobIndustry'] = $jobIndustry;
        $industryType = organization_manager_getOrganizationIndustryTypeById($jobIndustry);
        $industryStr            = $industryType->title;
        $allJobString[]         = $industryStr;
    }
    $location = array(
        'country' => 0,
        'state'   => 0,
        'city'    => 0,
    );
    $locationStr = "All locations";
    if (!empty($get['location'])) {
        $location = $get['location'];
        if (!empty($get['location']['country'])) {
            $where[] = '`zol`.`countryId` = :location_country';
            $jobsJoinWhere[] = ' `jobsl`.`countryId` = :location_country ';
            $params[':location_country'] = $location['country'];
        }
        if (!empty($get['location']['state'])) {
            $where[] = '`zol`.`stateId` = :location_state';
            $jobsJoinWhere[] = ' `jobsl`.`stateId` = :location_state ';
            $params[':location_state'] = $location['state'];
        }
        if (!empty($get['location']['city'])) {
            $where[] = '`zol`.`cityId` = :location_city';
            $jobsJoinWhere[] = ' `jobsl`.`cityId` = :location_city ';
            $params[':location_city'] = $location['city'];
        }
        $join[] = " LEFT JOIN `zd_org_loc` `zol` ON `zo`.`id` = `zol`.`organizationId` ";
        if (!empty($jobsJoinWhere)) {
            $jobsJoin[] = " LEFT JOIN `zd_jobs_locations` `jobsl` ON `zd_jobs`.`id` = `jobsl`.`jobId` AND " . implode(' AND ', $jobsJoinWhere);
        } else {
            $jobsJoin[] = " LEFT JOIN `zd_jobs_locations` `jobsl` ON `zd_jobs`.`id` = `jobsl`.`jobId` ";
        }
        $locationStr         = organization_manager_getOrganizationLocationById($location);
        $allJobString[]      = $locationStr;
    }
    $keyword = 0;
    $companyName = '';
    if (!empty($get['company_name']) && !empty($get['keyword'])) {
        $companyName            = trim($get['company_name']);
        $keyword                = $get['keyword'];
        $allJobString[]         = $companyName;
        $where[]                = '`zo`.`name` LIKE :companyName';
        $params[':companyName'] = '%' . db_like($companyName) . '%';
        $url['keyword']         = 1;
    }

    //if Featured Jobs - add filter to sql
    if (!empty($get['type']) && $get['type'] == 'featured_jobs') {
        $where[] = " `zo`.`internLink` != '' ";
    }

    $url['job_type']     = $jobType;
    $url['job_industry'] = $jobIndustry;
    $url['location']     = $location;
    $url['company_name'] = $companyName;
    $url['display']      = $limit;
    
    $sql = "SELECT SQL_CALC_FOUND_ROWS $sqlSave zo.id, zo.name,
            zo.homePageUrl, zo.internLink, zo.graduateLink, zo.veteranLink, zo.careerLink, zo.mbaLink, zo.experiencedLink,
            COUNT(`zd_jobs`.`id`) AS jobsCount, zu.title AS metaTitle, zu.description AS metaDesc
            FROM `zd_organization` `zo`
            LEFT JOIN `zd_jobs`ON `zo`.`id` = `zd_jobs`.`organizationId` "
            . " LEFT JOIN `zd_organization_urls` `zu` ON `zu`.`organizationId` = `zo`.`id` AND `zu`.`status`=200 AND `zu`.`type` = '".$jobTypeJoinUrl."' "
            . implode(' ', $jobsJoin)
            . implode(' ', $join) . 
            "WHERE `zo`.`status`=1 "
            . ((!empty($jobsWhere))?(" AND " . implode(' AND ', $jobsWhere)):'');
            

    if (!empty($where)) {
        $sql .= " AND " . implode(' AND ', $where);
    }

    // if company name isn't empty and no filter for keyword set new sql
    if (!empty($get['company_name']) && empty($keyword)) {
        $companyName = trim($get['company_name']);
        
        $sql    = "SELECT SQL_CALC_FOUND_ROWS `zo`.`id`, `zo`.`name`, " . $sqlSave . "
                zo.homePageUrl, zo.internLink, zo.graduateLink, zo.veteranLink, zo.careerLink, zo.mbaLink, zo.experiencedLink, 
                COUNT(`zd_jobs`.`id`) AS jobsCount, zu.title AS metaTitle, zu.description AS metaDesc
                FROM `zd_organization` `zo`
                LEFT JOIN `zd_jobs`ON `zo`.`id` = `zd_jobs`.`organizationId`
                LEFT JOIN `zd_save_entity` `zde` ON `zde`.`uid` = :uid AND `zde`.`entity_type` = 0 AND `zde`.entity_id = `zo`.`id`
                LEFT JOIN `zd_organization_urls` `zu` ON `zu`.`organizationId` = `zo`.`id` AND `zu`.`status`=200 AND `zu`.`type` = '".$jobTypeJoinUrl."'
                WHERE `zo`.`name` LIKE :companyName AND `zo`.`status`=1 ";
        $params = array(
            ':companyName' => '%' . db_like($companyName) . '%',
            ':uid'         => $user->uid,
        );
        $allJobString = array($companyName);
    }

    $sql .= " GROUP BY `zo`.`id` ";

    $sql .= " ORDER BY `zo`.`name` ASC LIMIT " . ($currentPage * $limit) . ", " . $limit;
    
    $result = db_query($sql, $params);

    $countRows = db_query('SELECT FOUND_ROWS();')->fetchField();
    if ($countRows < $limit) {
        $limit = $countRows;
    }

    $countPage = 0;
    if ($countRows > $limit) {
        $countPage = ceil($countRows / $limit);
    }
    
    $organizations = array();
    foreach ($result as $record) {
        $record->encodeName = urlencode($record->name);
        $organizations[] = $record;
    }

    

    $featuredJobs = false;
    if (!empty($get['type']) && $get['type'] == 'featured_jobs') {
        $url = '/featured-jobs/internships/' . $get['urlAlias'] . '/page/';
        $featuredJobs = true;
    } else {
        $url = '/find-jobs?' . http_build_query($url) . '&page=';
    }

    $organizations = organization_manager_setOrganizationsUrlByJobType($organizations, $jobType);

    foreach ($allJobString as $key => $item) {
        if (empty($item)) {
            unset($allJobString[$key]);
        }
    }
    $userCanEdit = false;
    if ($router_item = menu_get_item('admin/organization-manager/organizations/edit/%')) {
      $userCanEdit = $router_item['access'];
    }

    


    //////////////////////////////
    return array(
        'organizations' => $organizations,
        'limit'         => $limit,
        'countRows'     => $countRows,
        'countPage'     => $countPage,
        'currentPage'   => $currentPage,
        'url'           => $url,
        'dotted'        => $dotted,
        'allJobString'  => implode('<br/>', $allJobString),
        'location'      => $location,
        'jobType'       => $jobType,
        'jobIndustry'   => $jobIndustry,
        'companyName'   => $companyName,
        'featuredJobs'  => $featuredJobs,
        'locationStr'   => $locationStr,
        'typeStr'       => $typeStr,
        'home'          => $base_url,
        'displayArray'  => $displayArray,
        'userCanEdit'   => $userCanEdit,
        'requestedLimit'=> $requested_limit,
        'requestedPage' => $requested_page,
        'needLogIn'     => $needLogIn
    );
}

/**
 * Set organization url by job type Multi
 */
function organization_manager_setOrganizationsUrlByJobType($organizations, $jobType)
{
    foreach ($organizations as $org) {
        $url = '';
        switch ($jobType) {
            case 0:
                $url = organization_manager_chooseOrganizationsUrl($org->careerLink, $org->careerLink, $org->homePageUrl);
                break;
            case 1:
                $url = organization_manager_chooseOrganizationsUrl($org->internLink, $org->careerLink, $org->homePageUrl);
                break;
            case 2:
                $url = organization_manager_chooseOrganizationsUrl($org->graduateLink, $org->careerLink, $org->homePageUrl);
                break;
            case 3:
                $url = organization_manager_chooseOrganizationsUrl($org->mbaLink, $org->careerLink, $org->homePageUrl);
                break;
            case 4:
                $url = organization_manager_chooseOrganizationsUrl($org->experiencedLink, $org->careerLink, $org->homePageUrl);
                break;
            case 8:
                $url = organization_manager_chooseOrganizationsUrl($org->veteranLink, $org->careerLink, $org->homePageUrl);
                break;
            default:
                $url = $org->homePageUrl;
                break;
        }
        $org->url = $url;
    }
    return $organizations;
}

/**
 * get url table name by job type id
 */
function organization_manager_getUrlJobTypeNameById($id)
{
    $urls = array(
        0 => 'home',
        1 => 'intern',
        2 => 'graduate',
        3 => 'mba',
        4 => 'experienced',
        8 => 'veteran',
        //10 => 'career',
    );
    return $urls[$id];
}

/**
 * Choose no empty link of list
 */
function organization_manager_chooseOrganizationsUrl($url1, $url2, $url3)
{
    if (!empty($url1)) {
        $url = $url1;
    } elseif (!empty($url2)) {
        $url = $url2;
    } else {
        $url = $url3;
    }
    $parseUrl = parse_url($url);
    if (!empty($parseUrl) && empty($parseUrl['scheme'])) {
        $url = 'http://' . $url;
    }
    return $url;
}

function organization_manager_find_jobs()
{
    global $user;
    drupal_add_css(drupal_get_path('module', 'organization_manager') . '/css/find-jobs.css');
    drupal_add_js(drupal_get_path('module', 'organization_manager')  . '/js/typeahead.min.js');
    drupal_add_js(drupal_get_path('module', 'organization_manager')  . '/js/find-jobs.js');

    $variables = organization_manager_find_jobs_getOrganizationsData($_GET);
    $variables['path'] = drupal_get_path('module', 'organization_manager');
    $variables['user'] = $user;

    drupal_add_js(
        array(
        'location'      => $variables['location'],
        'page'          => $variables['currentPage'],
        'jobType'       => $variables['jobType'],
        'jobIndustry'   => $variables['jobIndustry'],
        'companyName'   => $variables['companyName'],
        'display'       => $variables['limit'],
        'requestedLimit'=> $variables['requestedLimit'],
        'requestedPage' => $variables['requestedPage'],
        'needLogIn'     => $variables['needLogIn'],
        ), 'setting'
    );

    return theme('organization_manager_find_jobs', $variables);
}

function organization_manager_find_jobs_getOrganizations()
{
    $post = (array) json_decode(file_get_contents("php://input"));


    if (!empty($post)) {
        $post['location'] = (array) $post['location'];
        $variables = organization_manager_find_jobs_getOrganizationsData($post);
        print json_encode($variables);
    }
    exit();
}

function organization_manager_find_jobs_getJobs()
{
    if (!empty($_GET)) {
        $variables = organization_manager_find_jobs_getJobsData($_GET);
        print json_encode($variables);
    }
    exit();
}

function organization_manager_find_jobs_getJobsData($get)
{
    $limit     = 6;
    $dotted    = 4;
    $url       = array();
    $jobsJoin  = array();
    $jobsWhere = array();

    $currentPage = 0;
    if (!empty($get['page'])) {
        $currentPage = intval($get['page']);
    }

    $jobsWhere[]               = '`organizationId` = :organizationId';
    $organizationId            = intval($get['organizationId']);
    $params[':organizationId'] = $organizationId;

    $jobType = 0;
    if (!empty($get['jobType']) && $get['jobType'] != 0) {
        $jobType            = intval($get['jobType']);
        $jobsWhere[]        = '`jobsjt`.`typeId` = :jobType';
        $jobsJoin[]         = " INNER JOIN `zd_jobs_job_types` `jobsjt` ON `id` = `jobsjt`.`jobId` ";
        $params[':jobType'] = $jobType;
    }
    $jobIndustry = 0;
    if (!empty($get['industryType'])) {
        $jobIndustry            = intval($get['industryType']);
        $jobsWhere[]            = '`jobsi`.`industryId` = :jobIndustry';
        $jobsJoin[]             = " INNER JOIN `zd_jobs_industries` `jobsi` ON `id` = `jobsi`.`jobId` ";
        $params[':jobIndustry'] = $jobIndustry;
    }
    $location = 0;
    if (!empty($get['location'])) {
        $location = $get['location'];
        if (!empty($get['location']['country'])) {
            $jobsWhere[] = '`jobsl`.`countryId` = :location_country';
            $params[':location_country'] = $location['country'];
        }
        if (!empty($get['location']['state'])) {
            $jobsWhere[] = '`jobsl`.`stateId` = :location_state';
            $params[':location_state'] = $location['state'];
        }
        if (!empty($get['location']['city'])) {
            $jobsWhere[] = '`jobsl`.`cityId` = :location_city';
            $params[':location_city'] = $location['city'];
        }
        $jobsJoin[]          = " INNER JOIN `zd_jobs_locations` `jobsl` ON `id` = `jobsl`.`jobId` ";
    }

    $url['jobType']        = $jobType;
    $url['industryType']   = $jobIndustry;
    $url['location']       = $location;
    $url['organizationId'] = $organizationId;

    $sql = "SELECT SQL_CALC_FOUND_ROWS id, title, description 
            FROM `zd_jobs` "
        . implode(' ', $jobsJoin)
        . "\r\nWHERE " . implode(' AND ', $jobsWhere)
        . "\r\nORDER BY `id` DESC LIMIT " . ($currentPage * $limit) . ", " . $limit;

    $result = db_query($sql, $params);

    $jobs = array();
    foreach ($result as $record) {

        $record->jobTypes = array('0' => 'All jobs');
        $jobs[]           = $record;
    }
    $countRows = db_query('SELECT FOUND_ROWS();')->fetchField();
    if ($countRows < $limit) {
        $limit = $countRows;
    }

    $countPage = 0;
    if ($countRows > $limit) {
        $countPage = ceil($countRows / $limit);
    }
    //ting
    

    return array(
        'jobs'           => $jobs,
        'limit'          => $limit,
        'countRows'      => $countRows,
        'countPage'      => $countPage,
        'currentPage'    => $currentPage,
        'url'            => '/find-jobs-get-jobs?' . http_build_query($url),
        'dotted'         => $dotted,
        'location'       => $location,
        'jobType'        => $jobType,
        'jobIndustry'    => $jobIndustry,
        'organizationId' => $organizationId,
    );
}

function organization_manager_getOrganizationJobTypeById($id)
{
    if (!empty($id))
        return db_select('zd_job_types', 'zjt')
                ->fields('zjt', array('title','alias_all'))
                ->condition('id', $id)
                ->execute()
                ->fetchAll();
    return null;
}

function organization_manager_getOrganizationIndustryTypeById($id)
{
    if (!empty($id))
        return db_select('zd_job_industries', 'zji')
                ->fields('zji', array('title', 'pageTitle', 'pageDescription', 'pageKeywords'))
                ->condition('id', $id)
                ->execute()
                ->fetch();
    return null;
}

function organization_manager_getOrganizationLocationById($location)
{
    if (empty($location['country'])) {
        return t('Global');
    }
    $str = array();
    if (!empty($location['country'])) {
        $str[] = organization_manager_getLocationNameById($location['country']);
    }
    if (!empty($location['state'])) {
        $str[] = organization_manager_getLocationNameById($location['state']);
    }
    if (!empty($location['city'])) {
        $str[] = organization_manager_getLocationNameById($location['city']);
    }
    return implode(', ', $str);
}

function organization_manager_getLocationNameById($lid)
{
    return db_select('zd_locations', 'zl')
        ->fields('zl', array('title'))
        ->condition('id', $lid)
        ->execute()
        ->fetchColumn();
}

function organization_manager_featured_jobs()
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
        ->orderBy('title')
        ->condition('zojt.typeId', $internshipId)
        ->condition('zo.internLink', '', '<>')
        ->extend('PagerDefault')
        ->limit($limit)
        ->groupBy('zji.id')
        ->execute();


    $industries_url_overload = array();
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

    $industries = array();
    foreach ($results as $res) {
        if (isset($industries_url_overload[$res->id])){
            $res->url = $industries_url_overload[$res->id];
        }
        else{
        $res->url = drupal_get_path_alias('featured-jobs/internships/' . $res->id);
        }   
        if (!empty($res->uri)) {
            $res->image = file_create_url($res->uri);
        } else {
            $res->image = '/sites/default/files/slider_images/feature-4.jpg';
		}

		if (isset($title_overload[$res->id])){
            $res->title = $title_overload[$res->id];
		}
        $industries[] = $res;
    }


    $variables = array(
        'industries' => $industries,
        'pager'      => theme('pager', array('tags' => array()))
    );

    return theme('organization_manager_featured_jobs', $variables);
}

function organization_manager_getFeaturedJobsQueryParams($industryId = 0)
{
    if (arg(0) != 'featured-jobs' || !is_numeric(arg(2))) {
        $alias = arg(0) . '/' . arg(1) . '/' . arg(2);
        $url = drupal_lookup_path('source', $alias);
        $industryId = intval(str_replace('featured-jobs/internships/', '', $url));
        $urlString  = arg(2);
    } else {
        $industryId = arg(2);
        $url = drupal_get_path_alias('featured-jobs/internships/' . $industryId);
        $urlString  = str_replace('featured-jobs/internships/', '', $url);
    }
    return (object) array(
        'industryId' => $industryId,
        'urlString'  => $urlString,
    );
}

function organization_manager_featured_jobs_organizationList($industryId, $page = 0)
{
    drupal_add_css(drupal_get_path('module', 'organization_manager') . '/css/find-jobs.css');
    drupal_add_js(drupal_get_path('module', 'organization_manager') . '/js/underscore-min.js');
    drupal_add_js(drupal_get_path('module', 'organization_manager') . '/js/backbone-min.js');
    drupal_add_js(drupal_get_path('module', 'organization_manager') . '/js/find-jobs.js');
    $internshipId = 1;

    $params = organization_manager_getFeaturedJobsQueryParams($industryId);
    $industryId = $params->industryId;
    $urlString = $params->urlString;

    $industryType = organization_manager_getOrganizationIndustryTypeById($industryId);

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

    $get = array(
        'job_type'     => $internshipId,
        'job_industry' => $industryId,
        'location'     => 0,
        'type'         => 'featured_jobs',
        'page'         => $page,
        'urlAlias'     => $urlString,
        'limit'        => 5,
    );
    $variables = organization_manager_find_jobs_getOrganizationsData($get);

    $variables['path'] = drupal_get_path('module', 'organization_manager');
    $variables['industryStr'] = $industryType->title;
    
    drupal_add_js(
        array(
        'location'    => $variables['location'],
        'page'        => $variables['currentPage'],
        'jobType'     => $variables['jobType'],
        'jobIndustry' => $variables['jobIndustry'],
        'companyName' => $variables['companyName'],
        'urlAlias'    => $urlString,
        ), 'setting'
    );

    return theme('organization_manager_find_jobs', $variables);
}

/**
 * Implement hook_preprocess_html().
 */
function organization_manager_preprocess_html(&$variables) {
    $variables['head_title'] = organization_manager_getIndustryTypePageTitle($variables['head_title']);
}


/**
 * Featured jobs get ajax organizations
 */
function organization_manager_featured_jobs_getAjaxOrganizationList()
{
    $post = (array) json_decode(file_get_contents("php://input"));

    if (!empty($post)) {
        $post['location'] = 0;
        $post['type'] = 'featured_jobs';
        $variables = organization_manager_find_jobs_getOrganizationsData($post);
        print json_encode($variables);
    }
    exit();
}

function organization_manager_find_jobs_getEmployers()
{
    ignore_user_abort(false);
    $response = array(
        'status' => 'ERROR',
        'data'   => 'No result',
    );
    if (!empty($_GET['company_name'])) {
        $companyName = $_GET['company_name'];
        $query = db_select('zd_organization', 'zo');
        $query->leftJoin('zd_org_industries', 'zoi', 'zoi.organizationId = zo.id');
        $query->leftJoin('zd_org_job_types', 'zojt', 'zojt.organizationId = zo.id');
        $query->leftJoin('zd_org_loc', 'zol', 'zol.organizationId = zo.id');
        $query = $query->fields('zo', array('name'))
            ->condition('name', db_like($companyName) . '%', 'LIKE');
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
        $query->condition('zo.status', 1);
        $query = $query->range(0, 20)
            ->groupBy('zo.id')
            ->execute()
            ->fetchAll();
        if (!empty($query)) {
            if (count($query) > 1) {
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
