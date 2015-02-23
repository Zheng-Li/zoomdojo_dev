<?php

/**
 * Tab list
 */
function zoomdojo_blocks_getTabs()
{
    return '';
}

/**
 * Add tab form
 */
function zoomdojo_blocks_addTabsForm()
{
    $form['title'] = array(
        '#type'         => 'textfield', 
        '#title'        => t('Tab title'), 
        '#size'         => 60,
        '#maxlength'    => 255, 
        '#required'     => TRUE,
    );
    $form['weight'] = array(
        '#type'         => 'weight', 
        '#title'        => t('Weight'), 
        '#delta'        => 20, 
    );
    $form['save'] = array(
        '#type'     => 'submit', 
        '#value'    => t('Save'),
    );
    $form['actions']['cancel'] = array(
        '#markup' => l(t('Cancel'), 'admin/zoomdojo/tablet-panel/list'),
    );
    return $form;
}

/**
 * Block list
 */
function zoomdojo_blocks_getTabletPanelBlocks()
{
    return '';
}

/**
 * Add block form
 */
function zoomdojo_blocks_addTabletBlockForm()
{
    return $form;
}