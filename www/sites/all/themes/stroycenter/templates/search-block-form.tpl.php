<?php

/**
 * @file
 * Displays the search form block.
 *
 * Available variables:
 * - $search_form: The complete search form ready for print.
 * - $search: Associative array of search elements. Can be used to print each
 *   form element separately.
 *
 * Default elements within $search:
 * - $search['search_block_form']: Text input area wrapped in a div.
 * - $search['actions']: Rendered form buttons.
 * - $search['hidden']: Hidden form elements. Used to validate forms when
 *   submitted.
 *
 * Modules can add to the search form, so it is recommended to check for their
 * existence before printing. The default keys will always exist. To check for
 * a module-provided field, use code like this:
 * @code
 *   <?php if (isset($search['extra_field'])): ?>
 *     <div class="extra-field">
 *       <?php print $search['extra_field']; ?>
 *     </div>
 *   <?php endif; ?>
 * @endcode
 *
 * @see template_preprocess_search_block_form()
 */
$path_image_loop = url(drupal_get_path('theme', 'stroycenter') . '/images/lop.jpg', array('absolute' => TRUE));

global $user;

// For usability's sake, avoid showing two login forms on one page.
if (!$user->uid && !(arg(0) == 'user' && !is_numeric(arg(1)))) {
  ctools_include('ajax');
  ctools_include('modal');

  // Add CTools' javascript to the page.
  ctools_modal_add_js();
  // Include the CTools tools that we need.
//  $user_login = l(t('Вход'), 'user-login/nojs/login', array('attributes' => array('class' => 'user-login-link')));
  $user_login = ctools_modal_text_button(t('Вход'), 'user-login/nojs/login', 'Вход', 'user-login-link');
//  $user_register = l(t('Региcтрация'), 'user-login/nojs/register', array('attributes' => array('class' => 'user-login-link')));
  $user_register = ctools_modal_text_button(t('Региcтрация'), 'user-login/nojs/register', 'user-register-link');

  $variables['items'] = array($user_login, $user_register);
  $variables['type'] = 'ul';
  $variables['attributes'] = array('class' => 'wrapper-user-login');
  $output = theme('item_list', $variables);
  $str_tools_user_login = $output;
}



?>
<div class="container-inline">
    <div class ="search-wrapper">
        <input type="text" class="search-input" maxlength="128" size="25" value="" name="search_block_form" id="search-block-form-input">
        <input type="image" class="search-submit" src="<?php print $path_image_loop ?>" align="absmiddle" id="submit-button-search">
    </div>
  <?php if (isset($str_tools_user_login)) {print $str_tools_user_login;}; ?>
  <?php print $search['hidden']; ?>
</div>

