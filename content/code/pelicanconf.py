#!/usr/bin/env python
# -*- coding: utf-8 -*- #
from __future__ import unicode_literals

# name of the website
SITENAME = u'halting problem'

# base URL
SITEURL = 'http://www.bassi.io'

# all times are relative to London
TIMEZONE = 'Europe/London'

# me
AUTHOR = 'ebassi'

# where the content is
PATH = 'content'

# default language
DEFAULT_LANG = u'en'
# use the file's mtime as the default date
DEFAULT_DATE = 'fs'
# a bland category name; content found under a sub-directory of PATH
# will use the directory name as the category, by default
DEFAULT_CATEGORY = 'misc'
# Month day, Year
DEFAULT_DATE_FORMAT = '%B %d, %Y'
# show 4 posts per page
DEFAULT_PAGINATION = 4

# my own little theme
THEME = 'theme/hlt'

# files under static paths are going to be copies as they are
STATIC_PATHS = [
    'images',
    'code',
]

# keep this True for local testing
RELATIVE_URLS = True

# dictionary of authors, used by the author-info.html template
AUTHORS = {
  'ebassi': (
    'Emmanuele Bassi',
    'geek, husband, lover, software developer, londoner. not necessarily in that order.',
    'ebassi.png',
    'pages/about-me'
  ),
}

# disable all feeds
AUTHOR_FEED_ATOM = None
AUTHOR_FEED_RSS = None
CATEGORY_FEED_ATOM = None
CATEGORY_FEED_RSS = None
TRANSLATION_FEED_ATOM = None
TRANSLATION_FEED_RSS = None
TAG_FEED_ATOM = None
TAG_FEED_RSS = None

# nothing in the blog roll
LINKS = ()

# social links
SOCIAL = (('twitter', 'https://twitter.com/ebassi'),
          ('tumblr', 'http://tumblr.emmanuelebassi.name'),
          ('G+', 'https://plus.google.com/+EmmanueleBassi'),
          ('github', 'https://github.com/ebassi'),)

# enable typogrification
TYPOGRIFY = True

# location of the per-section indices
AUTHORS_SAVE_AS = 'authors/index.html'
CATEGORIES_SAVE_AS = 'categories/index.html'
TAGS_SAVE_AS = 'tags/index.html'

# articles have the date in their URL
ARTICLE_URL = 'articles/{date:%Y}/{date:%m}/{date:%d}/{slug}/'
ARTICLE_SAVE_AS = 'articles/{date:%Y}/{date:%m}/{date:%d}/{slug}/index.html'

# whereas pages do not
PAGE_URL = 'pages/{slug}/'
PAGE_SAVE_AS = 'pages/{slug}/index.html'

# archives are supersets of the articles
YEAR_ARCHIVE_SAVE_AS = 'articles/{date:%Y}/index.html'
MONTH_ARCHIVE_SAVE_AS = 'articles/{date:%Y}/{date:%m}/index.html'

# sub-pages for each section
AUTHOR_URL = 'author/{slug}/'
AUTHOR_SAVE_AS = 'author/{slug}/index.html'

CATEGORY_URL = 'category/{slug}'
CATEGORY_SAVE_AS = 'category/{slug}/index.html'

TAG_URL = 'tag/{slug}'
TAG_SAVE_AS = 'tag/{slug}/index.html'

# used by the liquid_tags.include_code plugin
CODE_DIR = 'code'

# some useful plugin 
PLUGINS = [
  'plugins.liquid_tags.figure',
  'plugins.liquid_tags.img',
  'plugins.liquid_tags.include_code',
  'plugins.related_posts',
]
