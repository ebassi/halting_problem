Title: Dev v Ops
Tags: design, free software, distribution, platform, security
Date: 2017-08-10 16:51 +0100
Modified: 2017-08-10 18:55 +0100
Summary: In which application development and packaging are discussed, vis-a-vis old and new practices
Abstract: Initially, I decided not to post this article, even if it deals with a GUADEC presentation, in the section that gets syndacated on Planet GNOME; I didn't want to be inappropriately confrontational, and I didn't want this to be picked up as the position of GNOME, my employer, or essentially anybody but myself. I've received positive feedback from various people, so I feel a bit better about my intentions coming through.

In [his talk][rb-talk] at the 2017 GUADEC in Manchester, Richard Brown
presented a set of objections to the current trend of new packaging systems
— mostly AppImage, Snap, and Flatpak — from the perspective of a Linux
distribution integrator.

I'm not entirely sure he managed to convince everybody in the attendance,
but he definitely presented a well-reasoned argument, steeped in history. I
freely admit I went in not expecting to be convinced, but fully expecting to
be engaged and I can definitely say I left the room thoroughly satisfied,
and full of questions on how we can make the application development and
distribution story on Linux much better. Talking with other people involved
with [Flatpak][flatpak-web] and [Flathub][flathub-web] we already identified
various places where things need to be improved, and how to set up automated
tools to ensure we don't regress.

In the end, though, all I could think of in order to summarise it when
describing the presentation to people that did not attend it, was this:

> Linux distribution developer tells application and system developers that
> packaging is a solved problem, as long as everyone uses the same OS,
> distribution, tools, and becomes a distro packager.

Which, I'm the first to admit, seems to subject the presentation to
impressive levels of lossy compression. I want to reiterate that I think
Richard's argument was presented much better than this; even if the talk was
really doom and gloom predictions from a person who sees new technologies
encroaching in his domain, Richard had wholesome intentions, so I feel a bit
bad about condensing them into a quip.

Of course, this leaves me in quite a bind. It would be easy — *incredibly*
easy — to dismiss a lot of the objections and points raised by Richard as a
case of the Italian idiom "do not ask to the inn-keeper if the house wine is
good". Nevertheless, I want to understand why those objections where made in
the first place, because it's not going to be the last we are going to be
hearing them.

I've been turning an answer to that question in my head for a while, now,
and I think I finally came up with something that tries to rise to the level
of Richard's presentation, in the sense that I tried to capture the issue
behind it, instead of just reacting to it.

- - -

Like many things in tech, it all comes down to developers and system
administators.

I don't think I'm being controversial, or exposing some knowledge for
initiates, when I say that Linux distributions are not made by the people
that write the software they distribute. Of course, there are various
exceptions, with upstream developers being involved (by volunteer or more
likely paid work) with *a particular distribution* of their software, but by
and large there has been a complete disconnect between who *writes* the code
and who *packages* it.

Another, I hope, uncontroversial statement is that people on the Linux
distribution side of things are mostly interested in making sure that the
overall OS fits into a fairly specific view of how computer systems should
work: a central authority that oversees, via policies and validation tools
that implement those policies, how all the pieces fit together, up to a
certain point. There's a name for that kind of authority: system
administrators.

Linux distributions are the continuation of system administration policies
via other means: all installed Linux machines are viewed as part of the same
shared domain, with clear lines of responsibility and ownership that trace
from a user installation to the packager, to the people that set up the
policies of integration, and which may or may not involve the people that
make the software in the first place — after all, that's what distro patches
are for.

You may have noticed that in the past 35 years the landscape of computing
has been changed by the introduction of the personal computer; that the
release of Windows 95 introduced the concept of a mass marketable operating
system; and that, by and large, there has been a complete disintermediation
between software vendors and users. A typical computer user won't have an
administrator giving them a machine with the OS, validating and managing all
the updates; instead of asking an admin to buy, test, and deploy an
application for them, users went to a shop and bought a box with floppies or
an optical storage — and now they just go to online version of that shop
(typically owned by the OS vendor) and download it. The online store may
just provide users with the guarantee that the app won't steal all their
money without asking in advance, but that's pretty much where the
responsibility of the owners of the store ends.

Linux does not have stores.

You're still supposed to go ask your sysadmin for an application to be
available, and you're still supposed to give your application to the
sysadmin so that they can deploy it — with or without modifications.

Yet, in the 25 years of their history, Linux distribution haven't managed to
convince the developers of

  - Perl
  - Python
  - Ruby
  - JavaScript
  - Rust
  - Go
  - PHP
  - `insert_your_language_here`

applications to defer all their dependency handling and integration to
distro packagers.

They have just about managed to convince C and C++ developers, because the
practices of those languages are so old and entrenched, the tools so poor,
and because they share part of the same heritage; and TeX writers, for some
weird reason, as you can witness by looking at how popular distribution
package all the `texlive` modules.

The crux is that nobody, on any existing major (≥ 5% of market penetration)
platform, develops applications like Linux distributors want them to. Nobody
**wants to**. Not even the walled gardens you keep in your pocket and use to
browse the web, watch a video, play a game, and occasionally make a phone
call, work like that, and those are the closest thing to a heavily managed
system you can get outside of a data center.

The issue is not the "managed by somebody" part; the issue is the inevitable
intermediary between an application developer and an application user.

Application developers want to be able to test and have a reproducible
environment, because it makes it easier for them to find bugs and to ensure
that their project works as they intented; the easiest way to do that is to
have people literally use the developer's computer — this is why web
applications deployed on top of a web browser engine that consumes all your
CPU cores in a fiery pit are eating everybody's lunch; or because software
as a service even exists. The closest thing application developers have
found to ship their working laptop to the users of our applications without
physically shipping hardware, is to give them a read-only file system image
that we have built ourselves, or a list of dependencies hosted on a public
source code repository that the build system will automatically check out
prior to deploying the application.

The Linux distribution model is to have system administrators turned
packagers control all the dependencies and the way they interact on a
system; check all the licensing terms and security issues, when not
accidentally introducing them; and then fight among themselves on the
practicalities and ideologies of how that software should be distributed,
installed, and managed.

The more I think about it, the less I understand how that ever worked in the
first place. It is not a mystery, though, why it's a dying model.

When I say that "nobody develops applications like the Linux distributions
encourages and prefers" I'm not kidding around: Windows, macOS, iOS,
Electron, and Android application developers are heavily based on the
concept of a core set of OS services; a parallel installable blocks of
system dependencies shipped and retired by the OS vendor; and a bundling
system that allows application developers to provide their own dependencies,
and control them.

Sounds familiar?

If it does, it's becase, in the past 25 years, every other platform (and I
include programming languages with a fairly comprehensive standard library
in that definition, not just operating systems) has implemented something
like this — even in free and open source software, where this kind of
invention mostly exists both as a way to replicate Linux distributions on
Windows, and to route around Linux distributions on Linux.

It should not come as a surprise that there's going to be friction; while
for the past two decades architects of both operating systems and
programming languages have been trying to come up with a car, Linux
distributions have been investing immeasurable efforts in order to come up
with a jet fueled, SRB-augmented horse. Sure: it's so easy to run `apt
install foo` and get `foo` installed. How did `foo` get into the repository?
How can you host a repository, if you can't, or don't want to host it on
somebody else's infrastructure? What happens when you have to deal with a
bajillion, slightly conflicting, ever changing policies? How do you keep
your work up to date for everyone, and every combination? What happens if
you cannot give out the keys to your application to everyone, even if the
application itself may be free software?

Scalability is the problem; too many intermediaries, too many gatekeepers.
Even if we had a single one, that's still one too many. People using
computers expect to access whatever application they need, at the touch of a
finger or at the click of a pointer; if they cannot get to something in time
for the task they have to complete, they will simply leave and never come
back. Sure, they can probably appreciate the ease of installing 30 different
console text editors, 25 IRC clients, and 12 email clients, all in various
state of disrepair and functionality; it won't really mean much, though,
because they will be using something else by that time.

Of course, now we in the Linux world are in the situation of reimplementing
the past 20 years of mistakes other platforms have made; of course, there
will be growing pains, and **maybe**, if we're careful enough, we can
actually learn for somebody else's blunders, and avoid falling into common
traps. We're going to have new and exciting traps to fall into!

Does this mean it's futile, and that we should just give up on everything
and just go back to our comfort zone? If we did, it would not only be a
disservice to our existing users, but also to the users of every other
platform. Our — and I mean the larger free software ecosystem — proposition
is that we wish all users to have the tools to modify the software they are
using; to ensure that the software in question has not been modified against
their will or knowledge; and to access their own data, instead of merely
providing it to third parties and renting out services with it. We should
have fewer intermediaries, not more. We should push for adoption and access.
We should provide a credible alternative to other platforms.

This will not be easy.

We will need to grow up a lot, and in little time; adopt better standards
than just "it builds on my laptop" or "it works if you have been in the
business for 15 years and know all the missing stairways, and by the way,
isn't that a massive bear trap covered with a tarpaulin on the way to the
goal". Complex upstream projects will have to start caring about things like
reproducibility; licensing; security updates; continuous integration; QA and
validation. We will need to care about stable system services, and backward
compatibility. We will not be shielded by a third party any more.

The good news is: we have a lot of people that know about this stuff, and we
can ask them how to make it work. We can take existing tools and make them
generic and part of our build pipeline, instead of having them inside silos.
We can adopt shared policies upstream instead of applying them downstream,
and twisting software to adapt to all of them.

Again, this won't be easy.

If we wanted easy, though, we would not be making free and open source
software for everyone.

[rb-talk]: https://2017.guadec.org/talks-and-events/#abstract-1-resurrecting_dinosaurs_what_can_possibly_go_wrong
[flatpak-web]: http://flatpak.org
[flathub-web]: https://flathub.org
