Title: GSK Demystified (II) — Rendering
Slug: gsk-demystified-2
Date: 2016-08-10 15:20 +0100
Tags: gtk, gsk, gsk demystified, development, welcome to the world of tomorrow
Summary: In which rendering GTK with GSK is explained
Abstract: One of the goals of GSK is provide a way for moving GTK from an immediate mode rendering mechanism to a tree of rendering operations that can be optimized according to our own semantics, instead of teaching Cairo about CSS, which would be a hilarious layering violation as well as an impressive waste of time.

*See the [previous article][gsk-primer-1] for an introduction to GSK.*

---

In order to render with GSK we need to get acquainted with two classes:

 * `GskRenderNode`, a single element in the rendering tree
 * `GskRenderer`, the object that effectively turns the rendering tree
   into rendering commands

### GskRenderNode

The usual way to put things on the screen involves asking the windowing
system to give us a memory region, filling it with something, and then
asking the windowing system to present it to the graphics hardware, in the
hope that everything ends up on the display. This is pretty much how every
windowing system works. The only difference lies in that "filling it with
something".

With Cairo you get a surface that represents that memory region, and a
(stateful) drawing context; every time you need to draw you set up your
state and emit a series of commands. This happens on every frame, starting
from the top level window down into every leaf object. At the end of the
frame, the content of the window is swapped with the content of the buffer.
Every frame is drawn while we're traversing the widget tree, and we have
no control on the rendering outside of the state of the drawing context.

{% figure {filename}/images/gtk-widget-tree.png A tree of GTK widgets %}

With GSK we change this process with a small layer of indirection; every
widget, from the top level to the leaves, creates a series of *render
nodes*, small objects that each hold the drawing state for their contents.
Each node is, at its simplest, a collection of:

 * a rectangle, representing the region used to draw the contents
 * a transformation matrix, representing the parent-relative set
   of transformations applied to the contents when drawing
 * the contents of the node

Every frame, thus, is composed of a tree of render nodes.

{% figure {filename}/images/gsk-render-tree.png A tree of GTK widgets and GSK render nodes %}

The important thing is that the render tree does not draw anything; it
describes what to draw (which can be a rasterization generated using Cairo)
and how and where to draw it. The actual drawing is deferred to the
`GskRenderer` instance, and will happen only once the tree has been built.

After the rendering is complete we can discard the render tree. Since the
rendering is decoupled from the widget state, the widgets will hold all the
state across frames — as they already do. Each `GskRenderNode` instance is,
thus, a very simple instance type instead of a full GObject, whose lifetime
is determined by the renderer.

### GskRenderer

The renderer is the object that turns a render tree into the actual draw
commands. At its most basic, it's a simple compositor, taking the content of
each node and its state and blending it on a rendering surface, which then
gets pushed to the windowing system. In practice, it's a tad more
complicated than that.

Each top-level has its own renderer instance, as it requires access to
windowing system resources, like a GL context. When the frame is started,
the renderer will take a render tree and a drawing context, and will proceed
to traverse the render tree in order to translate it into actual render
commands. 

As we want to offload the rendering and blending to the GPU, the
`GskRenderer` instance you'll most likely get is one that uses OpenGL to
perform the rendering. The GL renderer will take the render tree and convert
it into a (mostly flat) list of data structures that represent the state to
be pushed on the state machine — the blending mode, the shading program, the
textures to sample, and the vertex buffer objects and attributes that
describe the rendering. This "translation" stage allows the renderer to
decide which render nodes should be used and which should be discarded; it
also allows us to create, or recycle, all the needed resources when the
frame starts, and minimize the state transitions when doing the actual
rendering.

### Going from here to there

Widgets provided by GTK will automatically start using render nodes
instead of rendering directly to a Cairo context.

There are various fallback code paths in place in the existing code, which
means that, luckily, we don't have to break any existing out of tree widget:
they will simply draw themselves (and their children) on an implicit render
node. If you want to port your custom widgets or containers, on the other
hand, you'll have to remove the `GtkWidget::draw` virtual function
implementation or signal handler you use, and override the `GtkWidget::get_render_node()`
virtual function instead.

Containers simply need to create a render node for their own background,
border, or custom drawing; then they will have to retrieve the render node
for each of their children. We'll provide convenience API for that, so the
chances of getting something wrong will be, hopefully, reduced to zero.

Leaf widgets can remain unported a bit longer, unless they are composed of
multiple rendering elements, in which case they simply need to create a new
render node for each element.

I'll provide more example of porting widgets in a later article, as soon as
the API will have stabilized.

[gsk-primer-1]: https://www.bassi.io/articles/2016/07/05/gsk-demystified-1/
