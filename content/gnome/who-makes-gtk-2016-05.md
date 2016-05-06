Title: Who wrote GTK+ 3.20
Slug: who-wrote-gtk-3-20
Date: 2016-05-06
Tags: glib, gtk, development, gnome, who makes gnome
Summary: a recap of the contributions to the GTK+ 3.20 development cycle
Abstract: A bit late recap of the 3.20 development cycle, now that we already started working on 3.22, but I guess better late than never

Last time I tried to dispel the notion that GTK+ is dead or dying. Others
have also [chimed in][csoriano-nautilus], and it seems that we're picking
up the pace into making GTK a more modern, more useful driving force into
the Linux desktop ecosystem.

Let's see how much has changed in the six months of the 3.20 development
cycle.

Once again, to gather the data, I've used the most excellent [`git-dm`](http://repo.or.cz/w/git-dm.git)
tool that Jonathan Corbet wrote for the "Who wrote the Linux kernel" columns
for LWN. As usual, I've purposefully skipped the commits dealing with
translations, to avoid messing up the statistics.

You should look at my [previous article][ebassi-gtk-3-18] as a comparison
point.

### Activity

For the 3.20 cycle, the numbers are:

|      | Version | Lines added | Lines removed | Delta | Contributors |
|------|---------|------------:|--------------:|------:|-------------:|
| GLib | 2.48    |       20597 |          7544 | 13053 |           55 |
| GTK+ | 3.20    |      158427 |        117823 | 40604 |           81 |

More or less stable in terms of contributors, but as you can see the number
of lines added and removed has doubled. This is definitely the result of the
changes in the CSS machinery that have (finally) brought it to a stable as
well as more featureful state.

### Contributors

#### GLib

Of the 55 developers that contributed the 271 changesets of GLib during the
3.20 development cycle, the most active are:

| Name                    | Per changeset | Name                    | Per changed lines |
|:------------------------|--------------:|:------------------------|------------------:|
| Ignacio Casal Quinteiro |    56 (20.7%) | Ignacio Casal Quinteiro |      8530 (39.7%) |
| Philip Withnall         |    42 (15.5%) | Philip Withnall         |      5402 (25.1%) |
| Allison Ryan Lortie     |    27 (10.0%) | Matthias Clasen         |      3228 (15.0%) |
| Chun-wei Fan            |    22  (8.1%) | Chun-wei Fan            |      1440  (6.7%) |
| Matthias Clasen         |    18  (6.6%) | Allison Ryan Lortie     |      1338  (6.2%) |
| Dan Winship             |     9  (3.3%) | Javier Jardón           |       565  (2.6%) |
| Mikhail Zabaluev        |     7  (2.6%) | Iain Lane               |       149  (0.7%) |
| Marc-André Lureau       |     6  (2.2%) | Ruslan Izhbulatov       |       147  (0.7%) |
| Ruslan Izhbulatov       |     6  (2.2%) | Dan Winship             |        95  (0.4%) |
| Rico Tzschichholz       |     6  (2.2%) | Lars Uebernickel        |        79  (0.4%) |
| Xavier Claessens        |     6  (2.2%) | Xavier Claessens        |        74  (0.3%) |
| Emmanuele Bassi         |     5  (1.8%) | Christian Hergert       |        71  (0.3%) |
| Iain Lane               |     4  (1.5%) | Mikhail Zabaluev        |        48  (0.2%) |
| Lars Uebernickel        |     3  (1.1%) | Rico Tzschichholz       |        45  (0.2%) |
| Sébastien Wilmet        |     3  (1.1%) | Daiki Ueno              |        42  (0.2%) |
| Simon McVittie          |     3  (1.1%) | Simon McVittie          |        27  (0.1%) |
| Javier Jardón           |     3  (1.1%) | Emmanuele Bassi         |        25  (0.1%) |
| Christian Hergert       |     3  (1.1%) | Robert Ancell           |        23  (0.1%) |
| coypu                   |     2  (0.7%) | Marc-André Lureau       |        14  (0.1%) |
| Sebastian Geiger        |     2  (0.7%) | Jan de Groot            |        14  (0.1%) |

Ignacio has been hard at work, helped by Ruslan and Fan, in making 2.48 the
best GLib release ever in terms of supporting Windows — both for cross
and native compilation, using autotools and the Microsoft Visual C compiler
suite. If you can build an application for Windows as reliably as you can on
Linux, it's because of the work of them.

#### GTK+

For GTK+, on the other hand, the most active of the 81 contributors are:

| Name                    | Per changeset | Name                    | Per changed lines |
|:------------------------|--------------:|:------------------------|------------------:|
| Matthias Clasen         |  1220 (43.7%) | Matthias Clasen         |     78960 (41.1%) |
| Benjamin Otte           |   472 (16.9%) | Benjamin Otte           |     35975 (18.7%) |
| Lapo Calamandrei        |   203  (7.3%) | Lapo Calamandrei        |     35352 (18.4%) |
| Cosimo Cecchi           |   167  (6.0%) | Cosimo Cecchi           |     10408  (5.4%) |
| Carlos Garnacho         |   147  (5.3%) | Jakub Steiner           |      6927  (3.6%) |
| Timm Bäder              |   107  (3.8%) | Carlos Garnacho         |      5334  (2.8%) |
| Emmanuele Bassi         |    41  (1.5%) | Alexander Larsson       |      3128  (1.6%) |
| Paolo Borelli           |    39  (1.4%) | Chun-wei Fan            |      2394  (1.2%) |
| Ruslan Izhbulatov       |    29  (1.0%) | Paolo Borelli           |      1771  (0.9%) |
| Carlos Soriano          |    28  (1.0%) | Ruslan Izhbulatov       |      1635  (0.9%) |
| Jakub Steiner           |    26  (0.9%) | Timm Bäder              |      1326  (0.7%) |
| Olivier Fourdan         |    26  (0.9%) | Takao Fujiwara          |      1269  (0.7%) |
| Jonas Ådahl             |    23  (0.8%) | Jonas Ådahl             |      1243  (0.6%) |
| Chun-wei Fan            |    22  (0.8%) | Emmanuele Bassi         |       885  (0.5%) |
| Piotr Drąg              |    18  (0.6%) | Olivier Fourdan         |       646  (0.3%) |
| Ray Strode              |    18  (0.6%) | Ray Strode              |       570  (0.3%) |
| Ignacio Casal Quinteiro |    16  (0.6%) | Sébastien Wilmet        |       494  (0.3%) |
| William Hua             |    16  (0.6%) | Carlos Soriano          |       427  (0.2%) |
| Alexander Larsson       |    14  (0.5%) | Ignacio Casal Quinteiro |       333  (0.2%) |
| Christoph Reiter        |    10  (0.4%) | William Hua             |       321  (0.2%) |

Benjamin has worked on the new [CSS gadget][mclasen-css-gadgets] internal
API; Matthias, Cosimo, and Timm have worked on porting existing widgets to
it, in order to validate the API. Lapo and Jakub have worked on updating
Adwaita and the other in tree themes to the new style declarations.

Carlos Soriano has worked on the widgets shared between the file chooser
dialog and Nautilus.

Carlos Garnacho has worked on the input layer in GDK, in order to make it
behave correctly under the new world order of Wayland; and speaking of
Wayland, Carlos, Jonas, and Olivier have worked really hard to implement
all the missing features in the Wayland backend, as well as the fallout of
the Wayland switch when it comes to window sizing and positioning.

### Affiliation

#### GLib

| Affiliation | Per changeset | Affiliation | Per lines     | Affiliation | Per contributor (total 55)|
|-------------|--------------:|-------------|--------------:|-------------|--------------------------:|
| (Unknown)   |   136 (50.2%) | (Unknown)   | 10942 (50.9%) | (Unknown)   |                35 (60.3%) |
| Collabora   |    49 (18.1%) | Collabora   |  5491 (25.6%) | Red Hat     |                 9 (15.5%) |
| Canonical   |    41 (15.1%) | Red Hat     |  3398 (15.8%) | Canonical   |                 5  (8.6%) |
| Red Hat     |    36 (13.3%) | Canonical   |  1612  (7.5%) | Collabora   |                 4  (6.9%) |
| Endless     |     6  (2.2%) | Endless     |    34  (0.2%) | Endless     |                 2  (3.4%) |
| Centricular |     1  (0.4%) | Centricular |     4  (0.0%) | Centricular |                 1  (1.7%) |
| Intel       |     1  (0.4%) | Intel       |     2  (0.0%) | Intel       |                 1  (1.7%) |
| Novell      |     1  (0.4%) | Novell      |     1  (0.0%) | Novell      |                 1  (1.7%) |

As usual, GLib is a little bit more diverse, in terms of employers, because
of its versatility and use in various platforms.

#### GTK+

| Affiliation | Per changeset | Affiliation | Per lines      | Affiliation | Per contributor (total 81)|
|-------------|--------------:|-------------|---------------:|-------------|--------------------------:|
| Red Hat     |  1940 (69.5%) | Red Hat     | 131833 (68.7%) | (Unknown )  |                63 (75.9%) |
| (Unknown)   |   796 (28.5%) | (Unknown)   |  59204 (30.8%) | Red Hat     |                15 (18.1%) |
| Endless     |    41  (1.5%) | Endless     |    885  (0.5%) | Canonical   |                 4  (4.8%) |
| Canonical   |    13  (0.5%) | Canonical   |    104  (0.1%) | Endless     |                 1  (1.2%) |

Not many changes in these tables, but if your company uses the GNOME core
platform and you wish to have a voice in where the platform goes, you should
really consider contributing employee time to work upstream.

It is also very important to note that, while Red Hat still retains the
majority of commits, the vast majority of committers are unaffiliated.

### Methodology

The command line I used for `gitdm` is:

```
git log \
 --numstat \
 -M $START..$END | \
 gitdm -r '.*(?<!po)$' -l 20 -u -n
```

For GLib, I started from commit [37fcab17](https://git.gnome.org/browse/glib/commit/?id=37fcab17)
which contains the version bump to 2.47, and ended on the 2.48.0 tag.

For GTK+, I started from commit [2f0d4b68](https://git.gnome.org/browse/gtk+/commit/?id=2f0d4b68)
which contains the first new API of the 3.19 cycle and precedes the version
bump, and ended on the 3.20.0 tag.

The only changes to the `gitdm` stock configuration are the addition of a
couple of email/name/employer association; I can publish them on request.

[csoriano-nautilus]: https://csorianognome.wordpress.com/2016/05/04/nautilus-gtk-status-1-year-of-progress/
[ebassi-gtk-3-18]: https://www.bassi.io/articles/2015/09/15/who-wrote-gtk-3-18/
[mclasen-css-gadgets]: https://blogs.gnome.org/mclasen/2015/12/22/css-boxes-in-gtk/
