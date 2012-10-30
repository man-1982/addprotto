<?php

function stroycenter_theme(&$existing, $type, $theme, $path) {
  return array(
    'main_menu' => array(
      'variables' => array(),
    ),
  );
}

/**
 *
 * @return HTML render for
 */
function stroycenter_main_menu() {
  $menu_name = variable_get('menu_main_links_source', 'main-menu');

  $menu_output = &drupal_static(__FUNCTION__, array());

  if (!isset($menu_output[$menu_name])) {
    $tree = stroycenter_menu_tree_all_data($menu_name);
    $menu_output[$menu_name] = menu_tree_output($tree);
  }
  return drupal_render($menu_output[$menu_name]);
}

/**
 * @param $menu_name
 * @return array
 */
function stroycenter_menu_tree_all_data($menu_name) {
  $tree = &drupal_static(__FUNCTION__, array());

  // Check if the active trail has been overridden for this menu tree.
  $active_path = menu_tree_get_path($menu_name);
  // Load the menu item corresponding to the current page.
  if ($item = menu_get_item($active_path)) {
    // Generate a cache ID (cid) specific for this page.
    $cid = 'links:' . $menu_name . ':page:' . $item['href'] . ':' . $GLOBALS['language']->language . ':' . (int) $item['access'];

    if (!isset($tree[$cid])) {
      // If the static variable doesn't have the data, check {cache_menu}.
      $cache = cache_get($cid, 'cache_menu');
      if ($cache && isset($cache->data)) {
        // If the cache entry exists, it contains the parameters for
        // menu_build_tree().
        $tree_parameters = $cache->data;
      }
      // If the tree data was not in the cache, build $tree_parameters.
      if (!isset($tree_parameters)) {
        $tree_parameters = array(
          'min_depth' => 1,
          'max_depth' => MENU_MAX_DEPTH,
        );
        // Parent mlids; used both as key and value to ensure uniqueness.
        // We always want all the top-level links with plid == 0.
        $active_trail = array(0 => 0);

        // If the item for the current page is accessible, build the tree
        // parameters accordingly.
        if ($item['access']) {
          // Find a menu link corresponding to the current path. If $active_path
          // is NULL, let menu_link_get_preferred() determine the path.
          if ($active_link = menu_link_get_preferred($active_path, $menu_name)) {
            // The active link may only be taken into account to build the
            // active trail, if it resides in the requested menu. Otherwise,
            // we'd needlessly re-run _menu_build_tree() queries for every menu
            // on every page.
            if ($active_link['menu_name'] == $menu_name) {
              // Use all the coordinates, except the last one because there
              // can be no child beyond the last column.
              for ($i = 1; $i < MENU_MAX_DEPTH; $i++) {
                if ($active_link['p' . $i]) {
                  $active_trail[$active_link['p' . $i]] = $active_link['p' . $i];
                }
              }
            }
          }
          $parents = $active_trail;

            // Collect all the links set to be expanded, and then add all of
            // their children to the list as well.
            do {
              $result = db_select('menu_links', NULL, array('fetch' => PDO::FETCH_ASSOC))
                ->fields('menu_links', array('mlid'))
                ->condition('menu_name', $menu_name)
                ->condition('has_children', 1)
                ->condition('plid', $parents, 'IN')
                ->condition('mlid', $parents, 'NOT IN')
                ->execute();
              $num_rows = FALSE;
              foreach ($result as $item) {
                $parents[$item['mlid']] = $item['mlid'];
                $num_rows = TRUE;
              }
            } while ($num_rows);
          $tree_parameters['expanded'] = $parents;
          $tree_parameters['active_trail'] = $active_trail;
        }
        // If access is denied, we only show top-level links in menus.
        else {
          $tree_parameters['expanded'] = $active_trail;
          $tree_parameters['active_trail'] = $active_trail;
        }
        // Cache the tree building parameters using the page-specific cid.
        cache_set($cid, $tree_parameters, 'cache_menu');
      }

      // Build the tree using the parameters; the resulting tree will be cached
      // by _menu_build_tree().
      $tree[$cid] = menu_build_tree($menu_name, $tree_parameters);
    }
    return $tree[$cid];
  }

  return array();
}

/**
 * extarct page trails from menu
 */
function stroycenter_build_page_trails($page_menu) {

  $trail = array();
  foreach ($page_menu as $item) {
    if ($item['link']['in_active_trail']) {
      $trail[] = $item['link']['mlid'];
    }
    if ($item['below']) {
      $trail = array_merge($trail, stroycenter_build_page_trails($item['below']));
    }
  }

  return $trail;
}

/**
 * @param $vars
 */
function stroycenter_preprocess_page(&$vars) {
//  dpm($vars);
    // Вставлеям лого в середину меню
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


function stroycenter_preprocess_search_block_form(&$variables) {
}

/**
 * Implements hook_form_BASE_FORM_ID_alter().
 *
 */

function stroycenter_form_search_block_form_alter(&$form, &$form_state, $form_id) {
}