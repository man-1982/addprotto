<?php

//function acquia_marina_theme() {
//
//}
//
//function acquia_marina_form_alter(&$form, &$form_state, $form_id) {
//  switch($form_id) {
//    case 'views_exposed_form':
//      if($form['#id'] == 'views-exposed-form-www-page') {
//
//        if(isset($form['term_node_tid_depth'])) {
//         $form['term_node_tid_depth']['#post_render'][] =  'acquia_marina_term_node_tid_depth';
//
//        }
//
//        dpm($form, $form_id);
//      }
//  }
//}
//
//function acquia_marina_term_node_tid_depth($content, &$element) {
//  dpm(compact('content', 'element'), __FUNCTION__);
//
//  element_set_attributes($element, array('id', 'name', 'size'));
//  _form_set_class($element, array('form-select'));
//
////  foreach($element['#options'] as $key => $value) {
////    if(is_object($value)) {
////      foreach($value->option as $tid => $title) {
////        $parents = taxonomy_get_parents($tid);
////        if(empty($parents)) {
////          $element['#options'][$key]->option[$tid] = '<p class="no-parents">' . $title .'</p>' ;
////        }
////        else {
////          $element['#options'][$key]->option[$tid] = '<p class="have-parents">' . $title .'</p>' ;
////        }
////      }
////    }
////  }
//
//  $output =  '<select' . drupal_attributes($element['#attributes']) . '>' . acquia_marina_form_select_options($element) . '</select>';
//
//  return $output;
//}
//
//function acquia_marina_form_select_options($element, $choices = NULL) {
//  if (!isset($choices)) {
//    $choices = $element['#options'];
//  }
//  // array_key_exists() accommodates the rare event where $element['#value'] is NULL.
//  // isset() fails in this situation.
//  $value_valid = isset($element['#value']) || array_key_exists('#value', $element);
//  $value_is_array = $value_valid && is_array($element['#value']);
//  $options = '';
//  foreach ($choices as $key => $choice) {
//
//     $parents = taxonomy_get_parents($key);
//
//    if (is_array($choice)) {
//      $options .= '<optgroup label="' . $key . '">';
//      $options .= form_select_options($element, $choice);
//      $options .= '</optgroup>';
//    }
//    elseif (is_object($choice)) {
//      $options .= form_select_options($element, $choice->option);
//    }
//    else {
//
//      $key = (string) $key;
//      if ($value_valid && (!$value_is_array && (string) $element['#value'] === $key || ($value_is_array && in_array($key, $element['#value'])))) {
//        $selected = ' selected="selected"';
//      }
//      else {
//        $selected = '';
//      }
//
//
//      if(!empty($parents)) {
//       $class = 'class="no-parents"';
//      }
//      else {
//        $class = 'class="have-parents"';
//      }
//      $options .= '<option'. $class .' value="' . check_markup($key) . '"' . $selected . '>' . check_markup($choice) . '</option>';
//    }
//  }
//  return $options;
//}