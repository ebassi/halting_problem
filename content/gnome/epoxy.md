Title: Epoxy
Date: 2017-02-11 01:34 +0000
Tags: build systems, meson, libepoxy, development
Summary: In which I recount the process of moving libepoxy to Meson and becoming its maintainer
Abstract: One of the things I ended up doing in GNOME is babysitting the Continuous build and delivery system; this usually ends up in me getting notified of build breakages across the whole GNOME stack. This is how I found out that libepoxy, one of the dependencies of GTK+, broke its autotools build in a tragic attempt at a CMake port. Since I didn't want to switch to CMake, but I also didn't want to deal with autotools in 2017, I decided to experiment with a Meson build port, after using Meson in many of my personal projects.

[Epoxy](https://github.com/anholt/libepoxy) is a small library that GTK+,
and other projects, use in order to access the OpenGL API in somewhat sane
fashion, hiding all the awful bits of craziness that actually need to happen
because apparently somebody dosed the water supply at SGI with large
quantities of LSD in the mid-'90s, or something.

As an added advantage, Epoxy is also portable on different platforms, which
is a plus for GTK+.

Since I've started using [Meson](http://mesonbuild.com) for my personal (and
some [work-related](https://github.com/ebassi/emeus)) projects as well, I've
been on the lookout for adding Meson build rules to other free and open
source software projects, in order to improve both their build time and
portability, and to improve Meson itself.

As a small, portable project, Epoxy sounded like a good candidate for the
port of its build system from autotools to [Meson](http://mesonbuild.com).

To the Bat Build Machine!

### tl;dr

Since you may be interested just in [the numbers](https://github.com/ebassi/libepoxy/wiki/Moving-Epoxy-to-Meson),
building Epoxy with Meson on my Kaby Lake four Core i7 and NMVe SSD takes about
45% less time than building it with autotools.

A fairly good fraction of the autotools time is spent going through the
autogen and configure phases, because they both aren't parallelised, and
create a ton of shell invocations.

Conversely, Meson's configuration phase is incredibly fast; the **whole**
Meson build of Epoxy fits in the same time the autogen.sh and configure
scripts complete their run.

### Administrivia

Epoxy is a simple library, which means it does not need a hugely complicated
build system set up; it does have some interesting deviations, though, which
made the porting an interesting challenge.

For instance, on Linux and similar operating systems Epoxy uses `pkg-config`
to find things like the EGL availability and the X11 headers and libraries;
on Windows, though, it relies on finding the `opengl32` shared or static
library object itself. This means that we get something straightforward in
the former case, like:

```python
# Optional dependencies
gl_dep = dependency('gl', required: false)
egl_dep = dependency('egl', required: false)
```

and something slightly less straightforward in the latter case:

```python
if host_system == 'windows'
  # Required dependencies on Windows
  opengl32_dep = cc.find_library('opengl32', required: true)
  gdi32_dep = cc.find_library('gdi32', required: true)
endif
```

And, still, this is miles better than what you have to deal with when using
autotools.

Let's take a messy thing in autotools, like checking whether or not the
compiler supports a set of arguments; usually, this involves some m4 macro
that's either part of [autoconf-archive](https://www.gnu.org/software/autoconf-archive/)
or some additional repository, like the [xorg macros](https://cgit.freedesktop.org/xorg/util/macros).
Meson handles this in a much better way, out of the box:

```python
# Use different flags depending on the compiler
if cc.get_id() == 'msvc'
  test_cflags = [
    '-W3',
    ...,
  ]
elif cc.get_id() == 'gcc'
  test_cflags = [
    '-Wpointer-arith',
    ...,
  ]
else
  test_cflags = [ ]
endif

common_cflags = []
foreach cflag: test_cflags
  if cc.has_argument(cflag)
    common_cflags += [ cflag ]
  endif
endforeach
```

In terms of speed, the configuration step could be made even faster by
parallelising the compiler argument checks; right now, Meson has to do them
all in a series, but nothing except some additional parsing effort would
prevent Meson from running the whole set of checks in parallel, and gather
the results at the end.

### Generating code

In order to use the GL entry points without linking against `libGL` or
`libGLES*` Epoxy takes the XML description of the API from the Khronos
repository and generates the code that ends up being compiled by using a
Python script to parse the XML and generating header and source files.

Additionally, and unlike most libraries in the G\* stack, Epoxy stores its
public headers inside a separate directory from its sources:

```
libepoxy
├── cross
├── doc
├── include
│   └── epoxy
├── registry
├── src
└── test
```

The autotools build has the `src/gen_dispatch.py` script create both the
source and the header file for each XML at the same time using a rule
processed when recursing inside the `src` directory, and proceeds to put the
generated header under `$(top_builddir)/include/epoxy`, and the generated
source under `$(top_builddir)/src`. Each code generation rule in the
`Makefile` manually creates the `include/epoxy` directory under the build
root to make up for parallel dispatch of each rule.

Meson makes is harder to do this kind of spooky-action-at-a-distance build,
so we need to generate the headers in one pass, and the source in another.
This is a bit of a let down, to be honest, and yet a build that invokes the
generator script twice for each API description file is still faster under
Ninja than a build with the single invocation under Make.

There are sill issues in this step that are being addressed by the Meson
developers; for instance, right now we have to use a custom target for each
generated header and source separately instead of declaring a generator and
calling it multiple times. Hopefully, this will be fixed fairly soon.

### Documentation

Epoxy has a **very** small footprint, in terms of API, but it still benefits
from having some documentation on its use. I decided to generate the API
reference using [Doxygen](http://www.stack.nl/~dimitri/doxygen/), as it's
not a G\* library and does not need the additional features of gtk-doc.
Sadly, Doxygen's default style is absolutely terrible; it would be great if
somebody could fix it to make it look half as good as the look gtk-doc gets
out of the box.

### Cross-compilation and native builds

Now we get into "interesting" territory.

Epoxy is portable; it works on Linux and \*BSD systems; on macOS; and on
Windows. Epoxy also works on both Intel Architecture and on ARM.

Making it run on Unix-like systems is not at all complicated. When it comes
to Windows, though, things get weird fast.

Meson uses [cross files](https://github.com/mesonbuild/meson/wiki/Cross%20compilation)
to determine the environment and toolchain of the *host machine*, i.e. the
machine where the result of the build will eventually run. These are simple
text files with key/value pairs that you can either keep in a separate
repository, in case you want to share among projects; or you can keep them
in your own project's repository, especially if you want to easily set up
continuous integration of cross-compilation builds.

Each toolchain has its own; for instance, this is the description of a cross
compilation done on Fedora with MingW:

```
[binaries]
c = '/usr/bin/x86_64-w64-mingw32-gcc'
cpp = '/usr/bin/x86_64-w64-mingw32-cpp'
ar = '/usr/bin/x86_64-w64-mingw32-ar'
strip = '/usr/bin/x86_64-w64-mingw32-strip'
pkgconfig = '/usr/bin/x86_64-w64-mingw32-pkg-config'
exe_wrapper = 'wine'
```

This section tells Meson where the binaries of the MingW toolchain are; the
`exe_wrapper` key is useful to run the tests under Wine, in this case.

The cross file also has an additional section for things like special
compiler and linker flags:

```
[properties]
root = '/usr/x86_64-w64-mingw32/sys-root/mingw'
c_args = [ '-pipe', '-Wp,-D_FORTIFY_SOURCE=2', '-fexceptions', '--param=ssp-buffer-size=4', '-I/usr/x86_64-w64-mingw32/sys-root/mingw/include' ]
c_link_args = [ '-L/usr/x86_64-w64-mingw32/sys-root/mingw/lib' ]
```

These values are taken from the equivalent bits that Fedora provides in
their MingW RPMs.

Luckily, the tool that generates the headers and source files is written in
Python, so we don't need an additional layer of complexity, with a tool
built and run on a different platform and architecture in order to generate
files to be built and run on a different platform.

### Continuous Integration

Of course, any decent process of porting, these days, should deal with
continuous integration. CI gives us confidence as to whether or not any
change whatsoever we make actually works — and not just on our own computer,
and our own environment.

Since Epoxy is hosted on GitHub, the quickest way to deal with continuous
integration is to use [TravisCI](https://travis-ci.org), for Linux and
macOS; and [Appveyor](https://www.appveyor.com/) for Windows.

The requirements for Meson are just Python3 and Ninja; Epoxy also requires
Python 2.7, for the dispatch generation script, and the shared libraries for
GL and the native API needed to create a GL context (GLX, EGL, or WGL); it
also optionally needs the X11 libraries and headers and Xvfb for running the
test suite.

Since Travis offers an older version of Ubuntu LTS as its base system, we
cannot build Epoxy with Meson; additionally, running the test suite is a
crapshoot because the Mesa version if hopelessly out of date and will either
cause most of the tests to be skipped or, worse, make them segfault. To
sidestep this particular issue, I've prepared a [Docker image](https://github.com/ebassi/epoxyci)
with its own harness, and I use it as the containerised environment for
Travis.

On Appveyor, thanks to the contribution of [Thomas Marrinan](https://github.com/tmarrinan)
we just need to download Python3, Python2, and Ninja, and build everything
inside its own root; as an added bonus, Appveyor allows us to take the build
artefacts when building from a tag, and shoving them into a zip file that
gets deployed to the release page on GitHub.

### Conclusion

Most of this work has been done off and on over a couple of months; the
rough Meson build conversion was done last December, with the
cross-compilation and native builds taking up the last bit of work.

Since [Eric](http://anholt.livejournal.com/) does not have any more spare
time to devote to Epoxy, he was kind enough to give me access to the
original repository, and I've tried to reduce the amount of open pull
requests and issues there.

I've also [released version 1.4.0](https://github.com/anholt/libepoxy/releases/tag/v1.4)
and I plan to do a 1.4.1 release soon-ish, now that I'm positive Epoxy works
on Windows.

I'd like to thank:

 * Eric Anholt, for writing Epoxy and helping out when I needed a hand
   with it
 * [Jussi Pakkanen](http://nibblestew.blogspot.co.uk/) and
   [Nirbheek Chauhan](http://blog.nirbheek.in/search/label/gnome), for writing
   Meson and for helping me out with my dumb questions on `#mesonbuild`
 * Thomas Marrinan, for working on the Appveyor integration and testing
   Epoxy builds on Windows
 * Yaron Cohen-Tal, for maintaining Epoxy in the interim
