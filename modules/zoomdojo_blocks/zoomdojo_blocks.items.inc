<?php

/**
 * Get list items category
 */
function zoomdojo_blocks_getItemsCategories()
{
    drupal_add_js(drupal_get_path('module', 'zoomdojo_blocks') . '/js/items/zd-admin-items.js');
    $limit = 10;
    $header = array(
        array('data' => t('Category title'), 'field' => 'title'),
        array('data' => t('Begin words'), 'field' => 'begin_word'),
        array('data' => t('Show count items'), 'field' => 'num_show'),
        array('data' => t('Weight'), 'field' => 'weight'),
        array('data' => t('Operations'), 'colspan' => 2)
    );
    
    $query = db_select('zd_items_category', 'zic')
        ->fields('zic');
    $query->addExpression('begin_word', 'beginWord');
    $query->addExpression('num_show', 'numShow');
    $query = $query->extend('TableSort')
        ->orderByHeader($header)
        ->extend('PagerDefault')
        ->limit($limit)
        ->orderBy('weight');
    $results = $query->execute();

    $rows = array();
    foreach ($results as $item) {
        $rows[] = array(
            $item->title,
            $item->beginWord,
            $item->numShow,
            $item->weight,
            l(t('Edit'), 'admin/zoomdojo/items-block/categories/edit/' . $item->id),
            l(
                t('Delete'), 'admin/zoomdojo/items-block/categories/delete/' . $item->id, array(
                    'attributes' => array(
                        'class' => 'delete-items-category'
                    )
                )
            ),
        );
    }
    $build['category_table'] = array(
        '#theme'  => 'table',
        '#header' => $header,
        '#rows'   => $rows,
        '#weight' => 2,
    );
    $build['pager_bottom'] = array(
        '#theme' => 'pager',
        '#weight' => 3
    );
    return $build;
}

/**
 * Add new items category
 */
function zoomdojo_blocks_addItemsCategoryForm()
{
    drupal_set_title('Add category');
    $form['title'] = array(
        '#type'      => 'textfield', 
        '#title'     => t('Tab title'), 
        '#size'      => 60,
        '#maxlength' => 255, 
        '#required'  => TRUE,
    );
    $form['words'] = array(
        '#type'      => 'textfield', 
        '#title'     => t('Begin words'), 
        '#size'      => 60,
        '#maxlength' => 255, 
        '#required'  => TRUE,
    );
    $form['number'] = array(
        '#type'      => 'textfield', 
        '#title'     => t('Show count items'), 
        '#size'      => 10,
        '#maxlength' => 255, 
        '#required'  => TRUE,
    );
    $form['weight'] = array(
        '#type'          => 'weight', 
        '#title'         => t('Weight'), 
        '#delta'         => 20,
        '#default_value' => 0,
    );
    $form['save'] = array(
        '#type'     => 'submit', 
        '#value'    => t('Save'),
    );
    $form['actions']['cancel'] = array(
        '#markup' => l(t('Cancel'), 'admin/zoomdojo/items-block/categories'),
    );
    return $form;
}

/**
 * Implementation hook_validate
 */
function zoomdojo_blocks_addItemsCategoryForm_validate($formId, $formValue)
{
    if (!is_numeric($formValue['values']['number'])) {
        form_set_error('number', t('This field must be numeric'));
    }
}

/**
 * Implementation hook_submit
 */
function zoomdojo_blocks_addItemsCategoryForm_submit($formId, $formValue)
{
    $name = $formValue['values']['title'];
    $res = db_insert('zd_items_category')
        ->fields(
            array(
                'title'      => $formValue['values']['title'],
                'begin_word' => $formValue['values']['words'],
                'num_show'   => $formValue['values']['number'],
                'weight'     => $formValue['values']['weight'],
            )
        )->execute();
    if ($res) {
        drupal_set_message(t('Category :name has been created', array(':name' => $name)), 'status');
    } else {
        drupal_set_message(t('Category :name hasn\'t been created', array(':name' => $name)), 'error');
    }
}

/**
 * Edit items categiry
 */
function zoomdojo_blocks_editItemsCategoryForm()
{
    $cid = intval(arg(5));
    drupal_set_title('Edit category');

    $def = db_select('zd_items_category', 'zic')
        ->fields('zic');
    $def->addExpression('begin_word', 'beginWord');
    $def->addExpression('num_show', 'numShow');
    $def = $def->condition('id', $cid)
        ->execute()
        ->fetch();
    
    $form['title'] = array(
        '#type'          => 'textfield', 
        '#title'         => t('Tab title'), 
        '#size'          => 60,
        '#maxlength'     => 255, 
        '#required'      => TRUE,
        '#default_value' => $def->title,
    );
    $form['words'] = array(
        '#type'          => 'textfield', 
        '#title'         => t('Begin words'), 
        '#size'          => 60,
        '#maxlength'     => 255, 
        '#required'      => TRUE,
        '#default_value' => $def->beginWord,
    );
    $form['number'] = array(
        '#type'          => 'textfield', 
        '#title'         => t('Show count items'), 
        '#size'          => 10,
        '#maxlength'     => 255, 
        '#required'      => TRUE,
        '#default_value' => $def->numShow,
    );
    $form['weight'] = array(
        '#type'          => 'weight', 
        '#title'         => t('Weight'), 
        '#delta'         => 20,
        '#default_value' => $def->weight,
    );
    $form['id'] = array(
        '#type'          => 'hidden', 
        '#default_value' => $def->id,
    );
    $form['save'] = array(
        '#type'     => 'submit', 
        '#value'    => t('Save'),
    );
    $form['actions']['cancel'] = array(
        '#markup' => l(t('Cancel'), 'admin/zoomdojo/items-block/categories'),
    );
    return $form;
}

/**
 * Implementation hook_validate
 */
function zoomdojo_blocks_editItemsCategoryForm_validate($formId, $formValue)
{
    if (!is_numeric($formValue['values']['number'])) {
        form_set_error('number', t('This field must be numeric'));
    }
}

/**
 * Implementation hook_submit
 */
function zoomdojo_blocks_editItemsCategoryForm_submit($formId, $formValue)
{
    $name = $formValue['values']['title'];
    $res = db_update('zd_items_category')
        ->fields(
            array(
                'title'      => $formValue['values']['title'],
                'begin_word' => $formValue['values']['words'],
                'num_show'   => $formValue['values']['number'],
                'weight'     => $formValue['values']['weight'],
            )
        )->condition('id', $formValue['values']['id'])
        ->execute();
    if ($res) {
        drupal_set_message(t('Category :name has been changed', array(':name' => $name)), 'status');
    } else {
        drupal_set_message(t('Category :name hasn\'t been changed', array(':name' => $name)), 'error');
    }
    drupal_goto('admin/zoomdojo/items-block/categories');
}

/**
 * Delete items category (ajax)
 */
function zoomdojo_blocks_deleteItemsCategory($cid)
{
    $response = array(
        'status' => 'FAIL',
    );
    $cid = intval($cid);
    if (!empty($cid)) {
        $res = db_delete('zd_items_category')
            ->condition('id', $cid)
            ->execute();
        if ($res) {
            $response['status'] = 'OK';
        }
    }
    print json_encode($response);
    exit();
}

/**
 * Get list items blocks
 */
function zoomdojo_blocks_getItemsBlocks()
{
    drupal_add_js(drupal_get_path('module', 'zoomdojo_blocks') . '/js/items/zd-admin-items.js');
    $limit = 10;
    $header = array(
        array('data' => t('Block name'), 'field' => 'name'),
        array('data' => t('Operations'), 'colspan' => 4)
    );
    
    $query = db_select('zd_blocks', 'zb')
        ->fields('zb');
    $query = $query->extend('TableSort')
        ->orderByHeader($header)
        ->extend('PagerDefault')
        ->limit($limit)
        ->condition('delta', 'items');
    $results = $query->execute();

    $rows = array();
    foreach ($results as $item) {
        $rows[] = array(
            $item->name,
            l(t('Edit'), 'admin/zoomdojo/items-block/blocks/edit/' . $item->id),
            l(
                t('Configure visible area'), 
                'admin/structure/block/manage/zoomdojo_blocks/zoomdojo_blocks_'.$item->id.'/configure', array(
                    'attributes' => array(
                        'target' => '_blank'
                    )
                )
            ),
            l(t('Configure'), 'admin/zoomdojo/items-block/blocks/config/' . $item->id),
            l(
                t('Delete'), 'admin/zoomdojo/items-block/blocks/delete/' . $item->id, array(
                    'attributes' => array(
                        'class' => 'delete-items-block'
                    )
                )
            ),
        );
    }
    $build['category_table'] = array(
        '#theme'  => 'table',
        '#header' => $header,
        '#rows'   => $rows,
        '#weight' => 2,
    );
    $build['pager_bottom'] = array(
        '#theme' => 'pager',
        '#weight' => 3
    );
    return $build;
}

/**
 * Add new items block
 */
function zoomdojo_blocks_addItemsBlocksForm()
{
    drupal_set_title('Add block');
    $form['name'] = array(
        '#type'      => 'textfield', 
        '#title'     => t('Block name'), 
        '#size'      => 60,
        '#maxlength' => 255, 
        '#required'  => TRUE,
    );
    $form['save'] = array(
        '#type'     => 'submit', 
        '#value'    => t('Save'),
    );
    $form['save_and_config'] = array(
        '#type'     => 'submit', 
        '#value'    => t('Save and Configure'),
    );
    $form['actions']['cancel'] = array(
        '#markup'     => l(t('Cancel'), 'admin/zoomdojo/items-block/blocks', array(
            'attributes' => array(
                    'class' => 'button',
                )
            ) 
        ),
    );
    return $form;
}

/**
 * Implementation hook_submit
 */
function zoomdojo_blocks_addItemsBlocksForm_submit($formId, $formValue)
{
    $themes = list_themes();
    $themeName = '';
    foreach ($themes as $theme) {
        if ($theme->status == 1 && $theme->name != 'seven') {
            $themeName = $theme->name;
        }
    }

    $name = $formValue['values']['name'];
    $res = db_insert('zd_blocks')
        ->fields(
            array(
                'name'  => $name,
                'delta' => 'items',
            )
        )->execute();
    if ($res) {
        drupal_set_message(t('Block :name has been created', array(':name' => $name)), 'status');
        //insert block
        db_insert('block')
            ->fields(
                array(
                    'module'     => 'zoomdojo_blocks',
                    'delta'      => 'zoomdojo_blocks_'.$res,
                    'theme'      => $themeName,
                    'status'     => '0',
                    'weight'     => '0',
                    'region'     => '-1',
                    'custom'     => '0',
                    'visibility' => '0',
                    'cache'      => '1',
                    'i18n_mode'  => '0',
                    'pages'      => '',
                )
            )
            ->execute();
        if ($formValue['triggering_element']['#value'] !== 'Save') {
            drupal_goto('admin/zoomdojo/items-block/blocks/config/'.$res);
        }
    } else {
        drupal_set_message(t('Block :name hasn\'t been created', array(':name' => $name)), 'error');
    }
}

/**
 * Edit items block
 */
function zoomdojo_blocks_editItemsBlocksForm()
{
    $bid = intval(arg(5));
    drupal_set_title('Edit block');

    $def = db_select('zd_blocks', 'zb')
        ->fields('zb')
        ->condition('id', $bid)
        ->execute()
        ->fetch();
    
    $form['name'] = array(
        '#type'          => 'textfield', 
        '#title'         => t('Block name'), 
        '#size'          => 60,
        '#maxlength'     => 255, 
        '#required'      => TRUE,
        '#default_value' => $def->name,
    );
    $form['id'] = array(
        '#type'          => 'hidden', 
        '#default_value' => $def->id,
    );
    $form['save'] = array(
        '#type'     => 'submit', 
        '#value'    => t('Save'),
    );
    $form['save_and_config'] = array(
        '#type'     => 'submit', 
        '#value'    => t('Save and Configure'),
    );
    $form['actions']['cancel'] = array(
        '#markup'     => l(t('Cancel'), 'admin/zoomdojo/items-block/blocks', array(
            'attributes' => array(
                    'class' => 'button',
                )
            ) 
        ),
    );
    return $form;
}

/**
 * Implementation hook_submit
 */
function zoomdojo_blocks_editItemsBlocksForm_submit($formId, $formValue)
{
    $name = $formValue['values']['name'];
    $res = db_update('zd_blocks')
        ->fields(
            array(
                'name' => $name,
            )
        )->condition('id', $formValue['values']['id'])
        ->execute();
    if ($res) {
        drupal_set_message(t('Block :name has been changed', array(':name' => $name)), 'status');
        if ($formValue['triggering_element']['#value'] !== 'Save') {
            drupal_goto('admin/zoomdojo/items-block/blocks/config/'.$formValue['values']['id']);
        }
    } else {
        drupal_set_message(t('Block :name hasn\'t been changed', array(':name' => $name)), 'error');
    }
    drupal_goto('admin/zoomdojo/items-block/blocks');
}

/**
 * Delete items block
 */
function zoomdojo_blocks_deleteItemsBlocks($bid)
{
    $response = array(
        'status' => 'FAIL',
    );
    $bid = intval($bid);
    if (!empty($bid)) {
        $res = db_delete('zd_blocks')
            ->condition('id', $bid)
            ->execute();
        if ($res) {
            db_delete('zd_items_content')
                ->condition('bid', $bid)
                ->execute();
            $response['status'] = 'OK';
        }
    }
    print json_encode($response);
    exit();
}


/**
 * Configure items block
 */
function zoomdojo_blocks_configItemsBlock($bid)
{
    if (isset($_POST['save'])) {
        zoomdojo_blocks_configItemsBlockSave($_POST, $bid);
    }
    drupal_add_css(drupal_get_path('module', 'zoomdojo_blocks') . '/css/jquery-ui-1.10.3.custom.min.css');
    drupal_add_css(drupal_get_path('module', 'zoomdojo_blocks') . '/css/zd-admin-items.css');

    drupal_add_js(drupal_get_path('module', 'zoomdojo_blocks') . '/js/jquery-1.9.1.js');
    drupal_add_js(drupal_get_path('module', 'zoomdojo_blocks') . '/js/jquery-ui-1.10.3.custom.min.js');
    drupal_add_js(drupal_get_path('module', 'zoomdojo_blocks') . '/js/underscore-min.js');
    drupal_add_js(drupal_get_path('module', 'zoomdojo_blocks') . '/js/backbone-min.js');
    drupal_add_js(drupal_get_path('module', 'zoomdojo_blocks') . '/js/jquery.tablednd.js');
    drupal_add_js(drupal_get_path('module', 'zoomdojo_blocks') . '/js/items/zd-admin-items.js');

    $allCategories = db_select('zd_items_category', 'zic')
        ->fields('zic')
        ->execute()
        ->fetchAll();

    $query = db_select('zd_items_content', 'zic')
        ->fields('zic')
        ->condition('bid', $bid)
        ->orderBy('weight')
        ->execute()
        ->fetchAll();

    $items = array();
    $cids  = array();
    foreach ($query as $item) {
        $items[$item->cid][] = $item;
        $cids[] = $item->cid;
    }

    $categories = db_select('zd_items_category', 'zic')
        ->fields('zic');
    if (!empty($cids)) {
        $categories->condition('id', $cids, 'IN');
    }
    $categories = $categories->execute()
        ->fetchAll();
    
    $variables = array(
        'categories'    => $categories,
        'allCategories' => $allCategories,
        'items'         => $items,
        'bid'           => $bid,
    );
    return theme('zoomdojo_blocks_items_block_config', $variables);
}

/**
 * Save config block
 */
function zoomdojo_blocks_configItemsBlockSave($val, $bid) 
{
    $items = array();
    $ids   = array();
    foreach ($val['id'] as $cid => $v) {
        foreach ($v as $n => $i) {
            $item   = $val['item'][$cid][$n];
            $weight = $val['weight'][$cid][$n];
            if (!empty($item)) {
                $ids[] = $i;
                $items[] = array(
                    'id'     => $i,
                    'item'   => $item,
                    'cid'    => $cid,
                    'bid'    => $bid,
                    'weight' => $weight,
                );
            }
        }
    }

    if (!empty($ids)) {
        db_delete('zd_items_content')
            ->condition('bid', $bid)
            ->condition('id', $ids, 'NOT IN')
            ->execute();
    }
    foreach ($items as $item) {
        db_merge('zd_items_content')
            ->key(array('id' => $item['id']))
            ->fields($item)
            ->execute();
    }
    drupal_goto('admin/zoomdojo/items-block/blocks');
}

/**
 * Items block View
 */
function zoomdojo_blocks_itemsBlocksView($bid) 
{
    drupal_add_css(drupal_get_path('module', 'zoomdojo_blocks') . '/css/items/zd-items-view.css');
    drupal_add_js(drupal_get_path('module', 'zoomdojo_blocks') . '/js/items/zd-items-view.js');
    $query = db_select('zd_items_content', 'zic');
    $query->join('zd_items_category', 'zc', 'zc.id=zic.cid');
    $query->fields('zic')
        ->fields('zc');
    $query = $query->condition('zic.bid', $bid)
        ->orderBy('zic.weight')
        ->execute()
        ->fetchAll();

    $items = array();
    foreach ($query as $item) {
        $items[$item->cid]['title']      = $item->title;
        $items[$item->cid]['num_show']   = $item->num_show;
        $items[$item->cid]['begin_word'] = $item->begin_word;
        $items[$item->cid]['data'][]     = $item->item;
    }

    $variables = array(
        'items' => $items,
    );
    return theme('zoomdojo_blocks_items_block_view', $variables);
}