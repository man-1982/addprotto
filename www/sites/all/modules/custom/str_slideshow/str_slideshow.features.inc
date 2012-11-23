<?php
/**
 * @file
 * str_slideshow.features.inc
 */

/**
 * Implements hook_views_api().
 */
function str_slideshow_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function str_slideshow_image_default_styles() {
  $styles = array();

  // Exported image style: 418x468.
  $styles['418x468'] = array(
    'name' => '418x468',
    'effects' => array(
      2 => array(
        'label' => 'Масштабирование и обрезка',
        'help' => '«Масштабирование и обрезка» сначала масштабирует изображение, а затем обрезает большее значение. Это наиболее эффективный способ создания миниатюр без искажения пропорций исходного изображения.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '418',
          'height' => '468',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: 640x320.
  $styles['640x320'] = array(
    'name' => '640x320',
    'effects' => array(
      1 => array(
        'label' => 'Масштабирование и обрезка',
        'help' => '«Масштабирование и обрезка» сначала масштабирует изображение, а затем обрезает большее значение. Это наиболее эффективный способ создания миниатюр без искажения пропорций исходного изображения.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '640',
          'height' => '320',
        ),
        'weight' => '1',
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function str_slideshow_node_info() {
  $items = array(
    'baner' => array(
      'name' => t('baner'),
      'base' => 'node_content',
      'description' => t('Банеры'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
