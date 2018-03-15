Title: pkg-config and paths 
Slug: pkg-config-and-paths
Tags: development
Summary: In which I explain how to use paths and pkg-config variables 
Date: 2018-03-15 16:45 +0000

This is something of a frequently asked question, as it comes up every once
in a while. The [pkg-config][pkgconfig-web] documentation is fairly terse,
and even [pkgconf][pkgconf-web] hasn't improved on that.

### The problem

Let's assume you maintain a project that has a dependency using pkg-config.

Let's also assume that the project you are depending on loads some files
from a system path, and your project plans to install some files under that
path.

The questions are:

 - how can the project you are depending on provide an appropriate way for
   you to discover where that path is
 - how can the project you maintain use that information

The answer to both questions is: *by using variables in the pkg-config file*.
Sadly, there's still some confusion as to how those variables work, so this
is my attempt at clarifying the issue.

### Defining variables in pkg-config files

The typical preamble stanza of a pkg-config file is something like this:

```
prefix=/some/prefix
libdir=${prefix}/lib
datadir=${prefix}/share
includedir=${prefix}/include
```

Each variable can reference other variables; for instance, in the example
above, all the other directories are relative to the `prefix` variable.

Those variables that can be extracted via pkg-config itself:

```sh
$ pkg-config --variable=includedir project-a
/some/prefix/include
```

As you can see, the `--variable` command line argument will automatically
expand the `${prefix}` token with the content of the `prefix` variable.

Of course, you can define any and all variables inside your own pkg-config
file; for instance, this is the definition of the `giomoduledir` variable
inside the `gio-2.0` pkg-config file:

```
prefix=/usr
libdir=${prefix}/lib

…

giomoduledir=${libdir}/gio/modules
```

This way, the `giomoduledir` variable will be expanded to
`/usr/lib/gio/modules` when asking for it.

> If you are defining a path inside your project's pkg-config file,
> **always** make sure you're using a relative path!

We're going to see why this is important in the next section.

### Using variables from pkg-config files

Now, this is where things get complicated.

As I said above, pkg-config will expand the variables using the definitions
coming from the pkg-config file; so, in the example above, getting the
`giomoduledir` will use the prefix provided by the `gio-2.0` pkg-config
file, which is the prefix into which GIO was installed. This is all well and
good if you just want to know where GIO installed its own modules, in the
same way you want to know where its headers are installed, or where the
library is located.

What happens, though, if your own project needs to install GIO modules in a
shared location? More importantly, what happens if you're building your
project in a separate prefix?

If you're thinking: "I should install it into the same location as specified
by the GIO pkg-config file", think again. What happens if you are building
against the system's GIO library? The prefix into which it has been
installed is only going to be accessible by the administrator user; or it
could be on a read-only volume, managed by libostree, so `sudo` won't save
you.

Since you're using a separate prefix, you really want to install the files
provided by your project under the prefix used to configure your project.
That does require knowing all the possible paths used by your dependencies,
hard coding them into your own project, and ensuring that they never change.

This is clearly not great, and it places additional burdens on your role as
a maintainer.

The correct solution is to tell pkg-config to expand variables using your
own values:

```sh
$ pkg-config \
> --define-variable=prefix=/your/prefix \
> --variable=giomoduledir
> gio-2.0
/your/prefix/lib/gio/modules
```

This lets you rely on the paths as defined by your dependencies, and does
not attempt to install files in locations you don't have access to.

### Build systems

How does this work, in practice, when building your own software?

If you're using [Meson][meson-web], you can use the
`get_pkgconfig_variable()` method of the `dependency` object, making sure to
replace variables:

```
gio_dep = dependency('gio-2.0')
giomoduledir = gio_dep.get_pkgconfig_variable(
  'giomoduledir',
  define_variable: [ 'libdir', get_option('libdir') ],
)
```

This is the equivalent of the `--define-variable/--variable` command line
arguments.

If you are using Autotools, sadly, the `PKG_CHECK_VAR` m4 macro won't be
able to help you, because it does not allow you to expand variables. This
means you'll have to deal with it in the old fashioned way:

```
giomoduledir=`$PKG_CONFIG --define-variable=libdir=$libdir --variable=giomoduledir gio-2.0`
```

Which is annoying, and yet another reason why you should move off from
Autotools and to Meson. 😃

### Caveats

All of this, of course, works **only** if paths are expressed as locations
relative to other variables. If that does not happen, you're going to have a
bad time. You'll still get the variable as requested, but you won't be able
to make it relative to your prefix.

If you maintain a project with paths expressed as variables in your
pkg-config file, check them now, and make them relative to existing
variables, like `prefix`, `libdir`, or `datadir`.

If you're using Meson to generate your pkg-config file, make sure that the
paths are relative to other variables, and file bugs if they aren't.

[pkgconfig-web]: https://people.freedesktop.org/~dbn/pkg-config-guide.html
[pkgconf-web]: http://pkgconf.org/
[meson-web]: http://mesonbuild.com
