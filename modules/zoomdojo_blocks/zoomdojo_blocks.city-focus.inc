<?php

/**
 * List cities
 */
function zoomdojo_blocks_listCities()
{
    $limit = 10;
    $header = array(
        array('data' => t('City name'), 'field' => 'name'),
        array('data' => t('Weight'), 'field' => 'weight'),
    );

    $cities = db_select('taxonomy_term_data', 'ttd')
        ->fields('ttd');
    $cities = $cities->extend('TableSort')
        ->condition('vid', 2)
        ->orderByHeader($header)
        ->extend('PagerDefault')
        ->limit($limit)
        ->execute();

    $rows = array();
    foreach ($cities as $item) {
        $rows[] = array(
            l($item->name, 'admin/zoomdojo/city-focus/property/' . $item->tid),
            $item->weight,
        );
    }
    $build['cities_table'] = array(
        '#theme'  => 'table',
        '#header' => $header,
        '#rows'   => $rows,
        '#weight' => 2,
    );
    $build['pager_bottom'] = array(
        '#theme'  => 'pager',
        '#weight' => 3
    );
    return $build;
}

/**
 * Config weight of cities (Form)
 */
function zoomdojo_blocks_cityFocusConfig($form, $formState, $cid)
{
    $cityName = zoomdojo_blocks_getCityFocusName($cid);
    drupal_set_title('Configure ' . $cityName . ' properties');

    $form['properties']['#tree'] = TRUE;

    $results = zoomdojo_blocks_getCityFocusProperties($cid);
    
    foreach ($results as $item) {
        $form['properties'][$item->id] = array(
            'name' => array(
                '#markup' => $item->name,
            ),
            'value' => array(
                '#markup' => $item->value,
            ),
            'id' => array(
                '#type'          => 'hidden',
                '#size'          => 3,
                '#default_value' => $item->id,
                '#disabled'      => TRUE,
            ),
            'cid' => array(
                '#type'          => 'hidden',
                '#size'          => 3,
                '#default_value' => $item->cid,
                '#disabled'      => TRUE,
            ),
            'weight' => array(
                '#type'          => 'weight',
                '#title'         => t('Weight'),
                '#default_value' => $item->weight,
                '#delta'         => 50,
                '#title_display' => 'invisible',
                '#class' => 'tabledrag-hide'
            ),
            'edit' => array(
                '#markup' => l('Edit', 'admin/zoomdojo/city-focus/property/'.$item->cid.'/edit/'.$item->id),
            ),
            'delete' => array(
                '#markup' => l('Delete', 'admin/zoomdojo/city-focus/property/'.$item->cid.'/delete/'.$item->id, array(
                        'attributes' => array(
                            'onclick' => "if (!confirm('Are you sure?')){return false;}"
                        )
                    )
                ),
            ),
        );
    }

    $form['cid'] = array(
        '#type'  => 'hidden',
        '#value' => $cid,
    );

    $form['description'] = array(
        '#type'          => 'text_format',
        '#title'         => t('Description'),
        '#default_value' => zoomdojo_blocks_getCityFocusDesc($cid),
        '#format'        => 'full_html',
        '#weight'        => 0,
    );

    $form['actions']           = array('#type' => 'actions');
    $form['actions']['submit'] = array('#type'  => 'submit', '#value' => t('Save Changes'));
    return $form;
}

function theme_zoomdojo_blocks_cityFocusConfig($variables)
{
    $form = $variables['form'];
    $rows = array();
    foreach (element_children($form['properties']) as $id) {
        $form['properties'][$id]['weight']['#attributes']['class'] = array('example-item-weight');
        $rows[] = array(
          'data' => array(
              drupal_render($form['properties'][$id]['name']),
              drupal_render($form['properties'][$id]['value']),
              drupal_render($form['properties'][$id]['id']),
              drupal_render($form['properties'][$id]['cid']),
              drupal_render($form['properties'][$id]['weight']),
              drupal_render($form['properties'][$id]['edit']),
              drupal_render($form['properties'][$id]['delete']),
          ),
          'class' => array('draggable'),
        );
    }

    $header = array(
        array('data' => t('Name')),
        array('data' => t('Value'), 'colspan' => 3),
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

function zoomdojo_blocks_cityFocusConfig_submit($form, $form_state) 
{
    db_merge('zd_city_focus_description')
      ->key(array('cid' => $form_state['values']['cid']))
      ->fields(array(
            'cid'         => $form_state['values']['cid'],
            'description' => $form_state['values']['description']['value'],
      ))
      ->execute();
    foreach ($form_state['values']['properties'] as $id => $item) {
        db_update('zd_city_focus_block')
          ->fields(array('weight' => $item['weight']))
          ->condition('id', $id)
          ->execute();
    }
}

/**
 * Add property 
 */
function zoomdojo_blocks_cityFocusAddItem($form, $formState, $cid)
{
    $cityName = zoomdojo_blocks_getCityFocusName($cid);
    drupal_set_title('Add property to ' . $cityName);

    $form = array();

    $form['name'] = array(
        '#type'         => 'textfield', 
        '#title'        => t('Name'), 
        '#size'         => 60,
        '#maxlength'    => 255, 
        '#required'     => TRUE,
    );

    $form['value'] = array(
        '#type'         => 'textfield', 
        '#title'        => t('Value'), 
        '#size'         => 60,
        '#maxlength'    => 255, 
        '#required'     => TRUE,
    );

    $form['cid'] = array(
        '#type'  => 'hidden', 
        '#value' => $cid,
    );

    $form['weight'] = array(
        '#type'          => 'weight', 
        '#title'         => t('Weight'),
        '#required'      => TRUE,
        '#delta'         => 20,
        '#default_value' => 0,
    );

    $form['save'] = array(
        '#type'     => 'submit', 
        '#value'    => t('Save'),
    );

    $form['actions']['cancel'] = array(
        '#markup' => l(t('Cancel'), 'admin/zoomdojo/city-focus/property/' . $cid),
    );

    return $form;
}

/**
 * Implementation hook_submit
 */
function zoomdojo_blocks_cityFocusAddItem_submit($formId, $formValues)
{
    $val = $formValues['values'];
    if (!empty($val)) {
        $res = db_insert('zd_city_focus_block')
            ->fields(
                array(
                    'name'   => $val['name'],
                    'value'  => $val['value'],
                    'cid'    => $val['cid'],
                    'weight' => $val['weight'],
                )
            )->execute();
        if ($res) {
            drupal_set_message(t('Data has been created'), 'status');
        } else {
            drupal_set_message(t('Data hasn\'t been created'), 'error');
        }
    }
}

/**
 * Edit property 
 */
function zoomdojo_blocks_cityFocusEditItem($formId, $formState, $cid, $id)
{
    $cityName = zoomdojo_blocks_getCityFocusName($cid);
    drupal_set_title('Edit property item of ' . $cityName);

    $def = db_select('zd_city_focus_block', 'zcfb')
        ->fields('zcfb')
        ->condition('id', $id)
        ->execute()
        ->fetch();

    $form = array();

    $form['name'] = array(
        '#type'         => 'textfield', 
        '#title'        => t('Name'), 
        '#size'         => 60,
        '#maxlength'    => 255, 
        '#required'     => TRUE,
        '#default_value' => $def->name,
    );

    $form['value'] = array(
        '#type'         => 'textfield', 
        '#title'        => t('Value'), 
        '#size'         => 60,
        '#maxlength'    => 255, 
        '#required'     => TRUE,
        '#default_value' => $def->value,
    );

    $form['cid'] = array(
        '#type'  => 'hidden', 
        '#value' => $cid,
    );

    $form['id'] = array(
        '#type'  => 'hidden', 
        '#value' => $id,
    );

    $form['weight'] = array(
        '#type'          => 'weight', 
        '#title'         => t('Weight'),
        '#required'      => TRUE,
        '#delta'         => 20,
        '#default_value' => $def->weight,
    );

    $form['save'] = array(
        '#type'     => 'submit', 
        '#value'    => t('Save'),
    );

    $form['actions']['cancel'] = array(
        '#markup' => l(t('Cancel'), 'admin/zoomdojo/city-focus/property/' . $cid),
    );

    return $form;
}

/**
 * Implementation hook_submit
 */
function zoomdojo_blocks_cityFocusEditItem_submit($formId, $formValues)
{
    $val = $formValues['values'];
    if (!empty($val)) {
        $res = db_update('zd_city_focus_block')
            ->fields(
                array(
                    'name'   => $val['name'],
                    'value'  => $val['value'],
                    'cid'    => $val['cid'],
                    'weight' => $val['weight'],
                )
            )->condition('id', $val['id'])
            ->execute();
        if ($res) {
            drupal_set_message(t('Data has been changed'), 'status');
        } else {
            drupal_set_message(t('Data hasn\'t been changed'), 'error');
        }
    }
    drupal_goto('admin/zoomdojo/city-focus/property/'.$val['cid']);
}

/**
 * Delete property
 */
function zoomdojo_blocks_cityFocusDeleteItem($cid, $id)
{
    if (!empty($id)) {
        db_delete('zd_city_focus_block')
            ->condition('id', $id)
            ->execute();
    }
    drupal_goto('admin/zoomdojo/city-focus/property/'.$cid);
}

/**
 * Get properties City focus by cid
 */
function zoomdojo_blocks_getCityFocusProperties($cid)
{
    return db_select('zd_city_focus_block', 'zcfb')
        ->fields('zcfb')
        ->condition('cid', $cid)
        ->orderBy('weight')
        ->execute()
        ->fetchAll();
}

/**
 * Get description City focus by cid
 */
function zoomdojo_blocks_getCityFocusDesc($cid)
{
    return db_select('zd_city_focus_description', 'zcfd')
        ->fields('zcfd', array('description'))
        ->condition('cid', $cid)
        ->execute()
        ->fetchColumn();
}

/**
 * Get city name
 */
function zoomdojo_blocks_getCityFocusName($cid)
{
    return db_select('taxonomy_term_data', 'ttd')
        ->fields('ttd', array('name'))
        ->condition('tid', $cid)
        ->execute()
        ->fetchColumn();
}

/**
 * View block
 */
function zoomdojo_blocks_cityFocusBlockView()
{
    if (arg(0) === 'taxonomy' && arg(1) === 'term' && is_numeric(arg(2))) {
        $cid     = arg(2);
        $results = zoomdojo_blocks_getCityFocusProperties($cid);

        $variables = array(
            'cityName'    => zoomdojo_blocks_getCityFocusName($cid),
            'properties'  => $results,
            'description' => zoomdojo_blocks_getCityFocusDesc($cid),
        );
        return theme('zoomdojo_blocks_city_focus_view', $variables);
    } elseif (arg(0) === 'node' && is_numeric(arg(1))) {
        $nid = arg(1);

        $query = db_select('node', 'n');
        $query->join('field_data_field_tags', 'fdft', 'fdft.entity_id=n.nid');
        $cid = $query->fields('fdft', array('field_tags_tid'))
            ->condition('nid', $nid)
            ->condition('bundle', 'city_focus')
            ->execute()
            ->fetchColumn();

        if (!empty($cid)) {
            $results = zoomdojo_blocks_getCityFocusProperties($cid);

            $variables = array(
                'cityName'    => zoomdojo_blocks_getCityFocusName($cid),
                'properties'  => $results,
                'description' => zoomdojo_blocks_getCityFocusDesc($cid),
            );
            return theme('zoomdojo_blocks_city_focus_view', $variables);
        }
    }
    return null;
}

/**
 * Node list of current City-focus page (View block)
 */
function zoomdojo_blocks_cityFocusBlockNodeListView()
{
    $cid = 0;
    global $language ;
    $lang  = $language->language;

    // for sub-category (node)
    if (arg(0) === 'node' && is_numeric(arg(1))) {
        $nid = arg(1);

        $query = db_select('node', 'n');
        $query->join('field_data_field_tags', 'fdft', 'fdft.entity_id=n.nid');
        $cid = $query->fields('fdft', array('field_tags_tid'))
            ->condition('nid', $nid)
            ->condition('bundle', 'city_focus')
            ->execute()
            ->fetchColumn();
    }

    // for taxonomy term (node teaser)
    if (arg(0) === 'taxonomy' && arg(1) === 'term' && is_numeric(arg(2))) {
        $cid = arg(2);
    }

    if (!empty($cid)) {
        $query = db_select('node', 'n')
            ->fields('n');
        $query->join('field_data_field_tags', 'fdft', 'fdft.entity_id=n.nid');
        $query->join('taxonomy_index', 'ti', 'ti.nid=n.nid');
        $results = $query->condition('fdft.field_tags_tid', $cid)
            ->condition('n.language', $lang)
            ->orderBy('ti.weight', 'ASC')
            ->execute();

        $nodes = array();
        foreach ($results as $node) {
            $nodes[] = (object) array(
                'nid'   => $node->nid,
                'title' => $node->title,
                'url'   => drupal_get_path_alias('node/' . $node->nid)
            );
        }

        if (!empty($nodes)) {

            $variables = array(
                'cityName' => zoomdojo_blocks_getCityFocusName($cid),
                'nodes'    => $nodes,
            );
            return theme('zoomdojo_blocks_city_focus_node_list_view', $variables);
        }
    }
    return null;
}