#!/usr/bin/env python
# -*- coding: utf-8 -*- #
from __future__ import unicode_literals

# This file is only used if you use `make publish` or
# explicitly specify it as your config file.

import os
import sys
sys.path.append(os.curdir)
from pelicanconf import *

SITEURL = 'http://www.bassi.io'
RELATIVE_URLS = False

FEED_ALL_ATOM = 'feeds/all.atom.xml'
CATEGORY_FEED_ATOM = 'feeds/%s.atom.xml'

DELETE_OUTPUT_DIRECTORY = True

STATIC_PATHS = [
    'images',
    'code',
    'talks',
    'extra/robots.txt',
]

EXTRA_PATH_METADATA = {
    'extra/robots.txt': {'path': 'robots.txt'},
}

# Following items are often useful when publishing

#GITHUB_URL = 'https://github.com/ebassi/halting_problem'
TWITTER_USERNAME = 'ebassi'
GOOGLE_ANALYTICS = 'UA-51960001-1'
