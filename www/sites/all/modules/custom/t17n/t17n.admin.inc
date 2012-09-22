<?php
/**
 * @file
 *
 * taxonomy effects adminstations settings
 */


/**
 * Callback funtion for hook_menu
 * @return string List of access vocabularies
 */
function t17n_voc_list() {

  $output = l(t('Add new vocabulary'), 'admin/structure/taxonomy/add/vocabulary') .' | ';
  $output .= l(t('Edit vocabulary settings'), 'admin/structure/taxonomy') .'<br /><br />';

  $vocabularies = taxonomy_get_vocabularies();
  $voc_list = array();

  foreach ($vocabularies as $vocabulary) {
    $voc_list[] = l($vocabulary->name, 'admin/structure/t17n/voc/'. $vocabulary->machine_name);
  }
  if (!count($voc_list)) {
    $voc_list[] = t('No Vocabularies available');
  };
  if(!empty($vocabularies)) {
    drupal_set_message(t('Select vocabularies for added effects'), 'status');
  }
  $output .= theme('item_list', array('items' => $voc_list, 'title' => t('Vocabularies')));

  return $output;

}
/**
 * Defines form for  settings effects
 * @param $form
 * @param $form_state
 * @param $voc
 */
function t17n_settings_voc_form($form, &$form_state, $voc) {
  $module_path = drupal_get_path('module', 't17n') .'/';
  drupal_set_title(t('Settings "Accordion effects" for vocabulary "@name"', array('@name' => $voc->name)));
  $form['disabled'] = array(
    '#title'            => 'disabled',
    '#type'             => 'select',
    '#description'      => t('Disables (true) or enables (false) the accordion. Can be set when initialising (first creating) the accordion.'),
    '#options'         => array(
      'false' => 'false',
      'true'  => 'true',
    ),
    '#default_value'   => variable_get('t17n_accordion_disabled', array('false' => 'false')),
  );
  $form['active'] = array(
    '#title' => 'active',
    '#type'           => 'textfield',
    '#description'     => t('Selector for the active element. Set to false to display none at start. Needs collapsible: true.'),
    '#default_value' => variable_get('t17n_accordion_first_child', 'first child'),
    '#size' => 60,
    '#maxlength' => 128,
  );

  $form['animated'] = array(
    '#title'          => 'animated',
    '#description'    => t('Choose your favorite animation, or disable them.'),
    '#type'           => 'select',
    '#options'        => array(
      'slide'         => 'slide',
      'bounceslide'   => 'bounceslide'
    ),
    '#default_value' =>variable_get('t17n_accordion_animated', array('slide' => 'slide')),
  );

  $jquery_update_path = drupal_get_path('module', 'jquery_update') . '/replace/';
  $jquery_ui_path_js = $jquery_update_path .'ui/ui/';
  $jquery_ui_path_css = $jquery_update_path .'ui/themes/';

  $form['#attached']['css'][] = $jquery_ui_path_css .'base/jquery.ui.accordion.css';
  $form['#attached']['js'][] = $jquery_ui_path_js .'jquery-ui.js';
  $form['#attached']['js'][] = $jquery_ui_path_js .'jquery.ui.accordion.js';

  $hierarchical_tree = t17n_get_hierarchical_tree($voc->vid);
  dpm(t17n_get_hierarchical_tree($voc->vid), 'child tree');

  dpm(theme_t17n_hierarchical_tree($hierarchical_tree));

  return $form;
}

/**
 * Get all parents tree whith parents id =0
 * @param $vid
 * @return array
 */
function t17n_get_parents_tree($vid) {

  $parents = &drupal_static(__FUNCTION__, array());

  if ($vid && !isset($parents[$vid])) {
    $query = db_select('taxonomy_term_data', 't');
    $query->join('taxonomy_term_hierarchy', 'h', 'h.tid = t.tid');
    $query->addField('t', 'tid');
    $query->condition('t.vid', $vid);
    $query->condition('h.parent', 0);
    $query->addTag('term_access');
    $query->orderBy('t.weight');
    $query->orderBy('t.name');
    $tids = $query->execute()->fetchCol();
    $parents[$vid] = taxonomy_term_load_multiple($tids);
  }

  return isset($parents[$vid]) ? $parents[$vid] : array();
}

/**
 * Get childs for terms tree
 * @param $tree
 */
function t17_get_childs_tree($tree_parent) {

  $childs_tree = array();

  foreach($tree_parent as $key => $parent_term) {
    $childs = taxonomy_get_children($parent_term->tid, $parent_term->vid);
    if (!empty($childs)) {
      $tree_parent[$key]->childs = t17_get_childs_tree($childs);

    }
  }
  return $tree_parent;
}

/**
 * Get hierarctical tree with childs
 */
function t17n_get_hierarchical_tree($vid) {

  $parent_tree = t17n_get_parents_tree($vid);

  $hierarchical_tree =  t17_get_childs_tree($parent_tree);

  return $hierarchical_tree;
}

/**
 * @param $voc
 */
function theme_t17n_hierarchical_tree($hierarchical_tree) {
  $output = _theme_t17n_hierarchical_tree($hierarchical_tree);
 return $output;
}

/**
 * Helper function for theming
 * @param $hierarchical_tree
 * @return string
 */
function _theme_t17n_hierarchical_tree($hierarchical_tree) {

  $items = array();
  if (!is_array($hierarchical_tree)|| empty($hierarchical_tree)) {
    return $items;
  }
  foreach($hierarchical_tree as $key => $term) {
    $items[] = array(
      'data'  => check_plain($term->name),
      //TODO add class
      'class' => array(),
    );
    if(is_array($term->childs)&&!empty($term->childs)) {
      $childs_array = $term->childs;
      $items[]= array(
        'children'  =>  _theme_t17n_hierarchical_tree($childs_array),
        //TODO add class
        'class'     => array(),
      );
    }
  }
  return $items;
}