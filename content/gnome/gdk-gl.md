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

given that I plan to use OpenGL to do compositing of layers in GSK, the
first thing I had to do to get stuff on the screen properly was to sit down
and solve the OpenGL integration.

[wiki-ridley]: https://wiki.gnome.org/Attic/ProjectRidley
[bug-opengl]: https://bugzilla.gnome.org/show_bug.cgi?id=119189
