"""
Figure Tag
---------
This implements a Liquid-style figure tag for Pelican.

Syntax
------
{% figure [class] [http[s]:/]/path/to/image [caption text] %}

Examples
--------
{% figure image-caption /images/ninja.png Ninja Attack! %}

Output
------
<figure>
  <figcaption class="image-caption">
    <p>Ninja Attack!</p>
  </figcaption>
  <div>
    <img src="/images/ninja.png"/>
  </div>
</figure>
"""
import re
from .mdx_liquid_tags import LiquidTags

SYNTAX = '{% figure [class name(s)] [http[s]:/]/path/to/image [caption text] %}'

# Regular expression to match the entire syntax
ReFigure = re.compile("""(?P<class>\S.*\s+)?(?P<src>(?:https?:\/\/|\/|\S+\/)\S+)(?:\s+(?P<width>\d+))?(?:\s+(?P<height>\d+))?(?P<title>\s+.+)?""")

@LiquidTags.register('figure')
def figure(preprocessor, tag, markup):
    attrs = None
    figure_class = 'image-caption'
    title = 'Untitled'

    # Parse the markup string
    match = ReFigure.search(markup)
    if match:
        attrs = dict([(key, val.strip())
                      for (key, val) in match.groupdict().iteritems() if val])
    else:
        raise ValueError('Error processing input. '
                         'Expected syntax: {0}'.format(SYNTAX))

    if not attrs.get('class'):
        attrs['class'] = figure_class

    if not attrs.get('title'):
        attrs['title'] = title

    # Return the formatted text
    figure_out = """
      <figure>
        <figcaption class="{class}">
          <p>{title}</p>
        </figcaption>
        <div><img src="{src}"/></div>
      </figure>
    """.format(**attrs).strip()

    return figure_out 

#----------------------------------------------------------------------
# This import allows image tag to be a Pelican plugin
from liquid_tags import register

