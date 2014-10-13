Title: quiet strain
Slug: quiet-strain
Status: draft
Tags: gtk, opengl, development, im in ur platform, fixing 10 yrs old bugs
Summary: GTK is getting OpenGL support out of the box
Abstract: the first step in getting to a modern tool kit with a decent handling of the graphic pipeline is to actually have a decent handling of the graphic pipeline; it turns out that Cairo does some of that for us, but since everyone has decided that the only API to be exposed by GPU drivers is OpenGL (and its variants) we probably need to do something about it.

as promised during [GUADEC](https://www.guadec.org), I'm going to blog a bit
more about the development of GSK — and now that I have some code, it's
actually easier to do.

so, let's start from the top, and speak about GDK.

in April 2008 I was in Berlin, enjoying the city, the company, and good
food, and incidentally attending the first GTK+ hackfest. those were the
days of [Project Ridley][wiki-ridley], and when the plan for GTK+ 3.0 was
to release without deprecated symbols and with all the instance structures
sealed.

in the long discussions about the issue of a "blessed" canvas library to be
used by GTK app developers and by the GNOME project, we ended up discussing
the support of the OpenGL API in GDK and GTK+. the [original bug][bug-opegl]
had been opened by Owen about 5 years prior, and while we had ancillary
libraries like GtkGLExt and GtkGLArea, the integration was a pretty sore
point. the consensus at the end of the hackfest was to provide wrappers
around the platform-specific bits of OpenGL inside GDK, enough to create a
GL context and bind it to a specific GdkWindow, to let people draw with
OpenGL commands at the right time in the drawing cycle of GTK+ widgets. the
consensus was also that I would look at the bug, as a person that at the
time was dealing with OpenGL inside tool kits for his day job.

well, that didn't really work out, because cue to 6 years after that
hackfest, the bug is still open.

to be fair, the landscape of GTK and GDK has changed a lot since those days.
we actually released GTK+ 3.0, and with a lot more features than just
deprecations removal; the whole frame cycle is much better, and the paint
sequence is reliable and completely different than before. yet, we still
have to rely on poorly integrated external libraries to deal with OpenGL.

right after GUADEC, I started hacking on getting the minimal amount of API
necessary to create a GL context, and being able to use it to draw on a GTK
widget. it turns out that it wasn't that big of a job to get something on
the screen in a semi-reliable way — after all, we already had libraries like
[GtkGLExt][gtk-glext] and [GtkGLArea][gtk-glarea] living outside of the GTK
git repository that did that, even if they had to use deprecated or broken
API. the complex part of this work involved being able to draw GL inside the
same infrastructure that we currently use for Cairo. we need to be able to
synchronise the frame drawing, and we need to be able to blend the contents
of the GL area with both content that was drawn before and after, likely
with Cairo — otherwise we would not be able to do things like drawing an
overlay notification on top of the usual spinning gears, while keeping the
background color of the window:

{% figure {filename}/images/gdk-gl-gears.png welcome to the world of tomorrow (for values of tomorrow close to 2005) %}

luckily, thanks to [Alex][alexl-blog], the amount of changes in the internals
of GDK was kept to a minimum, and we can enjoy GL rendering running natively
on X11 *and* Wayland, using GLX or EGL respectively.

on top of the low level API, we have a `GtkGLArea` widget that renders all
the GL commands you submit to it, and it behaves like any other GTK+ widgets.

today, [Matthias][mclasen-blog] merged the topic branch into `master`, which
means that, barring disastrous regressions, GTK+ 3.16 will finally have
native OpenGL support — and we'll be one step closer to GSK as well.

right now, there's still some work to do — namely: examples, performance,
documentation, porting to MacOS and Windows — but the API is already fairly
solid, so we'd all like to get feedback from the users of libraries like
GtkGLExt and GtkGLArea, to see what they need or what we missed. feedback
is, as usual, best directed at the `gtk-devel` mailing list, or on the
`#gtk+` IRC channel.

[wiki-ridley]: https://wiki.gnome.org/Attic/ProjectRidley
[bug-opengl]: https://bugzilla.gnome.org/show_bug.cgi?id=119189
[gtk-glext]: https://projects.gnome.org/gtkglext/
[gtk-glarea]: http://www.mono-project.com/archived/gtkglarea/
[alexl-blog]: http://blogs.gnome.org/alexl/
[mclasen-blog]: http://blogs.gnome.org/mclasen/
