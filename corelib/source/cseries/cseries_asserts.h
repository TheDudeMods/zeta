#pragma once

/* ---------- macros */

#define vassert(expr, diag) if (!(expr)) assert_halt(diag, __FILE__, __LINE__)
#define assert(expr) vassert(expr, #expr)

/* ---------- prototypes/CSERIES_ASSERTS.CPP */

[[noreturn]]
void assert_halt(char const *message, char const *file, unsigned long line);
