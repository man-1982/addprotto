<?php

/**
 * @file
 * select_with_style_handle_filter_term_node_tid.inc
 *
 * Views filter override to style exposed term filters.
 * Also covers the case where exposed filter forms are in blocks.
 */

class select_with_style_handler_filter_term_node_tid extends views_handler_filter_term_node_tid {

  function value_form(&$form, &$form_state) {

    if (empty($this->options['expose']['identifier'])) {
      parent::value_form($form, $form_state);
      return;
    }

    $name = $this->options['expose']['identifier'];

    // Check if the filter name has '_tid' appended. If so, chop it to find
    // the associated field name.
    if (drupal_substr($name, -4) == '_tid') {
      $field_name = drupal_substr($name, 0, drupal_strlen($name) - 4);
    }
    else {
      $field_name = $name;
    }
    $options = array();
    if ($field = field_info_field($field_name)) {

      $instance = select_with_style_get_field_instance($field_name);

      // Override widget setting if "Show hierarchy in dropdown" isn't ticked
      // on the filter's Settings panel.
      if (empty($this->options['hierarchy'])) {
        $instance['widget']['settings']['select_with_style']['hierarchy_depth_prefix'] = NULL;
      }
      elseif (empty($instance['widget']['settings']['select_with_style']['hierarchy_depth_prefix'])) {
        // If "Show in hierarcy in dropdown" is ticked but the widget does not
        // have it enabled, enable it using a single hyphen (core behaviour).
        $instance['widget']['settings']['select_with_style']['hierarchy_depth_prefix'] = '-';
      }
      // Load options (with/without hierarchy prefixes) and get attributes too.
      list($options, $option_attributes) = _select_with_style_options_and_attributes_lists($field, $instance);
    }
    if (empty($options)) {
      // If any of the above failed, then default to what Views does normally.
      parent::value_form($form, $form_state);
      return;
    }

    if (!empty($this->options['expose']['reduce'])) {
      $options = $this->reduce_value_options($options);

      // For optgroups, remove parents that have no children ...
      foreach ($options as $parent => $children) {
        if (is_array($children) && empty($children)) {
          unset($options[$parent]);
        }
      }
    }
    if (!empty($instance['widget']['settings']['select_with_style']['multi_select_height'])) {
      if ($field['cardinality'] > 1 || $field['cardinality'] == FIELD_CARDINALITY_UNLIMITED) {
        $form[$name]['#size'] = $instance['widget']['settings']['select_with_style']['multi_select_height'];
      }
    }
    $max_size = empty($form[$name]['#size']) ? 9 : $form[$name]['#size'];
    $form[$name]['#size'] = min($max_size, $this->count_entries($options));

    $form[$name]['#type'] = 'select';
    $form[$name]['#multiple'] = TRUE;
    $form[$name]['#options'] = $options;
    $form[$name]['#option_attributes'] = $option_attributes;

    $form['#attached']['css'][] = drupal_get_path('module', 'select_with_style') . '/select_with_style.css';

    // The caller, exposed_form(), wants to receive the element in 'value'.
    $form['value'] = $form[$name];
  }

  // Determine length of select list, including parent headings.
  function count_entries($array) {
    $count = 0;
    foreach ($array as $value) {
      $count += is_array($value) ? 1 + $this->count_entries($value) : 1;
    }
    return $count;
  }
}
