Title: Constraints
Slug: constraints
Tags: development, layout, gtk, constraints, solvers
Date: 2016-09-23 12:00
Summary: Experiments with constraint-based layout systems for GTK+
Abstract: Aside from working on GSK, a long-running side project of mine is to write and add new layout policy that is based on constraints instead of fixed positioning and boxes-within-boxes; I've been meaning to add this to GTK+ since the time I wrote a naïve implementation inside Clutter, years ago, and now I got to do it properly for my work at Endless.

GUI toolkits have different ways to lay out the elements that compose an
application's UI. You can go from the fixed layout management — somewhat
best represented by the old '90s Visual tools from Microsoft; to the
"springs and struts" model employed by the Apple toolkits until recently; to
the "boxes inside boxes inside boxes" model that GTK+ uses to this day. All
of these layout policies have their own distinct pros and cons, and it's not
unreasonable to find that many toolkits provide support for more than one
policy, in order to cater to more use cases.

For instance, while GTK+ user interfaces are mostly built using nested boxes
to control margins, spacing, and alignment of widgets, there's a sizeable
portion of GTK+ developers that end up using [GtkFixed][gtk-fixed-api] or
[GtkLayout][gtk-layout-api] containers because they need fixed positioning
of children widget — until they regret it, because now they have to handle
things like reflowing, flipping contents in right-to-left locales, or font
size changes.

Additionally, most UI designers do not tend to "think with boxes", unless
it's for Web pages, and even in that case CSS affords a certain freedom that
cannot be replicated in a GUI toolkit. This usually results in engineers
translating a UI specification made of ties and relations between UI
elements into something that can be expressed with a pile of grids, boxes,
bins, and stacks — with all the back and forth, validation, and resources
that the translation entails.

It would certainly be easier if we could express a GUI layout in the same
set of relationships that can be traced on a piece of paper, a UI design
tool, or a design document:

  - this label is at 8px from the leading edge of the box
  - this entry is on the same horizontal line as the label, its leading
    edge at 12px from the trailing edge of the label
  - the entry has a minimum size of 250px, but can grow to fill the
    available space
  - there's a 90px button that sits between the trailing edge of the
    entry and the trailing edge of the box, with 8px between either
    edges and itself

Sure, all of these constraints can be replaced by a couple of boxes; some
packing properties; margins; and minimum preferred sizes. If the design
changes, though, like it often does, reconstructing the UI can become
arbitrarily hard. This, in turn, leads to pushback to design changes from
engineers — and the cost of iterating over a GUI is compounded by technical
inertia.

For my daily work at Endless I've been interacting with our design team for
a while, and trying to get from design specs to applications more quickly,
and with less inertia. Having CSS available allowed designers to be more
involved in the iterative development process, but the CSS subset that GTK+
implements is not allowed — for eminently good reasons — to change the UI
layout. We could go "full Web", but that comes with a very large set of
drawbacks — performance on low end desktop devices,  distribution,
interaction with system services being just the most glaring ones. A native
toolkit is still the preferred target for our platform, so I started looking
at ways to improve the lives of UI designers with the tools at our disposal.

Expressing layout through easier to understand relationships between its
parts is not a new problem, and as such it does not have new solutions;
other platforms, like the [Apple operating systems][ios-autolayout], or
Google's [Android][android-constraints], have started to provide this kind
of functionality — mostly available through their own IDE and UI building
tools, but also available programmatically. It's even available for
platforms like [the Web][autolayout-js].

What many of [these solutions][overconstrained-web] seem to have in common
is using more or less the same solving algorithm — [Cassowary][cassowary-web].
Cassowary is:

> an incremental constraint solving toolkit that efficiently solves systems
> of linear equalities and inequalities. Constraints may be either
> requirements or preferences. Client code specifies the constraints to be
> maintained, and the solver updates the constrained variables to have
> values that satisfy the constraints.

This makes it particularly suited for user interfaces.

The original implementation of Cassowary was written in 1998, in Java, C++,
and Smalltalk; since then, various other re-implementations surfaced:
JavaScript, Haskell, slightly-more-modern-C++, etc.

[swing-springlayout]: https://docs.oracle.com/javase/tutorial/uiswing/layout/spring.html
[android-constraints]: https://developer.android.com/training/constraint-layout/index.html
[ios-autolayout]: https://developer.apple.com/library/content/documentation/UserExperience/Conceptual/AutolayoutPG/
[autolayout-js]: http://ijzerenhein.github.io/autolayout.js/
[cassowary-web]: http://constraints.cs.washington.edu/cassowary/
[overconstrained-web]: http://overconstrained.io
[gtk-fixed-api]: https://developer.gnome.org/gtk3/stable/GtkFixed.html
[gtk-layout-api]: https://developer.gnome.org/gtk3/stable/GtkLayout.html
[emeus-wikipedai]: https://en.wikipedia.org/wiki/Eastern_moa
