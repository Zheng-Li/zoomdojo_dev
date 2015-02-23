<?php
function organization_manager_job_types_list($form_state){

    $form['job_types']['#tree'] = TRUE;

    $result = organization_manager_job_types_get_data();

    foreach ($result as $item) {
        $form['job_types'][$item->id] = array(
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

    // $form['actions']           = array('#type' => 'actions');
    // $form['actions']['submit'] = array('#type'  => 'submit', '#value' => t('Save Changes'));
    return $form;
}

function organization_manager_job_types_get_data($without_aliases = false){
    $rootnodes = db_query('SELECT id, title, weight, pid 
                       FROM {zd_job_types}
                       WHERE (pid = 0 '.($without_aliases?'&& alias_all != 1':'').')
                       ORDER BY weight ASC');
    $itemtree  = array();
    $depth     = -1;
    foreach ($rootnodes as $parent) {
        organization_manager_job_types_get_tree($parent, $itemtree, $depth);
    }
    return $itemtree;
}

function organization_manager_job_types_get_tree($parentitem, &$itemtree = array(), &$depth = 0){
    $depth++;
    $parentitem->depth         = $depth;
    $itemtree[$parentitem->id] = $parentitem;
    $children                  = db_query('SELECT id, title, weight, pid
                      FROM {zd_job_types}
                      WHERE (pid = :pid)
                      ORDER BY weight ASC', array(':pid' => $parentitem->id));
    foreach ($children as $child) {
        if (!in_array($child->id, array_keys($itemtree))) {
            organization_manager_job_types_get_tree($child, $itemtree, $depth);
        }
    }
    $depth--;
    return;
}

function theme_organization_manager_job_types_list($variables)
{
    $form = $variables['form'];

    $rows = array();

    foreach (element_children($form['job_types']) as $id) {
        $form['job_types'][$id]['weight']['#attributes']['class'] = array('example-item-weight');
        $form['job_types'][$id]['id']['#attributes']['class']  = array('example-item-id');
        $form['job_types'][$id]['pid']['#attributes']['class'] = array('example-item-pid');
        $class = array('draggable');
        $indent = theme('indentation', array('size' => $form['job_types'][$id]['depth']['#value']));
        unset($form['job_types'][$id]['depth']);
        $rows[] = array(
            'data'  => array(
                $indent . drupal_render($form['job_types'][$id]['title']),
                array('data' => drupal_render($form['job_types'][$id]['weight']), 'class' => 'tabledrag-hide'),
                array('data' =>drupal_render($form['job_types'][$id]['id']), 'style' => 'display:none;'),
                array('data' =>drupal_render($form['job_types'][$id]['pid']), 'style' => 'display:none;'),
                l(t('Edit'), 'admin/organization-manager/job-types/edit/' . $id),
                l(t('Delete'), 'admin/organization-manager/job-types/delete/' . $id),
            ),
            //'class' => $class,
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

function organization_manager_job_types_list_submit($form, &$form_state)
{
    foreach ($form_state['values']['job_types'] as $id => $item) {
        db_query(
            "UPDATE {zd_job_types} SET weight = :weight, pid = :pid WHERE id = :id", array(':weight' => $item['weight'], ':pid'    => $item['pid'], ':id'     => $id)
        );
    }
}

function organization_manager_job_type_add()
{
    $id = arg(4);

    if ($id) {
        $jobType = db_select('zd_job_types', 't')
            ->fields('t', array('id', 'title','alias_all'))
            ->condition('id', $id)
            ->execute()
            ->fetch();
    }
    
    $form['id']    = array(
        '#type'  => 'hidden',
        '#value' => $id
    );
    if(!$id){
        $data = organization_manager_job_types_get_data();
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
    $form['alias_all'] = array(
        '#type'      => 'checkbox',
        '#title'     => t('Alias for "All jobs"'),
        '#value'     => $id ? $jobType->alias_all : 0
    );
    $form['save']  = array(
        '#type'  => 'submit',
        '#value' => 'save'
    );
    return $form;
}

function organization_manager_job_type_add_submit($formId, &$formValue)
{
    $fields = array(
        'title' => t($formValue['input']['title']),
        'alias_all' => $formValue['input']['alias_all'] ? 1 : 0,
    );
    if($formValue['input']['pid']){
        $fields['pid'] = t($formValue['input']['pid']);
    }
    db_merge('zd_job_types')
        ->key(array('id' => t($formValue['values']['id'])))
        ->fields($fields)
        ->execute();

    $formValue['redirect'] = 'admin/organization-manager/job-types';
}

function organization_manager_job_type_delete()
{
    $id = arg(4);
    db_delete('zd_job_types')
        ->condition('id', $id)
        ->execute();
    
    drupal_goto('admin/organization-manager/job-types');
}