Title: Long term support for GTK+
Tags: gtk, lts
Date: 2016-06-15
Summary: In which I reply to Morten's latest unnecessary rant
Abstract: I hate turning my blog into a comment section, but some times it's warranted when people that should know better, but evidently don't care, just spout baseless accusations

Dear Morten,

> A belief that achieving stability can be done after most of the paid
> contributors have run off to play with new toys is delusional. The record
> does not support it.

The record (in terms of commit history) seem to **not** support your
position — as much as you think everyone else is "delusional" about it, the
commit log does not really lie.

The 2.24.0 release was cut in January, 2011 — five and half years ago. No
new features, no new API. Precisely what would happen with the new release
plan, except that the new plan would also give a much better cadence to this
behaviour.

Since then, the 2.24 branch — i.e. the "feature frozen" branch has seen 873
commits (as of this afternoon, London time), and 30 additional releases.

Turns out that people *are* being paid to maintain feature-frozen branches
because that's what the boring bits are — security issues, stability bugs,
etc. Volunteers are much more interested in getting the latest and greatest
feature that probably does not interest you now, but may be requested by
your users in two years.

Isn't it what you asked multiple times? A "long term support" release that
gives you time to port your application to a stable API that has seen most
of the bugs and uncertainty already squashed?
