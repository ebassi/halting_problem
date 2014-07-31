Title: Lazy loading using the GLib main loop
Slug: lazy-loading
Date: 2006-03-30 18:42
Modified: 2014-07-30 18:00
Tags: essays, gtk, glib, lazy loading, patterns
Status: hidden
Abstract: I wrote this page in 2006, back when I was starting out with complex GTK+ user interfaces, and I had to reply multiple times to questions on IRC and mailing lists that asked how to use threads to load content into a list store; this was my attempt at demonstrating that you don't really need threads at all, but you need to break down your work and parcellize it in discrete steps.

Sometimes you have a long list of simple stuff you want to feed into a
`GtkListStore` in order to view it with a `GtkTreeView`. Soon, you realize that
simply dogfeeding the data using a loop like this:

{% include_code lazy/list-store-add-loop.c lang:cpp %}

is really inefficient, as the `GtkTreeView` has to handle every row insertion.

Moving the assignment of the model after the loop makes things slightly better:

{% include_code lazy/list-store-add-loop-fixed.c lang:cpp %}

but the population of the `GtkListStore` might take quite some time
nevertheless, and block your UI.

At this point, people will begin thinking about using a thread to do the list
loading without interfering with the main application loop.

Threads are desiderable only if your application is already threaded - but
introducing threads just to load stuff into a ListStore is simply overkill;
also, making the threading work with the GTK is always a bit hairy, especially
if you also want to update the GUI while loading. Instead, you should use the
great main loop implementation that GLib has. All you need to do is set up a
little finite state machine for loading stuff, use an idle function that gets
called with low priority, and then feed the populated ListStore to the
TreeView.

First step: set up the finite state machine. We use four states, two of which
are the actual states for loading the items into the model and the model to the
view:

{% include_code lazy/list-store-add-idle.c lang:cpp lines:1-10 %}

we also set up an opaque container for some data to be used in the idle callbacks:

{% include_code lazy/list-store-add-idle.c lang:cpp lines:11-32 %}

Then, we set up the idle functions; we use the `g_idle_add_full()` function
because we will reach the `STATE_FINISHED` state in a clean up function,
and assign the model to the view there:

{% include_code lazy/list-store-add-idle.c lang:cpp lines:33-81 %}

The `load_items_idle()` function will be called each time the main loop is
idle, and will load the content of the items list one item at a time; as
soon as the `load_items_idle()` has finished its run on the entire list, the
`cleanup_load_items()` function will be called.

{% include_code lazy/list-store-add-idle.c lang:cpp lines:83-130 %}

As you can see, this function appends one item at a time, using the
`IdleData` structure to store the data between the runs.

This is it. Now the ListStore will get loaded lazily inside an idle callback
that should not mess up with the responsiveness of your UI, without having to
resort to threads. Another reason why GTK rocks!
