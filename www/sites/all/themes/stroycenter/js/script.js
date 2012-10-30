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
        $("#search-block-form .search-input").not('corner-process').corner('10px').addClass('corner-process');
        $("#main #content").not('corner-process').corner('4px').addClass('corner-process');
        $(".wrapper-page-bottom").not('corner-process').corner('top 6px' ).addClass('corner-process');
      }

    }
  };

  Drupal.behaviors.mainMenu = {
    attach: function(context, settings) {
      var top_nice_menu = $('#main-menu').offset();


//      $('#main-menu').addClass('primary-menu-top-position');

      $(window).scroll(function() {
        if(window.console) {
          console.log($(this).scrollTop());
          console.log(top_nice_menu.top);
        }

        if($(this).scrollTop() > top_nice_menu.top) {
          $('#main-menu').addClass('primary-menu-top-position');
        }
        else {
          $('#main-menu').removeClass('primary-menu-top-position');
        }

      });
    }
  }


})(jQuery, Drupal, this, this.document);
