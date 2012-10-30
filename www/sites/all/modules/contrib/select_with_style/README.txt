
Select with Style
=================

This module allows you to attractively style select lists, in particular those
that feature parent/child hierarchies, like taxonomies. The module adds CSS
classes that reflect family names and depths in the hierarchy, so you can render
one family differently from another and different from their children. You can
apply colours, font styles or even images, like country flags.

A basic .css file is provided to get you started.

You can also set the height of select boxes and may use any hierarchy depth
indicator prefix string instead of core's stale '-'.

All of the above is achieved through two new variants of the classic "Select
list" widget. Both variants are on offer when you select a widget for a field
of type list or type term reference. The new widgets are:
- Select list, styled optgroups
- Select list, styled tree

The two widgets are similar in appearance, but different in functionality. In
the styled optgroups parent options become labels, which cannot be selected
(clicked), whereas in the styled tree the parents are selectable options, just
like the children. Another difference between the styled optgroups and the
styled tree is that due to W3C/browser restrictions optgroups only go one level
deep, whereas trees can be nested as deep as your taxonomy dictates.

By the way, the definition of a parent is any item that is not a leaf.

This is a lightweight, javascript-free solution without any dependencies. No
libraries are required. There are no module configurations. Just enable the
module and tweak your CSS.

CSS classes added for a parent label or option are of this format:

  class="option-parent group-PARENT tid-NUMBER depth-0"

CSS classes added for a child option are of this format:

  class="option-child group-PARENT tid-NUMBER depth-2"

Where PARENT is the name of the parent taxonomy term and NUMBER the id of the
option term.

Finally, while the main "Select with Style" functionality does not require any
javascript, you may choose to add some additional special effects. See
select_with_style.js


HTML/CSS DISCLAIMER:
Anno 2012 browser support for select lists is still so-so. Firefox is generally
great, but Chrome and Safari do not honour all of the attributes that are
standard on other HTML elements. This is especially so for single-choice
drop-downs.


INVITE FOR FUTURE EXTENSION:
Someone to create a widget to make general lists other than taxonomies
hierarchical, maybe using indentation to denote an item is a child of the
preceding item:

1|parent1
  11|child_a
  49|child_b
5|parent2
  66|child_c
  ...
...
