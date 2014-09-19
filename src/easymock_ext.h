
// pycparser does not parse any compiler (gcc) extensions
// so we need to define them out

#define __attribute__(x)
#define __asm__(x)
#define __builtin_offsetof(x,y) 0

#define __const const
#define __inline
#define __inline__
#define __extension__
#define __restrict
#define __builtin_va_list void
