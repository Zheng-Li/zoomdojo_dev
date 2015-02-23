<?php

/**
 * Get list "Job Search Tips" pages
 */
function zoomdojo_getJobSearchTipsPages()
{
    global $language ;
    $vid  = 3;
    $lang = $language->language;

    $types   = taxonomy_get_tree($vid);
    $termIds = array();
    foreach ($types as $type) {
        $termIds[] = $type->tid;
    }
    $query = db_select('node', 'n');
    $query->join('field_data_field_dos_donts', 'fdfdd', 'fdfdd.entity_id=n.nid');
    $query->fields('n', array('nid', 'title'));
    $query = $query->condition('n.language', $lang)
        ->condition('fdfdd.field_dos_donts_tid', $termIds, 'IN')
        ->orderBy('n.title')
        ->execute()
        ->fetchAll();

    $items = array(
        (object) array(
            'nid'   => 0,
            'title' => 'Job Search Tips Home Page',
            'url'   => 'job-search-tips',
        ),
    );
    foreach ($query as $item) {
        $item->url = drupal_get_path_alias('node/' . $item->nid);
        $items[] = $item;
    }

    return $items;
}

/**
 * Get list "City Focus" pages
 */
function zoomdojo_getCityFocusPages()
{
    global $language;
    $vidCityFocus = 2;
    $lang = $language->language;
    $query = db_select('taxonomy_term_data', 'ttd');
    $query->addExpression('ttd.name', 'title');
    $query->fields('ttd', array('tid'));

    $query = $query->condition('ttd.language', $lang)
        ->condition('ttd.vid', $vidCityFocus)
        ->orderBy('ttd.name')
        ->execute();

    $terms = array(
        (object) array(
            'nid'   => 0,
            'title' => 'City Guides Home Page',
            'url'   => 'city-guides',
        ),
    );
    foreach ($query as $term) {
        $term->url = drupal_get_path_alias('taxonomy/term/' . $term->tid);
        $terms[] = $term;
    }

    return $terms;
}

/**
 * Get list "Featured Jobs" pages
 */
function zoomdojo_getFeaturedJobsPages()
{
    $internshipId = 1;
    $query = db_select('zd_job_industries', 'zji');
    $query->join('zd_org_industries', 'zoi', 'zoi.industryId = zji.id');
    $query->join('zd_organization', 'zo', 'zo.id = zoi.organizationId');
    $query->join('zd_org_job_types', 'zojt', 'zojt.organizationId = zo.id');
    $query->fields('zji', array('id', 'title'));
    $results = $query->orderBy('weight')
        ->condition('zojt.typeId', $internshipId)
        ->orderBy('zji.title')
        ->groupBy('zji.id')
        ->execute();

    $industries = array(
        (object) array(
            'nid'   => 0,
            'title' => 'Featured Jobs Home Page',
            'url'   => 'featured-jobs/internships',
        ),
    );

    foreach ($results as $res) {
        $res->url = drupal_get_path_alias('featured-jobs/internships/' . $res->id);
        $industries[] = $res;
    }

    return $industries;
}

/**
 * Get list "Young Professionals" pages
 */
function zoomdojo_getYoungProfessionalsPages()
{
    global $language ;
    $vidYoungProf = 1;
    $lang  = $language->language;

    $query = db_select('taxonomy_term_data', 'ttd');
    $query->addExpression('ttd.name', 'title');
    $query->fields('ttd', array('tid'));
    $query = $query->condition('ttd.language', $lang)
        ->condition('ttd.vid', $vidYoungProf)
        ->execute();

    $terms = array(
        (object) array(
            'nid'   => 0,
            'title' => 'Young Professionals Home Page',
            'url'   => 'young-professionals',
        ),
    );
    foreach ($query as $term) {
        $term->url  = drupal_get_path_alias('taxonomy/term/' . $term->tid);
        if ($term->tid != 16)
            $terms[]    = $term;
    }

    return $terms;
}

/**
 * Get list "Veterans Resources" pages
 */
function zoomdojo_getVeteransResourcesPages()
{
    global $language ;
    $lang  = $language->language;

    $query = db_select('node', 'n')
        ->fields('n', array('nid', 'title'))
        ->condition('n.type', 'veterans')
        ->condition('n.language', $lang)
        ->orderBy('n.title')
        ->execute();

    $items = array(
        (object) array(
            'nid'   => 0,
            'title' => 'Veterans Home Page',
            'url'   => 'veterans',
        ),
    );
    foreach ($query as $item) {
        $item->url = drupal_get_path_alias('node/' . $item->nid);
        $items[] = $item;
    }
    $items[] = (object) array(
        'nid'   => 0,
        'title' => 'Student Veterans',
        'url'   => 'veterans/student-veterans',
    );

    return $items;
}

/**
 * Get list "Experts Speak" pages
 */
function zoomdojo_getExpertsSpeakPages()
{
    global $language ;
    $lang  = $language->language;

    $query = db_select('node', 'n')
        ->fields('n', array('nid', 'title'))
        ->condition('n.type', 'experts_speak')
        ->condition('n.language', $lang)
        ->orderBy('n.title')
        ->execute();

    $items = array();
    foreach ($query as $item) {
        $item->url = drupal_get_path_alias('node/' . $item->nid);
        $items[] = $item;
    }

    return $items;
}

/**
 * Get list "Resumes" pages
 */
function zoomdojo_getResumesPages()
{
    global $language ;
    $lang  = $language->language;

    $query = db_select('node', 'n')
        ->fields('n', array('nid'));
    $query->addExpression('fdfbh.field_body_header_value', 'title');
    $query->join('field_data_field_body_header', 'fdfbh', 'fdfbh.entity_id=n.nid');
    $query = $query->condition('n.type', 'resumes')
        ->condition('n.language', $lang)
        ->orderBy('title')
        ->execute();

    $items = array();
    foreach ($query as $item) {
        $item->url = drupal_get_path_alias('node/' . $item->nid);
        $items[] = $item;
    }

    return $items;
}

/**
 * Get list "Basic page" pages
 */
function zoomdojo_getBasicpagePages()
{
    global $language ;
    $lang  = $language->language;

    $query = db_select('node', 'n')
        ->fields('n', array('nid', 'title'))
        ->condition('n.type', 'page')
        ->condition('n.language', $lang)
        ->orderBy('n.title')
        ->execute();

    $items = zoomdojo_getOtherPages();
    foreach ($query as $item) {
        $item->url = drupal_get_path_alias('node/' . $item->nid);
        $items[] = $item;
    }

    return $items;
}

/**
 * Get list "Dialogs" pages
 */
function zoomdojo_getDialogsPages()
{
    global $language ;
    $lang  = $language->language;

    $query = db_select('node', 'n')
        ->fields('n', array('nid'));
    $query->addExpression('fdfrt.field_resume_title_value', 'title');
    $query->join('field_data_field_resume_title', 'fdfrt', 'fdfrt.entity_id=n.nid');
    $query = $query->condition('n.language', $lang)
        ->orderBy('title')
        ->execute();

    $items = array();
    foreach ($query as $item) {
        $item->url = drupal_get_path_alias('young-professionals/resume/' . $item->nid);
        $items[] = $item;
    }

    return $items;
}

/**
 * Get Events pages
 */
function zoomdojo_getEventsPages()
{
    return array(
        (object) array(
            'nid'   => 0,
            'title' => 'Events Home Page',
            'url'   => 'events',
        ),
        (object) array(
            'nid'   => 0,
            'title' => 'Past Events',
            'url'   => 'all-past-events',
        ),
    );
}

/**
 * Get list "Other" pages
 */
function zoomdojo_getOtherPages()
{
    return array(
        (object) array(
            'nid'   => 0,
            'title' => 'Home page',
            'url'   => '',
        ),
        (object) array(
            'nid'   => 0,
            'title' => 'Blog',
            'url'   => 'zoomple',
        ),
        (object) array(
            'nid'   => 0,
            'title' => 'Contact Us',
            'url'   => 'contact',
        ),
        (object) array(
            'nid'   => 0,
            'title' => 'Job Search Results',
            'url'   => 'find-jobs',
        ),
    );
}