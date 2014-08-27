Title: GDK and threads
Date: 2014-08-27 12:01
Summary: using GDK with threads is never a good idea
Abstract: I've seen a few bugs filed against GTK and GLib about potential regressions in the GDK threading API with GLib ≥ 2.41, and thought it would be best to write an article about it before people on the internet start screaming bloody murder and how everyone is switching to Qt because GTK+ kills puppies.
Tags: gtk, development, threads

> a programmer has a problem. "I know," he said, "I will use threads!"
> now has he problems two.
>		-- old Romulan proverb

we all know that using GTK+ and threads is a fan favourite question; I
routinely answered it on IRC, mailing lists, Stack Overflow, and even in
person multiple times. some time ago, we actually fixed the documentation to
provide an authoritative answer as to how you should do your long-running,
blocking operations on a thread, and then update the UI from within the main
thread at various synchronization points.

sadly, both the API and the documentation that came before the tenet above
became well-known, were lacking. the wording was ambiguous, and the examples
were far from clear in showing the idiomatic way of initializing and using
GTK+ in a multi-threaded application.

if I asked ten random developers using GTK+ for their applications what is
the correct way of initializing threading support, I'd probably get the
answer "call `gdk_threads_init()` before you call `gtk_init()`" from at least
half of them — and their answer would be wrong, but most likely they never
noticed it.

the correct answer for the question of how to initialize thread safety
support in GTK+ is actually this idiomatic code snippet:

    :::cpp
    int
    main (int argc, char *argv[])
    {
      // initialize GDK thread support
      gdk_threads_init ();

      // acquire the GDK lock
      gdk_threads_enter ();

      // initialize GTK+
      gtk_init (&argc, &argv);

      // build your UI ...

      // start the main loop
      gtk_main ();

      // tear down your UI...

      // release the GDK lock
      gdk_threads_leave ();

      // exit
      return 0;
    }

as you can see, we acquire the GDK lock before calling the GTK+ API, like
the [documentation says][gdk2-threads]:

> As always, you must also surround any calls to GTK+ not made within a
> signal handler with a `gdk_threads_enter()` / `gdk_threads_leave()` pair.

why is this needed? because the `gtk_main()` call will try to release the
GDK lock before entering the main loop, and re-acquire it before returning
the control flow to you. this is needed to avoid deadlocks from within GDK
itself, since the GDK frame processing is going to acquire the GDK lock
whenever it's needed inside its own critical sections.

if you don't acquire the lock, `gtk_main()` will try to release an unlocked
mutex, and if you carefully read the `g_mutex_unlock()` [documentation][glib-mutex]
you will notice that doing that results in *undefined behaviour*. what does
*undefined behaviour* means? in GLib and GTK+, we use the term in the same
sense as the [ISO C standard uses it][llvm-undefined].

in this specific instance, if you're on Linux, *undefined behaviour* does
not mean much: by default, the GNU libc implementation of pthreads is
permissive, so it will simply ignore the double unlock. if you're running on
an operating system from the \*BSD family, however, your application will
uncerimoniously abort. hence, why so far very few people actually noticed
this.

starting from GLib 2.42 (the next stable release), the `GMutex`
implementation on Linux has been switched from a pure pthread wrapper to be
futex-based. given that we don't pay any penalty for it, we decided to ensure
consistent behaviour, and proper usage of the API. this means that GLib 2.42
will abort if you try to clear an uninitialized or locked `GMutex`, as well
as if you try to unlock an already unlocked one. this ensures that your code
will actually be portable, and you'll catch errors much more quickly.

this also means that non-idiomatic GTK+ code will start breaking on Linux as
well, just like it would on non-Linux platforms.

since our documentation was not really good enough for people to use, and
since we could not enforce proper idiomatic code at the toolkit level, GDK
[will try to compensate][gdk-threads-init-bug].

- - -

it's important to not that this does not absolve you from fixing your code:
you **are** doing something wrong. it will allow, though, existing code to
continue working even in the face of undefined behaviour. take this as a
chance to rework your code not to use the GDK API to mark critical sections,
and instead use the proper approach of worker threads notifying the UI
through idle and timeout callbacks executed from within the main thread.

[gdk2-threads]: https://developer.gnome.org/gdk2/2.24/gdk2-Threads.html
[glib-mutex]: https://developer.gnome.org/glib/stable/glib-Threads.html#g-mutex-unlock
[gdk-threads-init-bug]: https://bugzilla.gnome.org/show_bug.cgi?id=735428#c11
[llvm-undefined]: http://blog.llvm.org/2011/05/what-every-c-programmer-should-know.html
