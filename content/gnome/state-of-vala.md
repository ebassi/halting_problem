Title: On Vala
Date: 2017-02-13 13:12 +0000
Summary: In which I look at the state of Vala and hope for some introspection to happen
Tags: vala, development, languages, gnome

It seems I raised a bit of a stink on Twitter last week:

<blockquote class="twitter-tweet" data-lang="en"><p lang="en" dir="ltr">PSA: if you want to write a new <a href="https://twitter.com/gnome">@gnome</a> application, don&#39;t use Vala; if you&#39;re already using it, consider porting to a non-dead language.</p>&mdash; Emmanuele Bassi (@ebassi) <a href="https://twitter.com/ebassi/status/827482509982195712">February 3, 2017</a></blockquote>
<script async src="//platform.twitter.com/widgets.js" charset="utf-8"></script>

Of course, and with reason, I've been called out on this by various people.
Luckily, it was on Twitter, so we haven't seen articles on Slashdot and
Phoronix and LWN with headlines like "GNOME developer says Vala is dead and
will be removed from all servers for all eternity and you all suck". At
least, I've only seen a bunch of comments on Reddit about this, but nobody
cares about that particular cesspool of humanity.

Sadly, 140 characters do not leave any room for nuance, so maybe I should
probably clarify what I wrote on a venue with no character limit.

First of all, I'd like to apologise to people that felt I was attacking them
or their technical choices: it was not my intention, but see above, re:
character count. I may have only about 1000 followers on Twitter, but it
seems that the network effect is still a bit greater than that, so I should
be careful when wording opinions. I'd like to point out that it's my private
Twitter account, and you can only get to what it says if you follow me, or
if you follow people who follow me and decide to retweet what I write.

My PSA was intended as a reflection on the state of Vala, and its impact on
the GNOME ecosystem in terms of newcomers, from the perspective of a person
that used Vala for his own personal projects; recommended Vala to newcomers;
and has to deal with the various build issues that arise in GNOME because
something broke in Vala or in projects using Vala. If you're using Vala
outside of GNOME, you have two options: either ignore all I'm saying, as it
does not really apply to your case; or do a bit of soul searching, and see
if what I wrote **does** indeed apply to you.

First of all, I'd like to qualify my assertion that Vala is a "dead
language". Of course people see activity in the [Git repository][vala-git],
see the recent commits and think "the project is still alive". Recent
commits do not tell a complete story.

Let's look at the project history for the past 10 cycles (roughly 2.5
years). These are the commits for every cycle, broken up in two values: one
for the full repository, the other one for the whole repository *except* the
`vapi` directory, which contains the VAPI files for language bindings:

![Commits]({filename}/images/vala-repo-commits.png)

Aside from the latest cycle, Vala has seen very little activity; the project
itself, if we exclude binding updates, has seen less than 100 commits for
every cycle — some times even far less. The latest cycle is a bit of an
outlier, but we can notice a pattern of very little work for two/three
cycles, followed by a spike. If we look at the currently in progress cycle,
we can already see that the number of commits has decreased back to 55/42,
as of this morning.

![Commits]({filename}/images/vala-repo-commits-2.png)

Number of commits is just a metric, though; more important is the number of
contributors. After all, small, incremental changes may be a good thing in a
language — though, spoiler alert: they are usually an indication of a series
of larger issues, and we'll come to that point later.

These are the number of developers over the same range of cycles, again
split between committers to the full repository and to the full repository
minus the `vapi` directory:

![Developers]({filename}/images/vala-repo-developers.png)

As you can see, the number of authors of changes is mostly stable, but still
low. If we have few people that actively commit to the repository it means
we have few people that can review a patch. It means patches linger longer
and longer, while reviewers go through their queues; it means that
contributors get discouraged; and, since nobody is paid to work full time on
Vala, it means that any interruption caused by paid jobs will be a
bottleneck on the project itself.

These concerns are not unique of a programming language: they exist for
every volunteer-driven free and open source project. Programming languages,
though, like core libraries, are problematic because any bottleneck causes
ripple effects. You can take any stalled project you depend on, and vendor
it into your own, but if that happens to the programming language you're
using, then you're pretty much screwed.

For these reasons, we should also look at how well-distributed is the
workload in Vala, i.e. which percentage of the work is done by the authors
of those commits; the results are **not** encouraging. Over that range of
cycles, Only two developers routinely crossed the 5% of commits:

  * Rico Tzschichholz
  * Jürg Billeter

And Rico has been the only one to consistently author >50% of the commits.
This means there's only one person dealing with the project on a day to day
basis.

As the maintainer of a project who basically had to do all the work, I
cannot even begin to tell you how soul-crushing that can become. You get
burned out, and you feel responsible for everyone using your code, and then
you get burned out some more. I honestly don't want Rico to burn out, and
you shouldn't, either.

So, let's go into unfair territory. These are the commits for
[Rust][rust-web] — the compiler and standard library:

![Rust]({filename}/images/rust-commits.png)

These are the commits for [Go][go-web] — the compiler and base library:

![Go]({filename}/images/go-commits.png)

These are the commits for Vala — both compiler and bindings:

![Vala]({filename}/images/vala-commits.png)

These are the number of commits over the past **year**. Both languages are
younger than Vala, have more tools than Vala, and are more used than Vala.
*Of course*, it's completely unfair to compare them, but those numbers
should give you a sense of scale, of what is the current high bar for a
successful programming language these days. Vala is a niche language, after
all; it's heavily piggy-backing on the GNOME community because it transpiles
to C and needs a standard library and an ecosystem like the one GNOME
provides. I never expected Vala to rise to the level of mindshare that Go
and Rust currently occupy.

Nevertheless, we need to draw some conclusions about the current state of
Vala — starting from [this thread][vala-future-mail], perhaps, as it best
encapsulates the issues the project is facing.

Vala, as a project, is limping along. There aren't enough developers to
actively effect change on the project; there aren't enough developers to
work on ancillary tooling — like build system integration, debugging and
profiling tools, documentation. Saying that "Vala compiles to C so you can
use tools meant for C" is comically missing the point, and it's effectively
like saying that "C compiles to binary code, so you can disassemble a
program if you want to debug it". Being able to inspect the language using
tools native to the language is a powerful thing; if you have to do the name
mangling in your head in order to set a breakpoint in GDB you are elevating
the barrier of contributions way above the head of many newcomers.

Being able to effect change means also being able to introduce change
effectively and without fear. This means things like continuous integration
and a full test suite heavily geared towards regression testing. The test
suite in Vala is made of 210 units, for a total of 5000 lines of code; the
code base of Vala (vala AST, codegen, C code emitter, and the compiler) is
nearly 75 thousand lines of code. There is no continuous integration,
outside of the one that GNOME Continuous performs when building Vala, or the
one GNOME developers perform when using jhbuild. Regressions are found after
days or weeks, because developers of projects using Vala update their
compiler and suddenly their projects cease to build.

I don't want to minimise the enormous amount of work that every Vala
contributor brought to the project; they are heroes, all of them, and they
deserve as much credit and praise as we can give. The idea of a
project-oriented, community-oriented programming language has been
vindicated many times over, in the past 5 years.

If I scared you, or incensed you, then you can still blame me, and my lack
of tact. You can still call me an asshole, and you can think that I'm
completely uncool. What I do hope, though, is that this blog post pushes
you into action. Either to contribute to Vala, or to re-new your commitment
to it, so that we can look at my words in 5 years and say "boy, was
Emmanuele wrong"; or to look at alternatives, and explore new venues in
order to make GNOME (and the larger free software ecosystem) better.

[vala-future-mail]: https://mail.gnome.org/archives/vala-list/2016-September/msg00001.html
[vala-git]: https://git.gnome.org/browse/vala
[rust-web]: https://www.rust-lang.org/
[go-web]: https://golang.org/
