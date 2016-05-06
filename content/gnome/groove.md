Title: The hacker's new groove 
Slug: groove
Tags: groove, projects, development
Summary: Writing a new media player and indexer
Status: draft

In early 1998, I downloaded my first MP3 file. It was on a website, and all I
had was a 56k modem, so it took me ages to download the 4 megabytes of 128
kbit/s music goodness. Before that file magically appearing on my hard
drive, if we exclude a brief dalliance with MOD files, the only music I had
on my computer came either in MIDI or in WAV format.

In the almost 20 years passed since that seminal moment, my music collection
has steadily increased in size — to the point that I cannot comfortably keep
it my current computer's storage without cutting into the available space
for other stuff and without taking ages when copying it to new machines; and
if I had to upload it to a cloud service, I'd end up paying monthly storage
fees that would definitely not make me happy. Plus, I like being able to
listen to my music without having a network connection — say, when I'm
travelling. For these reasons, I have my music collection on a dedicated
USB3 drive (and subsets of the whole thing reside on various 64 GB SD cards
that I use when travelling, to avoid bumping around a spinning rust drive).

In order to listen to that first MP3 file, I also had to download a music
player, and back in 1998 there was this little software called
[WinAmp][winamp-wiki], which apparently *really whipped the llama's ass*.
At that time I was dual-booting between Windows and Linux, and, obviously,
Linux had its own Winamp clone called [x11amp][x11amp-wiki]. This means
that, since 1998, I've also tested more or less all mainstream Linux media
collection managers — Rhythmbox, Muine, Banshee — and various less
mainstream ones. I also used iTunes on OSX and Windows, but I don't speak of
that.

Turns out that, with the very special exception of Muine, I hate all of
them. They are all fairly inefficient when it comes to managing my music
collection; or they are barely maintained; or (but, most often, and) they
are massive iTunes clones — as if cloning iTunes was a worthy goal for
anything remotely connected to music, or computing in general.

I did enjoy using Banshee, up to a point; it wasn't overly offensive to my
eyes and pointing devices, and had the advantage of minimising its UI
without getting in the way. It just bitrotted with the rest of the GNOME 2
platform even before GNOME bumped major version, and it still wasn't as good
as Muine.

I need to take a quick aside just for GNOME Music; I honestly wanted to like
it — after all, I install, use, and like the rest of the core GNOME apps.
Still, Music is just plain garbage fire for my use case — and you'll have to
believe me when I say that I mean it in the least offensive way that I can
muster. It's, for my use case of managing a 70+ GB music off-line collection
on an external drive, a useless application that fails in so many ways that
I cannot for the life of me even consider it seriously. It's not just that
its UI is a massive iTunes rip-off; or that it's slow because it tries to
use plain GTK widgets instead of ad hoc drawing to scale to the size of the
data set it needs to display; it's also because it uses barely optimized
queries on a database that cannot be optimized in any way, in order to turn
generic metadata into internal data structures, and has to do so *every*
time the application starts, or the database changes underneath it. In
short, it's because it's using Tracker.

[winamp-wiki]: https://en.wikipedia.org/wiki/Winamp
[x11amp-wiki]: https://en.wikipedia.org/wiki/XMMS
