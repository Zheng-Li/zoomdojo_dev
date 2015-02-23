<?php

/**
 * Tab list
 */
function zoomdojo_blocks_getTabs()
{
    drupal_add_js(drupal_get_path('module', 'zoomdojo_blocks') . '/js/zd-admin-tabled-categ.js');
    $categories = db_select('zd_tabbed_panel_tab', 'ztpt')
        ->fields('ztpt')
        ->orderBy('weight')
        ->execute()
        ->fetchAll();
    $variables = array(
        'categories' => $categories,
    );
    return theme('zoomdojo_blocks_tabbed_panels_categories_list', $variables);
}

/**
 * Add tab form
 */
function zoomdojo_blocks_addTabsForm()
{
    drupal_set_title('Add category');
    global $language;
    $languages = language_list();
    $options = array('und' => 'Language neutral');
    foreach ($languages as $lanCode => $lan) {
        $options[$lanCode] = $lan->language;
    }
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
    $form['language'] = array(
        '#type'          => 'select', 
        '#title'         => t('Language'),
        '#options'       => $options, 
        '#default_value' => $language->language,
    );
    $form['save'] = array(
        '#type'     => 'submit', 
        '#value'    => t('Save'),
    );
    $form['actions']['cancel'] = array(
        '#markup' => l(t('Cancel'), 'admin/zoomdojo/tablet-panel/categories'),
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
            'language' => $val['language'],
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

    global $language;
    $languages = language_list();
    $options = array('und' => 'Language neutral');
    foreach ($languages as $lanCode => $lan) {
        $options[$lanCode] = $lan->language;
    }

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
    $form['language'] = array(
        '#type'          => 'select', 
        '#title'         => t('Language'),
        '#options'       => $options, 
        '#default_value' => $def->language,
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
        '#markup' => l(t('Cancel'), 'admin/zoomdojo/tablet-panel/categories'),
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
            'language' => $val['language'],
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
 * Block list
 */
function zoomdojo_blocks_getTabletPanelBlocks()
{
    drupal_add_css(drupal_get_path('module', 'zoomdojo_blocks') . '/css/jquery-ui-1.10.3.custom.min.css');
    drupal_add_js(drupal_get_path('module', 'zoomdojo_blocks') . '/js/jquery-1.9.1.js');
    drupal_add_js(drupal_get_path('module', 'zoomdojo_blocks') . '/js/jquery-ui-1.10.3.custom.min.js');
    drupal_add_js(drupal_get_path('module', 'zoomdojo_blocks') . '/js/zd-admin-tabled-categ.js');

    // select for nodes
    $query = db_select('zd_tabbed_panel_block', 'ztpb')
        ->fields('ztpb', array('id', 'etity_id', 'type'))
        ->fields('n', array('title'));
    $query->addExpression('COUNT(*)', 'count');
    $query->leftJoin('node', 'n', 'n.nid=ztpb.etity_id');
    $nodesType = $query->condition('ztpb.type', db_like('node'), 'LIKE')
        ->orderBy('title')
        ->groupBy('etity_id')
        ->execute()
        ->fetchAll();

    // select for taxonomy term
    $query = db_select('zd_tabbed_panel_block', 'ztpb')
        ->fields('ztpb', array('id', 'etity_id', 'type'));
    $query->addExpression('COUNT(*)', 'count');
    $query->addExpression('ttd.name', 'title');
    $query->leftJoin('taxonomy_term_data', 'ttd', 'ttd.tid=ztpb.etity_id');
    $taxonomyType = $query->condition('ztpb.type', db_like('voc'), 'LIKE')
        ->orderBy('title')
        ->groupBy('etity_id')
        ->execute()
        ->fetchAll();

    $variables = array(
        'nodesType'    => $nodesType,
        'taxonomyType' => $taxonomyType
    );
    return theme('zoomdojo_blocks_tabbed_panels_blocks_list', $variables);
}

/**
 * Add block form
 */
function zoomdojo_blocks_addTabletBlockView()
{
    drupal_set_title('Add Tabbled Block');
    drupal_add_css(drupal_get_path('module', 'zoomdojo_blocks') . '/css/jquery-ui-1.10.3.custom.min.css');
    drupal_add_js(drupal_get_path('module', 'zoomdojo_blocks') . '/js/jquery-1.9.1.js');
    drupal_add_js(drupal_get_path('module', 'zoomdojo_blocks') . '/js/jquery-ui-1.10.3.custom.min.js');
    
    drupal_add_css(drupal_get_path('module', 'zoomdojo_blocks') . '/css/zd-admin-tabs.css');
    drupal_add_js(drupal_get_path('module', 'zoomdojo_blocks') . '/js/underscore-min.js');
    drupal_add_js(drupal_get_path('module', 'zoomdojo_blocks') . '/js/backbone-min.js');
    drupal_add_js(drupal_get_path('module', 'zoomdojo_blocks') . '/js/zd-admin-tabs.js');
    $contentTypes = node_type_get_types();
    $vocabularies = taxonomy_get_vocabularies();

    if (isset($_POST['bundle'])) {
        _zoomdojo_blocks_addTabletBlockViewSubmit($_POST);
    }

    $variables = array(
        'contentTypes' => $contentTypes,
        'vocabularies' => $vocabularies,
    );
    return theme('zoomdojo_blocks_tabbed_panels_blocks_add', $variables);
}

/**
 * save data for add block
 */
function _zoomdojo_blocks_addTabletBlockViewSubmit($vals) 
{
    if (!empty($vals['bundle']) && !empty($vals['type']) && !empty($vals['title']) 
            && !empty($vals['url']) && !empty($vals['entity'])) {
        $res      = 0;
        $entityId = $vals['entity'];
        $bundle   = $vals['bundle'];
        $type     = $vals['type'];
        $show     = intval($vals['show']);
        if ($type == 'edit') {
            db_delete('zd_tabbed_panel_block')
                ->condition('type', db_like($bundle), 'LIKE')
                ->condition('etity_id', $entityId)
                ->execute();
        }
        $items    = array();
        $query = db_insert('zd_tabbed_panel_block')
            ->fields(array('title', 'url', 'cid', 'etity_id', 'type', 'show_children', 'new_window'));
        foreach ($vals['title'] as $cid => $titles) {
            foreach ($titles as $key => $title) {
                $url       = $vals['url'][$cid][$key];
                $newWindow = isset($vals['nw'][$cid][$key])?intval($vals['nw'][$cid][$key]):0;
                if (!empty($url) && !empty($title)) {
                    $item = array(
                        'title'         => $title,
                        'url'           => $url,
                        'cid'           => $cid,
                        'etity_id'      => $entityId,
                        'type'          => $bundle,
                        'show_children' => $show,
                        'new_window'    => $newWindow,
                    );
                    $items[] = $item;
                    $query->values($item);
                }
            }
        }
        if (!empty($items)) {
            $res = $query->execute();
        }
        if ($res) {
            drupal_set_message(t('Data has been successfully saved'), 'status');
        } else {
            drupal_set_message(t('Block hasn\'t been created'), 'error');
        }
    }
}

/**
 * get list Entity
 */
function zoomdojo_blocks_getListEntity($type, $bundle)
{
    $response = array(
        'status' => 'ERROR',
        'data'   => ''
    );
    switch ($type) {
        case 'voc':
            $query = db_select('taxonomy_term_data', 't')
                ->fields('t', array('language'));
            $query->addExpression('t.tid', 'id');
            $query->addExpression('t.name', 'title');
            $query->addExpression("CONCAT('taxonomy/term/', t.tid)", 'url');
            $query = $query->condition('vid', $bundle)
                ->orderBy('title')
                ->execute()
                ->fetchAll();
            break;
        
        case 'node':
            $query = db_select('node', 'n')
                ->fields('n', array('title', 'language'));
            $query->addExpression('nid', 'id');
            $query->addExpression("CONCAT('node/', nid)", 'url');
            $query = $query->condition('status', 1)
                ->condition('type', db_like($bundle), 'LIKE')
                ->orderBy('title')
                ->execute()
                ->fetchAll();
            break;
    }
    if (!empty($query)) {
        $response = array(
            'status' => 'OK',
            'data'   => $query,
        );
    }
    print json_encode($response);
    exit();
}

/**
 * get tab add form
 */
function zoomdojo_blocks_getAddForm($lang)
{
    $or = db_or()->condition('language', db_like($lang), 'LIKE')
        ->condition('language', db_like('und'), 'LIKE');
    $allCategories = db_select('zd_tabbed_panel_tab', 'ztpt')
        ->fields('ztpt')
        ->condition($or)
        ->orderBy('weight')
        ->execute()
        ->fetchAll();
    $categories = array();
    foreach ($allCategories as $cat) {
        if ($cat->language === $lang) {
            $categories[] = $cat;
        }
    }

    $variables = array(
        'allCategories' => $allCategories,
        'categories'    => $categories,
        'src'           => drupal_get_path('module', 'zoomdojo_blocks') . '/images/',
        'bundle'        => 'node',
        'entityId'      => '0',
        'show'          => '0',
    );
    print theme('zoomdojo_blocks_tabbed_panels_blocks_add_form', $variables);
    exit();
}

/**
 *  Delete tab block
 */
function zoomdojo_blocks_deleteTabBlock($entityId, $bundle)
{
    $response = array(
        'status' => 'FAIL',
    );
    $entityId = intval($entityId);
    if (!empty($entityId)) {
        $res = db_delete('zd_tabbed_panel_block')
            ->condition('etity_id', $entityId)
            ->condition('type', db_like($bundle), 'LIKE')
            ->execute();
        if ($res) {
            $response['status'] = 'OK';
        }
    }
    print json_encode($response);
    exit();
}

/**
 * Edit tab block
 */
function zoomdojo_blocks_editTabBlock($entityId, $bundle)
{
    if (isset($_POST['bundle'])) {
        _zoomdojo_blocks_addTabletBlockViewSubmit($_POST);
        drupal_goto('admin/zoomdojo/tablet-panel/tabs');
    }
    drupal_set_title('Edit Tabbled Block');
    drupal_add_css(drupal_get_path('module', 'zoomdojo_blocks') . '/css/jquery-ui-1.10.3.custom.min.css');
    drupal_add_js(drupal_get_path('module', 'zoomdojo_blocks') . '/js/jquery-1.9.1.js');
    drupal_add_js(drupal_get_path('module', 'zoomdojo_blocks') . '/js/jquery-ui-1.10.3.custom.min.js');

    drupal_add_css(drupal_get_path('module', 'zoomdojo_blocks') . '/css/zd-admin-tabs.css');
    drupal_add_js(drupal_get_path('module', 'zoomdojo_blocks') . '/js/underscore-min.js');
    drupal_add_js(drupal_get_path('module', 'zoomdojo_blocks') . '/js/backbone-min.js');
    drupal_add_js(drupal_get_path('module', 'zoomdojo_blocks') . '/js/zd-admin-tabs.js');

    switch ($bundle) {
        case 'node':
                $lang = db_select('node', 'n')
                    ->fields('n', array('language'))
                    ->condition('nid', $entityId)
                    ->execute()
                    ->fetchColumn();
            break;
        case 'voc':
            $lang = db_select('taxonomy_term_data', 'ttd')
                    ->fields('ttd', array('language'))
                    ->condition('tid', $entityId)
                    ->execute()
                    ->fetchColumn();
            break;
    }
    
    $or = db_or()->condition('language', db_like('und'), 'LIKE')
        ->condition('language', db_like($lang), 'LIKE');
    $allCategories = db_select('zd_tabbed_panel_tab', 'ztpt')
        ->fields('ztpt')
        ->condition($or)
        ->orderBy('weight')
        ->execute()
        ->fetchAll();

    $query = db_select('zd_tabbed_panel_block', 'ztpb')
        ->fields('ztpb');
    $query->addExpression('ztpt.title', 'catName');
    $query->join('zd_tabbed_panel_tab', 'ztpt', 'ztpt.id=ztpb.cid');
    $query = $query->condition('etity_id', $entityId)
        ->condition('type', $bundle)
        ->execute()
        ->fetchAll();

    $categories = array();
    $formItems  = array();
    foreach ($query as $row) {
        $formItems[$row->cid][] = $row;
    }

    if (!empty($formItems)) {
        $variables = array(
            'allCategories' => $allCategories,
            'formItems'     => $formItems,
            'bundle'        => $bundle,
            'entityId'      => $entityId,
            'show'          => $query[0]->show_children,
        );
        return theme('zoomdojo_blocks_tabbed_panels_blocks_edit_form', $variables);
    } else {
        $variables = array(
            'allCategories' => $allCategories,
            'categories'     => $allCategories,
            'bundle'        => $bundle,
            'entityId'      => $entityId,
            'show'          => 1,
            'showChild'     => 0,
        );
        return '<div id="zd-tabs-add-form">'
               . theme('zoomdojo_blocks_tabbed_panels_blocks_add_form', $variables).'</div>';
    }
}

function zoomdojo_blocks_adminTaxSubmenu($eid, $type)
{
    drupal_goto('admin/zoomdojo/tablet-panel/tabs/edit/'.$eid.'/'.$type);
}

function zoomdojo_blocks_adminNodeSubmenu($eid, $type)
{
    drupal_goto('admin/zoomdojo/tablet-panel/tabs/edit/'.$eid.'/'.$type);
}