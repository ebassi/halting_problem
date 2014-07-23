#!/usr/bin/env python
# -*- coding: utf-8 -*- #
from __future__ import unicode_literals

# This file is only used if you use `make publish` or
# explicitly specify it as your config file.

# include the main configuration, so we can simply add/override
# settings when publishing
import os
import sys
sys.path.append(os.curdir)
from pelicanconf import *

# use full URIs when publishing
RELATIVE_URLS = False

# enable full and per-category feed
FEED_ALL_ATOM = 'feeds/all.atom.xml'
CATEGORY_FEED_ATOM = 'feeds/%s.atom.xml'

# start from a clean slate
DELETE_OUTPUT_DIRECTORY = True

# add 'robots.txt' to the list of static paths
STATIC_PATHS = [
    'images',
    'code',
    'extra/robots.txt',
]

# but place robots.txt in the root
EXTRA_PATH_METADATA = {
    'extra/robots.txt': {'path': 'robots.txt'},
}
