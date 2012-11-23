<?php

/**
 * @file
 * Default views template for displaying a slideshow.
 *
 * - $view: The View object.
 * - $options: Settings for the active style.
 * - $rows: The rows output from the View.
 * - $title: The title of this group of rows. May be empty.
 *
 * @ingroup views_templates
 */
?>

<div class="skin-<?php print $skin; ?>">
  <?php if (!empty($top_widget_rendered)): ?>
    <div class="baner-on-main-views-slideshow-controls-top clearfix">
      <?php print $top_widget_rendered; ?>
    </div>
  <?php endif; ?>

  <?php print $slideshow; ?>

  <div class="slideshow-right-corner">
      <div class="slideshow-left-corner"></div>
  </div>

  <?php if (!empty($bottom_widget_rendered)): ?>
    <div class="baner-on-main-views-slideshow-controls-bottom clearfix">
      <?php print $bottom_widget_rendered; ?>
    </div>
  <?php endif; ?>
</div>
