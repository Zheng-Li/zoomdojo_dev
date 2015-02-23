<?php

/**
 * Slider list
 */
function zoomdojo_blocks_listVeteranBlocks()
{
	$form['slides']['#tree'] = TRUE;

    $results = zoomdojo_blocks_getData(0, 'veteran');
    
    foreach ($results as $item) {
        $form['slides'][$item->id] = array(
            'image' => array(
                '#markup' => '<img src="'.$item->image.'" width="100px" />',
            ),
            'title' => array(
                '#markup' => $item->title,
            ),
            'id' => array(
                '#type' => 'hidden',
                '#size'          => 3,
                '#default_value' => $item->id,
                '#disabled'      => TRUE,
            ),
            'weight' => array(
                '#type'          => 'weight',
                '#title'         => t('Weight'),
                '#default_value' => $item->weight,
                '#delta'         => 10,
                '#title_display' => 'invisible',
                '#class' => 'tabledrag-hide'
            ),
            'edit' => array(
                '#markup' => l('Edit', 'admin/zoomdojo/veteran/edit/'.$item->id),
            ),
            'delete' => array(
                '#markup' => l('Delete', 'admin/zoomdojo/veteran/'.$item->id.'/delete', array(
                        'attributes' => array(
                            'onclick' => "if (!confirm('Are you sure?')){return false;}"
                        )
                    )
                ),
            ),
        );
    }

    $form['description'] = array(
        '#type'          => 'text_format',
        '#title'         => t('Ddescription'),
        '#default_value' => variable_get('veteran_desc', ''),
        '#format'        => 'full_html',
    );

    $form['actions']           = array('#type' => 'actions');
    $form['actions']['submit'] = array('#type'  => 'submit', '#value' => t('Save Changes'));
    return $form;
}


function theme_zoomdojo_blocks_listVeteranBlocks($variables)
{
    $form = $variables['form'];
    $rows = array();
    foreach (element_children($form['slides']) as $id) {
        $form['slides'][$id]['weight']['#attributes']['class'] = array('example-item-weight');
        $rows[] = array(
          'data' => array(
              drupal_render($form['slides'][$id]['image']),
              drupal_render($form['slides'][$id]['title']),
              drupal_render($form['slides'][$id]['id']),
              drupal_render($form['slides'][$id]['weight']),
              drupal_render($form['slides'][$id]['edit']),
              drupal_render($form['slides'][$id]['delete']),
          ),
          'class' => array('draggable'),
        );
    }

    $header = array(
        array('data' => t('Image')),
        array('data' => t('Title'), 'colspan' => 2),
        array('data' => t('Weight')),
        array('data' => t('Operations'), 'colspan' => 2)
    );

    $table_id = 'example-items-table';

    $output = theme('table', array(
        'header' => $header,
        'rows' => $rows,
        'attributes' => array('id' => $table_id),
    ));
    $output .= drupal_render_children($form);

    drupal_add_tabledrag($table_id, 'order', 'sibling', 'example-item-weight');

    return $output;
}

/**
 * Save width veteran block
 */
function zoomdojo_blocks_listVeteranBlocks_submit($form, $form_state) {
    foreach ($form_state['values']['slides'] as $id => $item) {
        db_update('zd_slider')
          ->fields(array('weight' => $item['weight']))
          ->condition('id', $id)
          ->execute();
    }
    variable_set('veteran_desc', $form_state['values']['description']['value']);
}

/**
 * Get add form for block
 */
function zoomdojo_blocks_addVeteranBlock()
{
    $def = new stdClass();
    $def->title  = '';
    $def->weight = '';
    $def->id     = 0;
    $def->fid    = 0;
    $def->image  = '';
    $def->text   = '';
    $def->url    = '';
    return drupal_get_form('zoomdojo_blocks_VeteranBlockForm', $def);
}

/**
 * Get edit form for block
 */
function zoomdojo_blocks_editVeteranBlock($id)
{
    $def = zoomdojo_blocks_getData($id, 'veteran');
    return drupal_get_form('zoomdojo_blocks_VeteranBlockForm', $def);
}

/**
 * Veteran form
 */
function zoomdojo_blocks_VeteranBlockForm($formId, $form, $def)
{
    $form = array();
    $form['title'] = array(
        '#type'          => 'textfield', 
        '#title'         => t('Block title'), 
        '#size'          => 60,
        '#maxlength'     => 255, 
        '#required'      => TRUE,
        '#default_value' => !empty($def->title)?$def->title:'',
    );
    $form['weight'] = array(
        '#type'          => 'weight', 
        '#title'         => t('Weight'),
        '#required'      => TRUE,
        '#default_value' => !empty($def->weight)?$def->weight:'',
    );
    
    if (!empty($def->image)) {
        $form['image'] = array(
            '#markup' => '<img src="'.$def->image.'" width="200px" />',
        );
    }

    $form['id'] = array(
        '#type'          => 'textfield', 
        '#default_value' => !empty($def->id)?$def->id:0,
        '#prefix'        => '<div style="display:none;">',
        '#suffix'        => '</div>',
    );
    $form['fid'] = array(
        '#type'  => 'hidden', 
        '#value' => !empty($def->fid)?$def->fid:'',
    );

    $form['image_category_image_fid'] = array(
        '#title'                => t('Image'),
        '#title_display'        => 'invisible',
        '#type'                 => 'managed_file',
        '#description'          => t('The uploaded image will be displayed on this page using the image style choosen below.'),
        '#upload_location'      => 'public://veteran/',
        '#default_value'        => !empty($def->fid)?$def->fid:'',
        '#file_value_callbacks' => array('zoomdojo_blocks_deleteImage'),
        '#required'             => TRUE,
    );
    $form['text'] = array(
        '#type'          => 'text_format',
        '#title'         => t('Text'),
        '#default_value' => !empty($def->text)?$def->text:'',
        '#format'        => 'full_html',
    );
    $form['url'] = array(
        '#type'          => 'textfield', 
        '#title'         => t('Url'), 
        '#size'          => 60,
        '#maxlength'     => 255, 
        '#required'      => TRUE,
        '#default_value' => !empty($def->url)?$def->url:'',
    );
    $form['save'] = array(
        '#type'     => 'submit', 
        '#value'    => t('Save'),
    );
    $form['actions']['cancel'] = array(
        '#markup' => l(t('Cancel'), 'admin/zoomdojo/veteran'),
    );

    return $form;
}

/**
 * Implementation hook_submit
 */
function zoomdojo_blocks_VeteranBlockForm_submit($formId, $formValues)
{
    global $user;
    $id     = $formValues['values']['id'];
    $title  = $formValues['values']['title'];
    $url    = $formValues['values']['url'];
    $text   = $formValues['values']['text']['value'];
    $weight = $formValues['values']['weight'];
    $fid    = $formValues['values']['image_category_image_fid'];
    $file   = file_load($fid);
    file_usage_add($file, 'zoomdojo_blocks', 'zoomdojo_blocks', $user->uid);

    if (!empty($text)) {
        $db = db_merge('zd_slider')
            ->key(array('id' => $id, 'delta'  => 'veteran'))
            ->fields(array(
                'id'     => $id,
                'title'  => $title,
                'url'    => $url,
                'text'   => $text,
                'weight' => $weight,
                'fid'    => $file->fid,
                'delta'  => 'veteran',
            ))
            ->execute();
        drupal_set_message(t('Data successfully saved'));
    }
    drupal_goto('admin/zoomdojo/veteran');
}

/**
 * Get categories of Student Veterans
 */
function zoomdojo_blocks_getStudentVeteransCategory()
{
    return array(
        (object) array(
           'id'     => 0,
           'title'  => 'Pat Tillman Foundation',
           'fields' => array(
                (object) array(
                    'type' => 'text',
                    'name' => t('College Name'),
                ),
                (object) array(
                    'type' => 'link',
                    'name' => t('Url'),
                ),
                (object) array(
                    'type' => 'text',
                    'name' => t('City'),
                ),
                (object) array(
                    'type' => 'text',
                    'name' => t('State'),
                ),
            ),
        ),
        (object) array(
           'id'     => 1,
           'title'  => 'Student Veterans Association', 
           'fields' => array(
                (object) array(
                    'type' => 'text',
                    'name' => t('College Name'),
                ),
                (object) array(
                    'type' => 'link',
                    'name' => t('Url'),
                ),
                (object) array(
                    'type' => 'text',
                    'name' => t('City'),
                ),
                (object) array(
                    'type' => 'text',
                    'name' => t('State'),
                ),
            ),
        ),
        (object) array(
           'id'     => 2,
           'title'  => 'Veteran Students Organization',
           'fields' => array(
                (object) array(
                    'type' => 'text',
                    'name' => t('College Name'),
                ),
                (object) array(
                    'type' => 'link',
                    'name' => t('Url'),
                ),
                (object) array(
                    'type' => 'text',
                    'name' => t('City'),
                ),
                (object) array(
                    'type' => 'text',
                    'name' => t('State'),
                ),
            ),
        ),
        (object) array(
           'id'     => 3,
           'title'  => 'Veterans\' Association (Vets\' Club)',
           'fields' => array(
                (object) array(
                    'type' => 'text',
                    'name' => t('College Name'),
                ),
                (object) array(
                    'type' => 'link',
                    'name' => t('Url'),
                ),
                (object) array(
                    'type' => 'text',
                    'name' => t('City'),
                ),
                (object) array(
                    'type' => 'text',
                    'name' => t('State'),
                ),
            ),
        ),
        (object) array(
           'id'     => 4,
           'title'  => 'Other',
           'fields' => array(
                (object) array(
                    'type' => 'text',
                    'name' => t('Name'),
                ),
                (object) array(
                    'type' => 'link',
                    'name' => t('College Homepage'),
                ),
                (object) array(
                    'type' => 'link',
                    'name' => t('Career Center Link'),
                ),
                (object) array(
                    'type' => 'link',
                    'name' => t('Campus Veterans Center Link'),
                ),
            ),
        ),       
    );
}

/**
 * Get veterans student items
 */
function zoomdojo_blocks_getStudentVeteransData()
{
    $query = db_select('zd_veteran_items', 'zvi')
        ->fields('zvi')
        ->orderBy('weight')
        ->execute();
    $items = array();
    foreach ($query as $item) {
        $items[$item->cid][] = $item;
    }
    return $items;
}

/**
 * Edit Student Veterans page (admin)
 */
function zoomdojo_blocks_editStudentVeteransViewPage()
{
    if (sizeof($_POST)) {
        zoomdojo_blocks_editStudentVeteransViewPageSubmit($_POST);
    }

    drupal_add_css(drupal_get_path('module', 'zoomdojo_blocks') . '/css/jquery-ui-1.10.3.custom.min.css');
    drupal_add_css(drupal_get_path('module', 'zoomdojo_blocks') . '/css/zd-admin-items.css');

    drupal_add_js(drupal_get_path('module', 'zoomdojo_blocks') . '/js/jquery-1.9.1.js');
    drupal_add_js(drupal_get_path('module', 'zoomdojo_blocks') . '/js/jquery-ui-1.10.3.custom.min.js');
    drupal_add_js(drupal_get_path('module', 'zoomdojo_blocks') . '/js/underscore-min.js');
    drupal_add_js(drupal_get_path('module', 'zoomdojo_blocks') . '/js/backbone-min.js');
    drupal_add_js(drupal_get_path('module', 'zoomdojo_blocks') . '/js/jquery.tablednd.js');
    drupal_add_js(drupal_get_path('module', 'zoomdojo_blocks') . '/js/items/zd-admin-items.js');

    $items      = zoomdojo_blocks_getStudentVeteransData();
    $categories = zoomdojo_blocks_getStudentVeteransCategory();
    
    $variables = array(
        'categories'    => $categories,
        'items'         => $items,
    );
    return theme('zoomdojo_blocks_veterans_edit_students', $variables);
}

/**
 * Save student veterans items
 */
function zoomdojo_blocks_editStudentVeteransViewPageSubmit($val)
{
    $items = array();
    $ids   = array(0);
    if (isset($val['id'])) {
        foreach ($val['id'] as $cid => $v) {
            foreach ($v as $n => $i) {
                $field0 = trim($val['field0'][$cid][$n]);
                $field1 = trim($val['field1'][$cid][$n]);
                $field2 = trim($val['field2'][$cid][$n]);
                $field3 = trim($val['field3'][$cid][$n]);
                $weight = $val['weight'][$cid][$n];
                if (!empty($field0) || !empty($field1) || !empty($field2) || !empty($field3)) {
                    $ids[] = $i;
                    $items[] = array(
                        'id'     => $i,
                        'field0' => $field0,
                        'field1' => $field1,
                        'field2' => $field2,
                        'field3' => $field3,
                        'cid'    => $cid,
                        'weight' => $weight,
                    );
                }
            }
        }
        if (!empty($ids)) {
            db_delete('zd_veteran_items')
                ->condition('id', $ids, 'NOT IN')
                ->execute();
        }
        foreach ($items as $item) {
            db_merge('zd_veteran_items')
                ->key(array('id' => $item['id']))
                ->fields($item)
                ->execute();
        }
    }
}

/**
 * View Veteran blocks
 */
function zoomdojo_blocks_veteransViewPage()
{
    // seo
    drupal_add_html_head(array(
        '#tag' => 'meta',
        '#attributes' => array(
            'name' => 'description',
            'content' => "Finding jobs can be difficult as a veteran. Luckily, there are many resources to guide GIs in their career search.",
        ),
    ), 'description');
    drupal_add_html_head(array(
        '#tag' => 'meta',
        '#attributes' => array(
            'name' => 'keywords',
            'content' => "jobs for veterans, gi jobs, hiring veterans, veterans resources, careers for veterans",
        ),
    ), 'keywords');

    $blocks = zoomdojo_blocks_getData(0, 'veteran');
    $description = variable_get('veteran_desc', '');

    $variables = array(
        'blocks'      => $blocks,
        'description' => $description,
    );
    return theme('zoomdojo_blocks_veterans_view', $variables);
}

/**
 * View Student Veterans page
 */
function zoomdojo_blocks_studentVeteransViewPage()
{
    // seo
    drupal_add_html_head(array(
        '#tag' => 'meta',
        '#attributes' => array(
            'name' => 'description',
            'content' => "Education is a great tool for veterans, learn about college and career choices.",
        ),
    ), 'description');
    drupal_add_html_head(array(
        '#tag' => 'meta',
        '#attributes' => array(
            'name' => 'keywords',
            'content' => "veterans educaion, college for veterans, veterans college, college vets, gi education",
        ),
    ), 'keywords');

    $items      = zoomdojo_blocks_getStudentVeteransData();
    $categories = zoomdojo_blocks_getStudentVeteransCategory();
    
    drupal_add_js("jQuery(document).ready(function(){jQuery('#student-veterans-tab a:first').tab('show');});", 'inline');

    $variables = array(
        'categories'    => $categories,
        'items'         => $items,
    );
    return theme('zoomdojo_blocks_veterans_students_view', $variables);
}