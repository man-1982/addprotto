/**
 * @file
 * A JavaScript file for the theme.
 *
 * In order for this JavaScript to be loaded on pages, see the instructions in
 * the README.txt next to this file.
 */

// JavaScript should be made compatible with libraries other than jQuery by
// wrapping it with an "anonymous closure". See:
// - http://drupal.org/node/1446420
// - http://www.adequatelygood.com/2010/3/JavaScript-Module-Pattern-In-Depth
(function ($, Drupal, window, document, undefined) {

  Drupal.behaviors.stroycenterEqualheights = {
    attach: function (context, settings) {
      if (jQuery().equalHeights) {
//        $(".column").equalHeights();
        var main_height = $('#main').height();
        $('.region-sidebar-second').height(main_height);
      }


      if(jQuery().corner) {
        $("#search-block-form .search-input").corner('10px');
//        $(".wrapper-page-bottom").corner("top 40px" );
      }

    }
  };


})(jQuery, Drupal, this, this.document);
