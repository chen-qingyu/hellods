#ifndef CHECK_FULL_H
#define CHECK_FULL_H

#include <stdio.h>
#include <stdlib.h>

// Check whether there is any remaining capacity.
static inline void check_full(int size, int capacity)
{
    if (size == capacity)
    {
        fprintf(stderr, "ERROR: The container has reached the maximum size: %d.\n", capacity);
        exit(EXIT_FAILURE);
    }
}

#endif // CHECK_FULL_H
