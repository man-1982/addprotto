<?php

/**
 * @file
 * select_with_style.admin.inc
 *
 * Configuration options for Select with style module.
 */

/**
 * Menu callback for admin configuration settings.
 */
function select_with_style_admin_configure() {
  $form['select_with_style_show_widgets_in_field_list'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show widget names in <a href="/admin/reports/fields">Field list</a> overview (Reports page).'),
    '#default_value' => variable_get('select_with_style_show_widgets_in_field_list', TRUE),
    '#description' => t('')
  );
  return system_settings_form($form);
}

/**
 * Menu callback; lists all defined fields with their widgets for quick reference.
 *
 * Code adapted from function field_ui_fields_list(), field_ui.admin.inc
 */
function select_with_style_fields_and_widgets_list() {
  $instances = field_info_instances();
  $field_types = field_info_field_types();
  $bundles = field_info_bundles();

  $modules = system_rebuild_module_data();

  $show_widget_column = variable_get('select_with_style_show_widgets_in_field_list', TRUE);

  $header = array(t('Field name'), t('Field type'), t('Used in'));
  if ($show_widget_column) {
    $header[] = t('Widget');
  }
  $rows = array();
  foreach ($instances as $entity_type => $type_bundles) {
    foreach ($type_bundles as $bundle => $bundle_instances) {
      foreach ($bundle_instances as $field_name => $instance) {
        $field = field_info_field($field_name);

        // Initialize the row if we encounter the field for the first time.
        if (!isset($rows[$field_name])) {
          $rows[$field_name]['class'] = $field['locked'] ? array('menu-disabled') : array('');
          $rows[$field_name]['data'][0] = $field['locked'] ? t('@field_name (Locked)', array('@field_name' => $field_name)) : $field_name;
          $module_name = $field_types[$field['type']]['module'];
          $rows[$field_name]['data'][1] = $field_types[$field['type']]['label'] . ' ' . t('(module: !module)', array('!module' => $modules[$module_name]->info['name']));
        }

        // Add the current instance.
        $admin_path = _field_ui_bundle_admin_path($entity_type, $bundle);
        $rows[$field_name]['data'][2][] = $admin_path ? l($bundles[$entity_type][$bundle]['label'], $admin_path . '/fields') : $bundles[$entity_type][$bundle]['label'];

        if ($show_widget_column) {
          if (!isset($rows[$field_name]['data'][3])) {
            $rows[$field_name]['data'][3] = array();
          }
          // Add the field widget details (name + module)
          $module_name = $instance['widget']['module'];
          $widget_name = $instance['widget']['type'] . ' ' . t('(module: !module)', array('!module' => $modules[$module_name]->info['name']));
          if (!in_array($widget_name, $rows[$field_name]['data'][3])) {
            $rows[$field_name]['data'][3][] = $widget_name;
          }
        }
      }
    }
  }
  foreach ($rows as $field_name => $cell) {
    $rows[$field_name]['data'][2] = implode(', ', $cell['data'][2]);
    if ($show_widget_column) {
      $rows[$field_name]['data'][3] = implode(', ', $cell['data'][3]);
    }
  }
  if (empty($rows)) {
    $output = t('No fields have been defined yet.');
  }
  else {
    // Sort rows by field name.
    ksort($rows);
    $output = theme('table', array('header' => $header, 'rows' => $rows));
  }
  return $output;
}
