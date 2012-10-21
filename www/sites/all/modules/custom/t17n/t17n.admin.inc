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
  $form['voc'] = array(
    '#type'   => 'value',
    '#value'  => $voc,
  );
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



  $hierarchical_tree = t17n_get_hierarchical_tree($voc->vid);

//  dpm(t17n_get_hierarchical_tree($voc->vid), 'child tree');
  $variables['hierarchical_tree'] = $hierarchical_tree;
  $variables['attributes'] = array();
  $form['tree'] = array(
    '#markup' => theme('t17n_hierarchical_tree', $variables),
);
  $form['submit'] = array(
    '#type'     => 'submit',
     '#submit'  => array('t17n_settings_voc_form_submit'),
    '#value'    => t('Submit'),
  );
//  dpm(theme_t17n_hierarchical_tree($hierarchical_tree), 'theme_t17n_hierarchical_tree');

  return $form;
}

function t17n_settings_voc_form_submit($form, &$form_state) {
  $values = $form_state['values'];
  variable_set('t17n_voc_block_' . $values['voc']->vid, 't17n_voc_block_' . $values['voc']->vid);
}






