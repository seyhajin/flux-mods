#ifndef __STD_H__
#define __STD_H__

// ObjC stuff
#if __OBJC__
    #import <Foundation/Foundation.h>
#endif

#ifndef SX_COMPILER_MSVC
    //#define __forceinline inline __attribute__((always_inline))
#endif

// C++ stuff
//#include <new>
//#include <initializer_list>

//#include <cstdio>
//#include <cstdlib>
//#include <cstring>
//#include <cctype>
//#include <cmath>

#ifdef SX_THREADS
    #include <atomic>
#endif

// C stuff
#include <stdio.h>

#endif //!__STD_H__