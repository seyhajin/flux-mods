//
// Platform preprocessor definitions:
//      Contains processor/arch/compiler/os definitions for different platforms
//
// Parts of this code is copied from bx library: https://github.com/bkaradzic/bx
//
// Another useful reference: https://sourceforge.net/p/predef/wiki/Home/
//
#ifndef __SX_PLATFORM_H__
#define __SX_PLATFORM_H__

////////// Macros

//
#define SX_STRINGIZE(_x) SX_STRINGIZE_(_x)
#define SX_STRINGIZE_(_x) #_x

////////// Decls

// Architecture
#define SX_ARCH_32BIT 0
#define SX_ARCH_64BIT 0

// Compiler
#define SX_COMPILER_CLANG 0
#define SX_COMPILER_GCC   0
#define SX_COMPILER_MSVC  0

// Endianess
#define SX_CPU_ENDIAN_BIG    0
#define SX_CPU_ENDIAN_LITTLE 0

// CPU
#define SX_CPU_ARM   0
#define SX_CPU_JIT   0
#define SX_CPU_MIPS  0
#define SX_CPU_PPC   0
#define SX_CPU_RISCV 0
#define SX_CPU_X86   0

// C Runtime
#define SX_CRT_BIONIC 0
#define SX_CRT_BSD    0
#define SX_CRT_GLIBC  0
#define SX_CRT_LIBCXX 0
#define SX_CRT_MINGW  0
#define SX_CRT_MSVC   0
#define SX_CRT_NEWLIB 0
#ifndef SX_CRT_MUSL
    #define SX_CRT_MUSL 0
#endif // SX_CRT_MUSL
#ifndef SX_CRT_NONE
    #define SX_CRT_NONE 0
#endif // SX_CRT_NONE

// Platform
#define SX_PLATFORM_ANDROID    0
#define SX_PLATFORM_BSD        0
#define SX_PLATFORM_EMSCRIPTEN 0
#define SX_PLATFORM_HAIKU      0
#define SX_PLATFORM_HURD       0
#define SX_PLATFORM_IOS        0
#define SX_PLATFORM_MACOS      0
#define SX_PLATFORM_LINUX      0
#define SX_PLATFORM_NX         0
#define SX_PLATFORM_PS4        0
#define SX_PLATFORM_RPI        0
#define SX_PLATFORM_WINDOWS    0
#define SX_PLATFORM_WINRT      0
#define SX_PLATFORM_XBOXONE    0

////////// Defs

// Architecture
// https://sourceforge.net/p/predef/wiki/Architectures/
#if defined(__x86_64__)    \
 || defined(_M_X64)        \
 || defined(__aarch64__)   \
 || defined(__64BIT__)     \
 || defined(__mips64)      \
 || defined(__powerpc64__) \
 || defined(__ppc64__)     \
 || defined(__LP64__)
    #undef  SX_ARCH_64BIT
    #define SX_ARCH_64BIT 64
#else
    #undef  SX_ARCH_32BIT
    #define SX_ARCH_32BIT 32
#endif // Architecture

// Compiler
// https://sourceforge.net/p/predef/wiki/Compilers/
#if defined(__clang__)
    // clang defines __GNUC or _MSC_VER
    #undef  SX_COMPILER_CLANG
    #define SX_COMPILER_CLANG (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)
#elif defined(_MSC_VER)
    #undef  SX_COMPILER_MSVC
    #define SX_COMPILER_MSVC _MSC_VER
#elif defined(__GNUC__)
    #undef  SX_COMPILER_GCC
    #define SX_COMPILER_GCC (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#else
    #error "SX_COMPILER_* is not defined!"
#endif // Compiler

// CPU
// https://sourceforge.net/p/predef/wiki/Architectures/
#if defined(__arm__) \
 || defined(__aarch64__) \
 || defined(_M_ARM)
    #undef  SX_CPU_ARM
    #define SX_CPU_ARM 1
    #define SX_CACHE_LINE_SIZE 64
#elif defined(__MIPSEL__) \
   || defined(__mips_isa_rev) \
   || defined(__mips64)
   #undef  SX_CPU_MIPS
   #define SX_CPU_MIPS 1
   #define SX_CACHE_LINE_SIZE 64
#elif defined(_M_PPC) \
   || defined(__powerpc__) \
   || defined(__powerpc64__)
   #undef  SX_CPU_PPC
   #define SX_CPU_PPC 1
   #define SX_CACHE_LINE_SIZE 128
#elif defined(__riscv) \
   || defined(__riscv__) \
   || defined(RISCVEL)
   #undef  SX_CPU_RICSV
   #define SX_CPU_RISCV 1
   #define SX_CACHE_LINE_SIZE 64
#elif defined(_M_IX86) \
   || defined(_M_X64) \
   || defined(__i386__) \
   || defined(__x86_64__)
   #undef  SX_CPU_X86
   #define SX_CPU_X86 1
   #define SX_CACHE_LINE_SIZE 64
#else // PNaCl doesn't have CPU defined
    #undef  SX_CPU_JIT
    #define SX_CPU_JIT 1
    #define SX_CACHE_LINE_SIZE 64
#endif // CPU

// Endianess
// https://sourceforge.net/p/predef/wiki/Endianness/
#if SX_CPU_PPC
// __BIG_ENDIAN__ is gcc predefined macro
    #if defined(__BIG_ENDIAN__)
        #undef  SX_CPU_ENDIAN_BIG
        #define SX_CPU_ENDIAN_BIG 1
    #else
        #undef  SX_CPU_ENDIAN_LITTLE
        #define SX_CPU_ENDIAN_LITTLE 1
    #endif
#else
    #undef  SX_CPU_ENDIAN_LITTLE
    #define SX_CPU_ENDIAN_LITTLE 1
#endif // SX_CPU_PPC

// Platform
// https://sourceforge.net/p/predef/wiki/OperatingSystems/
#if defined(_DURANGO) || defined(_XBOX_ONE)
    #undef  SX_PLATFORM_XBOXONE
    #define SX_PLATFORM_XBOXONE 1
#elif defined(_WIN32) || defined(_WIN64)
// http://msdn.microsoft.com/en-us/library/6sehtctf.aspx
    #ifndef NOMINMAX
        #define NOMINMAX
    #endif
    // If _USING_V110_SDK71_ is defined it means we are using the v110_xp or v120_xp toolset.
    #if !defined(WINAPI_FAMILY) || (WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP)
        #undef SX_PLATFORM_WINDOWS
        #if !defined(WINVER) && !defined(_WIN32_WINNT)
            #if SX_ARCH_64BIT
                // When building 64-bit target Win7 and above.
                #define WINVER 0x0601
                #define _WIN32_WINNT 0x0601
            #else
                // Windows Server 2003 with SP1, Windows XP with SP2 and above
                #define WINVER 0x0502
                #define _WIN32_WINNT 0x0502
            #endif // SX_ARCH_64BIT
        #endif // !defined(WINVER) && !defined(_WIN32_WINNT)
        #define SX_PLATFORM_WINDOWS _WIN32_WINNT
    #else
        #undef  SX_PLATFORM_WINRT
        #define SX_PLATFORM_WINRT 1
    #endif
#elif defined(__ANDROID__)
// Android compiler defines __linux__
    #include <sys/cdefs.h> // Defines __BIONIC__ and includes android/api-level.h
    #undef  SX_PLATFORM_ANDROID
    #define SX_PLATFORM_ANDROID __ANDROID_API__
#elif defined(__VCCOREVER__)
// Raspberry Pi compiler defines __linux__
    #undef  SX_PLATFORM_RPI
    #define SX_PLATFORM_RPI 1
#elif defined(__linux__)
    #undef  SX_PLATFORM_LINUX
    #define SX_PLATFORM_LINUX 1
#elif defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__) \
   || defined(__ENVIRONMENT_TV_OS_VERSION_MIN_REQUIRED__)
    #undef  SX_PLATFORM_IOS
    #define SX_PLATFORM_IOS 1
#elif defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__)
    #undef  SX_PLATFORM_MACOS
    #define SX_PLATFORM_MACOS __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__
#elif defined(__EMSCRIPTEN__)
    #undef  SX_PLATFORM_EMSCRIPTEN
    #define SX_PLATFORM_EMSCRIPTEN 1
#elif defined(__ORBIS__)
    #undef  SX_PLATFORM_PS4
    #define SX_PLATFORM_PS4 1
#elif defined(__FreeBSD__)        \
   || defined(__FreeBSD_kernel__) \
   || defined(__NetBSD__)         \
   || defined(__OpenBSD__)        \
   || defined(__DragonFly__)
    #undef  SX_PLATFORM_BSD
    #define SX_PLATFORM_BSD 1
#elif defined(__GNU__)
    #undef  SX_PLATFORM_HURD
    #define SX_PLATFORM_HURD 1
#elif defined(__NX__)
    #undef  SX_PLATFORM_NX
    #define SX_PLATFORM_NX 1
#elif defined(__HAIKU__)
    #undef  SX_PLATFORM_HAIKU
    #define SX_PLATFORM_HAIKU 1
#endif // Platform

// C Runtime
// https://sourceforge.net/p/predef/wiki/Libraries/
#if !SX_CRT_NONE
    #if defined(__BIONIC__)
        #undef  SX_CRT_BIONIC
        #define SX_CRT_BIONIC 1
    #elif defined(_MSC_VER)
        #undef  SX_CRT_MSVC
        #define SX_CRT_MSVC 1
    #elif defined(__GLIBC__)
        #undef  SX_CRT_GLIBC
        #define SX_CRT_GLIBC (__GLIBC__ * 10000 + __GLIBC_MINOR__ * 100)
    #elif defined(_MINGW32__) || defined(__MINGW64__)
        #undef  SX_CRT_MINGW
        #define SX_CRT_MINGW 1
    #elif defined(__apple_build_version__) || defined(__ORBIS__) || defined(__EMSCRIPTEN__) || defined(__llvm__) || defined(__HAIKU__)
        #undef  SX_CRT_LIBCXX
        #define SX_CRT_LIBCXX 1
    #elif SX_PLATFORM_BSD
        #undef  SX_CRT_BSD
        #define SX_CRT_BSD 1
    #endif

    #if  !SX_CRT_BIONIC \
      && !SX_CRT_BSD    \
      && !SX_CRT_GLIBC  \
      && !SX_CRT_LIBCXX \
      && !SX_CRT_MINGW  \
      && !SX_CRT_MSVC   \
      && !SX_CRT_MUSL   \
      && !SX_CRT_NEWLIB
        #undef  SX_CRT_NONE
        #define SX_CRT_NONE 1
    #endif // SX_CRT_*
#endif // !SX_CRT_NONE

////////// Helpers

/// Posix platforms
#define SX_PLATFORM_POSIX (0   \
	||  SX_PLATFORM_ANDROID    \
	||  SX_PLATFORM_BSD        \
	||  SX_PLATFORM_EMSCRIPTEN \
	||  SX_PLATFORM_HAIKU      \
	||  SX_PLATFORM_HURD       \
	||  SX_PLATFORM_IOS        \
	||  SX_PLATFORM_LINUX      \
	||  SX_PLATFORM_NX         \
	||  SX_PLATFORM_MACOS      \
	||  SX_PLATFORM_PS4        \
	||  SX_PLATFORM_RPI        \
	)

/// Unknown platform
#define SX_PLATFORM_NONE !(0   \
	||  SX_PLATFORM_ANDROID    \
	||  SX_PLATFORM_BSD        \
	||  SX_PLATFORM_EMSCRIPTEN \
	||  SX_PLATFORM_HAIKU      \
	||  SX_PLATFORM_HURD       \
	||  SX_PLATFORM_IOS        \
	||  SX_PLATFORM_LINUX      \
	||  SX_PLATFORM_NX         \
	||  SX_PLATFORM_MACOS      \
	||  SX_PLATFORM_PS4        \
	||  SX_PLATFORM_RPI        \
	||  SX_PLATFORM_WINDOWS    \
	||  SX_PLATFORM_WINRT      \
	||  SX_PLATFORM_XBOXONE    \
	)

/// Console platforms
#define SX_PLATFORM_CONSOLE (0 \
	||  SX_PLATFORM_NX         \
	||  SX_PLATFORM_PS4        \
	||  SX_PLATFORM_WINRT      \
	||  SX_PLATFORM_XBOXONE    \
	)

/// Desktop platforms
#define SX_PLATFORM_DESKTOP (0 \
	||  SX_PLATFORM_BSD        \
	||  SX_PLATFORM_HAIKU      \
	||  SX_PLATFORM_HURD       \
	||  SX_PLATFORM_LINUX      \
	||  SX_PLATFORM_MACOS      \
	||  SX_PLATFORM_WINDOWS    \
	)

/// Embedded platforms
#define SX_PLATFORM_EMBEDDED (0 \
	||  SX_PLATFORM_RPI         \
	)

/// Mobile platforms
#define SX_PLATFORM_MOBILE (0 \
	||  SX_PLATFORM_ANDROID   \
	||  SX_PLATFORM_IOS       \
	)

/// Web platforms
#define SX_PLATFORM_WEB      (0 \
	||  SX_PLATFORM_EMSCRIPTEN  \
	)

/// Compiler name
#if SX_COMPILER_GCC
    #define SX_COMPILER_NAME "GCC "      \
		SX_STRINGIZE(__GNUC__) "."       \
		SX_STRINGIZE(__GNUC_MINOR__) "." \
		SX_STRINGIZE(__GNUC_PATCHLEVEL__)
#elif SX_COMPILER_CLANG
    #define SX_COMPILER_NAME "Clang "     \
		SX_STRINGIZE(__clang_major__) "." \
		SX_STRINGIZE(__clang_minor__) "." \
		SX_STRINGIZE(__clang_patchlevel__)
#elif SX_COMPILER_MSVC
    #if SX_COMPILER_MSVC >= 1920 // Visual Studio 2019
        #define SX_COMPILER_NAME "MSVC 16.0"
    #elif SX_COMPILER_MSVC >= 1910 // Visual Studio 2017
        #define SX_COMPILER_NAME "MSVC 15.0"
    #elif SX_COMPILER_MSVC >= 1900 // Visual Studio 2015
        #define SX_COMPILER_NAME "MSVC 14.0"
    #elif SX_COMPILER_MSVC >= 1800 // Visual Studio 2013
        #define SX_COMPILER_NAME "MSVC 12.0"
    #elif SX_COMPILER_MSVC >= 1700 // Visual Studio 2012
        #define SX_COMPILER_NAME "MSVC 11.0"
    #elif SX_COMPILER_MSVC >= 1600 // Visual Studio 2010
        #define SX_COMPILER_NAME "MSVC 10.0"
    #elif SX_COMPILER_MSVC >= 1500 // Visual Studio 2008
        #define SX_COMPILER_NAME "MSVC 9.0"
    #else
        #define SX_COMPILER_NAME "MSVC"
    #endif //
#endif // SX_COMPILER_*

/// Platform name
#if SX_PLATFORM_ANDROID
    #define SX_PLATFORM_NAME "Android " \
	    SX_STRINGIZE(SX_PLATFORM_ANDROID)
#elif SX_PLATFORM_BSD
    #define SX_PLATFORM_NAME "BSD"
#elif SX_PLATFORM_EMSCRIPTEN
    #define SX_PLATFORM_NAME "asm.js "         \
		SX_STRINGIZE(__EMSCRIPTEN_major__) "." \
		SX_STRINGIZE(__EMSCRIPTEN_minor__) "." \
		SX_STRINGIZE(__EMSCRIPTEN_tiny__)
#elif SX_PLATFORM_HAIKU
    #define SX_PLATFORM_NAME "Haiku"
#elif SX_PLATFORM_HURD
    #define SX_PLATFORM_NAME "Hurd"
#elif SX_PLATFORM_IOS
    #define SX_PLATFORM_NAME "iOS"
#elif SX_PLATFORM_LINUX
    #define SX_PLATFORM_NAME "Linux"
#elif SX_PLATFORM_NONE
    #define SX_PLATFORM_NAME "None"
#elif SX_PLATFORM_NX
    #define SX_PLATFORM_NAME "NX"
#elif SX_PLATFORM_MACOS
    #define SX_PLATFORM_NAME "macOS"
#elif SX_PLATFORM_PS4
    #define SX_PLATFORM_NAME "PlayStation 4"
#elif SX_PLATFORM_RPI
    #define SX_PLATFORM_NAME "Raspberry Pi"
#elif SX_PLATFORM_WINDOWS
    #define SX_PLATFORM_NAME "Windows"
#elif SX_PLATFORM_WINRT
    #define SX_PLATFORM_NAME "WinRT"
#elif SX_PLATFORM_XBOXONE
    #define SX_PLATFORM_NAME "Xbox One"
#else
    #error "Unknown SX_PLATFORM!"
#endif // SX_PLATFORM_*

/// CPU name
#if SX_CPU_ARM
    #define SX_CPU_NAME "ARM"
#elif SX_CPU_JIT
    #define SX_CPU_NAME "JIT-VM"
#elif SX_CPU_MIPS
    #define SX_CPU_NAME "MIPS"
#elif SX_CPU_PPC
    #define SX_CPU_NAME "PowerPC"
#elif SX_CPU_RISCV
    #define SX_CPU_NAME "RISC-V"
#elif SX_CPU_X86
    #define SX_CPU_NAME "x86"
#endif // SX_CPU_

// C Runtime name
#if SX_CRT_BIONIC
    #define SX_CRT_NAME "Bionic libc"
#elif SX_CRT_BSD
    #define SX_CRT_NAME "BSD libc"
#elif SX_CRT_GLIBC
    #define SX_CRT_NAME "GNU C Library"
#elif SX_CRT_MSVC
    #define SX_CRT_NAME "MSVC C Runtime"
#elif SX_CRT_MINGW
    #define SX_CRT_NAME "MinGW C Runtime"
#elif SX_CRT_LIBCXX
    #define SX_CRT_NAME "Clang C Library"
#elif SX_CRT_NEWLIB
    #define SX_CRT_NAME "Newlib"
#elif SX_CRT_MUSL
    #define SX_CRT_NAME "musl libc"
#elif SX_CRT_NONE
    #define SX_CRT_NAME "None"
#else
    #error "Unknown SX_CRT!"
#endif // SX_CRT_*

// Architecture name
#if SX_ARCH_32BIT
    #define SX_ARCH_NAME "32-bit"
#elif SX_ARCH_64BIT
    #define SX_ARCH_NAME "64-bit"
#endif // SX_ARCH_*

// C++ language standard name
#if SX_COMPILER_MSVC
    #if defined(_MSVC_LANG)
        #if _MSVC_LANG < 201103L
            #error "Pre-C++11 compiler is not supported!"
        #elif _MSVC_LANG < 201402L
            #define SX_CPP_NAME "C++11"
        #elif __cplusplus < 201703L
            #define SX_CPP_NAME "C++14"
        #elif __cplusplus < 201704L
            #define SX_CPP_NAME "C++17"
        #else
            #define SX_CPP_NAME "C++ MSVC Unknown"
        #endif // SX_CPP_NAME
    #endif // defined(_MSVC_LANG)
#elif defined(__cplusplus)
    #if __cplusplus < 201103L
        #error "Pre-C++11 compiler is not supported!"
    #elif __cplusplus < 201402L
        #define SX_CPP_NAME "C++11"
    #elif __cplusplus < 201703L
        #define SX_CPP_NAME "C++14"
    #elif __cplusplus < 201704L
        #define SX_CPP_NAME "C++17"
    #else
        // See: https://gist.github.com/bkaradzic/2e39896bc7d8c34e042b#orthodox-c
        #define SX_CPP_NAME "C++WayTooModern"
    #endif // SX_CPP_NAME
#else
    #define SX_CPP_NAME "C++ Unknown"
#endif // defined(__cplusplus)

// C language standard name
#if defined(__STDC__)
    #if defined(__STDC_VERSION__)
        #if __STDC_VERSION__ < 199901L
          #error "Pre-C99 compiler is not supported!"
        #elif __STDC_VERSION__ < 201112L
            #define SX_CXX_NAME "C99"
        #elif __STDC_VERSION__ < 201710L
            #define SX_CXX_NAME "C11"
        #elif __STDC_VERSION__ < 201711L
            #define SX_CXX_NAME "C18"
        #else
            #define SX_CXX_NAME "C WayTooModern"
        #endif
    #else
        #define SX_CXX_NAME "C Unknown"
    #endif
#else
    #define SX_CXX_NAME "C Unknown"
#endif // defined(__STDC__)


#endif // __SX_PLATFORM_H__