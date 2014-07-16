#!/usr/bin/env python
# -*- coding: utf-8 -*- #
from __future__ import unicode_literals

AUTHOR = u'Emmanuele Bassi'
SITENAME = u'halting problem'
SITEURL = 'http://www.emmanuelebassi.name'

PATH = 'content'

TIMEZONE = 'Europe/London'

DEFAULT_LANG = u'en'
DEFAULT_DATE = 'fs'
DEFAULT_CATEGORY = 'misc'
DEFAULT_DATE_FORMAT = '%B %d, %Y'
DEFAULT_PAGINATION = 4

AUTHOR = 'ebassi'

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

AUTHORS_SAVE_AS = ''
CATEGORIES_SAVE_AS = 'categories/index.html'
TAGS_SAVE_AS = 'tags/index.html'

ARTICLE_URL = 'articles/{date:%Y}/{date:%m}/{date:%d}/{slug}/'
ARTICLE_SAVE_AS = 'articles/{date:%Y}/{date:%m}/{date:%d}/{slug}/index.html'

PAGE_URL = 'pages/{slug}/'
PAGE_SAVE_AS = 'pages/{slug}/index.html'

YEAR_ARCHIVE_SAVE_AS = 'articles/{date:%Y}/index.html'
MONTH_ARCHIVE_SAVE_AS = 'articles/{date:%Y}/{date:%m}/index.html'

AUTHOR_URL = ''
AUTHOR_SAVE_AS = ''

CATEGORY_URL = 'category/{slug}'
CATEGORY_SAVE_AS = 'category/{slug}/index.html'

TAG_URL = 'tag/{slug}'
TAG_SAVE_AS = 'tag/{slug}/index.html'

THEME = 'theme/hlt'

PLUGINS = ['plugins.related_posts']

# Uncomment following line if you want document-relative URLs when developing
RELATIVE_URLS = True
WITH_FUTURE_DATES = False
