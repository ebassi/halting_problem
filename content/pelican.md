Title: pelican
Slug: pelican
Date: 2014-06-16
Author: ebassi

*or: the case for static websites*

if the alternative to anything is a [PHP monstrosity](http://wordpress.org), then clearly **anything** is preferable.

> this is a test of a quote. who knows how will it look like
> when placed inside the resulting HTML of the blog?

what happens to a code block, instead? let's go to another section to find out.

- - -

this is another section.

let's see with a C block:

    :::cpp
    G_DEFINE_TYPE_WITH_PRIVATE (Foo, foo, G_TYPE_OBJECT)

    static void
    foo_class_init (FooClass *klass)
    {
    }

    static void
    foo_init (Foo *self)
    {
    }

    Foo *
    foo_new (void)
    {
      return g_object_new (foo_get_type (), NULL);
    }

- - -

#### Python example

this is yet another section, this time with a heading.

now let's see a Python block:

    :::python
    from gi.repository import GObject

    class Foo (GObject.Object):
        def __init__(self):
            GObject.Object.__init__(self)

should look okay.
