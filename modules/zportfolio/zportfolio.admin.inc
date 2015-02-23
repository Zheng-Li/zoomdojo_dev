<?php

/**
 * Get Tips Blocks data
 */
function zportfolio_getHelpTips($id = 0, $order = null,$limit = 50) {
  $tip = db_select('users_portfolio_tips', 'ze')
      ->fields('ze')
      ->extend('TableSort');
  if(!is_null($order)){
    $tip->orderByHeader($order)
        ->extend('PagerDefault')
        ->limit($limit);
  }
  if (!empty($id)) {
    $tip = $tip->condition('id', $id)
        ->execute()
        ->fetch();
  }
  else {
    $tip = $tip->execute()
        ->fetchAll();
  }
  return $tip;
}

/**
 * Tips Blocks list
 */
function zportfolio_listHelpTips($types,$limit = 1) {
  
  drupal_add_js(drupal_get_path('module', 'zportfolio') . '/js/zportfolio-admin.js');
  
  $header = array(
    array('data' => t('Block Title'), 'field' => 'title'),
    array('data' => t('Type'), 'field' => 'type'),
    array('data' => t('Operations'), 'colspan' => 3)
  );
  
  $tips =  zportfolio_getHelpTips(null,$header,$limit);
  $rows = array();
  foreach ($tips as $item) {
    $rows[] = array(
      $item->title,
      $types[$item->type],
      l(t('Edit'), 'admin/zoomdojo/z-portfolio-help-tips/block/edit/' . $item->id ),
      l(
          t('Delete'), 'admin/zoomdojo/z-portfolio-help-tips/block/delete/' . $item->id , array(
        'attributes' => array(
          'class' => 'delete-row'
        )
          )
      ),
    );
  }
  $build['category_table'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
    '#weight' => 2,
  );
  $build['pager_bottom'] = array(
    '#theme' => 'pager',
    '#weight' => 3
  );
  return $build;
}

/**
 * Add & Edit Tips Block Form
 */
function zportfolio_editHelpTipsBlock($formId, $formState, $types, $eid = 0) {
  
  $edit = intval($eid) ? true : false;
  $def = new stdClass();
  $def->id = 0;
  $def->title = '';
  $def->type = 0;

  if ($edit) {
    $def = zportfolio_getHelpTips($eid);
  }
  $form = array();
  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Block title'),
    '#size' => 60,
    '#maxlength' => 255,
    '#required' => TRUE,
    '#default_value' => $def->title,
  );
  
  $form['text'] = array(
    '#type'          => 'text_format',
    '#title'         => t('Text'),
    '#default_value' => $def->text,
    '#format'        => 'full_html',
    '#required'      => TRUE,
    '#rows'          => 20,
  );

  $form['type'] = array(
    '#type' => 'select',
    '#title' => t('Block type'),
    '#required' => TRUE,
    '#options' => $types,
    '#default_value' => $def->type,
  );
  
  $form['id'] = array(
    '#type' => 'hidden',
    '#default_value' => $def->id,
  );

  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t(!$edit ? 'Save and add next' : 'Save'),
  );
  if (!$edit) {
    $form['save_end_exit'] = array(
      '#type' => 'submit',
      '#value' => t('Save and exit'),
    );
  }
  $form['actions']['cancel'] = array(
    '#markup' => l(t('Cancel'), 'admin/zoomdojo/z-portfolio-help-tips', array(
      'attributes' => array(
        'class' => 'button'
      )
        )
    ),
  );

  return $form;
}

/**
 * Implementation hook_submit
 */
function zportfolio_editHelpTipsBlock_submit($formId, $formValue) {
  $value = $formValue['values'];
  $eid = $value['id'];
  $title = $value['title'];
  $type = $value['type'];
  $text = isset($value['text']['value'])?$value['text']['value']:null;
  $op   = $formValue['values']['op'];
  $fields = array(
    'title' => $title,
    'type'  => $type,
    'text'  => $text
  );
  $status = db_merge('users_portfolio_tips')
      ->key(array('id' => $eid))
      ->fields($fields)
      ->execute();

  $lastId = $eid;
  if ($status == MergeQuery::STATUS_INSERT) {
    $lastId = db_query("SELECT LAST_INSERT_ID()")->fetchField();
  }

  if ($op === 'Save and add next') {
    
  }else{
    drupal_goto('admin/zoomdojo/z-portfolio-help-tips');
  }
}

/**
 * Delete Tips Block
 */
function zportfolio_deleteHelpTipsBlock($eid)
{
    $response = array(
        'status' => 'FAIL',
    );
    $eid = intval($eid);
    if (!empty($eid)) {
        $res = db_delete('users_portfolio_tips')
            ->condition('id', $eid)
            ->execute();
        if ($res) {
            $response['status'] = 'OK';
        }
    }
    print json_encode($response);
    exit();
}