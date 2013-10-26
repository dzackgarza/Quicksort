/*****************************************************

    Zack Garza
    CISP 430 - TTH 5:30 pm
    Programming Project 4 - Recursive Sorting / Quicksort
    24 October 2013

*****************************************************/

#ifndef QUICK_SORT_H
#define QUICK_SORT_H
#define ItemType int
#include <cstdlib>
void Quicksort2( void* base, size_t nelem, size_t width,
                int (*fcmp)( const void*, const void* ) );
#endif
