Title: Laptop review
Tags: laptops, hardware, development, reviews
Date: 2016-12-17
Summary: In which I do a review of two laptops: Dell XPS (2016) and Lenovo Yoga 900
Abstract: For personal and work-related reasons I recently came into possession of two different laptops running Linux, and I decided to do a minimalistic review of both.

## Dell XPS 13 (Developer Edition 2016)

After three and a half years with my trusty mid-2013 MacBook Air, I decided
to get a new personal laptop. To be fair, my Air could have probably lasted
another 12-18 months, even though its 8GB of RAM and Haswell Core i7 were
starting to get pretty old for system development. The reason why I couldn't
keep using it reliably was that the SSD had already started showing SMART
errors in January, and I already had to reset it and re-install from scratch
once. Refurbishing the SSD out of warranty is still an option, if I decided
to fork over a fair chunk of money and could live without a laptop for about
a month[^1].

After getting recommendations for the previous XPS iterations by various
other free software developers and Linux users, I waited until the new, Kaby
Lake based model was available in the EU and ordered one. After struggling a
bit with Dell's website, I managed to get an XPS 13 with a US keyboard
layout[^2] — which took about two weeks from order to delivery.

The hardware out of the box experience is pretty neat, with a nice, clean
box; very Apple-like. The software's first boot experience could be better,
to say the least. Since I chose the Developer Edition, I got Ubuntu as the
main OS instead of Windows, and I have been thoroughly underwhelmed by the
effort spent by Dell and Canonical in polishing the software side of things.
As soon as you boot the laptop, you're greeted with an abstract video
playing while the system does *something*. The video playback is not
skippable, and does not have volume controls, so I got to "experience" it at
full blast out of the speakers.

Ubuntu's first boot experience UI to configure the machine is rudimentary,
at best, and not really polished; it's the installer UI without the actual
installation bits, but it clearly hasn't been refined for the HiDPI screen.
The color scheme has progressively gone worse over the years; while all
other OSes are trying to convey a theme of lightness using soft tones, the
dark grey, purple, and dark orange tones used by Ubuntu make the whole UI
seem heavier and oppressive. 

After that, you get into Unity, and no matter how many times I try it, I
still cannot enjoy using it. I also realized *why* various people coming
from Ubuntu complain about the GNOME theme being too heavy on the
whitespace: the Ubuntu default theme is super-compressed, with controls
hugging together so closely that they almost seem to overlap. There is
barely no affordance for the pointer, let alone for interacting through the
touchscreen.

All in all, I resisted half a day on it, mostly to see what was the state of
stock Ubuntu after many years of Fedora[^3]. After that, I downloaded a
Fedora 25 USB image and re-installed from scratch.

Sadly, I still have to report that Anaconda doesn't shine at all. Luckily, I
didn't have to deal with dual booting, so I only needed to interact with the
installer just enough to tell it to use the stock on disk layout and create
the `root` user. Nevertheless, figuring out how to tell it to split my
`/home` volume and encrypt it required me to go through the partitioning
step three times because I couldn't for the life of me understand how to
commit to the layout I wanted.

After that, I was greeted by GNOME's first boot experience — which is
definitely more polished than Ubuntu's, but it's still a bit too
"functional" and plain.

Fedora recognised the whole hardware platform out of the box: wifi,
bluetooth, webcam, HiDPI screen. On the power management side, I was able to
wring out about 8 hours of work (compilation, editing, web browsing, and a
couple of Google hangouts) while on wifi, without having to plug in the AC.

Coming from years of Apple laptops, I was especially skeptical of the
quality of the touchpad, but I have to say I was pleasantly surprised by its
accuracy and feedback. It's not MacBook-level, but it's definitely the
closest anyone has ever been to that slice of fried gold.

The only letdowns I can find are the position of the webcam, which is on the
bottom of the panel and to the left, which makes for **very** dramatic
angles when doing video calls, and requires you never type if you don't want
your fingers to be in the way; and the power brick, which has its own
proprietary connector. There's a USB-C port, though, so there may be
provisions for powering the laptop through it.

### The good

 - Fully supported hardware (Fedora 25)
 - Excellent battery life
 - Nice keyboard
 - Very good touchpad

### The bad

 - The position of the webcam
 - Yet another power brick with custom connector I have to lug around

- - - -

## Lenovo Yoga

Thanks to my [employer](https://endlessm.com) I now have a work laptop as
well, in the shape of a Lenovo Yoga 900. I honestly crossed off Lenovo as a
vendor after the vast [amounts][lenovo-ssl] of [stupidity][lenovo-accel]
they imposed on their clients — and that was after I decided to stop buying
ThinkPad-branded laptops, given their declining build quality and bad
technical choices. Nevertheless, you don't look a gift horse in the mouth.

The out of the box experience of the Yoga is very much on par with the one I
had with the XPS, which is to say: fairly Apple-like.

The Yoga 900 is a fairly well made machine. It's an Intel Sky Lake platform,
with a nice screen and good components. The screen can fold and turn the
whole thing into a "tablet", except that the keyboard faces downward, so
it's weird to handle in that mode. Plus, a 13" tablet is a pretty big thing
to carry around. On the other hand, folding the laptop into a "tent" and
using an external keyboard and pointer device is a nice twist on the whole
"home office" approach. The webcam is, thankfully, centered and placed at
the top of the panel — something that Lenovo has apparently changed in the
910 model, when they realised that folding the laptop would put the webcam
at the bottom of the panel.

On the software side, the first boot experience into Windows 10 was
definitely less than stellar. The Lenovo FBE software was **not**
HiDPI-aware, which posed interesting challenges to the user interaction.
This is something that a simple bit of QA would have found out, but
apparently QA is too much to ask when dealing with a £1000 laptop. Luckily,
I had to deal with that only inasmuch as I needed to get and install the
latest firmware updates before installing Linux on the machine. Again, I
went for Fedora.

As in the case of the Dell XPS, Fedora recognised all components of the
hardware plaform out of the box. Even the screen rotation and folding works
out of the box — though it can still get into inconsistent states when you
move the laptop around, so I kind of recommend you keep the screen rotation
locked until you actually need it.

On the power management side, I was impressed by how well the sleep states
conserve battery power; I'm able to leave the Yoga suspended for a week and
still have power on resume. The power brick has a weird USB-like connector
to the laptop which makes me wonder what on earth were Lenovo engineers
thinking; on the other hand, the adapter has a USB port which means you can
charge it from a battery pack or from a USB adapter as well. There's also a
USB-C port, but I still haven't tested if I can put power through it.

The keyboard is probably the biggest let down; the travel distance and feel
of the keys is definitely not up to par with the Dell XPS, or with the Apple
keyboards. The 900 has an additional column of navigation keys on the right
edge that invariably messes up my finger memory — though it seems that the
910 has moved them to Function key combinations.[^5] The power button is on
the right side of the laptop, which makes for unintended suspend/resume
cycles when trying to plug in the headphones, or when moving the laptop. The
touchpad is, sadly, very much lacking, with ghost tap events that forced me
to disable the middle-click emulation everywhere[^4].

### The good

 - Fully supported hardware (Fedora 25)
 - Solid build
 - Nice flip action
 - Excellent power management

### The bad

 - Keyboard is a toy
 - Touchpad is a pale imitation of a good pointing device

[^1]: Which may still happen, all things considered; I really like the Air
  as a travel laptop.
[^2]: After almost a decade with US layouts I find the UK layout inferior
  to the point of inconvenience.
[^3]: On my desktop machine/gaming rig I dual boot between Windows 10 and
  Ubuntu GNOME, mostly because of the nVidia GPU and Steam.
[^4]: That also increased my hatred of the middle-click-to-paste-selection
  easter egg a thousandfold, and I already hated the damned thing so much
  that my rage burned with the intensity of a million suns.
[^5]: Additionally, the keyboard layout is UK — see note 2 above.

[lenovo-ssl]: https://www.eff.org/deeplinks/2015/02/further-evidence-lenovo-breaking-https-security-its-laptops
[lenovo-accel]: http://www.zdnet.com/article/lenovo-begs-users-to-uninstall-accelerator-app-in-the-name-of-security/
