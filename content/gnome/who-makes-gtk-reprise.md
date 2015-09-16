Title: Who wrote GTK+ (Reprise)
Slug: who-wrote-gtk-reprise
Date: 2015-09-16
Tags: glib, gtk, development, gnome, who makes gnome
Summary: answering the question of who wrote past releases of GTK, one release at a time

As I've been asked by different people about data from older releases of
GTK+, after the previous article on *Who Wrote GTK+ 3.18*, I ran the
`git-dm` script on every release and generated some more data:

| Release | Lines added | Lines removed | Delta   | Changesets | Contributors |
|---------|------------:|--------------:|--------:|-----------:|-------------:|
| 2.0[^1] |      666495 |        345348 |  321147 |       2503 |          106 |
| 2.2     |      301943 |        227762 |   74181 |       1026 |           89 |
| 2.4     |      601707 |        116402 |  485305 |       2118 |          109 |
| 2.6     |      181478 |         88050 |   93428 |       1421 |          101 |
| 2.8     |       93734 |         47609 |   46125 |       1155 |           86 |
| 2.10    |      215734 |         54757 |  160977 |       1614 |          110 |
| 2.12    |      232831 |         43172 |  189659 |       1966 |          148 |
| 2.14    |      215151 |        102888 |  112263 |       1952 |          140 |
| 2.16    |       71335 |         23272 |   48063 |        929 |          118 |
| 2.18    |       52228 |         23490 |   28738 |       1079 |           90 |
| 2.20    |       80397 |        104504 |  -24107 |        761 |           82 |
| 2.22    |       51115 |         71439 |  -20324 |        438 |           70 |
| 2.24    |        4984 |          2168 |    2816 |        184 |           37 |
| 3.0[^1] |      354665 |        580207 | -225542 |       4792 |          115 |
| 3.2     |      227778 |        168616 |   59162 |       2435 |           98 |
| 3.4     |      126934 |         83313 |   43621 |       2201 |           84 |
| 3.6     |      206620 |         34965 |  171655 |       1011 |           89 |
| 3.8     |       84693 |         34826 |   49867 |       1105 |           90 |
| 3.10    |      143711 |        204684 |  -60973 |       1722 |          111 |
| 3.12    |       86342 |         54037 |   32305 |       1453 |           92 |
| 3.14    |      130387 |        144926 |  -14539 |       2553 |           84 |
| 3.16    |       80321 |         37037 |   43284 |       1725 |           94 |
| 3.18\*  |       78997 |         54614 |   24383 |       1638 |           83 |

Here you can see the history of the GTK releases, since 2.0.

These numbers are to be taken with a **truckload** of salt, especially the
ones from the 2.x era. During the early 2.x cycle, releases did not follow
the GNOME timed release schedule; instead, they were done whenever needed:

| Release | Date           |
|-------- |:---------------|
| 2.0     | March 2002     |
| 2.2     | December 2002  |
| 2.4     | March 2004     |
| 2.6     | December 2004  |
| 2.8     | August 2005    |
| 2.10    | July 2006      |
| 2.12    | September 2007 |
| 2.14    | September 2008 |
| 2.16    | March 2009     |
| 2.18    | September 2009 |
| 2.20    | March 2010     |
| 2.22    | September 2010 |
| 2.24    | January 2011   |

Starting with 2.14, we settled to the same cycle as GNOME, as it made
releasing GNOME and packaging GTK+ on your favourite distribution a lot
easier.

This disparity in the length of the development cycles explains why the 2.12
and 2.14 cycles, which lasted a year, represent an anomaly in terms of
contributors (148 and 140, respectively) and in terms of absolute lines
changed.

The reduced activity between 2.20 and 2.24.0 is easily attributable to the
fact that people were working hard on the 2.90 branch that would become 3.0.

In general, once you adjust by release time, it's easy to see that the
amount of contributors is pretty much stable at around 90:

{%figure {filename}/images/gtk-contributors.png The average is 94.5, which means we have an hobbit somewhere in the commit log %}

Another interesting data point would be to look at the ecosystem of
companies spawned around GTK+ and GNOME, and how it has changed over the
years — but that's part of a larger discussion that would probably take more
than a couple of blog posts to unpack.

I guess the larger point is that GTK+ is definitely not dying; it's pretty
much being worked on by the same *amount* of people — which include long
timer as well as newcomers — as it was during the 2.x cycle.

[^1]: Both 2.0 and 3.0 are not wholly accurate; I used, as a starting point
      for the changeset period, the previous *released* branch point; for
      GTK+ 2.0, I started from the `GTK_1_3_1` tag, whereas for GTK+ 3.0
      I used the `2.90.0` tag. There are commits preceding both tags, but
      not enough to skew the results.
