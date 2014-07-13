Title: Linking against JSON-GLib < 0.16 and Pulseaudio
Date: 2013-09-21
Slug: json-glib-pulseaudio
Tags: development
Summary: a public announcement for users of json-glib and pulseaudio

this is a public announcement.

if you link against PulseAudio, whether you want it or not, you’ll get an
automatic dependency on json-c, a small C library that parses JSON and
doesn’t have any dependency. sadly, json-c leaks symbols all over the
place, and one of them is called `json_object_get_type()`.

JSON-GLib, the library that yours truly wrote about 6 years ago to parse
JSON using a decent C library as a base, also has a type called
`json_object_get_type()`.

if you link against PulseAudio and JSON-GLib then you’ll get a segmentation
fault with a weird stack trace, like [this one][1] and its duplicates.

the solution is to depend on a version of JSON-GLib greater than 0.16.1,
which builds JSON-GLib with the -Bsymbolic linker flag.

that would be all.

[1]: https://bugzilla.gnome.org/show_bug.cgi?id=703734
