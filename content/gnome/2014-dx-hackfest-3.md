Title: Berlin DX Hackfest / Day 3
Slug: 2014-dx-hackfest-3
Date: 2014-05-02
Tags: hackfests, berlin, dx, gtk
Summary: recap from the third and last day of the DX hackfest held in Berlin

the third, and last day of the DX hackfest opened with a quick recap as to what
people have been working on in the past couple of days.

we had a nice lunch nearby, and then we went back to the Endocode office to
tackle the biggest topic: a road map for GTK+.

we made good progress on all the items, and we have a fairly clear idea of who
is going to work on what. sadly, my optimism on GProperty landing soon did not
survive a discussion with Ryan; it turns out that there are many more layers of
yak to be shaved, though we kinda agreed on the assumption that there is, in
fact, a yak underneath all those layers. to be fair, the work on GProperty
enabled a lot of the optimizations of GObject: property notifications, bulk
installation of properties, and the private instance data reorganization of last
year are just examples. both Ryan and I agreed that we should not increase the
cost for callers of property setters — which right now would require asking the
GProperty instance to the class of the instance that we’re modifying, which
implies taking locks and other unpleasant stuff. luckily, we do have access to
private class data, and with few minor modification we can use that private data
to store the properties; thus, getting the properties of a class can be achieved
with simple pointer offsets and dereferences, without locks being involved. I’ll
start working on this very soon, and hopefully we’ll be able to revisit the
issue at GUADEC, in time for the next development cycle of GLib.

in the meantime, I kept hacking on my little helper library that provides data
types for canvases — and about which I’ll blog soon — as well as figuring out
what’s missing from the initial code drop of the GTK+ scene graph that will be
ready to be shown by the time GUADEC 2014 rolls around.

I’m flying back home on Saturday, so this is the last full day in Berlin for me.
it was a pleasure to be here, and I’d really like to thank Endocode for
generously giving us access to their office; Chris Kühl, for being a gracious
and mindful host; and the GNOME Foundation, for sponsoring attendance to all
these fine people and contributors, and me.

![Sponsored by the GNOME Foundation]({filename}/images/sponsored-badge-simple.png)
