<?php

function stroycenter_preprocess_page(&$vars) {
  dpm($vars);
  if (isset($vars['main_menu'])) {
    $image_logo = theme_image(
      array(
        'path'        => drupal_get_path('theme', 'stroycenter') . '/logo.png',
        'alt'         => t('Stroycenter'),
        'title'       => t('Stroycenter'),
        'attributes' => array('class' => array('logo')),

      ));
    $logo_link_menu = array(
      'html'        => TRUE,
      'title'       => $image_logo,
      'href'        => '',
    );
    $midle_of_items = round(count($vars['main_menu'])/2);
    $menu_with_image = array();
    foreach($vars['main_menu'] as $mlid => $items) {
      $menu_with_image[$mlid] = $items;
      if(count($menu_with_image) == $midle_of_items) {
        $menu_with_image['menu-with-logo'] = $logo_link_menu;
      }
    }
    $vars['main_menu'] = $menu_with_image;
  }
}