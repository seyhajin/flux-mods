#ifndef __SX_H__
#define __SX_H__

#include "std.h"

extern int sx_argc;
extern char **sx_argv;

//extern void sx_print(sxString str);
extern void sx_printf(const char *fmt, ...);

#endif //!__SX_H__