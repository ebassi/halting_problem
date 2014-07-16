Title: Building a website with Pelican
Slug: building-a-website-with-pelican
Status: draft
Category: life
Tags: essays, pelican, blagging, things I do so you don't have to
Abstract: creating complex, structured websites is a pain, that's why somebody invented a language to help out doing that; except that the language is PHP and it's full of bees and snakes, and if you're extremely lucky,  it just helps some kid in Russia to take over your server to mine bitcoin or scam you out of your credit card details.
Summary: if the alternative to nothing is a monstrosity in PHP, then nothingness is a great state in which we ought to be

once upon a time, I wrote a static website generator.

it was my first sizeable Perl application, and my second one using the GTK+
2.x Perl bindings. yes, my website generator had a GUI with an embedded text
editor and a list of all articles. I was 20-something, naïve, and had access
to CPAN — a combination that can only lead to the sentence "this should just
not happened", quickly followed by "I hope it didn't suffer too much for too
long" spoken in the general direction of a server somewhere.

at the time, I only had some space on a web server provided by my ISP, which
meant no fancy CGI stuff, or database, or dynamic web page. [WordPress][wp]
was still known as "b2", and it had pretty much the same feature-to-security
ratio as it has today. I had the option of using one of the budding blogging
platforms of the time, but they were pretty much consistently terrible, and
in the end I did not need anything special; so, I did what any
self-respecting procrastinator with a penchant for software engineering can
do when faced with a goal and no deadlines: I wrote my own script, then I
wrote a module to abstract the script I wrote, then I wrote a framework that
allowed me to write modules to abstract scripts. I was almost at the
"re-engineer my DNA to allow me to create better copies of myself" step of
the process when I decided I *actually* needed a comment form — see above,
re: naïve 20-something — which meant getting a some actual web space
somewhere. clearly, there was something wrong with me.

fast forward more than 10 years to last February, and me waking up in Sydney
with the hosting provider for my private server telling me that I was
serving credit card scam pages. after cleaning up everything, and restoring
from a back up, I got hacked by a script kiddie that figured it could
use my server hosted on a severely restricted VM to mine bitcoin. not the
smartest kid on the Internet, I grant you that.

now, this could be easily attributed to the fact that I barely have time to
do a proper sysadmin job, and you wouldn't be *that* off; fact is, I *do*
have a day job, and you may be shocked to know that it's not administering a
web server. to be precise, my daily mansions do not include managing two
WordPress installations, a MySQL instance, and an Apache web server, as well
as the operating system that runs them; they also do not include maintaining
those installations secured and keeping up with a ton of CVEs. on the other
hand, this whole mess can also be attributed to the fact that a platform for
content on the web should *probably* not have the capacity of allowing third
parties to control your server unless you keep updating it every month.

since nobody is paying me to actually handle this stuff, and since I'm doing
this in the copious (_haha_) amounts of time I have left in my life, I can
either blame my tools, while still using them, or do the right thing, and
change tools — possibly with tools that do not require full time
maintainership.

my first instinct was to just write a couple of scripts, generate my pages
from them, and back everything up with a Git repository; I actually spent a
bunch of time looking at existing stuff to build those scripts, and came
pretty close to committing to that plan. when I realized I was actually
starting a markdown parser library *in C*, I backed the fuck away from my
keyboard, opened a beer, and watched about four episodes of
[Nichijō][wiki-nichijou] back to back, in order to realize what a
spectacularly bad idea I had. I went back to the drawing board, and drafted
up the requirements for this adventure.

I was pretty much dead set on a static website, so I fired up the browser,
looked for _"list of open source static web site generators"_ and clicked on
[the first link I got][static-web]. I didn't want to install Ruby on my
local machine, and at the first mention of "hand-crafted" I had to reach for
my nerf gun. while I don't have a philosophical objection to node.js, I also
wanted to avoid downloading the entire GitHub mirror of node.js modules. I
think I laughed enough to pass out, because I don't have any memory of
looking at the Haskell website generators. I don't particularly like Python,
but since there were only two options in Perl, in the end I decided to dust
off my parseltongue and start counting the whitespace.

another requirement I set upon myself was being able to write posts in
markdown, because as much as markdown is a underdefined, piss poor idea of a
representational format, it's pretty much how I have been writing text files
since the late '90s, when I joined on Usenet. it also allows me to just fire
up ViM, write down some stuff, and not think about style until it's much too
late for anybody to do something about it.

I thus settled for [Pelican][pelican-web].

first of all, I cordoned off the whole thing into its own prefix using
`virtualenv`; if I had to nuke from orbit, I just wanted to be sure not to
blow up the rest of my system as well.

    :::console
    $ virtualenv ~/Source/pelican
    New python executable in /home/ebassi/Source/env/pelican/bin/python
    Installing Setuptools...done.
    Installing Pip...done.
    $ source ~/Source/pelican/bin/activate
    (pelican) $ # ← this is inside the virtualenv

I installed Pelican using `pip`:

    :::console
    (pelican) $ pip install pelican

then I used the `pelican-quickstart` script, which asked me a bunch of
questions and built a skeleton of a website, including a helpful `Makefile`
with a bunch of targets, a configuration file for local testing, and one for
publishing remotely.

I also needed to install a couple of optional modules; the first one was
`markdown`, since Pelican comes only with reStructured text and HTML by
support by default:

    :::console
    (pelican) $ pip install markdown
    ...

then I had to install the `typogrify` module, to get a set of filters to
clean up the typography of the text:

    :::console
    (pelican) $ pip install typogrify
    ...

that's pretty much it.

sure, I had to fix a couple of things in the configuration, and I had to
tweak the theme a bit to turn it into something that was not a throwback to
the simpler times of Geocities, circa 1997; nevertheless, it was pretty much
all there, and it allowed me to hit the ground running at a moderate speed.

in the process, I ended up getting up to speed with modern HTML and CSS —
the last time I wrote some web page, HTML 4 was all the rage, and we had
this new thing called XHTML 1.0, so you can guess I had some learning to do.
I guess having spent almost a year learning how the CSS machinery in a
modern web browser actually works helped me a bit, in this regard.

I guess I could recommend Pelican to anybody who wanted to set up a static
website or a blog, and does not need all the bells and whistles of a dynamic
content management system. [the documentation][pelican-docs] is fairly well
done, even if you need to hunt down the template syntax to the [Jinja
website][jinja-web]. I don't expect the latter to be a problem if you stick
to one of the [standard themes][pelican-themes]; if you want to modify one
of those to suit your needs, tho, you'll become fairly familiar with the
Jinha syntax pretty soon. Pelican also comes with an assorted variety of
[plugins][pelican-plugins]; I haven't found uses for them, yet, but they
seem to be useful.

[wp]: https://wordpress.org (WordPress)
[wiki-nichijou]: https://en.wikipedia.org/wiki/Nichijou (Nichijou. watch it. seriously)
[static-web]: http://www.staticgen.com
[pelican-web]: http://blog.getpelican.com/ (Pelican)
[pelican-docs]: http://docs.getpelican.com/en/3.4.0/
[pelican-themes]: https://github.com/getpelican/pelican-themes
[pelican-plugins]: https://github.com/getpelican/pelican-plugins
[jinja-web]: http://jinja.pocoo.org/
