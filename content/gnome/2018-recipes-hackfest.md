Title: Recipes hackfest
Slug: recipes-hackfest-2018
Tags: hackfest, recipes, gtk, design
Summary: In which I recap the Recipes hackfest held in Yogyakarta
Date: 2018-03-02 07:13 -0700

The Recipes application started as a celebration of GNOME's community and
history, and it's grown to be a great showcase for what GNOME is about:

 - design guidelines and attention to detail
 - a software development platform for modern applications
 - new technologies, strongly integrated with the OS
 - people-centered development

Additionally, Recipes has become a place where to iterate design and
technology for the rest of the GNOME applications.

Nevertheless, while design patterns, toolkit features, Flatpak and portals,
are part of the development experience, without content provided by the
people using Recipes there would not be an application to begin with.

If we look at the work Endless has been doing on its own
[framework][eos-knowledge-lib] for content-driven applications, there's a
natural fit — which is why I was really happy to attend the [Recipes
hackfest][wiki-hackfest] in Yogyakarta, this week.

{% figure {filename}/images/fried-jawanese-noodles.jpg Fried Jawanese noodle make a healty breakfast %}

In the Endless framework we take structured data — like a web page, or a PDF
document, or a mix of video and text — and we construct "shards", which
embed both the content, its metadata, and a [Xapian][xapian] database that
can be used for querying the data. We take the shards and distribute them
though [Flatpak][flatpak] as a runtime extension for our applications, which
means we can take advantage of Flatpak for shipping updates efficiently.

During the hackfest we talked about how to take advantage of the data model
Endless applications use, as well as its distribution model; instead of
taking tarballs with the recipe text, the images, and the metadata attached
to each, we can create shards that can be mapped to a custom data model.
Additionally, we can generate those shards locally when exporting the
recipes created by new chefs, and easily re-integrate them with the shared
recipe shards — with the possibility, in the future, to have a whole web
application that lets you submit new recipes, and the maintainers review
them without necessarily going through Matthias's email. 😉

The data model discussion segued into how to display that data. The Endless
framework has the concept of [cards][card-video], which are context-aware
data views; depending on context, they can have more or less details exposed
to the user — and all those details are populated from the data model
itself. Recipes has custom widgets that do a very similar job, so we talked
about how to create a shared layer that can be reused both by Endless
applications and by GNOME applications.

{% figure {filename}/images/unnamed-soup.jpg Sadly, I don't remember the name of this soup, only that it had chicken hearts in it, and that Cosimo loved it %}

At the end of the hackfest we were able to have a proof of concept of
Recipes loading the data from a custom shard, and using the Endless
framework to display it; translating that into shareable code and libraries
that can be used by other projects is the next step of the roadmap.

All of this, of course, will benefit more than just the Recipes application.
For instance, we could have a Dictionary application that worked offline,
and used Wiktionary as a source, and allowed better queries than just
substring matching; we could have applications like Photos and Documents
reuse the same UI elements as Recipes for their collection views; Software
and Recipes already share a similar "landing page" design (and widgets),
which means that Software could also use the "card" UI elements.

There's lots for everyone to do, but exciting times are ahead!

{% figure {filename}/images/poolside.jpg And after we're done we can relax by the pool %}

- - - -

I'd be remiss if I didn't thank our hosts at the [Amikom university][amikom].

Yogyakarta is a great city; I've never been in Indonesia before, and I've
greatly enjoyed my time here. There's lots to see, and I strongly recommend
visiting. I've loved the food, and the people's warmth.

I'd like to thank my employer, Endless, for letting me take some time to
attend the hackfest; and the GNOME Foundation, for sponsoring my travel.

{% figure {filename}/images/wilber-in-motion.jpg The travelling Wilber %}

- - - -

![Sponsored by the GNOME Foundation]({filename}/images/sponsored-badge-simple.png)

[eos-knowledge-lib]: https://endlessm.github.io/eos-knowledge-lib
[wiki-hackfest]: https://wiki.gnome.org/Hackfests/Recipes2018
[xapian]: http://xapian.org
[flatpak]: https://flatpak.org
[card-video]: https://vimeo.com/120858063
[amikom]: http://www.amikom.ac.id 
