#include <stdarg.h>

#include "sx.h"
#include "platform.h"

int sx_argc;
char **sx_argv;
int sx_main(int argc, char *argv[]);

#if SX_PLATFORM_ANDROID
    //TODO: sx_print, sx_printf
#elif !SX_PLATFORM_IOS

void sx_printf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    fflush(stdout);
}

#endif

//--------------------------------------------------------------
//
// Main entry point
//
//--------------------------------------------------------------
#if SX_PLATFORM_MOBILE
extern "C" int SDL_main(int argc, char *argv[]) {
#else
int main(int argc, char *argv[]) {
#endif

    sx_argc = argc;
    sx_argv = argv;
    return sx_main(argc, argv);
}

