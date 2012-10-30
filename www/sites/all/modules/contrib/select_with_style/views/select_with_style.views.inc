<?php

/**
 * @file
 * select_with_style.views.inc
 *
 * Alterations to Views filter handlers.
 */

/**
 * Implements hook_field_views_data_alter().
 *
 * Resets the term filter handler set by taxonomy_field_views_data().
 * We have to go through this palaver in order to get Views to render
 * exposed term forms in blocks properly. For some reason Views renders exposed
 * term forms in blocks differently from exposed forms embedded on the page.
 */
function select_with_style_field_views_data_alter(&$data, $field) {
  foreach ($data as $table_name => $table_data) {
    foreach ($table_data as $field_name => $field_data) {
      if (isset($data[$table_name][$field_name]['filter']['handler']) && $data[$table_name][$field_name]['filter']['handler'] == 'views_handler_filter_term_node_tid') {
        $data[$table_name][$field_name]['filter']['handler'] = 'select_with_style_handler_filter_term_node_tid';
      }
    }
  }
}

/**
 * Implements hook_views_data_alter().
 *
function select_with_style_views_data_alter(&$data) {
  if (isset($data['taxonomy_term_data']['tid']['filter']['handler'])) {
    $data['taxonomy_term_data']['tid']['filter']['handler'] = 'select_with_style_handler_filter_term_node_tid';
  }
  if (isset($data['taxonomy_index']['tid']['filter']['handler'])) {
    $data['taxonomy_index']['tid']['filter']['handler'] = 'select_with_style_handler_filter_term_node_tid';
  }
}
 */