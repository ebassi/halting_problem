Title: Linking against JSON-GLib < 0.16 and Pulseaudio
Date: 2013-09-21
Slug: json-glib-pulseaudio
Tags: development
Summary: a public announcement for users of json-glib and pulseaudio

this is a public announcement.

if you link against PulseAudio, whether you want it or not, you’ll get an
automatic dependency on json-c, a small C library that parses JSON and
doesn’t have any dependency[^1]. sadly, json-c leaks symbols all over the
place, and one of them is called `json_object_get_type()`[^2].

JSON-GLib, the library that yours truly wrote about 6 years ago to parse
JSON using a decent C library as a base, also has a type called
`json_object_get_type()`[^3].

if you link against PulseAudio and JSON-GLib[^4] then you’ll get a segmentation
fault with a weird stack trace, like [this one][1] and its duplicates[^5].

the solution is to depend on a version of JSON-GLib greater than 0.16.1,
which builds JSON-GLib with the `-Bsymbolic` linker flag[^6].

that would be all.

[1]: https://bugzilla.gnome.org/show_bug.cgi?id=703734

[^1]: which is arguably a plus for a system dæmon
[^2]: which returns an integer for I don't know which reason
[^3]:
    which returns a `GType` for the `JsonObject` boxed structure, so
    you can use them in properties and signal marshallers; as it happens,
    `GType` is a `long` look-alike
[^4]: or any other library that depends on JSON-GLib, like Clutter
[^5]:
    since both return values and arguments of the functions above are
    compatible, the linker won’t moan about it, so you won’t see any
    warning or error when building your code
[^6]:
    another solution is to statically link json-c inside PulseAudio instead
    of dynamically linking it; another solution is to link json-c with
    `-Bsymbolic`; yet another solution would be for PA to not use a dependency
    to parse JSON – or drop JSON entirely because I can’t for the life of me
    understand why an audio server is dealing with JSON at all
