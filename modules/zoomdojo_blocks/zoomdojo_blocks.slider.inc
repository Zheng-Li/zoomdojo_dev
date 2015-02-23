<?php

/**
 * Slider list
 */
function zoomdojo_blocks_listSlider()
{
	$form['slides']['#tree'] = TRUE;

    $results = zoomdojo_blocks_getData();
    
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
                '#markup' => l('Edit', 'admin/zoomdojo/slider/edit/'.$item->id),
            ),
            'delete' => array(
                '#markup' => l('Delete', 'admin/zoomdojo/slider/'.$item->id.'/delete', array(
                        'attributes' => array(
                            'onclick' => "if (!confirm('Are you sure?')){return false;}"
                        )
                    )
                ),
            ),
        );
    }

    $form['actions']           = array('#type' => 'actions');
    $form['actions']['submit'] = array('#type'  => 'submit', '#value' => t('Save Changes'));
    return $form;
}


function theme_zoomdojo_blocks_listSlider($variables)
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

function zoomdojo_blocks_listSlider_submit($form, $form_state) {
    foreach ($form_state['values']['slides'] as $id => $item) {
        db_update('zd_slider')
          ->fields(array('weight' => $item['weight']))
          ->condition('id', $id)
          ->execute();
    }
}

/**
 * Add slide
 */
function zoomdojo_blocks_addSlide()
{
	$form = array();
	$form['title'] = array(
		'#type'			=> 'textfield', 
		'#title'		=> t('Title'), 
		'#size'			=> 60,
		'#maxlength'	=> 255, 
		'#required'		=> TRUE,
	);
	$form['weight'] = array(
		'#type'			=> 'weight', 
		'#title'		=> t('Weight'),
		'#required'		=> TRUE,
	);
	$form['image_category_image_fid'] = array(
		'#title'			=> t('Image'),
		'#type'				=> 'managed_file',
		'#description'		=> t('The uploaded image will be displayed on this page using the image style choosen below.'),
		'#upload_location'	=> 'public://slider_images/',
		'#required'			=> TRUE,
	);
    $form['text'] = array(
        '#type'          => 'text_format',
        '#title'         => t('Text'),
        '#format'        => 'full_html',
    );
    $form['url'] = array(
        '#type'          => 'textfield', 
        '#title'         => t('Url'), 
        '#size'          => 60,
        '#maxlength'     => 255, 
        '#required'      => TRUE,
    );
	$form['save'] = array(
		'#type'		=> 'submit', 
		'#value'	=> t('Save'),
	);
	$form['actions']['cancel'] = array(
		'#markup' => l(t('Cancel'), 'admin/zoomdojo/slider'),
	);
	return $form;
}

/**
 *
 */
function zoomdojo_blocks_addSlide_submit($formId, $formValues)
{
    global $user;
    $title        = $formValues['values']['title'];
    $text         = $formValues['values']['text']['value'];
    $url          = $formValues['values']['url'];
    $weight       = $formValues['values']['weight'];
    $file         = file_load($formValues['values']['image_category_image_fid']);
    $file->status = FILE_STATUS_PERMANENT;
	file_save($file);
    file_usage_add($file, 'zoomdojo_blocks', 'zoomdojo_blocks', $user->uid);

	if (!empty($title)) {
		$db = db_insert('zd_slider')
			->fields(array(
                'title'  => $title,
                'fid'    => $file->fid,
                'weight' => $weight,
                'text'   => $text,
                'url'    => $url,
                'delta'  => 'slider',
			))
			->execute();
		drupal_set_message(t('Data successfully saved'));
	}
}

/**
 * Edit slide
 */
function zoomdojo_blocks_editSlide()
{
	$id = intval(arg(4));
    $slide = zoomdojo_blocks_getData($id);

    $form = array();
    $form['title'] = array(
        '#type'          => 'textfield', 
        '#title'         => t('Block title'), 
        '#size'          => 60,
        '#maxlength'     => 255, 
        '#required'      => TRUE,
        '#default_value' => !empty($slide->title)?$slide->title:'',
    );
    $form['weight'] = array(
        '#type'          => 'weight', 
        '#title'         => t('Weight'),
        '#required'      => TRUE,
        '#default_value' => !empty($slide->weight)?$slide->weight:'',
    );
    
    if (!empty($slide->image)) {
        $form['image'] = array(
            '#markup' => '<img src="'.$slide->image.'" width="200px" />',
        );
    }

    $form['id'] = array(
        '#type'          => 'textfield', 
        '#default_value' => !empty($slide->id)?$slide->id:'',
        '#prefix'        => '<div style="display:none;">',
        '#suffix'        => '</div>',
    );
    $form['fid'] = array(
        '#type'  => 'hidden', 
        '#value' => !empty($slide->fid)?$slide->fid:'',
    );

    $form['image_category_image_fid'] = array(
        '#title'                => t('Image'),
        '#title_display'        => 'invisible',
        '#type'                 => 'managed_file',
        '#description'          => t('The uploaded image will be displayed on this page using the image style choosen below.'),
        '#upload_location'      => 'public://slider_images/',
        '#default_value'        => !empty($slide->fid)?$slide->fid:'',
        '#file_value_callbacks' => array('zoomdojo_blocks_deleteImage'),
    );
    $form['text'] = array(
        '#type'          => 'text_format',
        '#title'         => t('Text'),
        '#default_value' => !empty($slide->text)?$slide->text:'',
        '#format'        => 'full_html',
    );
    $form['url'] = array(
        '#type'          => 'textfield', 
        '#title'         => t('Url'), 
        '#size'          => 60,
        '#maxlength'     => 255, 
        '#required'      => TRUE,
        '#default_value' => !empty($slide->url)?$slide->url:'',
    );
    $form['save'] = array(
        '#type'     => 'submit', 
        '#value'    => t('Save'),
    );
    $form['actions']['cancel'] = array(
        '#markup' => l(t('Cancel'), 'admin/zoomdojo/slider'),
    );

    return $form;
}

/**
 *
 */
function zoomdojo_blocks_editSlide_submit($formId, $formValues)
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
        $db = db_update('zd_slider')
            ->fields(array(
                'title'  => $title,
                'url'    => $url,
                'text'   => $text,
                'weight' => $weight,
                'fid'    => $file->fid,
            ))
            ->condition('id', $id)
            ->execute();
        drupal_set_message(t('Data successfully saved'));
    }
    drupal_goto('admin/zoomdojo/slider');
}

/**
 * Delete slide
 */
function zoomdojo_blocks_deleteSlide($id, $callbackPath)
{
	$id = intval($id);
    if (!empty($id)) {
        $fid = db_select('zd_slider', 'zs')
            ->fields('zs', array('fid'))
            ->condition('id', $id)
            ->execute()
            ->fetchColumn();
        $file = file_load($fid);
        file_delete($file);
        db_delete('zd_slider')
            ->condition('id', $id)
            ->execute();
    }
    drupal_goto('admin/zoomdojo/' . $callbackPath);
}

/**
 * Delete image
 */
function zoomdojo_blocks_deleteImage($element, $input, $form_state)
{
    if (!empty($input['fid']) && isset($form_state['input']['_triggering_element_value'])) {
    	$file = file_load($input['fid']);
        file_delete($file);
    }
    return $form_state;
}

/**
 * Get slider data
 */
function zoomdojo_blocks_getData($id = 0, $delta = 'slider')
{
	$results = db_select('zd_slider', 'zs');
    $results->leftJoin('file_managed', 'fm', 'fm.fid = zs.fid');
    $results->fields('zs')->fields('fm', array('uri'));
    if ($id > 0) {
        $results->condition('id', $id);
    }
	$results = $results->condition('delta', $delta)
        ->orderBy('weight', 'ASC')
		->execute();

    $sliders = array();
    foreach ($results as $res) {
        $res->image = file_create_url($res->uri);
        $sliders[]  = $res;
    }
    if ($id > 0) {
        return $sliders[0];
    }
    return $sliders;
}

/**
 * View Slider
 */
function zoomdojo_blocks_sliderView()
{
    $blocks = zoomdojo_blocks_getData();

    $variables = array(
        'blocks' => $blocks,
    );
    return theme('zoomdojo_blocks_slider_view', $variables);
}