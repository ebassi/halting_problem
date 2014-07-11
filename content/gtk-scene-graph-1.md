title: The Next GTK+ Scene Graph / 1
slug: gtk-scene-graph-1
status: draft

last year I had the privilege of [talking at GUADEC][guadec-2013-talk]
about designing and implementing the API for the next GTK+ scene graph;
it was mostly about the former, and a lot less about the latter.

> designing, and especially iterating over a design, is actually the
> most important part when writing a new API, or a new component

nevertheless, at the end of the day you need to implement what you have
been designing, because code won't magically appear out of thin air
directly in the source code repository.

luckily for me, but unluckily for GTK+, I have been pretty busy with my
[day job](https://endlessm.com), which means that I haven't been able to
work as much as I would have liked on what I began to outline last year
in Brno.

last year I identified a series of milestones needed to get from the
current situation to a point where I could submit my code for review
and integration:

 * integrating OpenGL with GDK
 * providing base types for shapes and transformations
 * writing the scene graph API
 * drawing the scene every time it changes
 * building an example application with the new scene graph API

most of the third step is basically taking the current `ClutterActor`
API, passing `sed` over it, and turning it into a `GskLayer`. it's
clearly a bit more complicated than that, especially when it comes
to sizing and drawing, but we'll get there.

- - -

I started hacking on the first milestone last year, even though it's
been on my to do list for probably the last 5. like everyone before me,
I started prototyping wrappers for GLX (given that X11 is what I still
use on my machine), and immediately regretted it. you can try to put
lipstick on both the GL and the GLX pigs, but it's still pretty dire
to deal with:

 1. the platform specific portion of the API to create GL context
    and drawables
 2. the platform agnostic portion of the API that deals with
    discovering extensions

on X11 *alone* — then you have to wrap the same API on Wayland, Quartz,
and Windows, all with their own matrix of supported features and
extensions.

back in the OpenedHand days, we had a small utility library that did
most of this for us; it papered over the platform-specific bits, and
abstracted the extensions needed by Clutter. we used to have it in
tree in the Clutter repository, and it was called *Cogl*. these days,
Cogl is a fairly complex API on top of OpenGL, that provides you with
the abstraction necessary to write GPU-intensive code without going
completely mad with the GL API. it's somewhat similar to what Apple
calls [Metal][apple-metal], and it's going to be available in iOS 8.

> it is immediately clear, by looking at the requirements for using
> OpenGL inside a GTK+ application, that using Cogl just for creating
> a GL context on the handful of platforms we support is not a good
> use of Cogl's API.

luckily for me, about 9 months ago Eric Anholt published a little
utility library called [libepoxy][epoxy-github] which provides
*exactly* what we need: a thin layer of glue code that deals with
the whole `dlopen()`, `dlsym()`, function pointer madness, as well
as giving you the correct headers and symbols for your platforms. then
you get to use GL, which may or may not be what you want, but at least
you don't get to care about the initial hassle of putting together a
dispatch table and stripping prefixes and suffixes from functions.

after finding libepoxy, I just chucked away the code I had written
for GLX only, and wrapped the platform specific bits of GL using types
inside GDK:

 * `GdkGLPixelFormat`: a type that lets you specify a set of features
   you want to ask when creating a GL context
 * `GdkGLContext`: a type that wraps the platform-specific GL context
   and can be tied to a `GdkWindow`

and that's the extent of the GL API inside GDK. we prepare an off screen
buffer for you to draw on, and then, depending on whether the target
`GdkWindow` is backed by a native windowing system surface or not, we
put the contents on the screen for you in the best or fastest way possible.

- - -

if you read [Planet GNOME](https://planet.gnome.org) in May this year
you will probably have noticed that I [announced][ebassi-graphene] that
I was working on a small utility library for common graphic library
types.

[guadec-2013-talk]: http://videos.guadec.org/2013/Future%20in%20the%20past%20GTK%20scene-graph/
[apple-metal]: https://developer.apple.com/library/prerelease/ios/documentation/Miscellaneous/Conceptual/MTLProgGuide/Introduction/Introduction.html
[epoxy-github]: https://github.com/anholt/libepoxy
[ebassi-graphene]: http://blogs.gnome.org/ebassi/2014/05/02/graphene/
