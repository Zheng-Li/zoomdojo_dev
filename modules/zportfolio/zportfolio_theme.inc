<?php
/**
 * Additional functions for build of template
 */


define('SKILL_TYPE_LANGUAGES', 1);
define('SKILL_TYPE_COMPUTER', 2);
define('SKILL_TYPE_OTHER', 3);
define('SKILL_TYPE_AWARDS', 4);

/**
 * Zoomdojo education tab
 *
 * @param $variables
 * @return string $out
 */
function zportfolio_theme_education($variables)
{
    $variables['class'] = '';
    $y = date('Y');
    $emptyEducation = array(
        'institution'           => '',
        'city'                  => '',
        'state'                 => '',
        'country'               => '',
        'course'                => '',
        'date_type'             => 0,
        'start_mounth'          => 1,
        'start_year'            => $y,
        'end_mounth'            => 1,
        'end_year'              => $y,
        'major'                 => '',
        'minor'                 => '',
        'cumulativegpa'         => '',
        'honors'                => '',
        'relaventcoursework'    => '',
        'new'                   => true,
    );

    $newEducations = array();

    if (!empty($variables['educations']['new'])) {
        foreach ($variables['educations']['new'] as $k => $item) {
            $item['new'] = true;
            $newEducations['new'][$k] = $item;
        }
        unset($variables['educations']['new']);
    }

    $class = '';
    $hide = false;
    if (count($variables['educations']) == 0) {
        $class = 'hide';
        $hide = true;
    }
    $out = zportfolio_theme_btn('add-new-education-row-top', $class, 'Add Institution', '', true, true, $hide);
    $out .= theme('zportfolio_education', $variables);

    // new education
    if (!empty($newEducations)) {
        $variables['educations'] = $newEducations['new'];
        $out .= theme('zportfolio_education', $variables);
    }
    unset($variables['educations']);
    // js education template
    $variables['educations']['<%=index%>'] = $emptyEducation;
    $out .= '<script type="text/x-template" id="education-js-template">'
        . theme('zportfolio_education', $variables)
        . '</script>';
    $out .= '<script type="text/x-template" id="education-small-js-template">'
        . theme('zportfolio_education_small', array('js' => true))
        . '</script>';
    return $out . zportfolio_theme_btn('add-new-education-row', '', 'Add Institution', '', true);
}

/**
 * Zportfolio coursework theme for education tab
 *
 * @param $responsibilities
 * @param $eid
 * @param $error
 * @return string
 */
function zportfolio_theme_education_coursework($education, $eid, $error)
{
    $responsibilities = $education['coursework'];
    $out = '';
    if (!empty($responsibilities)) {
        if (!empty($responsibilities['new'])) {
            $newResponsibility = $responsibilities['new'];
            unset($responsibilities['new']);
            $responsibility = array();
            foreach ($newResponsibility as $rid => $item) {
                $item['new'] = true;
                $responsibility[$rid] = $item;
            }
        }
        $variables = array(
            'items' => $responsibilities,
            'eid'   => $eid,
            'new'   => isset($education['new'])?'[new]':'',
            'error' => isset($error[$eid]['coursework'])?$error[$eid]['coursework']:'',
        );
        $out .= theme('zportfolio_education_small', $variables);

        if (!empty($responsibility)) {
            $variables['items'] = $responsibility;
            $out .= theme('zportfolio_education_small', $variables);
        }
    }
    $out .= zportfolio_theme_btn('', 'add-coursework btn-mini', 'Add Coursework', $eid);
    return $out;
}

/**
 * Zoomdojo experience tab
 *
 * @param $variables
 * @return string $out
 */
function zportfolio_theme_experience($variables)
{
    $emptyExperience = array(
        'organization'   => '',
        'jobtitle'       => '',
        'city'           => '',
        'state'          => '',
        'country'        => '',
        'date_type'      => 0,
        'start_mounth'   => '',
        'start_year'     => '',
        'end_mounth'     => '',
        'end_year'       => '',
        'responsibility' => array(),
        'new'            => true,
    );

    $newExperiences = array();
    if (!empty($variables['experiences']['new'])) {
        foreach ($variables['experiences']['new'] as $k => $item) {
            $item['new'] = true;
            $newExperiences['new'][$k] = $item;
        }
        unset($variables['experiences']['new']);
    }

    $class = '';
    $hide = false;
    if (count($variables['experiences']) == 0) {
        $class = 'hide';
        $hide = true;
    }
    $out = zportfolio_theme_btn('add-new-experience-row-top',$class,'Add Organization', '', true, true, $hide);

    $out .= theme('zportfolio_experience', $variables);

    // new education
    if (!empty($newExperiences)) {
        $variables['experiences'] = $newExperiences['new'];
        $out .= theme('zportfolio_experience', $variables);
    }
    unset($variables['experiences']);

    // js experience template
    $variables['experiences']['<%=index%>'] = $emptyExperience;
    $out .= '<script type="text/x-template" id="experience-js-template">'
        . theme('zportfolio_experience', $variables)
        . '</script>';
    $out .= '<script type="text/x-template" id="experience-small-js-template">'
        . theme('zportfolio_experience_small', array('js' => true))
        . '</script>';

    return $out . zportfolio_theme_btn('add-new-experience-row','','Add Organization', '', true);
}

/**
 * Zportfolio responsibility theme for experience tab
 *
 * @param $responsibilities
 * @param $eid
 * @param $error
 * @return string
 */
function zportfolio_theme_experience_responsibility($experience, $eid, $error)
{
    $responsibilities = $experience['responsibility'];
    $out = '';
    if (!empty($responsibilities)) {
        if (!empty($responsibilities['new'])) {
            $newResponsibility = $responsibilities['new'];
            unset($responsibilities['new']);
            $responsibility = array();
            foreach ($newResponsibility as $rid => $item) {
                $item['new'] = true;
                $responsibility[$rid] = $item;
            }
        }
        $variables = array(
            'items' => $responsibilities,
            'eid'   => $eid,
            'new'   => isset($experience['new'])?'[new]':'',
            'error' => isset($error[$eid]['responsibility'])?$error[$eid]['responsibility']:'',
        );
        $out .= theme('zportfolio_experience_small', $variables);

        if (!empty($responsibility)) {
            $variables['items'] = $responsibility;
            $out .= theme('zportfolio_experience_small', $variables);
        }
    }
    $out .= zportfolio_theme_btn('', 'add-responsibility btn', 'Add Job Responsibility', $eid);
    return $out;
}

/**
 * Zoomdojo leadership tab
 *
 * @param $variables
 * @return string $out
 */
function zportfolio_theme_leadership($variables)
{
    $emptyLeadership = array(
        'organization'      => '',
        'designationtitle'  => '',
        'city'              => '',
        'state'             => '',
        'country'           => '',
        'date_type'         => 0,
        'start_mounth'      => '',
        'start_year'        => '',
        'end_mounth'        => '',
        'end_year'          => '',
        'details'           => '',
        'responsibility'    => array(),
        'new'               => true,
    );

    $newLeaderships = array();
    if (!empty($variables['leaderships']['new'])) {
        foreach ($variables['leaderships']['new'] as $k => $item) {
            $item['new'] = true;
            $newLeaderships['new'][$k] = $item;
        }
        unset($variables['leaderships']['new']);
    }

    $class = '';
    $hide = false;
    if (count($variables['leaderships']) == 0) {
        $class = 'hide';
        $hide = true;
    }
    $out = zportfolio_theme_btn('add-new-leadership-row-top',$class,'Add Organization', '', true, true, $hide);
    $out .= theme('zportfolio_leadership', $variables);

    // new education
    if (!empty($newLeaderships)) {
        $variables['leaderships'] = $newLeaderships['new'];
        $out .= theme('zportfolio_leadership', $variables);
    }
    unset($variables['leaderships']);

    // js experience template
    $variables['leaderships']['<%=index%>'] = $emptyLeadership;
    $out .= '<script type="text/x-template" id="leadership-js-template">'
        . theme('zportfolio_leadership', $variables)
        . '</script>';
    $out .= '<script type="text/x-template" id="leadership-small-js-template">'
        . theme('zportfolio_leadership_small', array('js' => true))
        . '</script>';

    return $out . zportfolio_theme_btn('add-new-leadership-row','','Add Organization', '', true);
}

/**
 * Zportfolio responsibility theme for leadership tab
 *
 * @param $responsibilities
 * @param $eid
 * @param $error
 * @return string
 */
function zportfolio_theme_leadership_responsibility($experience, $eid, $error)
{
    $responsibilities = $experience['responsibility'];
    $out = '';
    if (!empty($responsibilities)) {
        if (!empty($responsibilities['new'])) {
            $newResponsibility = $responsibilities['new'];
            unset($responsibilities['new']);
            $responsibility = array();
            foreach ($newResponsibility as $rid => $item) {
                $item['new'] = true;
                $responsibility[$rid] = $item;
            }
        }
        $variables = array(
            'items' => $responsibilities,
            'eid'   => $eid,
            'new'   => isset($experience['new'])?'[new]':'',
            'error' => isset($error[$eid]['responsibility'])?$error[$eid]['responsibility']:'',
        );
        $out .= theme('zportfolio_leadership_small', $variables);

        if (!empty($responsibility)) {
            $variables['items'] = $responsibility;
            $out .= theme('zportfolio_leadership_small', $variables);
        }
    }
    $out .= zportfolio_theme_btn('', 'add-leadership-responsibility btn', 'Add More Details', $eid);
    return $out;
}

/**
 * Zoomdojo volunteer work tab
 *
 * @param $variables
 * @return string $out
 */
function zportfolio_theme_volunteer($variables)
{
    $variables['class'] = '';
    $y = date('Y');
    $emptyVolunteer = array(
        'organization'      => '',
        'designationtitle'  => '',
        'city'              => '',
        'state'             => '',
        'country'           => '',
        'date_type'         => 0,
        'start_mounth'      => '',
        'start_year'        => '',
        'end_mounth'        => '',
        'end_year'          => '',
        'new'               => true,
    );

    $newVolunteers = array();
    if (!empty($variables['volunteers']['new'])) {
        foreach ($variables['volunteers']['new'] as $k => $item) {
            $item['new'] = true;
            $newVolunteers['new'][$k] = $item;
        }
        unset($variables['volunteers']['new']);
    }

    $class = '';
    $hide = false;
    if (count($variables['volunteers']) == 0) {
        $class = 'hide';
        $hide = true;
    }
    $out = zportfolio_theme_btn('add-new-volunteer-row-top',$class,'Add Organization', '', true, true, $hide);

    $out .= theme('zportfolio_volunteer', $variables);

    // new education
    if (!empty($newVolunteers)) {
        $variables['volunteers'] = $newVolunteers['new'];
        $out .= theme('zportfolio_volunteer', $variables);
    }
    unset($variables['volunteers']);
    // js education template
    $variables['volunteers']['<%=index%>'] = $emptyVolunteer;
    $out .= '<script type="text/x-template" id="volunteer-js-template">'
        . theme('zportfolio_volunteer', $variables)
        . '</script>';
    $out .= '<script type="text/x-template" id="volunteer-small-js-template">'
        . theme('zportfolio_volunteer_small', array('js' => true))
        . '</script>';
    return $out . zportfolio_theme_btn('add-new-volunteer-row','','Add Organization', '', true);
}

/**
 * Zportfolio responsibility theme for volunteer tab
 *
 * @param $responsibilities
 * @param $eid
 * @param $error
 * @return string
 */
function zportfolio_theme_volunteer_responsibility($experience, $eid, $error)
{
    $responsibilities = $experience['responsibility'];
    $out = '';
    if (!empty($responsibilities)) {
        if (!empty($responsibilities['new'])) {
            $newResponsibility = $responsibilities['new'];
            unset($responsibilities['new']);
            $responsibility = array();
            foreach ($newResponsibility as $rid => $item) {
                $item['new'] = true;
                $responsibility[$rid] = $item;
            }
        }
        $variables = array(
            'items' => $responsibilities,
            'eid'   => $eid,
            'new'   => isset($experience['new'])?'[new]':'',
            'error' => isset($error[$eid]['responsibility'])?$error[$eid]['responsibility']:'',
        );
        $out .= theme('zportfolio_volunteer_small', $variables);

        if (!empty($responsibility)) {
            $variables['items'] = $responsibility;
            $out .= theme('zportfolio_volunteer_small', $variables);
        }
    }
    $out .= zportfolio_theme_btn('', 'add-volunteer-responsibility btn', 'Add More Details', $eid);
    return $out;
}

/**
 * Zoomdojo custom tab
 *
 * @param $variables
 * @return string $out
 */
function zportfolio_theme_custom($variables)
{
    $emptySection = array(
        'title'   => '',
        'new'            => true,
    );

    $newItems = array();
    if (!empty($variables['sections']['new'])) {
        foreach ($variables['sections']['new'] as $k => $item) {
            $item['new'] = true;
            if (!empty($item['new'])) {
              if(sizeof($item['items']['new'])){
              foreach ($item['items']['new'] as $ki => $iitem) {
                  $iitem['new'] = true;
                  $item['items'][$ki] = $iitem;
              }
              unset($item['items']['new']);
              }
            }
            $newItems['new'][$k] = $item;
        }
        unset($variables['sections']['new']);
    }

    $out = theme('zportfolio_custom', $variables);

    // new education
    if (!empty($newItems)) {
        $variables['sections'] = $newItems['new'];
        $out .= theme('zportfolio_custom', $variables);
    }
    unset($variables['custom']);

    // js custom template
    $variables['sections']['<%=index%>'] = $emptySection;
    $out .= '<script type="text/x-template" id="custom-js-template">'
        . theme('zportfolio_custom', array('js' => true,'button'=>zportfolio_theme_btn('add-custom-<%= sid %>', 'add-custom new', 'Add Item', '<%= sid %>', true),'buttonTop'=>zportfolio_theme_btn('add-custom-top-<%= sid %>', 'add-custom-top new hide', 'Add Item', '<%= sid %>', true, true, true)))
        . '</script>';
    $out .= '<script type="text/x-template" id="custom-small-js-template">'
        . theme('zportfolio_custom_small', array('js' => true, 'years'=>$variables['years'], 'years_to'=>$variables['years_to'],'months'=>$variables['months']))
        . '</script>';

    return $out;
}

/**
 * Zportfolio item theme for custom tab
 *
 * @param $section
 * @param $sid
 * @param $error
 * @return string
 */
function zportfolio_theme_custom_item($section, $sid, $error, $years, $years_to, $months)
{
    $items = $section['items'];
    $out = '';
    
    if (!empty($items)) {
        if (!empty($items['new'])) {
            $newResponsibility = $items['new'];
            unset($items['new']);
            $responsibility = array();
            foreach ($newResponsibility as $rid => $item) {
                $item['new'] = true;
                $responsibility[$rid] = $item;
            }
        }
        $variables = array(
            'items' => $items,
            'sid'   => $sid,
            'new'   => isset($section['new'])?'[new]':'',
            'error' => isset($error[$sid]['items'])?$error[$sid]['items']:'',
            'years' => $years,
            'years_to' => $years_to,
            'months' => $months
        );

        $out .= theme('zportfolio_custom_small', $variables);

        if (!empty($responsibility)) {
            $variables['items'] = $responsibility;
            $out .= theme('zportfolio_custom_small', $variables);
        }
    }
    $out .= zportfolio_theme_btn('add-custom-'.$sid, 'add-custom', 'Add Item', $sid, true);
    return $out;
}

/**
 * Zoomdojo other tab
 *
 * @param $variables
 * @return string
 */
function zportfolio_theme_skill($variables)
{
    $variables['languages'] = zportfolio_theme_languages(array(
        'items'      => zportfolio_skillsWrapper($variables['skills'], SKILL_TYPE_LANGUAGES),
        'langs'      => zportfolio_getLanguages(),
        'langLevels' => zportfolio_getLanguagesLevel(),
    ));
    $variables['computer'] = zportfolio_theme_skill_other(array(
        'items' => zportfolio_skillsWrapper($variables['skills'], SKILL_TYPE_COMPUTER),
    ), SKILL_TYPE_COMPUTER);
    $variables['otherSkills'] = zportfolio_theme_skill_other(array(
        'items' => zportfolio_skillsWrapper($variables['skills'], SKILL_TYPE_OTHER),
    ), SKILL_TYPE_OTHER);
    $variables['award'] = zportfolio_theme_skill_other(array(
        'items' => zportfolio_skillsWrapper($variables['skills'], SKILL_TYPE_AWARDS),
    ), SKILL_TYPE_AWARDS);
    return theme('zportfolio_other', $variables);
}

/**
 * Check is array empty
 *
 * @param $item
 * @param $type
 * @return array
 */
function zportfolio_skillsWrapper($item, $type)
{
    return !empty($item[$type])?$item[$type]:array();
}

/**
 * Language templates
 *
 * @param $variables
 * @return string
 */
function zportfolio_theme_languages($variables)
{
    $emptyLanguage = array(
        'val1' => 0,
        'val2' => '',
        'val3' => '',
        'val4' => '',
        'val5' => '',
        'new'  => true,
    );
    $out = '';
    if (!empty($variables['items']['new'])) {
        $newSkillLanguages = array();
        foreach ($variables['items']['new'] as $key => $item) {
            $item['new'] = true;
            $newSkillLanguages[$key] = $item;
        }
        unset($variables['items']['new']);
    }
    $out .= theme('zportfolio_other_language', $variables);
    if (!empty($newSkillLanguages)) {
        $variables['items'] = $newSkillLanguages;
        $out .= theme('zportfolio_other_language', $variables);
    }
    // js language template
    unset($variables['items']);
    $variables['items']['<%=index%>'] = $emptyLanguage;
    $out .= '<script type="text/x-template" id="language-js-template">'
        . theme('zportfolio_other_language', $variables)
        . '</script>';
    return $out;
}

/**
 * Other skill template
 *
 * @param $variables
 * @param $type
 * @return string
 */
function zportfolio_theme_skill_other($variables, $type)
{
    $variables['type'] = $type;
    $emptySkill = array(
        'val1' => '',
        'val2' => '',
        'val3' => '',
        'val4' => '',
        'val5' => '',
        'new'  => true,
    );
    $out = '';
    if (!empty($variables['items']['new'])) {
        $newSkills = array();
        foreach ($variables['items']['new'] as $key => $item) {
            $item['new'] = true;
            $newSkills[$key] = $item;
        }
        unset($variables['items']['new']);
    }
    $out .= theme('zportfolio_other_skill', $variables);
    if (!empty($newSkills)) {
        $variables['items'] = $newSkills;
        $out .= theme('zportfolio_other_skill', $variables);
    }
    // js skill template
    unset($variables['items']);
    $variables['items']['<%=index%>'] = $emptySkill;
    if ($type == SKILL_TYPE_AWARDS) {
        $variables['type'] = '<%=type%>';
        $out .= '<script type="text/x-template" id="skill-js-template">'
            . theme('zportfolio_other_skill', $variables)
            . '</script>';
    }
    return $out;
}

/**
 * Button template
 *
 * @param $id
 * @param string $class
 * @param string $text
 * @param $eid
 * @return string
 */
function zportfolio_theme_btn($id, $class = '', $text = 'Add new', $eid = '', $double = false, $top = false, $hideSaveBtn = false)
{
    return theme('zportfolio_add_btn', array(
        'idName' => $id,
        'class'  => $class,
        'text'   => $text,
        'eid'    => $eid,
        'double' => $double,
        'isTop'  => $top,
        'hideSaveBtn' => $hideSaveBtn,
    ));
}

/**
 * Get date for template
 *
 * @return array
 */
function zportfolio_getDate($future = 0, $past = 80)
{
    $years = array();
    $y = date('Y');
    for ($i = $y+$future; $i >= $y - $past; $i--) {
        $years[] = $i;
    }
    $months = getMonths();
    return array(
        'years'  => $past == 0 ? array_reverse($years) : $years,
        'months' => $months,
    );
}

function getMonths($id = null)
{
    $months = array(
        0  => 'none',
        1  => 'January',
        2  => 'February',
        3  => 'March',
        4  => 'April',
        5  => 'May',
        6  => 'June',
        7  => 'July ',
        8  => 'August',
        9  => 'September',
        10 => 'October',
        11 => 'November',
        12 => 'December',
        13 => 'Spring',
        14 => 'Summer',
        15 => 'Fall',
        16 => 'Winter',

    );
    return ($id === null)?$months:$months[$id];
}

/**
 * Get languages array
 *
 * @return array
 */
function zportfolio_getLanguages(){
    return array(
        0 => t('Choose Option'),
        1 => t('English'),
        2 => t('Mandarin'),
        3 => t('French'),
        4 => t('Hindi'),
        5 => t('Spanish'),
        6 => t('Other'),
    );
}

/**
 * Get languages level array
 *
 * @return array
 */
function zportfolio_getLanguagesLevel(){
    return array(
        0 => t('Choose Option'),
        1 => t('Excellent'),
        2 => t('Good'),
        3 => t('Conversational'),
    );
}