Title: GTK+ Hackfest 2013
Date: 2013-04-20
Slug: gtk-hackfest-2013
Tags: hackfests, gtk
Summary: recap of the first two days of the 2013 GTK+ hackfest in Boston

### Day 1

it turns out that this week wasn’t the best possible to hold a hackfest in
Boston and Cambridge; actually, it was the worst. what was supposed to be
the first day passed with us hacking in various locations, mostly from home,
or hotel lobbies. nevertheless, there were interesting discussions on
experimental work, like a rework of the drawing and content scrolling model
that Alex is working on.

- - -

### Day 2

_or Day 1 redux_

with the city-wide lockdown revoked, we finally managed to meet up at the
OLPC offices and start the discussion on Wayland, input, and compatibility;
we took advantage of Kristian attending so we could ask questions about
client-side decorations, client-side shadows, and Wayland compatibility. we
also discussed clipboard, and drag and drop, and the improvements in the API
that will be necessary when we switch to Wayland — right now, both clipboard
and DnD are pretty tied to the X11 implementation and API.

after lunch, the topic moved to EggListBox and EggFlowBox: scalability,
selection, row containers, CSS style propagation, and accessibility.

we also went over a whole set of issues, like positioning popups; high
resolution displays; input methods; integrating the Gd widgets into GTK+,
and various experimental proposals that I’m sure will be reported by their
authors on Planet GNOME soon. :-) it was mostly high level discussion, to
frame the problems and bring people up to speed with each problem space and
potential/proposed solutions.

we’d all want to thank OLPC, and especially Walter Bender, for being
gracious hosts at their office in Cambridge, even on a weekend, and the GNOME
Foundation for sponsoring the event.
