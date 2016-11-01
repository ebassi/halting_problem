Title: Constraints (reprise)
Slug: constraints-reprise
Tags: development, layout, gtk, constraints, solvers
Date: 2016-11-01 17:07 +0000
Summary: Further experiments with constraint-based layout systems for GTK+

After the [first article on Emeus][blog-emeus] various people expressed
interest in the internals of the library, so I decided to talk a bit about
what makes it work.

Generally, you can think about constraints as linear equations:

    view1.attr1 = view2.attr2 × multiplier + constant

You take the the value of `attr2` on the widget `view2`, multiply it by a
`multiplier`, add a `constant`, and apply the value to the attribute `attr1`
on the widget `view1`. You don't need `view2.attr2` either, for instance:

    view1.attr1 = constant

is a perfectly valid constraint.

You also don't need to use an equality; these two constraints:

    view1.width ≥ 180
    view1.width ≤ 250

specify that the `width` of `view1` must be in the `[ 180, 250 ]` range,
extremes included.

### Layout

A layout, then, is just a pile of linear equations that describe the
relations between each element. So, if we have a simple grid:

    +--------------------------------------------+
    | super                                      |
    |  +----------------+   +-----------------+  |
    |  |     child1     |   |     child2      |  |
    |  |                |   |                 |  |
    |  +----------------+   +-----------------+  |
    |                                            |
    |  +--------------------------------------+  |
    |  |               child3                 |  |
    |  |                                      |  |
    |  +--------------------------------------+  |
    |                                            |
    +--------------------------------------------+

We can describe each edge's position and size using constraints. It's
important to note that there's an implicit "reading" order that makes it
easier to write constraints; in this case, we start from left to right, and
from top to bottom. Generally speaking, it's possible to describe
constraints in any order, but the [Cassowary][cassowary-web] solving
algorithm is geared towards the "reading" order above.

Each layout has some implicit constraint already available. For instance,
the "trailing" edge is equal to the leading edge plus the width; the bottom
edge is equal to the top edge plus the height; the center point is equal to
the width or height, divided by two, plus the leading or bottom edges. These
constraints help solving the layout, as well as provide additional values to
other constraints.

So, let's start.

From the first row:

   * the leading edge of the `super` container is the same as the leading
     edge of `child1`, minus a padding
   * the trailing edge of `child1` is the same as the leading edge of
     `child2`, minus a padding
   * the trailing edge of `child2` is the same as the trailing edge of
     the `super` container, minus a padding
   * the width of `child1` is the same as the width of `child2`

From the second row:

   * the leading edge of the `super` container is the same as the leading
     edge of `child3`, minus a padding
   * the trailing edge of `child2` is the same as the trailing edge of
     the `super` container, minus a padding

From the first column:

   * the top edge of the `super` container is the same as the top edge
     of `child1`, minus a padding
   * the bottom edge of `child1` is the same as the top edge of `child3`,
     minus a padding
   * the bottom edge of the `super` container is the same as the bottom
     edge of `child3`, minus a padding
   * the height of `child3` is the same as the height of `child1`

From the second column:

   * the top edge of the `super` container is the same as the top edge
     of the `child2`, minus a padding
   * the bottom edge of `child1` is the same as the top edge of `child3`,
     minus a padding
   * the bottom edge of the `super` container is the same as the bottom
     edge of `child3`, minus a padding
   * the height of `child3` is the same as the height of `child2`

As you can see, there are some redundancies; these are necessary to ensure
that the layout is fully resolved, though obviously there are some
properties of the elements of the layout that implicitly eliminate some
results. For instance, if `child3`'s height is the same as `child1`, and
`child1` lies on the same row as `child2` and it's an axis-aligned
rectangle, the it immediately follows that `child3` must have the same
height of `child2` as well. It's important to note that, from a solver
perspective, there only are values, not boxes, and you could use the solver
with any kind of geometric shape; only the constraints give us the
information on what those shapes should be. It's also easier to start from a
fully constrained layout and then remove constraints, than to start from a
loosely constrained layout and add constraints until it's stable.

### Representation

From the text description we can now get into a system of equations:

  - super.start = child1.start - padding
  - child1.end = child2.start - padding
  - super.end = child2.end - padding
  - child1.width = child2.width
  - super.start = child3.start - padding
  - super.end = child3.end - padding
  - super.top = child1.top - padding
  - child1.bottom = child3.top - padding
  - super.bottom = child3.bottom - padding
  - child3.height = child1.height
  - super.top = child2.top - padding
  - child2.bottom = child3.top - padding
  - child3.height = child2.height

Apple, in its [infinite wisdom and foresight][newton-wiki], decided that
this form is still too verbose. After looking at the [Perl format][perldoc-format]
page for far too long, Apple engineers came up with the Visual Format
Language, or [VFL][apple-vfl] for short.

Using VFL, the constraints above become:

    H:|-(padding)-[child1(==child2)]-(padding)-[child2]-(padding)-|
    H:|-(padding)-[child3]-(padding)-|
    V:|-(padding)-[child1(==child3)]-(padding)-[child3]-(padding)-|
    V:|-(padding)-[child2(==child3)]-(padding)-[child3]-(padding)-|

Emeus, incidentally, ships with a simple utility that can take a set of VFL
format strings and generate GtkBuilder descriptions that you can embed into
your templates.

### Change

We've used a fair amount of constraints, or four lines of faily cryptic
ASCII art, to basically describe a non-generic `GtkGrid` with two equally
sized horizontal cells on the first row, and a single cell with a column
span of two; compared to the common layout managers inside GTK+, this does
not seem like a great trade off.

Except that we can describe any other layout without necessarily having to
pack widgets inside boxes, with margins and spacing and alignment rules; we
also don't have to change the *hierarchy* of the boxes if we want to change
the layout. For instance, let's say that we want `child3` to have a
different horizontal padding, and a minimum and maximum width; we just need
to change the constraints involved in that row:

    H:|-(hpadding)-[child3(>=250,<=500)]-(hpadding)-|

Additionally, we now want to decouple `child1` and `child3` heights, and
make `child1` a fixed height item:

    V:|-(padding)-[child1(==250)]-(padding)-[child3]-(padding)-|

And make the height of `child3` move within a range of values:

    V:|-(padding)-[child2]-(padding)-[child3(>=200,<=300)]-(padding)-|

For all these cases we'd have to add intermediate boxes in between our
children and the parent container — with all the issues of theming and
updating things like GtkBuilder XML descriptions that come with that.

### Future

The truth is, though, that describing layouts in terms of constraints is
another case of software engineering your way out of talking with
designers; it's great to start talking about incremental simplex solvers,
and systems of linear equations, and ASCII art to describe your layouts, but
it doesn't make UI designers *really* happy. They can deal with it, and
having a declarative language to describe constraints is more helpful than
parachuting them into an IDE with a Swiss army knife and a can of beans, but
I wouldn't recommend it as a solid approach to developer experience.

Havoc wrote [a great article][havoc-constraints] on how layout management
API doesn't necessarily have to suck:

  * we can come up with a better, descriptive API that does not make
    engineers and designers cringe in different ways
  * we should have support from our tools, in order to manipulate constraints
    and UI elements
  * we should be able to combine boxes (which are easy to style) and
    constraints (which are easy to lay out) together in a natural and
    flexible way

Improving layout management should be a goal in the development of GTK+ 4.0,
so feel free to jump in and help out.

[blog-emeus]: https://www.bassi.io/articles/2016/10/17/constraints/
[cassowary-web]: http://constraints.cs.washington.edu/cassowary/
[newton-wiki]: https://en.wikipedia.org/wiki/Apple_Newton
[perldoc-format]: http://perldoc.perl.org/perlform.html
[apple-vfl]: https://developer.apple.com/library/content/documentation/UserExperience/Conceptual/AutolayoutPG/VisualFormatLanguage.html
[havoc-constraints]: https://blog.ometer.com/2016/09/17/layout-apis-dont-have-to-be-terrible-lessons-from-bokeh/
