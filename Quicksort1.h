/*****************************************************

    Zack Garza
    CISP 430 - TTH 5:30 pm
    Programming Project 4 - Recursive Sorting
    24 October 2013

*****************************************************/
#ifndef QUICK_SORT_H
#define QUICK_SORT_H
#define ItemType int
#include <cstdlib>
void Quicksort( ItemType*, size_t,
                int (*)(const ItemType&, const ItemType&) );

unsigned Partition(ItemType*, size_t,
                   int (*)(const ItemType&, const ItemType&) )


int fcmp(ItemType&, ItemType&);
#endif
