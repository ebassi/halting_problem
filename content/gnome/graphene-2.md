Title: layer by layer
Tags: development, graphene
Date: 2014-12-06 13:30
Summary: my little library of math types for 3D canvas libraries is not so little any more
Abstract: in writing libraries, like in a game of chicken, the hard part is knowing when to flinch. in this specific case, when to stop adding symbols to a library that is barely six months old, while writing at least another two that directly depend on it. I think that Graphene reached that point.

I've been having some more fun working on [Graphene][graphene], lately,
thanks to [Alex][alexl-blog] and his port of [three.js][three-js] to
GObject, [Gthree][gthree-github].

the little library that [started in May][graphene-blog] with a bunch of basic
types for vectors and matrices, as well as some 2D types that were required for
convenience, has now grown to include some more 3D types, for the
convenience of people developing 3D canvases:

 * `graphene_triangle_t`, a simple triangle shape made of co-planar 3D points
 * `graphene_plane_t`, a representation of a 2D plane in 3D space
 * `graphene_box_t`, a 3D volume, defined by a minimum and a maximum vertices
 * `graphene_sphere_t`, a sphere, unsurprisingly
 * `graphene_frustum_t`, a [frustum][frustum-wiki] defined by six clipping planes
 * `graphene_euler_t`, a rotation described by [Euler angles][euler-wiki]

alongside these new types there are various new operators for vectors, as
well as utility functions for matrices and quaternions. all in all, ~120 new
symbols have been added to the public API since the 1.0 release, bringing
the total symbols a tad over 400, all documented.

obviously, given the amount of new types and entry points, I had to improve
the coverage of the test suite, which is now around at 60%. still ways to go
before it being good instead of just passable, but definitely better than
before.

for the deparment of the recycle bin of development history, I entertained
the idea of adding a vectorized `graphene_color_t` type, useful if you're
interpolating or operating on texture vertices; but in the end I decided
against it. it's easy enough to use `graphene_vec4_t` for those cases, and
the thing I don't want to do is re-implement the RGBA parsing and HSL
conversion and interpolation **again**, this time using SIMD instructions.

I guess, at this point, it has come a time to stop adding stuff, cut the 1.2
release, and wait until users come up with data types and API for their
particular needs. right now, Graphene has become a fairly sizeable library,
but one that is easy to keep in your head in its entirety — and I'd hate to
lose that characteristic.

[graphene-blog]: https://www.bassi.io/articles/2014/05/03/graphene/
[graphene]: http://ebassi.github.io/graphene
[alexl-blog]: https://blogs.gnome.org/alexl
[three-js]: http://threejs.org/
[gthree-github]: https://github.com/alexlarsson/gthree
[frustum-wiki]: http://en.wikipedia.org/wiki/Viewing_frustum
[euler-wiki]: http://en.wikipedia.org/wiki/Euler_angles
