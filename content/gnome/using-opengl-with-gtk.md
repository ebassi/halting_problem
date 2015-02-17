Title: Using OpenGL with GTK+
Slug: using-opengl-with-gtk
Date: 2015-02-17 00:09
Tags: gtk, opengl, development
Summary: how to use OpenGL with GTK+ 3.16
Abstract: now that GTK+ supports OpenGL natively (at least on Linux and Windows) it's probably a good time to show how to properly use OpenGL with GTK+.

let's say you are on a bleeding edge distribution, or have access to
bleeding edge GTK+.

let's say you want to use OpenGL inside your GTK+ application.

let's say you don't know where to start, except for the API reference of the
[GtkGLArea][gtk-glarea-api] widget, and all you can find are examples and
tutorials on how to use OpenGL with GLUT, or SDL, or worse some random
toolkit that nobody heard about.

this clearly won't do, so I decided to write down how to use OpenGL with
GTK+ using the newly added API available with GTK+ 3.16.

**disclaimer**: I am not going to write an OpenGL tutorial; there are other
resources for it, especially for modern API, like [Anton's OpenGL 4 tutorials][anton-gl4-tut].

I'll spend just a minimal amount of time explaining the details of some of
the API when it intersects with GTK+'s own. this blog will also form the
template for the documentation in the API reference.

### Things to know before we start

the OpenGL support inside GTK+ requires core GL profiles, and thus it won't
work with the fixed pipeline API that was common until OpenGL 3.2 and later
versions. this means that you won't be able to use API like `glRotatef()`,
or `glBegin()`/`glEnd()` pairs, or any of that stuff.

the dependency on non-legacy profiles has various advantages, mostly in
performance and requirements from a toolkit perspective; it adds minimum
requirements on your application — even if modern OpenGL is supported by
Mesa, MacOS, and Windows. before you ask: no, we won't add legacy profiles
support to GTK. it's basically impossible to support both core and legacy
profiles at the same time: you have to choose either one, which also means
duplicating all the code paths. yes, some old hardware does not support
OpenGL 3 and later, but there are software fallbacks in place. to be fair,
everyone using GL will tell you to stop using legacy profiles, and get on
with the times.

### Using the GtkGLArea widget

let's start with an example application that embeds a `GtkGLArea` widget and
uses it to render a simple triangle. I'll be using the [example
code][gtk-api-example] that comes with the GTK+ API reference as a template,
so you can also look at that section of the documentation. the code is also
available in [my GitHub repository][glarea-example-git].

we start by building the main application's UI from a `GtkBuilder` template
file its corresponding GObject class, called `GlareaAppWindow`:

{% include_code glarea/glarea-app-window.h lang:cpp %}

this class is used by the `GlareaApp` class, which in turn holds the
application state:

{% include_code glarea/glarea-app.h lang:cpp %}

the `GtkBuilder` template file contains a bunch of widgets, but the most
interesting section (at least for us) is this one:

{% include_code glarea/glarea-app-window.ui lang:xml lines:33-43 %}

which contains the definition for adding a `GtkGLArea` and connecting to its
signals.

once we connect all elements of the template to the `GlareaAppWindow` class:

{% include_code glarea/glarea-app-window.c lang:cpp lines:338-355 %}

and we compile and run the whole thing, we should get something like this:

{% figure {filename}/images/glarea-empty.png the empty GL drawing area %}

if there were any errors while initializing the GL context, you would see
them inside the `GtkGLArea` widget itself; you can control this behaviour,
just like you can control the creation of the `GdkGLContext` yourself.

as you saw in the code above, we use the `GtkWidget` signals to set up,
draw, and tear down the OpenGL state. in the old days of the fixed pipeline
API, we could have simply connected to the `GtkGLArea::render` signal,
called some OpenGL API, and have something appear on the screen. those days
are long gone. OpenGL requires more code to get going with the programmable
pipeline. while this means that you have access to a much leaner (and
powerful) API, some of the convenience went out of the window.

in order to get things going, we need to start by setting up the OpenGL
state; we use the `GtkWidget::realize` signal, as that allows our code to be
called after the `GtkGLArea` widget has created a `GdkGLContext`, so that we
can use it:

{% include_code glarea/glarea-app-window.c lang:cpp lines:188-202 %}

in the same way, we use `GtkWidget::unrealize` to free the resources we
created inside the `gl_init` callback:

{% include_code glarea/glarea-app-window.c lang:cpp lines:204-213 %}

at this point, the code to draw the context of the `GtkGLArea` is:

{% include_code glarea/glarea-app-window.c lang:cpp lines:247-263 %}

and *voilà*:

{% figure {filename}/images/glarea-triangle.png Houston, we have a triangle %}

obviously, it's a bit more complicated that.

let's start with the code that initializes the resources inside `gl_init()`;
what do `init_buffers()` and `init_shaders()` do? the former creates the
vertex buffers on the graphics pipeline, and populates it with the
per-vertex data that we want to use later on, namely: the position of each
vertex, and its color:

{% include_code glarea/glarea-app-window.c lang:cpp lines:36-48 %}

it does that by creating two buffers:

 * a Vertex Array Object, which holds all the subsequent vertex buffers
 * a Vertex Buffer Object, which holds the vertex data

{% include_code glarea/glarea-app-window.c lang:cpp lines:55-63 %}

the `init_shaders()` function is a bit more complex, as it needs to

 * compile a vertex shader
 * compile a fragment shader
 * link both the vertex and the fragment shaders together into a program
 * extract the location of the attributes and uniforms

the vertex shader is executed once for each vertex, and establishes the
location of each vertex:

{% include_code glarea/glarea-vertex.glsl lang:glsl %}

it also has access to the vertex data that we stored inside the vertex
buffer object, which we pass to the fragment shader:

{% include_code glarea/glarea-fragment.glsl lang:glsl %}

the fragment shader is executed once for each *fragment*, or pixel-sized
space between vertices.

once both the vertex buffers and the program are uploaded into the graphics
pipeline, the GPU will render the result of the program operating over the
vertex and fragment data — in our case, a triangle with colors interpolating
between each vertex:

{% include_code glarea/glarea-app-window.c lang:cpp lines:215-245 %}

now that we have a static triangle, we should connect the UI controls and
transform it around each axis. in order to do that, we compute the
transformation matrix using the value from the three `GtkScale` widgets as
the rotation angle around each axis. first of all, we connect to the
`GtkAdjustment::value-changed` signal, update the rotation angles, and use
them to generate the rotation matrix:

{% include_code glarea/glarea-app-window.c lang:cpp lines:312-336 %}

then we queue a redraw on the `GtkGLArea` widget, and that's it; the
`draw_triangle()` code will take the matrix, place it inside the vertex
shader, and we'll use it to transform the location of each vertex.

{% figure {filename}/images/glarea-triangle-transformed.png add a few more triangles and you get Quake %}

there is obviously a lot more that you can do, but this should cover the
basics.

### Porting from older libraries

back in the GTK+ 2.x days, there were two external libraries used to render
OpenGL pipelines into GTK+ widgets:

 * GtkGLExt
 * GtkGLArea

the GDK drawing model was simpler, in those days, so these libraries just
took a native windowing system surface, bound it to a GL context, and
expected everything to work. it goes without saying that it is not the case
any more when it comes to GTK+ 3, and with modern graphics architectures.

both libraries also had the unfortunate idea of abusing the GDK and GTK
namespaces, which means that, if ported to integrate with GTK+ 3, they would
collide with GTK's own symbols. this means that these two libraries are
forever tied to GTK+ 2.x, and as they are unmaintained already, you should
not be using them to write new code.

#### Porting from GtkGLExt

[GtkGLExt][gtkglext-web] is the library GTK+ 2.x applications used to
integrate OpenGL rendering inside GTK+ widgets. it is currently
unmaintained, and there is no GTK+ 3.x port. not only GtkGLExt is targeting
outdated API inside GTK+, it's also fairly tied to the old OpenGL 2.1 API
and rendering model. this means that if you are using it, you're also using
one legacy API on top of another legacy API.

if you were using [GtkGLExt][gtkglext-web] you will likely remove most of
the code dealing with initialization and the creation of the GL context. you
won't be able to use any random widget with a `GdkGLContext`, but you'll be
limited to using `GtkGLArea`. while there isn't anything specific about the
`GtkGLArea` widget, `GtkGLArea` will handle context creation for you, as
well as creating the offscreen framebuffer and the various ancillary buffers
that you can use to render on.

#### Porting from GtkGLArea

[GtkGLArea][gtkglarea-web] is another GTK+ 2.x library that was used to
integrate OpenGL rendering with GTK+. it has seen a GTK+ 3.x port, as well
as a namespace change that avoids the collision with the GTK namespace, but
the internal implementation is also pretty much tied to OpenGL 2.1 API and
rendering model.

unlike GtkGLExt, [GtkGLArea][gtkglarea-web] only provides you with the API
to create a GL context, a widget to render into. it is not tied to the GDK
drawing model, so you're essentially bypassing GDK's internals, which means
that changes inside GTK+ may break your existing code.

### Resources

 * [Anton's OpenGL 4 tutorials][anton-gl4-tut], by Anton Gerdelan
 * [Learning Modern 3D Graphics Programming][mckesson-tut], by Jason L. McKesson
 * [GtkGLArea API reference][gtk-glarea-api]

[mckesson-tut]: http://www.arcsynthesis.org/gltut/index.html
[anton-gl4-tut]: http://antongerdelan.net/opengl/index.html
[gtkglext-web]: https://projects.gnome.org/gtkglext/
[gtkglarea-web]: http://www.mono-project.com/archived/gtkglarea/
[gtk-api-example]: https://developer.gnome.org/gtk3/stable/ch01s05.html#id-1.2.3.7.5
[glarea-example-git]: https://github.com/ebassi/glarea-example 
[gtk-glarea-api]: https://developer.gnome.org/gtk3/unstable/GtkGLArea.html
