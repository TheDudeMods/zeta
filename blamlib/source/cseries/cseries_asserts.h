#pragma once

/* ---------- macros */

#ifdef _DEBUG
#define vassert(expr, diag) if (!(expr)) assert_halt(diag, __FILE__, __LINE__)
#else
#define vassert(expr, diag) (expr)
#endif 

#define assert(expr) vassert(expr, #expr)

/* ---------- prototypes/CSERIES_ASSERTS.CPP */

[[noreturn]]
void assert_halt(char const *message, char const *file, unsigned long line);
