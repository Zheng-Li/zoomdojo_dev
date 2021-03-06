<?php
function organization_manager_job_industries_list($form_state){

    $form['job_industries']['#tree'] = TRUE;

    $result = organization_manager_job_industries_get_data();

    foreach ($result as $item) {
        $form['job_industries'][$item->id] = array(
            'title' => array(
                '#markup' => $item->title,
            ),
            
            'id' => array(
                '#type' => 'hidden',
                '#size'          => 3,
                '#default_value' => $item->id,
                '#disabled'      => TRUE,
            ),
            'pid' => array(
                '#type' => 'hidden',
                '#default_value' => $item->pid,
                '#size'          => 3,
            ),
            
            'weight' => array(
                '#type'          => 'weight',
                '#title'         => t('Weight'),
                '#default_value' => $item->weight,
                '#delta'         => 50,
                '#title_display' => 'invisible',
                '#class' => 'tabledrag-hide'
            ),
            
            'depth' => array(
                '#type'  => 'hidden',
                '#value' => $item->depth,
            ),
            
        );
    }

     $form['actions']           = array('#type' => 'actions');
     $form['actions']['submit'] = array('#type'  => 'submit', '#value' => t('Save Changes'));
    return $form;
}

function organization_manager_job_industries_get_data(){
    $rootnodes = db_query('SELECT id, title, weight, pid
                       FROM {zd_job_industries}
                       WHERE (pid = 0)
                       ORDER BY title ASC');
    $itemtree  = array();
    $depth     = -1;
    foreach ($rootnodes as $parent) {
        organization_manager_job_industries_get_tree($parent, $itemtree, $depth);
    }
    return $itemtree;
}

function organization_manager_job_industries_get_tree($parentitem, &$itemtree = array(), &$depth = 0){
    $depth++;
    $parentitem->depth         = $depth;
    $itemtree[$parentitem->id] = $parentitem;
    $children                  = db_query('SELECT id, title, weight, pid
                      FROM {zd_job_industries}
                      WHERE (pid = :pid)
                      ORDER BY weight ASC', array(':pid' => $parentitem->id));
    foreach ($children as $child) {
        if (!in_array($child->id, array_keys($itemtree))) {
            organization_manager_job_industries_get_tree($child, $itemtree, $depth);
        }
    }
    $depth--;
    return;
}

function theme_organization_manager_job_industries_list($variables)
{
    $form = $variables['form'];

    $rows = array();

    foreach (element_children($form['job_industries']) as $id) {
        $form['job_industries'][$id]['weight']['#attributes']['class'] = array('example-item-weight');
        $form['job_industries'][$id]['id']['#attributes']['class']  = array('example-item-id');
        $form['job_industries'][$id]['pid']['#attributes']['class'] = array('example-item-pid');
        $class = array('draggable');
        $indent = theme('indentation', array('size' => $form['job_industries'][$id]['depth']['#value']));
        unset($form['job_industries'][$id]['depth']);
        $rows[] = array(
            'data'  => array(
                $indent . drupal_render($form['job_industries'][$id]['title']),
                array('data' => drupal_render($form['job_industries'][$id]['weight']), 'class' => 'tabledrag-hide'),
                array('data' =>drupal_render($form['job_industries'][$id]['id']), 'style' => 'display:none;'),
                array('data' =>drupal_render($form['job_industries'][$id]['pid']), 'style' => 'display:none;'),
                l(t('Edit'), 'admin/organization-manager/industry-types/edit/' . $id),
                l(t('Delete'), 'admin/organization-manager/industry-types/delete/' . $id),
            ),
            'class' => $class,
        );
    }

    $header = array(t('Name'), array('data' => t('Weight'), 'class' => 'tabledrag-hide'), array('data' => 'Operations', 'colspan' => 2));

    $table_id = 'example-items-table';

    $output = theme('table', array(
        'header'     => $header,
        'rows'       => $rows,
        'attributes' => array('id' => $table_id),
    ));

    $output .= drupal_render_children($form);

    drupal_add_tabledrag($table_id, 'match', 'parent', 'example-item-pid', 'example-item-pid', 'example-item-id', FALSE);

    drupal_add_tabledrag($table_id, 'order', 'sibling', 'example-item-weight', NULL, NULL, FALSE);

    return $output;
}

function organization_manager_job_industries_list_submit($form, &$form_state)
{
    foreach ($form_state['values']['job_industries'] as $id => $item) {
        db_query(
            "UPDATE {zd_job_industries} SET weight = :weight, pid = :pid WHERE id = :id", array(':weight' => $item['weight'], ':pid'    => $item['pid'], ':id'     => $id)
        );
    }
}

function organization_manager_job_industry_add($form, $formState)
{
    $id = arg(4);

    if ($id) {
        $jobType = db_select('zd_job_industries', 't')
            ->fields('t', array('id', 'title', 'fid', 'pageTitle', 'pageDescription', 'pageKeywords','internshipurl'))//mark
            ->condition('id', $id)
            ->execute()
            ->fetch();
    }
    
    $form['id']    = array(
        '#type'          => 'hidden',
        '#default_value' => !empty($id)?$id:0,
    );

    if(!$id){
        $data = organization_manager_job_industries_get_data();
        $data = array_values($data);
        $options = array();
        $options[0] = 'None';
        $depth = 0;
        foreach($data as $key=>$item){
            if($key && $item->pid == $data[$key-1]->id){ 
                $depth++;
            } elseif($key && $item->pid !== $data[$key-1]->pid) {
                $depth--;
            }
            if($item->pid == 0) $depth = 0;

            $options[$item->id] = ($depth?(' '.str_repeat('-',$depth).' '):'') . $item->title;
        }
        $form['pid'] = array(
            '#type'          => 'select',
            '#title'         => t('Parent'),
            '#required'      => FALSE,
            '#options'       => $options,
            '#default_value' => 0,
        );
    }
    
    $form['title'] = array(
        '#type'          => 'textfield',
        '#title'         => t('Title'),
        '#size'          => 60,
        '#maxlength'     => 255,
        '#required'      => TRUE,
        '#default_value' => $id ? $jobType->title : ''
    );
    if($id && $jobType->fid){
        $file = file_load($jobType->fid);
        $form['thumb'] = array(
            '#type'      => 'item',
            '#markup'     => '<img src="'.file_create_url($file->uri).'" width="200px" />',
        );
    }
    $form['image'] = array(
        '#title'                => t('Image'),
        '#type'                 => 'managed_file',
        '#description'          => t('The uploaded image will be displayed on this page using the image style choosen below.'),
        '#upload_location'      => 'public://industry_images/',
        '#required'             => TRUE,
        '#default_value'        => $id ? $jobType->fid : '',
        '#file_value_callbacks' => array('zoomdojo_blocks_deleteImage'),
	);
    //mark 
    $form['internship_url'] = array(
        '#type'          => 'textfield',
        '#title'         => t('Internship URL'),
        '#size'          => 60,
        '#maxlength'     => 255,
        '#required'      => FALSE,
        '#default_value' => $id ? $jobType->internshipurl : ''
    );

    //SEO
    $form['seo'] = array(
        '#type' => 'fieldset',
        '#title' => t('SEO'),
        '#collapsible' => TRUE,
        '#collapsed' => FALSE,
    );
    $form['seo']['page_title'] = array(
        '#type'          => 'textfield',
        '#title'         => t('Page title'),
        '#size'          => 60,
        '#maxlength'     => 255,
        '#default_value' => $id ? $jobType->pageTitle : ''
    );
    $form['seo']['page_description'] = array(
        '#type'          => 'textarea',
        '#title'         => t('Meta description'),
        '#default_value' => $id ? $jobType->pageDescription : ''
    );
    $form['seo']['page_keywords'] = array(
        '#type'          => 'textfield',
        '#title'         => t('Meta keywords'),
        '#size'          => 60,
        '#maxlength'     => 255,
        '#default_value' => $id ? $jobType->pageKeywords : ''
    );

    $form['save']  = array(
        '#type'  => 'submit',
        '#value' => 'save'
    );
    return $form;
}

function organization_manager_job_industry_add_submit($formId, &$formValue)
{
    global $user;
    $file         = file_load($formValue['values']['image']);
    $file->status = FILE_STATUS_PERMANENT;
	file_save($file);
    file_usage_add($file, 'organization_manager', 'organization_manager', $user->uid);
    $fields = array(
        'title'           => $formValue['values']['title'],
        'fid'             => $file->fid,
        'pageTitle'       => $formValue['values']['page_title'],
        'pageDescription' => $formValue['values']['page_description'],
        'pageKeywords'    => $formValue['values']['page_keywords'],
        //mark
        //'internshipurl'   => $formValue['values']['internship_url'],
    );
    if(isset($formValue['values']['pid'])){
        $fields['pid'] = $formValue['values']['pid'];
    }
    db_merge('zd_job_industries')
        ->key(array('id' => $formValue['values']['id']))
        ->fields($fields)
        ->execute();
    
    $urlAlias = drupal_lookup_path('alias',"featured-jobs/internships/{$formValue['values']['id']}");
    if( $urlAlias == '' ){
        $alternate_url = "featured-jobs/internships/".cleanString($formValue['values']['title']);
        $path = array(
            "source" => "featured-jobs/internships/{$formValue['values']['id']}",
            "alias" => $alternate_url
        );
        path_save($path);
    }
    $formValue['redirect'] = 'admin/organization-manager/industry-types';
}

function organization_manager_job_industry_delete()
{
    $id = arg(4);
    db_delete('zd_job_industries')
        ->condition('id', $id)
        ->execute();
    
    drupal_goto('admin/organization-manager/industry-types');
}

function cleanString($string, $separator = '-'){
	$accents = array('Š' => 'S', 'š' => 's', 'Ð' => 'Dj','Ž' => 'Z', 'ž' => 'z', 'À' => 'A', 'Á' => 'A', 'Â' => 'A', 'Ã' => 'A', 'Ä' => 'A', 'Å' => 'A', 'Æ' => 'A', 'Ç' => 'C', 'È' => 'E', 'É' => 'E', 'Ê' => 'E', 'Ë' => 'E', 'Ì' => 'I', 'Í' => 'I', 'Î' => 'I', 'Ï' => 'I', 'Ñ' => 'N', 'Ò' => 'O', 'Ó' => 'O', 'Ô' => 'O', 'Õ' => 'O', 'Ö' => 'O', 'Ø' => 'O', 'Ù' => 'U', 'Ú' => 'U', 'Û' => 'U', 'Ü' => 'U', 'Ý' => 'Y', 'Þ' => 'B', 'ß' => 'Ss','à' => 'a', 'á' => 'a', 'â' => 'a', 'ã' => 'a', 'ä' => 'a', 'å' => 'a', 'æ' => 'a', 'ç' => 'c', 'è' => 'e', 'é' => 'e', 'ê' => 'e', 'ë' => 'e', 'ì' => 'i', 'í' => 'i', 'î' => 'i', 'ï' => 'i', 'ð' => 'o', 'ñ' => 'n', 'ò' => 'o', 'ó' => 'o', 'ô' => 'o', 'õ' => 'o', 'ö' => 'o', 'ø' => 'o', 'ù' => 'u', 'ú' => 'u', 'û' => 'u', 'ý' => 'y', 'ý' => 'y', 'þ' => 'b', 'ÿ' => 'y', 'ƒ' => 'f');
	$string = strtr($string, $accents);
	$string = strtolower($string);
	$string = preg_replace('/[^a-zA-Z0-9\s]/', '', $string);
	$string = preg_replace('{ +}', ' ', $string);
	$string = trim($string);
	$string = str_replace(' ', $separator, $string);
 
	return $string;
}

function organization_manager_getIndustryTypePageTitle($title)
{
    $params = organization_manager_getFeaturedJobsQueryParams();
    if (!empty($params->industryId)) {
        $dbTitle = db_select('zd_job_industries', 'zji')
            ->fields('zji', array('pageTitle'))
            ->condition('id', $params->industryId)
            ->execute()
            ->fetchColumn();
    }
    return empty($dbTitle)?$title:$dbTitle;
}