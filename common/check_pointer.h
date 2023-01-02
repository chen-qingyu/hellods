#ifndef CHECK_POINTER_H
#define CHECK_POINTER_H

#include <stdio.h>
#include <stdlib.h>

// Check whether the pointer is a non-null pointer.
static inline void check_pointer(const void* pointer)
{
    if (pointer == NULL)
    {
        fprintf(stderr, "ERROR: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
}

#endif // CHECK_POINTER_H
