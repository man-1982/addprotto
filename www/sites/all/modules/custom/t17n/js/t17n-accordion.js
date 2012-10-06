
/**
 *
 */
(function ($, Drupal, window, document, undefined) {

  Drupal.behaviors.t17n_accordion =  {
    attach: function(context) {
      var accordionSelectror = Drupal.settings.t17n.accordion.selector;
      var accrodionOptions = {
        header      : 'li.t17n-level-0',
        collapsible : true
      }
      $( accordionSelectror, context).not('.t17-accordion-process').accordion(accrodionOptions).addClass('t17-accordion-process');
      if(window.console) {
        console.log($( accordionSelectror, context));
      }
    }

  }



})(jQuery, Drupal, this, this.document);