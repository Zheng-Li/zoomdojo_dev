<?php
function organization_manager_locations_list($form_state){

    $form['locations']['#tree'] = TRUE;

    $result = organization_manager_locations_get_data();
    
    foreach ($result as $item) {
        $form['locations'][$item->id] = array(
            'title' => array(
                '#markup' => $item->title . ' ('.$item->id.')',
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
                '#delta'         => 10,
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

function organization_manager_locations_get_data(){
    $rootnodes = db_query('SELECT id, title, weight, pid
                       FROM {zd_locations}
                       WHERE (pid = 0)
                       ORDER BY weight, title ASC');
    $itemtree  = array();
    $depth     = -1;
    foreach ($rootnodes as $parent) {
        organization_manager_locations_get_tree($parent, $itemtree, $depth);
    }
    return $itemtree;
}

function organization_manager_locations_get_tree($parentitem, &$itemtree = array(), &$depth = 0){
    $depth++;
    $parentitem->depth         = $depth;
    $itemtree[$parentitem->id] = $parentitem;
    $children                  = db_query('SELECT id, title, weight, pid
                      FROM {zd_locations}
                      WHERE (pid = :pid)
                      ORDER BY weight, title ASC', array(':pid' => $parentitem->id));
    foreach ($children as $child) {
        if (!in_array($child->id, array_keys($itemtree))) {
            organization_manager_locations_get_tree($child, $itemtree, $depth);
        }
    }
    $depth--;
    return;
}

function theme_organization_manager_locations_list($variables)
{
    $form = $variables['form'];

    $rows = array();

    foreach (element_children($form['locations']) as $id) {
        $form['locations'][$id]['weight']['#attributes']['class'] = array('example-item-weight');
        $form['locations'][$id]['id']['#attributes']['class']  = array('example-item-id');
        $form['locations'][$id]['pid']['#attributes']['class'] = array('example-item-pid');
        $class = array('draggable');
        $indent = theme('indentation', array('size' => $form['locations'][$id]['depth']['#value']));
        unset($form['locations'][$id]['depth']);
        $rows[] = array(
            'data'  => array(
                $indent . drupal_render($form['locations'][$id]['title']),
                array('data' => drupal_render($form['locations'][$id]['weight']), 'class' => 'tabledrag-hide'),
                array('data' =>drupal_render($form['locations'][$id]['id']), 'style' => 'display:none;'),
                array('data' =>drupal_render($form['locations'][$id]['pid']), 'style' => 'display:none;'),
                l(t('Edit'), 'admin/organization-manager/locations/edit/' . $id),
                l(t('Delete'), 'admin/organization-manager/locations/delete/' . $id),
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

function organization_manager_locations_list_submit($form, &$form_state)
{
    foreach ($form_state['values']['locations'] as $id => $item) {
        db_query(
            "UPDATE {zd_locations} SET weight = :weight, pid = :pid WHERE id = :id", array(':weight' => $item['weight'], ':pid'    => $item['pid'], ':id'     => $id)
        );
    }
}

function organization_manager_location_edit()
{
    $id = arg(4);

    if ($id) {
        $jobType = db_select('zd_locations', 't')
            ->fields('t', array('id', 'title'))
            ->condition('id', $id)
            ->execute()
            ->fetch();
    }
    
    $form['id']    = array(
        '#type'  => 'hidden',
        '#value' => $id
    );
    if(!$id){
        $data = organization_manager_locations_get_data();
        $data = array_values($data);
        $options = array();
        $depth = 0;
        $options[0] = 'None';
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
            '#type'      => 'select',
            '#title'     => t('Parent'),
            '#required'  => FALSE,
            '#options' => $options,
        );
    }
    $form['title'] = array(
        '#type'      => 'textfield',
        '#title'     => t('Title'),
        '#size'      => 60,
        '#maxlength' => 255,
        '#required'  => TRUE,
        '#value'     => $id ? $jobType->title : ''
    );
    $form['save']  = array(
        '#type'  => 'submit',
        '#value' => 'save'
    );
    return $form;
}

function organization_manager_location_edit_submit($formId, &$formValue)
{
    $fields = array(
        'title' => t($formValue['input']['title']),
    );
    if($formValue['input']['pid']){
        $fields['pid'] = t($formValue['input']['pid']);
    }
    db_merge('zd_locations')
        ->key(array('id' => t($formValue['values']['id'])))
        ->fields($fields)
        ->execute();

    $formValue['redirect'] = 'admin/organization-manager/locations';
}

function organization_manager_location_delete()
{
    $id = arg(4);
    db_delete('zd_locations')
        ->condition('id', $id)
        ->execute();
    
    drupal_goto('admin/organization-manager/locations');
}

/**
 * Get countries (AJAX) first level
 */
function _ajax_organization_manager_getCountriesOptions($get_all = false)
{
    $results = array();
    $query = db_select('zd_locations', 'zl')
            ->fields('zl', array('id', 'title'));
    if(!$get_all){
      $query->join('zd_org_loc', 'zol', 'zol.countryId=zl.id');
      $query->join('zd_organization', 'zo', 'zo.id=zol.organizationId');
      $query->distinct(true);
    }
    $results = $query->condition('zl.pid', 0)
        ->orderBy('zl.weight', 'ASC')
        ->orderBy('zl.title', 'ASC')
        ->execute()
        ->fetchAll();
    return $results;
}

/**
 * Get states (AJAX) second level
 */
function _ajax_organization_manager_getStatesOptions($countryId)
{
    $results = null;
    if (!empty($countryId)) {
        $query = db_select('zd_locations', 'zl')
            ->fields('zl', array('id', 'title'));
        $query->join('zd_org_loc', 'zol', 'zol.stateId=zl.id');
        $query->join('zd_organization', 'zo', 'zo.id=zol.organizationId');
        $query->distinct(true);
        $results = $query->condition('zl.pid', $countryId)
            ->orderBy('zl.weight', 'ASC')
            ->orderBy('zl.title', 'ASC')
            ->execute()
            ->fetchAll();
    }
    $locations = array(
        0 => (object) array(
                'id' => 0,
                'title' => 'select',
            ),
    );
    if (!empty($results)) {
        $locations = array_merge($locations, $results);
    }else {
        return array(
            0 => (object) array(
                    'id' => 0,
                    'title' => 'select',
                ),
        );
    }
    return $locations;
}

/**
 * Get cities (AJAX) third level
 */
function _ajax_organization_manager_getCitiesOptions($stateId)
{
    $results = null;
    if (!empty($stateId)) {
        $query = db_select('zd_locations', 'zl')
            ->fields('zl', array('id', 'title'));
        $query->join('zd_org_loc', 'zol', 'zol.cityId=zl.id');
        $query->join('zd_organization', 'zo', 'zo.id=zol.organizationId');
        $query->distinct(true);
        $results = $query->condition('pid', $stateId)
            ->orderBy('weight', 'ASC')
            ->orderBy('title', 'ASC')
            ->execute()
            ->fetchAll();
    }
    $locations = array(
        0 => (object) array(
                'id' => 0,
                'title' => 'select',
            ),
    );
    if (!empty($results)) {
        $locations = array_merge($locations, $results);
    }else {
        return array(
            0 => (object) array(
                    'id' => 0,
                    'title' => 'select',
                ),
        );
    }
    return $locations;
}

/**
 * Get countries (AJAX) first level for ADMIN
 */
function _ajax_organization_manager_getAdminCountriesOptions()
{
    return db_select('zd_locations', 'zl')
        ->fields('zl', array('id', 'title'))
        ->condition('zl.pid', 0)
        ->orderBy('zl.weight', 'ASC')
        ->orderBy('zl.title', 'ASC')
        ->execute()
        ->fetchAll();
}

/**
 * Get states (AJAX) second level FOR ADMIN
 */
function _ajax_organization_manager_getAdminStatesOptions($countryId)
{
    $results = null;
    if (!empty($countryId)) {
        $results = db_select('zd_locations', 'zl')
            ->fields('zl', array('id', 'title'))
            ->condition('zl.pid', $countryId)
            ->orderBy('zl.weight', 'ASC')
            ->orderBy('zl.title', 'ASC')
            ->execute()
            ->fetchAll();
    }
    $locations = array(
        0 => (object) array(
                'id' => 0,
                'title' => 'select',
            ),
    );
    if (!empty($results)) {
        $locations = array_merge($locations, $results);
    }else {
        return array(
            0 => (object) array(
                    'id' => 0,
                    'title' => 'select',
                ),
        );
    }
    return $locations;
}

/**
 * Get cities (AJAX) third level FOR ADMIN
 */
function _ajax_organization_manager_getAdminCitiesOptions($stateId)
{
    $results = null;
    if (!empty($stateId)) {
        $results = db_select('zd_locations', 'zl')
            ->fields('zl', array('id', 'title'))
            ->condition('pid', $stateId)
            ->orderBy('weight', 'ASC')
            ->orderBy('title', 'ASC')
            ->execute()
            ->fetchAll();
    }
    $locations = array(
        0 => (object) array(
                'id' => 0,
                'title' => 'select',
            ),
    );
    if (!empty($results)) {
        $locations = array_merge($locations, $results);
    }else {
        return array(
            0 => (object) array(
                    'id' => 0,
                    'title' => 'select',
                ),
        );
    }
    return $locations;
}