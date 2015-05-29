Title: PyClutter Reborn 
Slug: pyclutter-reborn 
Date: 2015-05-29 12:00
Tags: development, python, clutter
Summary: The Python bindings for Clutter have finally seen an update in the brave new world of introspection
Abstract: These days, writing C code to bind a GObject-based library usually implies that something went horribly wrong somewhere. At most, you may end up writing some Python code that makes the C API less terrible to use from Python, but hopefully that's the exception, not the rule.

Back when I started hacking on Clutter, the Python bindings were the first
thing that I was tasked to write. In order to make them happen, I had to
understand the intent of the library, and fix up the API to be
binding-friendly. It was another time — a time before introspection made
possible to have run-time bindings that automatically acquired support for
new API once the underlying shared library changed. I had to learn the
CPython API; the code generation utilities that turned C header files into
defs files, and defs files into C code; I also had to fix those utilities,
whenever they lied about what they did, or whenever they were pretty much ad
hoc code supporting GTK+ quirks; and, finally, I had to understand the build
system used by PyGTK that ate all this stuff on one end, blended it all, and
spat out a Python C module on the other.

For a long while, the [Python bindings for Clutter][pyclutter] have been
based on that particular brand on insanity; people were able to switch to
the introspection-based ones and drop PyClutter entirely, but the API was
not as nice to use, and you'd be missing out on some niceties provided by
both Python and Clutter.

In 2011, Bastian Winkler started porting the whole infrastructure to the
overrides mechanism provided by PyGObject; instead of just loading the
Clutter introspection data, you'd load a pure Python module that wrapped
specific bits of the exposed API, and made it nicer to use.

For various reasons — mostly lack of time on my side and lack of testing —
that work has been bitrotting in a branch of the Git repository. Well, no
more. The `master` branch of the PyClutter repository is now providing
introspection overrides similar to the ones for GTK+. I also added a bunch
of examples, ported from their C equivalent, to show the idiomatic use of
Clutter in a Python context.

I'll probably do a release, but I'd be happy if somebody wanted to pick up
the bindings and run with them — I'm not much of a Python programmer myself.

[pyclutter]: https://git.gnome.org/browse/pyclutter
