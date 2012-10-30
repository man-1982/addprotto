/*
 * While the main "Select with Style" functionality does not require any
 * javascript, you may choose to add some additional effects. Below are a
 * few ideas. Remove the /* and its closing counter part and customise the ones
 * you like.
 *
 * These behaviors are attached to the entire page. When the document is ready
 * all of the attach functions below are called, passing in the document context
 * and the value of Drupal.settings.
 */

(function($) {

  // #1 Put a green border around select lists, text fields and text areas, the
  //    moment an option is clicked or a value entered.
/*Drupal.behaviors.select_with_style_color_border_on_select = {
    attach: function(context, settings) {
      $(":input, :checkbox", context).change(function() { // can't seem to style checkboxes
        this.style.border = "2px solid #5ed230";
      });
    }
  }
*/

  // #2 Render select as small box initially. Then expand the select box
  //    to reveal all its options when the box is hovered over.
/*Drupal.behaviors.select_with_style_expand_on_hover = {
    attach: function(context, settings) {
      $("select", context).mouseover(function() {
        this.size = this.options.length;
      });
      $("select").mouseout(function() {
        this.size = 1;
      });
    }
  }
*/

})(jQuery);