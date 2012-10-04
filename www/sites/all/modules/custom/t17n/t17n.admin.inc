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
  $variables['hierarchical_tree'] = $hierarchical_tree;
  $variables['attributes'] = array();
  $form['tree'] = array(
    '#markup' => theme('t17n_hierarchical_tree', $variables),
);
//  dpm(theme_t17n_hierarchical_tree($hierarchical_tree), 'theme_t17n_hierarchical_tree');

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
    $terms = taxonomy_term_load_multiple($tids);
    $parents[$vid] = $terms;
  }

  return isset($parents[$vid]) ? $parents[$vid] : array();
}

/**
 * Get childs for terms tree
 * @param $tree
 */
function t17_get_childs_tree($tree, $depth = 0) {
  $tree_parent = array();
  if(is_array($tree)) {

    foreach($tree as $key => $parent_term) {
      $tree_parent[$key] = $parent_term;
      $childs = taxonomy_get_children($parent_term->tid, $parent_term->vid);

      $tree_parent[$key]->t17_depth = $depth;
      if (!empty($childs)) {
        $tree_parent[$key]->childs = t17_get_childs_tree($childs, ++$depth);
      }
    else {

      }

    }

  }


  return $tree_parent;
}

function t17_get_level($hierarchical_tree, $level = 0) {
    $deep = array();
  foreach($hierarchical_tree as $key => $terms) {
      $hierarchical_tree[$key]->depth = 0;
  }
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
function theme_t17n_hierarchical_tree($variables) {
  $hierarchical_tree = $variables['hierarchical_tree'];
  $attributes = $variables['attributes'];
  $output = _theme_t17n_hierarchical_tree($hierarchical_tree, $attributes);
 return $output;
}

/**
 * Helper function for theming
 * @param $hierarchical_tree
 * @return string
 */
function _theme_t17n_hierarchical_tree($hierarchical_tree, $attributes = array()) {
  if (!is_array($hierarchical_tree)|| empty($hierarchical_tree)) {
    return '';
  }
  $attributes['class'][] =  't17n-treeview';

  $output = '<ul' . drupal_attributes($attributes) . ">\n";

  foreach($hierarchical_tree as $key => $term) {
    $attributes_term = isset($term->attributes) ? $term->attributes : array();
     $output .= '<li' .drupal_attributes($attributes_term) . '>';

      $output .= l($term->name .' - ' . $term->tid, 'taxonomy/term/' . $term->tid);

        if(is_array($term->childs)&&!empty($term->childs)) {
          $childs_array = $term->childs;
           $output .= _theme_t17n_hierarchical_tree($childs_array, array('class' => array('child'))) . "\n";
        }
    $output .= "</li>\n";
  }
  $output .= "</ul>\n";
  return $output;
}

