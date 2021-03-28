#pragma once

// Macros for handling compatability with/without modules

#ifdef matmath_use_modules

#ifndef matmath_export
#define matmath_export export
#endif

#else

#ifndef matmath_export
#define matmath_export
#endif

#endif
