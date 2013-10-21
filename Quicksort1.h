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

void Quicksort( ItemType*, size_t,
                int (*)(const ItemType&, const ItemType&) );

unsigned Partition(ItemType*, size_t,
                   int (*)(const ItemType&, const ItemType&) );

void SwapIndex(unsigned& i1, unsigned& i2);

void SwapItem(ItemType*, unsigned&, unsigned&);

void ptrswap(int** a, int** b);

bool OutOfOrder(ItemType*, unsigned, unsigned);

void MoveIndex(unsigned&, unsigned&);

bool OutOfOrder (ItemType*, unsigned, unsigned,
                  int (*fcmp)(const ItemType&, const ItemType&) );

#endif
