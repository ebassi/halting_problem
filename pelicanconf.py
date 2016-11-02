#!/usr/bin/env python
# -*- coding: utf-8 -*- #
from __future__ import unicode_literals

AUTHOR = u'Emmanuele Bassi'
SITENAME = u'halting problem'
SITEURL = 'https://www.bassi.io'

PATH = 'content'

TIMEZONE = 'Europe/London'

DEFAULT_LANG = u'en'
DEFAULT_DATE = 'fs'
DEFAULT_CATEGORY = 'misc'
DEFAULT_DATE_FORMAT = '%B %d, %Y'
DEFAULT_PAGINATION = 4

AUTHOR = 'ebassi'

AUTHORS = {
  'ebassi': (
    'Emmanuele Bassi',
    'geek, husband, lover, software developer, londoner. not necessarily in that order.',
    'ebassi.png',
    'pages/about-me'
  ),
}

# generate only the full feed
AUTHOR_FEED_ATOM = None
AUTHOR_FEED_RSS = None
CATEGORY_FEED_ATOM = None
CATEGORY_FEED_RSS = None
TRANSLATION_FEED_ATOM = None
TRANSLATION_FEED_RSS = None
TAG_FEED_ATOM = None
TAG_FEED_RSS = None

# Blogroll
LINKS = ()

# Social widget
SOCIAL = (('twitter', 'https://twitter.com/ebassi'),
          ('tumblr', 'http://tumblr.emmanuelebassi.name'),
          ('G+', 'https://plus.google.com/+EmmanueleBassi'),
          ('github', 'https://github.com/ebassi'),)

TYPOGRIFY = True

#PAGINATION_PATTERNS = (
#    (1, '{base_name}/', '{base_name}/index.html'),
#    (2, '{base_name}/page/{number}', '{base_name}/page/{number}/index.html'),
#)

AUTHORS_SAVE_AS = 'authors/index.html'
CATEGORIES_SAVE_AS = 'categories/index.html'
TAGS_SAVE_AS = 'tags/index.html'

ARTICLE_URL = 'articles/{date:%Y}/{date:%m}/{date:%d}/{slug}/'
ARTICLE_SAVE_AS = 'articles/{date:%Y}/{date:%m}/{date:%d}/{slug}/index.html'

PAGE_URL = 'pages/{slug}/'
PAGE_SAVE_AS = 'pages/{slug}/index.html'

YEAR_ARCHIVE_SAVE_AS = 'articles/{date:%Y}/index.html'
MONTH_ARCHIVE_SAVE_AS = 'articles/{date:%Y}/{date:%m}/index.html'

AUTHOR_URL = 'author/{slug}/'
AUTHOR_SAVE_AS = 'author/{slug}/index.html'

CATEGORY_URL = 'category/{slug}'
CATEGORY_SAVE_AS = 'category/{slug}/index.html'

TAG_URL = 'tag/{slug}'
TAG_SAVE_AS = 'tag/{slug}/index.html'

THEME = 'theme/hlt'

CODE_DIR = 'code'

STATIC_PATHS = [
    'images',
    'code',
    'talks',
]

PLUGIN_PATHS = [ 'plugins' ]

PLUGINS = [
  'related_posts',
  'liquid_tags.figure',
  'liquid_tags.img',
  'liquid_tags.include_code',
  'post_stats',
]

# Uncomment following line if you want document-relative URLs when developing
RELATIVE_URLS = True
WITH_FUTURE_DATES = False
