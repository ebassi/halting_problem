GUADEC 2017
###########

:date: 2017-08-11 13:45 +0100
:modified: 2017-08-11 14:33 +0100
:tags: guadec, gnome, conferences, activities
:category: gnome
:slug: 2017-guadec
:summary: In which I report my activities at GUADEC 2017

Another year, another GUADEC_ — my 13th to date. Definitely not getting
younger, here. 😉

As usual, it was great to see so many faces, old and new. Lots of faces,
as well; attendance has been really good, this year.

The 20th anniversary party was a blast; the venue was brilliant, and
watching people going around the tables in order to fill in slots for the
raffle tickets was hilarious. I loved every minute of it — even if the
'90s music was an assault on my teenage years. See above, re: getting
older.

.. raw:: html

   <blockquote class="twitter-tweet" data-lang="en"><p lang="en" dir="ltr">Waiting for the <a href="https://twitter.com/hashtag/GnomeParty?src=hash">#GnomeParty</a> raffle to begin <a href="https://t.co/BdCQDgV6UZ">pic.twitter.com/BdCQDgV6UZ</a></p>&mdash; Emmanuele Bassi (@ebassi) <a href="https://twitter.com/ebassi/status/891390130900140032">July 29, 2017</a></blockquote>
   <script async src="//platform.twitter.com/widgets.js" charset="utf-8"></script>

The talks were, as usual, stellar. It's always so hard to chose from the
embarrassment of riches that is the submission pool, but every year I
think the quality of what ends up on the schedule is so high that I cannot
be sad.

.. raw:: html

   <blockquote class="twitter-tweet" data-lang="en"><p lang="en" dir="ltr">First <a href="https://twitter.com/hashtag/guadec2017?src=hash">#guadec2017</a> keynote by <a href="https://twitter.com/o0karen0o">@o0karen0o</a> - “The Battle over our technology” <a href="https://t.co/P0WnlASxe1">pic.twitter.com/P0WnlASxe1</a></p>&mdash; Emmanuele Bassi (@ebassi) <a href="https://twitter.com/ebassi/status/890921497937584128">July 28, 2017</a></blockquote>
   <script async src="//platform.twitter.com/widgets.js" charset="utf-8"></script>

.. raw:: html

   <blockquote class="twitter-tweet" data-lang="en"><p lang="en" dir="ltr">Flatpaks for the Flatpak throne! <a href="https://twitter.com/hashtag/guadec2017?src=hash">#guadec2017</a> <a href="https://t.co/RrfLRdlgGN">pic.twitter.com/RrfLRdlgGN</a></p>&mdash; Emmanuele Bassi (@ebassi) <a href="https://twitter.com/ebassi/status/890882943270440960">July 28, 2017</a></blockquote>
   <script async src="//platform.twitter.com/widgets.js" charset="utf-8"></script>

Lots and lots of people were happy to see the Endless_ contingent at the
conference; the talks from my colleagues were really well received, and
I'm sure we're going to see even more collaboration spring from the seeds
planted this year.

----

My talk_ about continuous integration in GNOME was well-received, I think;
I had to speed up a bit at the end because I lost time while connecting to
the projector (not enough juice when on battery to power the HDMI-over-USB
C connector; lesson learned for the next talk). I would have liked to get
some more time to explain what I'd like to achieve with Continuous_.

.. raw:: html

   <figure>
      <figcaption class="image-caption">
        <p>Do not disturb the build sheriff</p>
      </figcaption>
      <div><img src="{filename}/images/do-not-disturb.jpg"/></div>
   </figure>

I ended up talking with many people at the unconference days, in any case.
If you're interested in helping out the automated build of GNOME components
and to improve the reliability of the project, feel free to drop by on
irc.gnome.org (or on Matrix!) in the ``#testable`` channel.

----

The unconference_ days were also very productive, for me. The GTK+ session
was, as usual, a great way to plan ahead for the future; last year we
defined the new `release cycle`_ for GTK+ and jump start the 4.0 development
cycle. This year we drafted a roadmap_ with the remaining tasks.

I talked about Flatpak, FlatHub, Builder, performance in Mutter and GNOME
Shell; I wanted to attend the Rust and GJS sessions, but that would have
required the ability to clone myself, or be in more than one place at once.

During the unconference, I was also able to finally finish the GDK-Pixbuf
port of the build system to Meson_. Testing is very much welcome, before
we bin the Autotools build and bring one of the oldest modules in GNOME
into the future.

Additionally, I was invited to the GNOME Release Team, mostly to deal with
the various continuous integration build issues. This, sadly, does not mean
that I'm one step closer to my ascendance as the power mad dictator of all
of GNOME, but it means that if there are issues with your module, you have
a more-or-less official point of contact.

----

I can't wait for GUADEC 2018! See you all in Almería!

.. _GUADEC:
   https://2017.guadec.org

.. _talk:
   https://ebassi.github.io/2017-guadec

.. _release cycle:
   https://blog.gtk.org/2016/09/01/versioning-and-long-term-stability-promise-in-gtk/

.. _roadmap:
   https://wiki.gnome.org/Projects/GTK%2B/Roadmap/GTK4

.. _Endless:
   https://endlessos.com/

.. _Continuous:
   https://build.gnome.org

.. _unconference:
   https://wiki.gnome.org/GUADEC/2017/Unconference/

.. _Meson:
   http://mesonbuild.com
