Title: GSK Demystified (III) — Interlude
Slug: gsk-demystified-3
Date: 2016-08-27 10:28 +0100
Tags: gtk, gsk, gsk demystified, development, welcome to the world of tomorrow
Summary: In which we take a short pause and explain the current state of GSK 
Abstract: GSK is more than a new API provided by the GTK+ project; it's a multi-year project that attempts changing the way GTK itself draws its widgets, as well as providing a new tool for application developers.

*See the [the tag for the GSK demystified series][gsk-demystified] for the
other articles in the series.*

There have been multiple reports after [GUADEC][guadec-web] about the state
of GSK, so let's recap a bit by upholding the-long standing tradition of using
a FAQ format as a rhetorical device.

- - - -

### Q: Is GSK going to be merged in time for 3.22?

**A:** Short answer: no.

Long-ish answer: landing a rewrite of how GTK renders its widgets near the
end of a stable API cycle, when a bunch of applications that tend to eschew
GTK+ itself for rendering their content — like Firefox or LibreOffice —
finally, after many years, ported to GTK+ 3, seemed a bit sadistic on our
part.

Additionally, GSK still has some performance issues when it comes to large
or constantly updating UIs; try running, for instance `gtk3-widget-factory`
on HiDPI using the [wip/ebassi/gsk-renderer][gsk-git-branch] branch and
marvel at the 10 fps we achieve currently.

### Q: Aside from performance, are there any other concerns?

**A:** Performance is pretty much the biggest concern we found. We need to
reduce the amount of rasterizations we perform with Cairo, and we need
better ways to cache and reuse those rasterizations across frames; we really
want all buttons with the same CSS state and size to be rasterized once, for
instance, and just drawn multiple times in their right place. The same
applies to things like icons. Caching text runs and glyphs would also be a
nice win.

The nice bit is that, with a fully retained render tree, now we can actually
do this.

The API seems to have survived contact with the widget drawing code inside
GTK+, so it's a matter of deciding how much we need to provide in terms of
convenience API for out-of-tree widgets and containers. The fallback code is
in place, right now, which means that porting widgets can proceed at its own
pace.

There are a few bugs in the rendering code, like blend modes; and I still
want to have filters like blur and color conversions in the GskRenderNode
API.

Finally, there's still the open question of the mid-level scene graph API,
or `GskLayer`, that will replace Clutter and Clutter-GTK; the prototype is
roughly done, but things like animations are not set in stone due to lack of
users.

### Q: Is there a plan for merging GSK?

**A:** Yes, we do have a plan.

The merge window mostly hinges on when we're going to start with a new
development cycle for the next API, but we decided that as soon as the
window opens, GSK will land. Ideally we want to ensure that, by the time 4.0
rolls around, there won't be any users of `GtkWidget::draw` left inside
GNOME, so we'll be able to deprecate its use, and applications targeting the
new stable API will be able to port away from it.

Having a faster, more featureful, and more optimized rendering pipeline
inside GTK+ is a pretty good new feature for the next API cycle, and we
think that the port is not going to be problematic, given the amount of
fallback code paths in place.

Additionaly, by the time we release GTK+ 4.0, we'll have a more
battle-tested API to replace Clutter and Clutter-GTK, allowing applications
to drop a dependency.

### Q: How can I help?

**A:** If you're a maintainer of a GTK+ library or application, or if you
want to help out the development of GTK+ itself, then you can pick up my
[GSK development branch][gsk-git-branch], fork it off, and look at porting
widgets and containers. I'm particularly interested in widgets using complex
drawing operations. See where the API is too bothersome, and look for
patterns we can wrap into convenience API provided by GTK+ itself. For
instance, the various `gtk_render_*` family of functions are a prime
candidate for being replaced by equivalent functions that return a
`GskRenderNode` instead.

Testing is also welcome; for instance, look at missing widgets or fragments
of rendering.

- - - -

Hopefully, the answers above should have provided enough context for the
current state of GSK.

The next time, we'll return to design and implementation notes of the API
itself.

[gsk-demystified]: https://www.bassi.io/tag/gsk-demystified/
[guadec-web]: https://2016.guadec.org
[gsk-git-branch]: https://git.gnome.org/browse/gtk+/log/?h=wip/ebassi/gsk-renderer 
