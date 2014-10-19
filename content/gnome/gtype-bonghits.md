Status: draft
Title: GType bonghits
Tags: gobject, type system, design, platform
Summary: objects? where we're going, we don't need objects…
Abstract: in the type system of the core GNOME platform exist two distinct but equally important categories: objects, which can have properties, signals, and reference counts; and bonghits, which may or may not end up fixing them. these are their stories.

note: in this article I use the `monospace font` for class names, and the
*italic font* for libraries; this is necessary so that when I talk about
`GObject` or *GObject* you know whether I'm referring to the type name, or
the type system library.

I had a discussion with Ryan, once.

actually, it's been a constant discourse that has been going off and on for
about four years, now.

I was trying to have faster, better, and cleaner properties for *GObject*;
Ryan was trying to have fastest, best, cleanest properties for *GObject*. the
distance between the two positions is pretty obvious, and the end result is
that while we don't really have anything better in the properties
department, we *do* have better `GObject`s now than we did four years ago.

the last iteration of our discussion ended up touching the subject of
storing the property meta-classes into per-class data storage; this required
a bit of rejigging of how `GTypeClass` structures are allocated, but it was
pretty trivial. we can, now, handle per-class private data like we handle
per-instance private data, with simple pointer arithmetics that is
completely transparent for the user.

this opens up a series of design questions that I've just barely started to
explore.

the first one is: we can ask everyone to turn their idiomatic *GObject* code
into this:

{% include_code gobject-property-private.c lang:cpp %}

it would already be a net win: the property is declared inside the type
definition, so it cannot get added anywhere else like it works today (and
let's assume for a moment that we can handwave away what some language
bindings allow); the syntax is simpler and could actually be parsed instead
of inspected at run time; access to property meta-classes is faster and does
not require to take *all* the locks in the world.

the downside is that "class private" data structure sitting there, for no
good reason except the fact that we need a structure to get the size out.

can we get away without it?

we could, if we simply added knowledge of the properties to the type system,
instead of bolting them on top of it. if *GType* knew that a type we are
registering has properties, then we could simply grow the `GTypeClass`
ourselves, and keep a reference to the property meta-classes:

{% include_code gtype-property.c lang:cpp %}

the side effect of this approach is that it generates more questions on the
lower levels of the type system. to answer those questions, we may need to
start revising other bits and pieces of *GType* — starting from signals.

back when the type system was first introduced, the signal machinery was
attached to the `GTypeInstance`, instead of adding it to `GObject`; this is
largely seen as a mistake. the approach to rectify this issue that has been
explored in the last 10 years has been "move signals to `GObject`". after all,
`GObject` is already sporting properties, reference counting, and its memory
management.

what if, instead of moving stuff inside `GObject`, we moved stuff downwards,
and inside `GTypeInstance`?

signals are already there; properties can be added in a fairly
straightforward way: we use `GProperty`, which does not need virtual
functions inside the class virtual functions table, and can now decoupled
from `GParamSpec` because we don't have to preserve backward compatibility
with the existing `GObject` machinery; all that remains is reference counting
and the memory management functions necessary to release memory and break
reference cycles — and that can be moved side-ways, instead of inside
`GTypeInstance`.

reference counting is a memory management technique — garbage collection, if
you will. there is no essential need for a `GTypeInstance` to be reference
counted — that's why that machinery lives inside `GObject`. there is also
nothing particularly tied to the type system for reference counting to work;
reference counting can be applied to any memory region, as long as you know
which function ought to be called when the last reference drops, in order to
free the data.

at this point, reference counted pointers *could* live in GLib, as part of
the memory allocation API. we could have typed meta-classes that live in
*GObject* that allow you to create a reference counted `GTypeInstance`
sub-class — and we could have two of them, one for simple reference counted
types, and another for atomically reference counted types.

{% include_code gtype-next.c lang:cpp %}

there are lots of open questions, at this point.

is this work feasible, or even desirable?

where does this leave `GObject`? a legacy class, meant to be phased
out when we switch to GTK+ 4.x? can we re-implement `GObject` on top of a
`GTypeInstance` that does properties and signals, and that defers reference
counting to a separate meta-class?

what about introspection support? how can we provide the meta-information on
a type (its properties, its signals, its memory management) to language
bindings, hopefully in a way that does now require run-time discovery to
generate the XML description of the API?

if you have answers, or even more questions, feel free to send them to me.
