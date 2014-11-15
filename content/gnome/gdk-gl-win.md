Title: with a little help
Slug: with-a-little-help
Date: 2014-11-15 16:30
Tags: gtk, opengl, development, windows, quartz
Summary: if you use GTK+ on Windows or MacOS X, and you want to use GL, please help the GTK+ team out

this is a request for help.

GTK+ 3.16 will have [OpenGL][opengl-web] support [out of the box][gdk-gl].

at least, it will have it on X11 and Wayland.

if you are using (or you plan to use) GTK+ 3.x on Windows or MacOS X, and
you know how to use OpenGL on those two platforms, please consider helping
out the GTK+ developers by implementing the [`GdkGLContext`][gdkgl-api] API
using WGL and AppleGL.

we'd really like to get all backends working out of the box when we release
GTK+ 3.16.0, next year.

testing and feedback is also very much appreciated.

in the meantime, I'm doing some much needed spring cleaning in the
[GtkGLExt][bz-gtkglext] and [GtkGLArea][bz-gtkglarea] products on Bugzilla.

[opengl-web]: https://www.opengl.org/
[gdk-gl]: http://www.bassi.io/articles/2014/10/13/quiet-strain/
[gdkgl-api]: https://developer.gnome.org/gdk3/unstable/GdkGLContext.html
[bz-gtkglext]: https://bugzilla.gnome.org/browse.cgi?product=gtkglext
[bz-gtkglarea]: https://bugzilla.gnome.org/browse.cgi?product=gtkglarea
