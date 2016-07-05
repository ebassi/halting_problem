Title: GSK Demystified — A GSK primer (I)
Slug: gsk-demystified-1
Date: 2016-07-05
Tags: gtk, gsk, gsk demystified, development, welcome to the world of tomorrow
Summary: In which I start explaining what GSK is, does, and where it's at
Abstract: Some people started noticing bits and pieces of GSK landing in the GTK+ repository, mostly in topic branches, so it's probably a good time to explain what I'm doing, how am I doing it, how long it's going to take, and what it means for everybody else who is waiting for a scene graph API, or is just curious about it

Last month I published [an article][gtk-drawing] on how GTK+ draws widgets
on [the toolkit development blog][gtk-blog]. The article should give you
some background on the current state of what GTK does when something asks it
to draw what you see on the screen — so it's probably a good idea to read
that first, and then come back here. Don't worry, I'll wait…

---

<aside>If you're running with X11 you may find some of the XRENDER
extension operations to be implemented with a modicum of hardware
acceleration; that does not imply that what you see has hit the right code
paths in the stack.</aside>

Welcome back! Now that we're on the same page… What I didn't say in that
article is that most of it happens on your CPU, rather than on your GPU —
except the very last step, when the compositor takes the contents of each
window and pushes them to the GPU, likely via the 3D pipeline provided by
your windowing system, to composite them into what you'll likely see on your
screen.

The goal for GUI toolkits, for the past few years, has been to take
advantage of the GPU programmable pipeline as much as possible, as it allows
to use the right hardware for the job, while keeping your CPU free for
working on the application logic, or simply powered down and avoid polar
bears to squeeze on an ever reducing sheet of artic ice. It also allows to
improve the separation of jobs internally to the toolkit, with the potential
of splitting up the work across multiple CPU cores.

<aside>Yes, we also have Vulkan. Or, at least, we're soon going to have
Vulkan. You can swap OpenGL with Vulkan throughout this article, if you
want, and you'll get pretty much the same results. Hopefully, internally,
we'll be able to do the same.</aside>

As toolkit developers, we currently have only one major API for talking to
the GPU, programming it, and using it to put the contents of a window on the
screen, and that's OpenGL.

You may think: *well, we use Cairo; Cairo has support for an OpenGL device.
Just enable that, and we're good to go, right?* and you wouldn't be entirely
wrong — **except** that you really don't want to use the OpenGL Cairo
device in production, as it's both a poor fit for the Cairo drawing model
*and* it's basically unmaintained. Also, Cairo is pretty much 2D only, and
while you can fake some 3D transformations with it, it's definitely not up
to the task of implementing the full [CSS transformation][css-transforms]
specification.

---

Using OpenGL to generate pixel-perfect results is complicated, and in some
cases it just goes against the expectations of the GPU itself: reading back
data; minuscule fragments and tesselations; tons of state changes — those
are all pretty much no-go areas when dealing with a GPU.

<aside>If we could also move frame rendering to separate threads we could
have multiple frames scheduled on different cores running at the same time,
thus speeding up the whole drawing process.</aside>

On the other hand, we really want to stop relying so much on the CPU for
drawing; leaving your cores idle allows them to go into low power states,
preserving them and improving your battery life; additionally, any cycle
that is not spent inside the toolkit is a cycle available to your
application logic.

As you may know from the past few years, I've been working on writing a new
API that lets GTK offload to the GPU what currently happens on the CPU; it's
called **GSK** — short for *GTK Scene Kit* — and its meant to achieve two
things:

 * render the contents of a GTK application more efficiently
 * provide a scene graph API to both the toolkit and applications

With these two goals in mind, I want to give a quick overview on how GSK
works, and at which point we are in the development.

---

As GSK is meant to serve two purposes it makes sense to have two separate
layers of API. This is a design decision that solidified after various
discussions at GUADEC 2015. As such, it required a fair amount of rework
of the existing code base, but very much for the better.

At the lowest level we have:

 * `GskRenderNode`, which is used to describe a tree of textures, blend
   modes, filters, and transformations; this tree is easily converted in
   render operations for graphics API like Cairo and OpenGL, and Vulkan in
   the near future.
 * `GskRenderer`, an object that takes a tree of `GskRenderNode` instances
   that describes the contents of a frame, and renders it on a given
   `GdkDrawingContext`.

Every time you wish to render something, you build a tree of render nodes;
specify their content; set up their transformations, opacity, and blending;
and, finally, you pass the tree to the renderer. After that, the renderer
owns the render nodes tree, so you can safely discard it after each frame.

On top of this lower level API we can implement both the higher level scene
graph API based on `GskLayer` that I presented at GUADEC; and GTK+ itself,
which allows us to avoid reimplementing GTK+ widgets in terms of GSK layers.

I'm going to talk about `GskRenderer` and `GskRenderNode` more in depth in a
future blog post, but if you're looking for some form of prior art, you can
check the [`ClutterPaintNode`][clutter-paint-node-api] API in Clutter.

Widgets in GTK+ would not really be required to use render nodes: ideally,
we want to get to a future where widgets **are** a small, composable unit
whose appearances that can be described using CSS; while we build towards
that future, though, we can incrementally transition from the current
immediate more rendering model to a more structured tree of rendering
operations that can be reordered and optimized for the target graphics
layer.

Additionally, by sharing the same rendering model between the more complex
widget API and the more freeform layers one, we only have to care about
optmizing a single set of operations.

*You can check the current progress of my work in the
[gsk-renderer][gsk-renderer-branch] branch of the GTK+ repository.*

[gtk-drawing]: https://blog.gtk.org/2016/06/15/drawing-in-gtk/
[gtk-blog]: https://blog.gtk.org
[css-transforms]: https://www.w3.org/TR/css-transforms-1/
[clutter-paint-node-api]: https://developer.gnome.org/clutter/stable/ClutterPaintNode.html
[gsk-renderer-branch]: https://git.gnome.org/browse/gtk+/log/?h=wip/ebassi/gsk-renderer
