<?php

/**
 * Tab list
 */
function zoomdojo_blocks_getTabs()
{
    drupal_add_js(drupal_get_path('module', 'zoomdojo_blocks') . '/js/zd-admin-tabled-categ.js');

    $limit = 10;
    $header = array(
        array('data' => t('Category title'), 'field' => 'title'),
        array('data' => t('Weight'), 'field' => 'weight'),
        array('data' => t('Operations'), 'colspan' => 2)
    );

    $categories = db_select('zd_tabbed_panel_tab', 'ztpt')
        ->fields('ztpt');
    $categories = $categories->extend('TableSort')
        ->orderByHeader($header)
        ->extend('PagerDefault')
        ->limit($limit)
        ->execute();

    $rows = array();
    foreach ($categories as $item) {
        $rows[] = array(
            $item->title,
            $item->weight,
            l(t('Edit'), 'admin/zoomdojo/tablet-panel/categories/edit/' . $item->id),
            l(
                t('Delete'), 'admin/zoomdojo/tablet-panel/categories/delete/' . $item->id, array(
                    'attributes' => array(
                        'class' => 'zd-delete-tab-category'
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
 * Add tab form
 */
function zoomdojo_blocks_addTabsForm()
{
    drupal_set_title('Add category');
    $form['title'] = array(
        '#type'         => 'textfield', 
        '#title'        => t('Tab title'), 
        '#size'         => 60,
        '#maxlength'    => 255, 
        '#required'     => TRUE,
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
        '#markup' => l(t('Cancel'), 'admin/zoomdojo/tablet-panel/categories', 
            array(
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
function zoomdojo_blocks_addTabsForm_submit($formId, $formValues)
{
    $val = $formValues['values'];
    if (!empty($val['title'])) {
        $fields = array(
            'title'    => $val['title'],
            'weight'   => $val['weight'],
        );
        $res = db_insert('zd_tabbed_panel_tab')
            ->fields($fields)
            ->execute();
        if ($res) {
            drupal_set_message(t('Category :name has been created', array(':name' => $val['title'])), 'status');
        } else {
            drupal_set_message(t('Category :name hasn\'t been created', array(':name' => $val['title'])), 'error');
        }
    }
}

/**
 * Edit form for category tab
 */
function zoomdojo_blocks_editTabCategoryForm()
{
    $cid = intval(arg(5));
    drupal_set_title('Edit category');
    $def = db_select('zd_tabbed_panel_tab', 'ztpt')
        ->fields('ztpt')
        ->condition('id', $cid)
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
    $form['weight'] = array(
        '#type'          => 'weight', 
        '#title'         => t('Weight'), 
        '#delta'         => 20, 
        '#default_value' => $def->weight,
    );
    $form['cid'] = array(
        '#type'          => 'hidden', 
        '#default_value' => $def->id,
    );
    $form['save'] = array(
        '#type'     => 'submit', 
        '#value'    => t('Save'),
    );
    $form['actions']['cancel'] = array(
        '#markup' => l(t('Cancel'), 'admin/zoomdojo/tablet-panel/categories', 
            array(
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
function zoomdojo_blocks_editTabCategoryForm_submit($formId, $formValues)
{
    $val = $formValues['values'];
    if (!empty($val['cid'])) {
        $fields = array(
            'title'    => $val['title'],
            'weight'   => $val['weight'],
        );
        $res = db_update('zd_tabbed_panel_tab')
            ->fields($fields)
            ->condition('id', $val['cid'])
            ->execute();
        if ($res) {
            drupal_set_message(t('Category :name was updated', array(':name' => $val['title'])), 'status');
        } else {
            drupal_set_message(t('Category :name not was updated', array(':name' => $val['title'])), 'error');
        }
        drupal_goto('admin/zoomdojo/tablet-panel/categories');
    }
}

/**
 * Delete form for category tab
 */
function zoomdojo_blocks_deleteTabCategory($cid)
{
    $response = array(
        'status' => 'FAIL',
    );
    $cid = intval($cid);
    if (!empty($cid)) {
        $res = db_delete('zd_tabbed_panel_tab')
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
 * Add new category ajax
 */
function zoomdojo_blocks_addNewCategoryAjax()
{
    $response = array(
        'status' => 'FAIL',
        'text'   => '',
        'id'     => 0,
    );
    $categName = trim($_GET['name']);
    if (!empty($categName)) {
        $res = db_merge('zd_tabbed_panel_tab')
            ->key(array('title' => $categName))
            ->fields(array(
                'title'    => $categName,
                'language' => '',
                'weight'   => 0,
            ))
            ->execute();
        if ($res) {
            if ($res == MergeQuery::STATUS_INSERT) {
                $response['id'] = db_query("SELECT LAST_INSERT_ID()")->fetchField();
            }
            $response['status'] = 'OK';
        }
    } else {
        $response['text'] = 'Category name is empty!!!';
    }
    print json_encode($response);
    exit();
}

/**
 * Block list
 */
function zoomdojo_blocks_getTabletPanelBlocks()
{
    drupal_add_js(drupal_get_path('module', 'zoomdojo_blocks') . '/js/zd-admin-tabled-categ.js');
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
        ->condition('delta', 'tabs');
    $results = $query->execute();

    $rows = array();
    foreach ($results as $item) {
        $rows[] = array(
            $item->name,
            l(t('Edit'), 'admin/zoomdojo/tablet-panel/tabs/edit/' . $item->id),
            l(
                t('Configure visible area'), 
                'admin/structure/block/manage/zoomdojo_blocks/zoomdojo_blocks_'.$item->id.'/configure', array(
                    'attributes' => array(
                        'target' => '_blank'
                    )
                )
            ),
            l(t('Configure'), 'admin/zoomdojo/tablet-panel/tabs/config/' . $item->id),
            l(
                t('Delete'), 'admin/zoomdojo/tablet-panel/tabs/delete/' . $item->id, array(
                    'attributes' => array(
                        'class' => 'zd-delete-tab-block'
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
 * Add tabs block
 */
function zoomdojo_blocks_addTabletBlockView()
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
        '#markup'     => l(t('Cancel'), 'admin/zoomdojo/tablet-panel/tabs', array(
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
function zoomdojo_blocks_addTabletBlockView_submit($formId, $formValue) 
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
                'delta' => 'tabs',
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
            drupal_goto('admin/zoomdojo/tablet-panel/tabs/config/'.$res);
        }
    } else {
        drupal_set_message(t('Block :name hasn\'t been created', array(':name' => $name)), 'error');
    }
}

/**
 * edit tabs block
 */
function zoomdojo_blocks_editdTabletBlockView()
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
        '#markup'     => l(t('Cancel'), 'admin/zoomdojo/tablet-panel/tabs', array(
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
function zoomdojo_blocks_editdTabletBlockView_submit($formId, $formValue)
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
            drupal_goto('admin/zoomdojo/tablet-panel/tabs/config/'.$formValue['values']['id']);
        }
    } else {
        drupal_set_message(t('Block :name hasn\'t been changed', array(':name' => $name)), 'error');
    }
    drupal_goto('admin/zoomdojo/tablet-panel/tabs');
}

/**
 *  Delete tab block
 */
function zoomdojo_blocks_deleteTabBlock($bid)
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
            db_delete('zd_tabbed_panel_block')
                ->condition('bid', $bid)
                ->execute();
            $response['status'] = 'OK';
        }
    }
    print json_encode($response);
    exit();
}


/**
 * Configure tabs block
 */
function zoomdojo_blocks_configTabsBlock($bid)
{
    if (isset($_POST['save'])) {
        zoomdojo_blocks_configTabsBlockSave($_POST, $bid);
    }
    drupal_add_css(drupal_get_path('module', 'zoomdojo_blocks') . '/css/jquery-ui-1.10.3.custom.min.css');
    drupal_add_css(drupal_get_path('module', 'zoomdojo_blocks') . '/css/zd-admin-tabs.css');

    drupal_add_js(drupal_get_path('module', 'zoomdojo_blocks') . '/js/jquery-1.9.1.js');
    drupal_add_js(drupal_get_path('module', 'zoomdojo_blocks') . '/js/jquery-ui-1.10.3.custom.min.js');
    drupal_add_js(drupal_get_path('module', 'zoomdojo_blocks') . '/js/underscore-min.js');
    drupal_add_js(drupal_get_path('module', 'zoomdojo_blocks') . '/js/backbone-min.js');
    drupal_add_js(drupal_get_path('module', 'zoomdojo_blocks') . '/js/zd-admin-tabs.js');

    $allCategories = db_select('zd_tabbed_panel_tab', 'ztpt')
        ->fields('ztpt')
        ->execute()
        ->fetchAll();

    $query = db_select('zd_tabbed_panel_block', 'ztpb')
        ->fields('ztpb')
        ->condition('bid', $bid)
        ->orderBy('title')
        ->execute()
        ->fetchAll();

    $items = array();
    $cids  = array();
    foreach ($query as $item) {
        $items[$item->cid][] = $item;
        $cids[] = $item->cid;
    }

    $categories = db_select('zd_tabbed_panel_tab', 'ztpt')
        ->fields('ztpt');
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
    return theme('zoomdojo_blocks_tabbed_panels_blocks_config', $variables);
}

/**
 * Save tabs block configure
 */
function zoomdojo_blocks_configTabsBlockSave($val, $bid)
{

    $items = array();
    $ids   = array();
    foreach ($val['id'] as $cid => $v) {
        foreach ($v as $n => $i) {
            $title = $val['title'][$cid][$n];
            $url   = $val['url'][$cid][$n];
            $nw    = $val['hnw'][$cid][$n];
            if (!empty($title) && !empty($url)) {
                $ids[] = $i;
                $items[] = array(
                    'id'     => $i,
                    'title'   => $title,
                    'cid'    => $cid,
                    'bid'    => $bid,
                    'url' => $url,
                    'new_window' => $nw,
                );
            }
        }
    }
    if (!empty($ids)) {
        db_delete('zd_tabbed_panel_block')
            ->condition('bid', $bid)
            ->condition('id', $ids, 'NOT IN')
            ->execute();
    }
    foreach ($items as $item) {
        db_merge('zd_tabbed_panel_block')
            ->key(array('id' => $item['id']))
            ->fields($item)
            ->execute();
    }
    drupal_goto('admin/zoomdojo/tablet-panel/tabs');
}

/**
 * View tabs block 
 */
function zoomdojo_blocks_tabsBlocksView($bid)
{
    drupal_add_css(drupal_get_path('module', 'zoomdojo_blocks') . '/css/zd-tabs-view.css');
    drupal_add_js(drupal_get_path('module', 'zoomdojo_blocks') . '/js/zd-tabs-view.js');
    $query = db_select('zd_tabbed_panel_block', 'ztpb');
    $query->join('zd_tabbed_panel_tab', 'ztpt', 'ztpt.id=ztpb.cid');
    $query->fields('ztpb')
        ->fields('ztpt');
    $query->addExpression('ztpb.title', 'urlTitle');
    $query = $query->condition('ztpb.bid', $bid)
        ->orderBy('ztpt.weight')
        ->orderBy('ztpb.title')
        ->execute()
        ->fetchAll();

    $items = array();
    foreach ($query as $item) {
        $items[$item->cid]['title']    = $item->title;
        $items[$item->cid]['data'][]   = (object) array(
            'title' => $item->urlTitle,
            'url'   => $item->url,
            'nw' => $item->new_window,
        );
    }

    $variables = array(
        'items' => $items,
    );
    return theme('zoomdojo_blocks_tabs_block_view', $variables);
}