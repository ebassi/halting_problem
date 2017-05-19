Title: Further experiments in Meson
Date: 2017-05-19 18:20 +0100
Tags: development, build systems, meson, pango, gnome
Summary: in which more components gets ported to Meson

[Meson][meson-web] is definitely getting more traction in GNOME (and other
projects), with many components adding support for it in parallel to
autotools, or outright switching to it. There are still bugs, here and
there, and we definitely need to improve build environments — like
Continuous — to support Meson out of the box, but all in all I'm really
happy about not having to deal with autotools any more, as well as being
able to build the G\* stack much more quickly when doing continuous
integration.

Now that GTK+ has added Meson support, though, it's time to go through the
dependency chain in order to clean up and speed up the build in the lower
bits of our stack. After an aborted attempt at porting GdkPixbuf, I decided
to [port Pango](https://git.gnome.org/browse/pango/log/?h=wip/meson).

All in all, Pango proved to be an easy win; it took me about one day to port
from Autotools to Meson, and most of it was mechanical translation from
weird autoconf/automake incantations that should have been removed years
ago[^1]. Most of the remaining bits were:

 - ensuring that both Autotools and Meson would build the same
   DSOs, with the same symbols
 - generating the same introspection data and documentation
 - installing tests and data in the appropriate locations

Thanks to the ever vigilant eye of [Nirbheek Chauhan][nirbheek-blog], and
thanks to the new [Meson reference][meson-reference], I was also able to
make the Meson build slightly more idiomatic than a straight, 1:1 port would
have done.

The results are a full Meson build that takes about the same time as
`./autogen.sh` to run:

```
* autogen.sh:                         * meson
  real        0m11.149s                 real          0m2.525s
  user        0m8.153s                  user          0m1.609s
  sys         0m2.363s                  sys           0m1.206s

* make -j$(($(nproc) + 2))            * ninja
  real        0m9.186s                  real          0m3.387s
  user        0m16.295s                 user          0m6.887s
  sys         0m5.337s                  sys           0m1.318s

--------------------------------------------------------------

* autotools                           * meson + ninja
  real        0m27.669s                 real          0m5.772s
  user        0m45.622s                 user          0m8.465s
  sys         0m10.698s                 sys           0m2.357s
```

Not bad for a day's worth of work.

My plan would be to merge this in the `master` branch pretty soon; I also
have a branch that [drops Autotools entirely](https://git.gnome.org/browse/pango/log/?h=wip/meson-only)
but that can wait a cycle, as far as I'm concerned.

Now comes the hard part: porting libraries like GdkPixbuf, ATK,
gobject-introspection, and GLib to Meson. There's already a GLib port,
courtesy of [Centricular][centricular-web], but it needs further testing;
GdkPixbuf is pretty terrible, since it's a *really* old library; I don't
expect ATK and GObject introspection to be complicated, but the latter has a
non-recursive Make layout that is full of bees.

It would be nice to get to [GUADEC](https://2017.guadec.org) and have the
whole G\* stack build with Meson and Ninja. If you want to help out, reach
out in `#gtk+`, on IRC or on Matrix.

[^1]: The Windows support still checks for GCC 2.x or 3.x flags, for
  instance.

[meson-web]: http://mesonbuild.com
[meson-reference]: http://mesonbuild.com/Reference-manual.html
[nirbheek-blog]: http://blog.nirbheek.in/
[centricular-web]: http://www.centricular.com/
