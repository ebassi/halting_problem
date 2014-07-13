Title: Graphene
Slug: graphene
Tags: development, graphics, libraries
Date: 2014-05-02
Summary: a new library I wrote to handle common geometry  types for graphic
  libraries, possibly optimizing them

one of the challenges of writing a graphics library that is capable of doing
what modern UI designers and developers expect is providing the required data
types to achieve things like 3D transformations.

with the collective knowledge and attention to detail that the free and open
source software community brings to the table I was actually surprised to see
that all the code for doing vector and matrix math is usually tucked away into
various silos that also come with canvas implementations, physics engines, and
entire web browsers. it gets even worse when you want code that used features of
modern (and less modern) hardware, and instead all you get are just naive
implementations of four floating point values in a structure.

you can trust me when I say that I didn’t want to spend the past seven days
writing code that deals with vector and matrix operations, when I wasn’t reading
PDFs of Intel architecture opcodes, or ARM NEON instructions; I also didn’t want
to know that once you start implementing common operations on matrix types, like
projection and unprojection, you get to open a fairly deep can of worms that
forces you to implement point (2D and 3D), rectangle, quaternion, and quad
types.

luckily, it’s possible to find a bunch of implementations under various stages
of maintenance, and under suitable licenses, even though mostly are in C++ and
they overlap by just about 60% each; you really need to buckle up and start
translating naive matrix determinant code to SIMD four vector data structures,
and do a union of all possible API, before you have something you can actually
use.

the end result of these seven days is an almost decent, almost complete little
utility library that tries to be fairly thin in both what it requires and what
it provides. I called it graphene and it’s available in Git. at some point, when
I’m actually satisfied with it, I’ll even document it like the grown-up I’m
supposed to be. right now, I’ll have to write a ton of tests to check on the
math, because I’m pretty sure there must be at ton of bugs in there.

the main question is: what do I intend to use graphene for. the more attentive
amongst you, kind readers, will already guess that it’s for the forthcoming GTK+
scene graph API — which is indeed the correct answer, but you’ll have to wait
for the next blog post in the series for a proper introduction and description,
as well as a road map for the unicorn and ponies fuelled future.
