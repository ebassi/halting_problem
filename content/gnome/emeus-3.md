Title: Constraints editing 
Slug: constraints-editing
Tags: development, layout, gtk, constraints, editing 
Date: 2017-01-11 14:30 +0000
Summary: In which a wild editor of constraints appears inside Emeus
Abstract: Writing constraints by hand, even when using a dedicated mini-language, is hard without visualizing the result, and that's how Emeus got a small utility for it

[Last year][emeus-blog-2] I talked about the newly added support for Apple's
Visual Format Language in [Emeus][emeus-web], which allows to quickly
describe layouts using a cross between ASCII art and predicates. For
instance, I can use:

    H:|-[icon(==256)]-[name_label]-|
    H:[surname_label]-|
    H:[email_label]-|
    H:|-[button(<=icon)]
    V:|-[icon(==256)]
    V:|-[name_label]-[surname_label]-[email_label]-|
    V:[button]-|

and obtain a layout like this one:

{% figure {filename}/images/emeus-user-details.png Boxes approximate widgets %}

Thanks to the contribution of my colleague Martin Abente Lahaye, now Emeus
supports extensions to the VFL, namely:

  - arithmetic operators for constant and multiplication factors inside
    predicates, like `[button1(button2 * 2 + 16)]`
  - explicit attribute references, like `[button1(button1.height / 2)]`

This allows more expressive layout descriptions, like keeping aspect ratios
between UI elements, without requiring hitting the code base.

Of course, editing VFL descriptions blindly is not what I consider a fun
activity, so I took some time to write a simple, primitive editing tool that
lets you visualize a layout expressed through VFL constraints:

{% figure {filename}/images/emeus-edit-constraints.png I warned you that it was primitive and simple %}

Here's a couple of videos showing it in action:

{% youtube wroDZQi7HWA 640 480 %}

{% youtube \_nTvuEx1Wvs 640 480 %}

At some point, this could lead to a new UI tool to lay out widgets inside
[Builder][builder-web] and/or Glade.

As of now, I consider Emeus in a stable enough state for other people to
experiment with it — I'll probably make a release soon-ish. The Emeus
[website][emeus-web] is up to date, as it is [the API reference][emeus-api],
and I'm happy to review pull requests and feature requests.

[emeus-blog-2]: https://www.bassi.io/articles/2016/11/01/constraints-reprise/
[emeus-web]: https://ebassi.github.io/emeus/
[builder-web]: https://wiki.gnome.org/Apps/Builder
[emeus-api]: https://ebassi.github.io/emeus/docs/
