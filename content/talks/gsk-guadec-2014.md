# The GTK+ Scene Graph Kit

hello everyone, and welcome back to GUADEC.

I want to state up front that, while I indicated that there may be demos in this
talk, I honestly did not have time to prepare them. I know this is a breach of
trust, and I apologise for that. you're welcome to give me your piece after the
talk, I'll try and take it like an adult. sadly, I did not even finish the
actual library I am about to describe to you; work has found a way to prevent me
from committing as many resources as I wanted to in the form of a product that
needed to be shipping. to be fair, I kind of like the idea of being able to
afford food, shelter, and clothing — as well as going to fancy conferences like
GUADEC — and the hours in a day are limited resource, which meant something had
to give.

I also don't have any actual slide. over the years I have been steadily
decreasing the amount of data in my presentations — basically using pinpoint to
display large pictures with a couple of words, and maybe an occasional syntax.
since I want to talk to you about an API design, slides seem not only to be
unnecessary: they would be pointless. headers and documentation annotations are
probably more useful for you to understand what I am describing, so I'll do
exactly that.

if you remember, we were in Brno last year, and I talked about how I did not
think that we should have a Clutter 2.0 release, and that, instead, we should
work towards merging a subset of what Clutter provides directly into the GTK+
tool kit.

there were various reasons for that, but it could all be summed up with the fact
that having two tool kits, with fairly different ideas on how to render stuff,
and that only share some concepts about the windowing system, was a complex
proposition both for our users (or potential users) and for our own
maintainership capacity.

there are obvious benefits when it comes to having a scene graph inside our own
main tool kit, as opposed to a separate library, but the most obvious is the
fact that we have been moving pretty consistently towards a world where we style
and draw every widget using the concepts of CSS, and that world has some
expectations when it comes to rendering. those expectations can be made to work
with our current drawing model, but we're hitting the limits, and we already had
to change how GTK+ draws its widgets in a pretty radical way in order to get
things like shadows and borders to work as CSS expects to. padding, margin,
borders have a fairly well-define set of semantics, and making those style
properties work for composite and complex widgets has proven pretty painful.

we are also hitting limitations on what can be animated through CSS, as well as
in code. we can transition a simple widget between two states, but transitions
between complex states, or between states whose semantics are completely up to
the application developer, is very much still a case of writing a lot of code.
if the state transition entails changing the layout of a complex widget, this is
still pretty much ad hoc container territory, and that requires even more work.

during the past year I reworked a lot of the prototype code that I had already
written.

I had started off by adding GL support to GDK, and wrote the prototype code to
create a GLX context attached to a GdkDisplay. then, after realizing that I had
to do the same for every backend we have, and looking at the crazy code I had to
write — a dispatch table, the whole "check if we have an extension and provide a
wrapper functions for it", and possibly even autogenerating the entry points
from the XML description of the API from the Khronos group — I found out that
there was better code already available just for that in the form of `libepoxy`.

[libepoxy][epoxy-github] is a very small glue library written by Eric Anholt
that handles the GL functions for you; it's portable to all the platforms we
care about, and it's already used in various other projects, including KDE.

by switching to libepoxy I was able to clear out a lot of crappy code, and I get
support for MacOS and Windows without having to actually write that code.

truth is, though, that GL is just a step on a ladder, and it's not even the most
important; after all, I could already enable cairo-gl surfaces and pretty much
assume that they work well enough to do some basic blending. having GL (or GLES)
support in GDK, though, allows us to control the pipeline a bit better, and
ignore the fact that you *really* don;t want to use GL for drawing. compositing
textured data, yes. drawing, no. GL drawing bad. no cookie for you.

there's still the open question of Broadway, and how to deal with that. since we
are, after all, blending stuff internally to the scene graph, we may get away
with the `<canvas>` tag and CSS transformations; or maybe use webGL for
blending and compositing canvas items, instead of GL. it may be a fun side
project for someone web-inclined. I don't necessarily want to drop the Broadway
backend from GTK+ 4, but like with DirectFB, if we don't find a long term
maintainance model, we just might have to.

obviously, since we are talking about GL for blending and CSS for styling, we
are also talking about 3D transformations. turns out, we can't use data types
provided by Cairo for that. at most, Cairo supports affine transformations only.
adding 4 by 4 matrices, vectors, and other types to Cairo would imply being able
to use them in Cairo itself, which would be a massive undertaking — and one that
would likely go unreviewed and unmerged for a long time, at that.

as a side note: I think the past few years have clearly demonstrated that
Cairo's maintainance and release management model is not suited to GTK's needs;
or anybody's needs, really, considering the amount of projects that are not
GNOME that still use Cairo. I think the Cairo situation will require to be
addressed sooner, rather than later. I don't have a good solution to solve this
situation, and everything I can think of ranges from "repository move" to "we are
all going to die". last year I managed to anger the GStreamer developers; it
seems only fair that I do that for all our dependencies, at this point.

since we cannot use Cairo for basic geometry types, I ended up looking around
for libraries to depend on. it turns out that there are few libraries that do
that. some of them are part of other projects, and they come along with them.
while it would be neat to have GTK+ depend on Unity3D, I sincerely doubt we want
to do that. half of GNOME already depends on the Mozilla JS code, but depending
on the graphics code inside Gecko would also be slightly problematic; also,
getting Mozilla to actually handle SpiderMonkey like an actual library was
fairly complicated; I doubt they would release the Thebes code base as a
separate shared object. also: C++.

I ended up writing about seven thousand lines of code to provide some types that
do not make baby pandas cry, and that are mostly suited for a canvas library. it
is called [graphene][graphene-github] and [I announced it][graphene-blog] on my
blog around the same time we had the Developer Experience hackfest earlier this
year, in Berlin.

apparently, various people think that Graphene *is* the canvas library, or that
I plan to make it the canvas library, which is incorrect. Graphene is a
collection of geometry types — points, sizes, rectangles, vectors, quads,
quaternions, matrices — and that's all it does. it tries to optimize them so
that the naïve, four floats for vertex/four vertices for matrix implementation
is not the only one; it's also not strictly necessary to optimize that code,
because at the end of the day, your browser very likely does not use SIMD
instructions for that and yet it handles animations on the CPU fairly well
already.

the important bit about Graphene, though, it's the API. it allows us to avoid
exposing C arrays of floating point values, or opaque memory regions, which
means that you can actually manipulate vectors and matrices in other languages
as well, and that you're not going to have awful C code all over the place in
your library.

other projects have expressed interest in Graphene, and I plan to do a 1.0
release after GUADEC, to mark the point of API stability. there is still some
testing necessary, especially on ARM and on non-GCC/non-CLang compilers; I'd
really like to start dropping dead weight from GTK+'s platform requirements,
like C89, and smaller libraries can be useful to explore this space.

now, we get to the biggest step on the ladder: the actual scene graph code.

my initial plan was just to take Clutter and move it into a shared library in
tree with GTK+; then use GdkWindow as the backing store for a ClutterActor top
level (which we already kind of support in Clutter through the GDK backend),
and basically call it a day.

obviously, we can't really do that.

first of all, there's a symbol collision consideration that applies; there are
projects that link to both Clutter *and* GTK+, by way of clutter-gtk. all these
projects would suddenly be unable to run if GTK+ started shipping a public
shared `libclutter` object that exposed the same GTypes. we could conceivably
make this case work, but what happens to libraries like [Champlain][champlain]?

the secondary, but even more important, consideration is that ClutterActor
encodes a lot of history, with both good and some very poor decisions that were
taken along the way. there was a reason why I thought, a couple of years ago, to
start the 2.0 API development process, and just dumping out a cleaned version of
ClutterActor inside the GTK repository would not address the issues of cruft in
both API and design decisions.

we should be able to learn from the mistakes of the past, but we have the chance
here not to string them along. we can make different, new, and exciting poorly
thought out decisions!

for these two reasons, mainly, I decided to start from scratch — or, at least,
as close to scratch as I can.

I want to go through the main header file of the library with you, and explain
some of the design choices I made.

I also want to impress upon you that some of these design choices are not fixed
in stone, and can be changed given an appropriate amount of discussion and/or
beer bought to yours truly. I am, indeed, amenable more to the latter. while
this code has been committed to a Git repository, there is still time to figure
stuff out before we actually commit to any form of API stability. we are in the
last weeks of the 3.14 cycle, and even if we decided to railroad this effort for
the 3.16 cycle, we still have time to reconsider many things.

We are going to discuss further details during the GTK+ BoF session after the
core days, on Thursday. you can join, if you're interested.

I will publish these notes on my website soon after the talk.

[epoxy-github]: https://github.com/anholt/libepoxy
[graphene-github]: https://github.com/ebassi/graphene
[graphene-blog]: http://www.bassi.io/articles/2014/05/03/graphene/
[champlain]: https://git.gnome.org/browse/libchamplain/
