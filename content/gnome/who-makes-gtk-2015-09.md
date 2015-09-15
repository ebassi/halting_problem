Title: Who wrote GTK+ 3.18
Slug: who-wrote-gtk-3-18
Date: 2015-09-15
Tags: glib, gtk, development, gnome, who makes gnome
Summary: a recap of the contributions to the GTK+ 3.18 development cycle
Abstract: This may be a recurring series at the end of each development cycle, to sum up who worked on the core of the GNOME platform. Matthias is very good at blogging about the changes in GTK, with lots of screenshots, but I want to concentrate on who contributed what, in the spirit of the LWN series on the Linux kernel.

It's common "knowledge" in the Internet Peanut Gallery that GTK+ is "dead"
or "dying" — I assume in the same sense that NetCraft certified that BSD is
dead. It'd be (and, in point of fact, it *is*) easy to dismiss these rumors;
it's not like they come with actual numbers and trends, because the gods of
old never mentioned the requirement for comments on the Internet to be cogent,
let alone factually true, when they laid down the various RFCs.

On the other hand, not having an actual answer is a bit of a self-serving
argument on the side of people, like me, that actually contribute to GTK+ and
to the GNOME core platform; it allows a bit of leeway when we ask for help,
contributions, or simply for decent bug reports — "we don't have enough
resources, so if you want your pet bug fixed, or feature implemented, you'll
have to help us help you". Not that having actual numbers would change that;
after all, resources are not infinite, and there are a ton of bugs that need
to be fixed — including ones that require [a time machine](https://bugzilla.gnome.org/show_bug.cgi?id=171940).

As much as I wanted to dispel the rumors about the impending death of GTK+,
my goal was definitely to provide numbers on how much gets done every six
months in the core GNOME platform, thus honoring the people that work hard
on it. Having numbers also allows us to quantify what kind of help we need, so
that, the next time somebody complains that we don't work hard enough on fixing
*ALL* the bugs, at least we'll have a handy way to point out how much we work
already.

To gather the data, I've used the most excellent [`git-dm`](http://repo.or.cz/w/git-dm.git) tool that Jonathan
Corbet wrote for the "Who wrote the Linux kernel" columns for LWN.

### Activity

To provide a baseline, this is how the development activity looked like during
the GNOME 3.14 and 3.16 cycles, i.e. during the past year:

          Version       Lines added   Lines removed   Delta   Developers
    GLib  2.42          17195         9934            7261    61
    GLib  2.44          12504         2240            10264   49
    GTK+  3.14          130387        144945         -14558   84
    GTK+  3.16          80321         37043           43278   94

*Note*: the numbers do not include the translation work; as much as
translations are an important part of our stack, they tend to skew any
statistic, given the sheer size of lines touched.

The 3.14 cycle is an outlier for GTK+ because of the move of Adwaita in tree,
as well as the GTK+ Inspector.

For the 3.18 cycle, the numbers up to September 15th are:

          Version       Lines added   Lines removed   Delta   Developers
    GLib  2.46          19763         12437           7326    50
    GTK+  3.18          78676         54508           24168   83

As you can see, the numbers are mostly stable, in terms for code changes and
number of developers.

### Contributors

Of the 50 developers that contributed the 355 changesets of GLib during the
3.18 cycle, the most active are:

| Name               | Per changeset | Name               | Per changed lines |
|:-------------------|--------------:|:-------------------|------------------:|
| Matthias Clasen    |    89 (25.9%) | Руслан Ижбулатов   |      7337 (27.6%) |
| Philip Withnall    |    50 (14.5%) | Ryan Lortie        |      5709 (21.5%) |
| Ryan Lortie        |    31  (9.0%) | Chun-wei Fan       |      3426 (12.9%) |
| Dan Winship        |    29  (8.4%) | Matthias Clasen    |      2881 (10.8%) |
| Simon McVittie     |    19  (5.5%) | Philip Withnall    |      1729  (6.5%) |
| Chun-wei Fan       |    14  (4.1%) | Dan Winship        |      1590  (6.0%) |
| Руслан Ижбулатов   |    11  (3.2%) | Simon McVittie     |       867  (3.3%) |
| Mikhail Zabaluev   |     8  (2.3%) | Alexander Larsson  |       648  (2.4%) |
| Ting-Wei Lan       |     8  (2.3%) | Paolo Borelli      |       588  (2.2%) |
| Garrett Regier     |     6  (1.7%) | TingPing           |       358  (1.3%) |
| Alexander Larsson  |     5  (1.5%) | Janusz Lewandowski |       313  (1.2%) |
| Michael Catanzaro  |     5  (1.5%) | Mikhail Zabaluev   |       256  (1.0%) |
| Emmanuele Bassi    |     5  (1.5%) | Iain Lane          |       130  (0.5%) |
| Christophe Fergeau |     5  (1.5%) | Garrett Regier     |       128  (0.5%) |
| Paolo Borelli      |     5  (1.5%) | Michael Catanzaro  |       106  (0.4%) |
| Piotr Drąg         |     4  (1.2%) | Richard Hughes     |        97  (0.4%) |
| Kalev Lember       |     4  (1.2%) | Emmanuele Bassi    |        70  (0.3%) |
| Iain Lane          |     4  (1.2%) | Xavier Claessens   |        48  (0.2%) |
| TingPing           |     4  (1.2%) | Ross Lagerwall     |        35  (0.1%) |
| Rico Tzschichholz  |     3  (0.9%) | Ting-Wei Lan       |        32  (0.1%) |

Руслан Ижбулатов has been working on the Windows support, ensuring that the
library and test suites work correctly there. Chun-wei Fan has been fixing
the project files for building GLib (and GTK+, as well as a lot of libraries
in the GNOME stack) with Microsoft Visual Studio and the Microsoft Visual C
Compiler. Philip Withnall has been hard at work on the API reference and
GObject tutorial, incorporating the feedback he got from clients at Collabora.
Dan Winship and Michael Catanzaro have been working on the certificate API
inside GIO, even though the bulk of the work has been going on inside the
external glib-networking module. Simon McVittie has been working on GDBus; on
the testing API; and has been incorporating patches coming from the Debian
project.

For GTK+, on the other hand, the most active of the 83 contributors are:

| Name                          | Per changeset | Name                          | Per changed lines |
|:------------------------------|--------------:|:------------------------------|------------------:|
| Matthias Clasen               |   811 (49.8%) | Matthias Clasen               |     37393 (37.3%) |
| Benjamin Otte                 |   184 (11.3%) | Chun-wei Fan                  |     22644 (22.6%) |
| Carlos Garnacho               |   107  (6.6%) | Benjamin Otte                 |     10991 (11.0%) |
| Cosimo Cecchi                 |    40  (2.5%) | Jakub Steiner                 |      4762  (4.7%) |
| Jakub Steiner                 |    37  (2.3%) | Georges Basile Stavracas Neto |      3879  (3.9%) |
| Lapo Calamandrei              |    35  (2.1%) | Carlos Soriano                |      3827  (3.8%) |
| Emmanuele Bassi               |    33  (2.0%) | Lapo Calamandrei              |      3208  (3.2%) |
| Carlos Soriano                |    30  (1.8%) | Carlos Garnacho               |      2690  (2.7%) |
| Timm Bäder                    |    29  (1.8%) | Руслан Ижбулатов              |      1480  (1.5%) |
| Chun-wei Fan                  |    24  (1.5%) | Alexander Larsson             |      1001  (1.0%) |
| William Hua                   |    24  (1.5%) | William Hua                   |       947  (0.9%) |
| Alexander Larsson             |    23  (1.4%) | Cosimo Cecchi                 |       704  (0.7%) |
| Georges Basile Stavracas Neto |    23  (1.4%) | Paolo Borelli                 |       671  (0.7%) |
| Jonas Ådahl                   |    19  (1.2%) | Jasper St. Pierre             |       627  (0.6%) |
| Christian Hergert             |    17  (1.0%) | Christian Hergert             |       592  (0.6%) |
| Piotr Drąg                    |    17  (1.0%) | Sebastien Lafargue            |       570  (0.6%) |
| Paolo Borelli                 |    17  (1.0%) | Emmanuele Bassi               |       556  (0.6%) |
| Christoph Reiter              |    14  (0.9%) | Jonas Ådahl                   |       543  (0.5%) |
| Руслан Ижбулатов              |    13  (0.8%) | Christoph Reiter              |       488  (0.5%) |
| Jasper St. Pierre             |    11  (0.7%) | Ryan Lortie                   |       424  (0.4%) |

While Benjamin is hard at work at improving the correctness and performance of
the style machinery inside GTK+, Jakub and Lapo are constantly trying to find
ways to make Adwaita and the High Constrast themes push the boundaries of the
same style machinery. Carlos Soriano and Georges Basile Stavracas Neto have
been working on the components of the file selection dialog following the new
designs from Allan Day, for the Google Summer of Code; the code is going to be
shared between GTK+ and Nautilus, to improve consistency between Nautilus and
the `GtkFileChooser` widget, and keep bugs to a minimum. Carlos Garnacho has
worked on input — mostly the support for touchpad on Wayland. Also on Wayland,
Jonas Ådahl has been working on bug fixing and feature parity in GDK between
Wayland and X11.

From a company perspective, Red Hat still dominates, as it employs many of the
more prolific contributors; nevertheless, it's important to note that a larger
number of developers are unaffiliated, or contribute to GLib and GTK+ in their
own time:

#### GLib
                     Per changeset                          Per lines
    Red Hat            138 (40.1%)      (Unknown)       12892 (48.5%)
    (Unknown)           95 (27.6%)      Canonical        5794 (21.8%)
    Collabora           65 (18.9%)      Red Hat          5222 (19.6%)
    Canonical           37 (10.8%)      Collabora        2574  (9.7%)
    Endless              6  (1.7%)      Endless            72  (0.3%)
    Centricular          2  (0.6%)      Centricular        28  (0.1%)

        Per contributor (total 52)
    (Unknown)           32 (61.5%)
    Red Hat             10 (19.2%)
    Canonical            3  (5.8%)
    Collabora            2  (3.8%)
    Endless              2  (3.8%)
    Centricular          2  (3.8%)

#### GTK+

                     Per changeset                          Per lines
    Red Hat           1230 (75.5%)      Red Hat         61725 (61.6%)
    (Unknown)          340 (20.9%)      (Unknown)       36845 (36.7%)
    Endless             43  (2.6%)      Endless          1181  (1.2%)
    Canonical           13  (0.8%)      Canonical         491  (0.5%)
    Collabora            2  (0.1%)      Collabora          19  (0.0%)
    Intel                1  (0.1%)      Intel               2  (0.0%)

        Per contributor (total 85)
    (Unknown)           58 (68.2%)
    Red Hat             19 (22.4%)
    Canonical            3  (3.5%)
    Endless              2  (2.4%)
    Collabora            2  (2.4%)
    Intel                1  (1.2%)

### Conclusions

One of the most obvious conclusions that I can draw from these numbers is that
GLib and GTK+ are definitely capable of retaining existing contributors — you
just need to look at the names in the top committers and check how many GUADECs
they have attended; what's less obvious is the capacity of acquiring and
retaining new contributors. For the latter, the Summer of Code and Outreachy
programs are definitely a great resource. Carlos and Georges have been working
their way down the stack at an impressive speed, and are now responsible for
core functionality.

In terms of contributions, I think the code base has long since reached a point
where it cannot be increased without also increasing the number of stable
contributors. This is not a bad thing, per se; GLib and GTK+ are not the Linux
kernel; we cannot add widgets like the kernel adds drivers, or file systems. It
is mostly clear, though, that new functionality must come with new people that
take responsibility for it, or at the expense of deprecating old API.
