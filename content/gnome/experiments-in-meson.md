Title: Experiments in Meson
Date: 2016-06-09
Tags: development, build systems, meson
Summary: in which I talk about using the Meson build system on a project
Abstract: Just because I happen to know a bit about autotools does not imply I like them; it's just that, over the years, I haven't found anything that can replace them appropriately for all the things I usually do when it comes to building software. I still try to find a replacement, though, because the alternative is a sad future, filled with regret.

Last [GUADEC][guadec-2015] I attended Jussi Pakkanen's talk about his build
system, [Meson][meson-web]; if you weren't there, I strongly recommend you
[watch the recording][meson-guadec-talk]. I left the talk impressed, and I
wanted to give Meson a try. Cue 9 months later, and a really nice blog post
from [Nirbheek][nirbheek-meson-blog] on how Centricular is porting GStreamer
from autotools to Meson, and I decided to spend some evening/weekend time on
learning Meson.

I decided to use the simplest project I maintain, the one with the minimal
amount of dependencies and with a fairly clean autotools set up — i.e.
[Graphene][graphene-web].

Graphene has very little overhead in terms of build system by itself; all it
needs are:

 * a way to check for compiler flags
 * a way to check for the existence of headers and types
 * a way to check for platform-specific extensions, like SSE or NEON

Additionally, it needs a way to generate documentation and introspection
data, but those are mostly hidden in weird incantations provided by other
projects, like gtk-doc and gobject-introspection, so most of the complexity
is hidden from the maintainer (and user) point of view.

Armed with little more than the [Meson documentation wiki][meson-wiki]
and the [GStreamer port][gstreamer-centricular-meson] as an example, I set
off towards the shining new future of a small, sane, fast build system.

## The Good

Meson uses additional files, so I didn't have to drop the autotools set up
while working on the Meson one. Once I'm sure that the results are the same,
I'll be able to remove the various `configure.ac`, `Makefile.am`, and
friends, and leave just the Meson file.

---

Graphene generates two header files during its configuration process:

 * a `config.h` header file, for internal use; we use this file to check if
   a specific feature or header is available while building Graphene itself
 * a `graphene-config.h` header file, for public use; we expose this file to
   Graphene users for build time detection of platform features

While the autotools code that generates `config.h` is pretty much hidden
from the developer perspective, with autoconf creating a template file for
you by pre-parsing the build files, the part of the build system that
generates the `graphene-config.h` one is pretty much a mess of shell script,
cacheable variables for cross-compilation, and random m4 escaping rules.
Meson, on the other hand, treats both files exactly the same way: generate a
`configuration` object, set variables on it, then take the appropriate
configuration object and generate the header file — with or without a
template file as an input:

    # Internal configuration header
    configure_file(input: 'config.h.meson',
                   output: 'config.h',
                   configuration: conf)

    # External configuration header
    configure_file(input: 'graphene-config.h.meson',
                   output: 'graphene-config.h',
                   configuration: graphene_conf,
                   install: true,
                   install_dir: 'lib/graphene-1.0/include')

---

While explicit is better than implicit, at least most of the time, having
things taken care for you avoids the boring bits and, more importantly,
avoids getting the boring bits *wrong*. If I had a quid for every broken
invocation of the introspection scanner I've ever seen or had to fix, I'd
probably retire on a very small island. In Meson, this is taken care by a
function in the `gnome` module:

<pre>
    import('gnome')

    # Build introspection only if we enabled building GObject types
    build_gir = build_gobject
    if build_gobject and get_option('enable-introspection')
      gir = find_program('g-ir-scanner', required: false)
      build_gir = gir.found() and not meson.is_cross_build()
    endif

    if build_gir
      gir_extra_args = [
        '--identifier-filter-cmd=' + meson.source_root() + '/src/identfilter.py',
        '--c-include=graphene-gobject.h',
        '--accept-unprefixed',
        '-DGRAPHENE_COMPILATION',
        '--cflags-begin',
        '-I' + meson.source_root() + '/src',
        '-I' + meson.build_root() + '/src',
        '--cflags-end'
      ]
      gnome.generate_gir(libgraphene,
                         sources: headers + sources,
                         namespace: 'Graphene',
                         nsversion: graphene_api_version,
                         identifier_prefix: 'Graphene',
                         symbol_prefix: 'graphene',
                         export_packages: 'graphene-gobject-1.0,
                         includes: [ 'GObject-2.0' ],
                         install: true,
                         extra_args: gir_extra_args)
    endif
</pre>

---

Meson generates [Ninja][ninja-web] rules by default, and it's really fast at
that. I can get a fully configured Graphene build set up in less that a
couple of seconds. On top of that, Ninja is **incredibly** fast. The whole
build of Graphene takes less than 5 seconds — and I'm counting building the
tests and benchmarks, something that I had to move to be on demand for the
autotools set up because they added a noticeable delay to the build. Now I
always know if I've just screwed up the build, and not just when I run `make
check`.

---

Jussi is a very good maintainer, helpful and attentive at issues reported to
his project, and quick at reviewing patches. The terms for contributing to
Meson are fairly standard, and the barrier for entry is very low. For a
project like a build system, which interacts and enables other projects,
this is a very important thing.

### The Ugly

As I said, Meson has some interesting automagic handling of the boring bits
of building software, like the introspection data. But there are other
boring bits that do not have convenience wrappers, and thus you get into
overly verbose section of your `meson.build` — and while it's definitely
harder to get those wrong, compared to autoconf or automake, it can still
happen.

Even in the case of automagic handling, though, there are cases when you
have to deal with some of the magic escaping from under the rug. Generally
it's not hard to understand what's missing or what's necessary, but it can
be a bit daunting when you're just staring at a Python exception barfed on
your terminal.

---

The documentation is kept in a wiki, which is generally fine for keeping it
up to date; but it's hard to search — as all wikis are — and hard to
visually scan. I've lost count of the times I had to search for all the
methods on the `meson` built-in object, and I never remember which page I
have to search for, or in.

The inheritance chain for some objects is mentioned in passing, but it's
hard to track; which methods does the `test` object have? What kind of
arguments does the `compiler.compiles()` method have? Are they positional or
named?

The syntax and API reference documentation should probably be generated from
the code base, and look more like an API reference than a wiki.

---

Examples are hard to come by. I looked at the GStreamer port, but I also had
to start looking at Meson's own test suite.

---

Modules are all in tree, at least for the time being. This means that if I
want to add an *ad hoc* module for a whole complex project like, say, GNOME,
I'd have to submit it to upstream. Yeah, I know: bad example, Meson already
has a GNOME module; but the concept still applies.

---

Meson does not do dist tarballs. I've already heard people being skeptical
about this point, but I personally don't care that much. I can generate a
tarball from a Git tag, and while it won't be self-hosting, it's already
enough to get a distro going. Seriously, though: building from a Git tag is
a better option than building from a tarball, in 2016.

### The Bad

There shocking twist is that nothing stands out as "bad". Mostly, it's just
ugly stuff — caused either by missing convenience functionality that will by
necessity appear once people start using Meson more; or by the mere fact
that all build systems are inherently ugly.

On the other hand, there's some badness in the tooling around project
building. For instance, Travis-CI does not support it, mostly because they
use an ancient version of Ubuntu LTS as the base environment. Jhbuild does
not have a Meson/Ninja build module, so we'll have to write that one; same
thing for GNOME Builder. While we wait, having a dummy `configure` script
or a dummy `Makefile` that would probably help.

These are not bad things per se, but they definitely block further adoption.

### tl;dr

I think Meson has great potential, and I'd love to start using it more for
my projects. If you're looking for a better, faster, and more understandable
build system then you should grab Meson and explore it.

[guadec-2015]: https://2015.guadec.org/
[meson-web]: http://mesonbuild.com/
[meson-guadec-talk]: https://www.youtube.com/watch?v=wTf0NjjNwTU&index=14&list=PLcb5uDX8FIoDeC6z7SeW0-KW3cHUKwIHU
[nirbheek-meson-blog]: http://blog.nirbheek.in/2016/05/gstreamer-and-meson-new-hope.html
[graphene-web]: http://ebassi.github.io/graphene/
[ninja-web]: https://ninja-build.org/
[meson-wiki]: https://github.com/mesonbuild/meson/wiki
[gstreamer-centricular-meson]: https://github.com/centricular/gstreamer/tree/meson
