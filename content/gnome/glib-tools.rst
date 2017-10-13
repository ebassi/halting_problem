GLib tools rewrite
##################

:date: 2017-10-13 12:39 +0100
:modified: 2017-10-13 16:21 +0100
:tags: gnome, development, glib, autotools
:category: gnome
:slug: glib-tools
:summary: In which I make a public service announcement about the small utilities provided by GLib

You can safely skip this article if you're not building software using
enumeration types and signal handlers; or if you're already using Meson_.

For more that 15 years, GLib has been shipping with two small utilities:

- ``glib-mkenums``, which scans a list of header files and generates ``GEnum``
  and ``GFlags`` types out of them, for use in GObject properties and signals
- ``glib-genmarshal``, which reads a file containing a description of marshaller
  functions, and generates C code for you to use when declaring signals

If you update to GLib 2.54, released in September 2017, you may notice that the
``glib-mkenums`` and ``glib-genmarshal`` tools have become sligly more verbose and
slightly more strict about their input.

During the 2.54 development cycle, both utilities have been rewritten in Python
from a fairly ancient Perl, in the case of ``glib-mkenums``; and from C, in the
case of ``glib-genmarshal``. This port was done to address the proliferation of
build time dependencies on GLib; the cross-compilation hassle of having a small
C utility being built and used during the build; and the move to Meson as the
default (and hopefully only) build system for future versions of GLib. Plus, the
port introduced colorised output, and we all know everything looks better with
colors.

Sadly, none of the behaviours and expected input or output of both tools have
ever been documented, specified, or tested in any way. Additionally, it turns
out that lots of people either figured out how to exploit undefined behaviour,
or simply cargo-culted the use of these tools into their own project. This is
entirely on us, and I'm going to try and provide `better documentation`_ to both
tools in the form of a decent man page, with examples of integration inside
Autotools-based projects.

In the interest of keeping old projects building, both utilities will try to
replicate the undefined behaviours as much as possible, but now you'll get a
warning instead of the silent treatment, and maybe you'll get a chance at
fixing your build.

If you are maintaining a project using those two utilities, these are the
things to watch out for, and ideally to fix by strictly depending on
GLib ≥ 2.54.

glib-genmarshal
---------------

- if you're using ``glib-genmarshal --header --body`` to avoid the "missing
  prototypes" compiler warning when compiling the generated marshallers
  source file, please switch to using ``--prototypes --body``. This will
  ensure you'll get **only** the prototypes in the source file, instead of
  a whole copy of the header.
- Similarly, if you're doing something like the stanza below in order to
  include the header inside the body::

    foo-marshal.h: foo-marshal.list Makefile
            $(AM_V_GEN) \
              $(GLIB_GENMARSHAL) --header foo-marshal.list \
            > foo-marshal.h
    foo-marshal.c: foo-marshal.h
            $(AM_V_GEN) (
              echo '#include "foo-marshal.h"' ; \
              $(GLIB_GENMARSHAL) --body foo-marshal.list \
            ) > foo-marshal.c

  you can use the newly added ``--include-header`` command line argument,
  instead.
- The stanza above has also been used to inject ``#define`` and ``#undef``
  pre-processor directives; these can be replaced with the ``-D`` and
  ``-U`` newly added command line arguments, which work just like the
  GCC ones.
- This is not something that came from the Python port, as it's been
  true since the inclusion of ``glib-genmarshal`` in GLib, **17 years ago**:
  the ``NONE`` and ``BOOL`` tokens are deprecated, and should *not* be
  used; use ``VOID`` and ``BOOLEAN``, respectively. The new version of
  ``glib-genmarshal`` will now properly warn about this, instead of just
  silently converting them, and never letting you know you should fix
  your marshal.list file.

If you want to silence all messages outside of errors, you can now use the
``--quiet`` command line option; conversely, use ``--verbose`` if you want
to get more messages.

glib-mkenums
------------

The ``glib-mkenums`` port has been much more painful than the marshaller
generator one; mostly, because there are many, many more ways to screw up
code generation when you have command line options and file templates, and
mostly because the original code base relied heavily on Perl behaviour and
side effects. Cargo culting Autotools stanzas is also much more of a thing
when it comes to enumerations than marshallers, apparently. Imagine what
we could achieve if the tools that we use to build our code didn't actively
work against us.

- First of all, try and avoid having mixed encoding inside source code
  files that are getting parsed; mixing Unicode and ISO-8859 encoding is
  not a great plan, and C does not have a way to specify the encoding
  to begin with. Yes, you may be doing that inside comments, so who
  cares? Well, *a tool that parses comments might*.
- If you're mixing template files with command line arguments for some
  poorly thought-out reason, like this::

    foo-enums.h: foo-enums.h.in Makefile
            $(AM_V_GEN) $(GLIB_MKENUMS) \
              --fhead '#ifdef FOO_ENUMS_H' \
              --fhead '#defineFOO_ENUMS_H' \
              --template foo-enums.h.in \
              --ftail '#endif /* FOO_ENUMS_H */' \
            > foo-enums.h

  the old version of ``glib-mkenums`` would basically build templates
  depending on the phase of the moon, as well as some internal detail
  of how Perl works. The new tool has a specified order:

  - the ``HEAD`` stanzas specified on the command line are always prepended
    to the template file
  - the ``PROD`` stanzas specified on the command line are always appended
    to the template file
  - the ``TAIL`` stanzas specified on the command line are always appended
    to the template file

Like with ``glib-genmarshal``, the ``glib-mkenums`` tool also tries to be
more verbose in what it expects.

----

Ideally, by this point, you should have switched to Meson_, and you're now
using a sane build system that generates this stuff for you.

If you're still stuck with Autotools, though, you may also want to consider
dropping ``glib-genmarshal``, and use the FFI-based generic marshaller in
your signal definitions — which comes at a small performance cost, but if
you're putting signal emission inside a performance-critical path you should
just be ashamed of yourself.

For enumerations, you could use something like `this macro`_, which I tend
to employ in all my projects with just few, small enumeration types, and
where involving a whole separate pass at parsing C files is kind of overkill.
Ideally, GLib `would ship its own version`_, so maybe it'll be replaced
in a new version.

----

Many thanks to Jussi Pakkanen, Nirbheek Chauhan, Tim-Philipp Müller, and
Christoph Reiter for the work on porting ``glib-mkenums``, as well as
fixing my awful Parseltongue.

.. _Meson:
   http://mesonbuild.com

.. _this macro:
   https://github.com/endlessm/xapian-glib/blob/master/xapian-glib/xapian-enums.cc#L22

.. _would ship its own version:
   https://bugzilla.gnome.org/show_bug.cgi?id=627241

.. _better documentation:
   https://bugzilla.gnome.org/show_bug.cgi?id=788948
