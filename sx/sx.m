#include "sx.h"
#include "platform.h"

#if SX_PLATFORM_IOS

void sx_printf(const char *fmt, ...) {
    va_list args;
    va_start( args,fmt );
    NSLog( @"SX: %@",[[NSString alloc] initWithFormat:[NSString stringWithUTF8String:fmt] arguments:args] );
    va_end(args);
}

#endif