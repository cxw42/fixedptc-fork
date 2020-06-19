fixedptc library - a simple fixed point math header library for C.
Copyright (c) 2010-2012, 2020 Ivan Voras <ivoras@freebsd.org> and contributors.
Released under the BSD license.

Single-File Library
===================

fixedptc is intended to be simple to use and integrate in other simple
programs, thus is it implemented as a C header-only library.  By default, all
functions are inlined.  This makes the library easy to use, but can result in a
significant increase in code size for the final executable compared to
a separately-compiled library.

Separate Compilation
====================

If the complex functions are used often in the end-program, the library should
be implemented in a separate C file.  To do so:

1. Create a new C file with the text:

    #define FIXEDPTC_IMPLEMENTATION
    #include "fixedptc.h"

2. Add the new C file to be linked into your project.

3. In each file that uses fixedptc.h,

    #define FIXEDPTC_EXTERN
    #include "fixedptc.h"

EXPORT_SYMBOL
=============

If an EXPORT_SYMBOL macro is defined before the #include that pulls in the
implementation of fixedptc (FIXEDPTC_IMPLEMENTATION),  that macro will be
invoked for each fixedpt function as:

    EXPORT_SYMBOL(function_name);

This feature is designed to ease integration with the Linux kernel.
