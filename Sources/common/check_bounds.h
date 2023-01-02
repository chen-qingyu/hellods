#ifndef CHECK_BOUNDS_H
#define CHECK_BOUNDS_H

#include <stdio.h>
#include <stdlib.h>

// Check whether the index is valid (begin <= pos < end).
static inline void check_bounds(int pos, int begin, int end)
{
    if (pos < begin || pos >= end)
    {
        fprintf(stderr, "ERROR: Out of range: %d not in [%d, %d).\n", pos, begin, end);
        exit(EXIT_FAILURE);
    }
}

#endif // CHECK_BOUNDS_H
