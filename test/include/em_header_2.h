#ifndef EM_HEADER_2
#define EM_HEADER_2

#include <stdlib.h>

int em_open(const char *file, int oflag, ...);
int em_snprintf(char *str, size_t size, const char *format, ...);

#endif
