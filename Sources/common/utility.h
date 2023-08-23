#ifndef UTILITY_H
#define UTILITY_H

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

// Check whether is not empty.
static inline void check_empty(int size)
{
    if (size == 0)
    {
        fprintf(stderr, "ERROR: The container is empty.\n");
        exit(EXIT_FAILURE);
    }
}

// Check whether there is any remaining capacity.
static inline void check_full(int size, int capacity)
{
    if (size >= capacity)
    {
        fprintf(stderr, "ERROR: The container has reached the maximum size: %d.\n", capacity);
        exit(EXIT_FAILURE);
    }
}

// Check whether the pointer is a non-null pointer.
static inline void check_pointer(const void* pointer)
{
    if (pointer == NULL)
    {
        fprintf(stderr, "ERROR: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
}

#endif // UTILITY_H
