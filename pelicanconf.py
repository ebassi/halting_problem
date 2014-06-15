#!/usr/bin/env python
# -*- coding: utf-8 -*- #
from __future__ import unicode_literals

AUTHOR = u'Emmanuele Bassi'
SITENAME = u'halting problem'
SITEURL = 'http://www.emmanuelebassi.name/'

PATH = 'content'

TIMEZONE = 'Europe/London'

DEFAULT_LANG = u'en'

# Feed generation is usually not desired when developing
FEED_ALL_ATOM = None
CATEGORY_FEED_ATOM = None
TRANSLATION_FEED_ATOM = None

# Blogroll
LINKS = ()

# Social widget
SOCIAL = (('twitter', 'https://twitter.com/ebassi'),
          ('tumblr', 'http://tumblr.emmanuelebassi.name'),
          ('G+', 'https://plus.google.com/+EmmanueleBassi'),
          ('github', 'https://github.com/ebassi'),)

DEFAULT_PAGINATION = 3
PAGINATION_PATTERNS = (
    (1, '{base_name}/', '{base_name}/index.html'),
    (2, '{base_name}/page/{number}', '{base_name}/page/{number}/index.html'),
)

ARTICLE_URL = 'articles/{date:%Y}/{date:%m}/{date:%d}/{slug}/'
ARTICLE_SAVE_AS = 'articles/{date:%Y}/{date:%m}/{date:%d}/{slug}/index.html'

YEAR_ARCHIVE_SAVE_AS = 'articles/{date:%Y}/index.html'
MONTH_ARCHIVE_SAVE_AS = 'articles/{date:%Y}/{date:%m}/index.html'

THEME = 'theme/hlt'

TWITTER_USERNAME = 'ebassi'

# Uncomment following line if you want document-relative URLs when developing
RELATIVE_URLS = False
