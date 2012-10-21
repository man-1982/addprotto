<?

/**
 * @param $voc
 */
function theme_t17n_hierarchical_tree($variables) {

  $jquery_update_path = drupal_get_path('module', 'jquery_update') . '/replace/';
  $jquery_ui_path_js = $jquery_update_path .'ui/ui/';

  drupal_add_js( $jquery_ui_path_js .'jquery-ui.js');
  drupal_add_js( $jquery_ui_path_js .'jquery.ui.accordion.js');

  drupal_add_js(drupal_get_path('module', 't17n').'/js/t17n-accordion.js');
  drupal_add_css(drupal_get_path('module', 't17n') . '/css/ui-lightness/jquery-ui-1.8.23.custom.css');

  $output = '';
  $hierarchical_tree = $variables['hierarchical_tree'];
  $attributes = $variables['attributes'];
  $delta = isset($variables['delta'])? $variables['delta'] : 0;
  if (is_array($hierarchical_tree)&& !empty($hierarchical_tree)) {
    $output = '<div id="t17-accordion-'. $delta .'" class="t17-accordion-'. $delta .'">';
      $output .= _theme_t17n_hierarchical_tree($hierarchical_tree, $attributes);
    $output .='</div>';
  }

  $settings['accordion'] = array(
    'selector' =>  '#t17-accordion-' . $delta,
  );

  drupal_add_js(array('t17n' => $settings),array('type' => 'setting'));




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
    $attributes_term['class'][] = 't17n-level-' . $term->t17n_depth;
    // Headers for accordion
    $output .= '<li' .drupal_attributes($attributes_term) . '>';

    $output .= l($term->name .' - ' . $term->tid, 'taxonomy/term/' . $term->tid);

    $output .= "</li>\n";
    //end header for accordion

    // body of accordion
    $output .= '<div class="t17-body-accordion">'. l($term->name .' - ' . $term->tid, 'taxonomy/term/' . $term->tid) ;

    if(is_array($term->childs)&&!empty($term->childs)) {
      $childs_array = $term->childs;
      $output .= _theme_t17n_hierarchical_tree($childs_array, array('class' => array('child')))  . "\n";
    }
    $output .="</div>"  ;
    //end body of accordion

  }
  $output .= "</ul>\n";
  return $output;
}