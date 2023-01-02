#ifndef CHECK_EMPTY_H
#define CHECK_EMPTY_H

#include <stdio.h>
#include <stdlib.h>

// Check whether is not empty.
static inline void check_empty(int size)
{
    if (size == 0)
    {
        fprintf(stderr, "ERROR: The container is empty.\n");
        exit(EXIT_FAILURE);
    }
}

#endif // CHECK_EMPTY_H
