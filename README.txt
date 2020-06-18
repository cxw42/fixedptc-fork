fixedptc library - a simple fixed point math header library for C.
Copyright (c) 2010-2012. Ivan Voras <ivoras@freebsd.org>
Released under the BSDL.

fixedptc is intended to be simple to use and integrate in other simple
programs, thus is it implemented as a C header library. However, as
functions in this mode of operation are all inlined, it can result in a
significant increase in code size for the final executable. If the complex
functions are used often in the end-program, the library should be
implemented in a separate C file:

1. Create a new C file with the text:

    #define FIXEDPTC_IMPLEMENTATION
    #include "fixedptc.h"

2. Add the new C file to be linked into your project.

3. In each file that uses fixedptc.h,

    #define FIXEDPTC_EXTERN

   before #including fixedptc.h.

