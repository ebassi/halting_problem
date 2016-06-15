Title: GSK Demystified — A GSK primer (I)
Slug: gsk-demystified-1
Status: draft
Tags: gtk, gsk, gsk demystified, development, welcome to the world of tomorrow
Summary: In which I start explaining what GSK is, does, and where it's at
Abstract: Some people started noticing bits and pieces of GSK landing in the GTK+ repository, mostly in topic branches, so it's probably a good time to explain what I'm doing, how am I doing it, how long it's going to take, and what it means for everybody else who is waiting for a scene graph API, or is just curious about it

On Wednesday I published [an article][gtk-drawing] on how GTK+ draws widgets
on [the toolkit development blog][gtk-blog]. The article should give you
some background on the current state of what GTK does when something asks it
to draw what you see on the screen — so it's probably a good idea to read
that first, and then come back here.

What I didn't say in that article is that most of it happens on your CPU,
rather than on your GPU — except the very last step, when the compositor
takes the contents of each window and pushes them to the GPU, likely via the
3D pipeline provided by your windowing system, to composite them into what
you'll likely see on your screen.

<aside>If you're running with X11 you may find some of the XRENDER
extension operations to be implemented with a modicum of hardware
acceleration; that does not imply that what you see has hit the right code
paths in the stack.</aside>

The goal for GUI toolkits, for the past few years, has been to take
advantage of the GPU programmable pipeline as much as possible, as it allows
to use the right hardware for the job, while keeping your CPU free for
working on the application logic, or simply powered down and avoid polar
bears to squeeze on an ever reducing sheet of artic ice. It also allows to
improve the separation of jobs internally to the toolkit, with the potential
of splitting up the work across multiple CPU cores.

As toolkit developers, we currently have only one major API for talking to
the GPU, programming it, and using it to put the contents of a window on the
screen, and that's OpenGL.

<aside>Yes, we also have Vulkan. Or, at least, we're soon going to have
Vulkan. You can swap OpenGL with Vulkan throughout this article, if you
want.</aside>

You may think: *well, we use Cairo; Cairo has support for an OpenGL device.
Just enable that, and we're good to go, right?* and you wouldn't be entirely
wrong — **except** that you really don't want to use the OpenGL Cairo
device in production, as it's both a poor fit for the Cairo drawing model
and it's basically unmaintained.



[gtk-drawing]:
[gtk-blog]: https://blog.gtk.org
