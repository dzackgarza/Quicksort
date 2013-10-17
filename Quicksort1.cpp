/*****************************************************

    Zack Garza
    CISP 430 - TTH 5:30 pm
    Programming Project 4 - Recursive Sorting
    24 October 2013

*****************************************************/

#include "Quicksort1.h"

void Quicksort( ItemType* it, size_t nelem,
                int (*fcmp)(const ItemType&, const ItemType&) )
{
    if (nelem <= 1) return;
    unsigned pivot = Partition(it, nelem, fcmp);
    Quicksort(it,pivot, fcmp);
    Quicksort(it+pivot+1, nelem-pivot, fcmp);
}

unsigned Partition(ItemType* it, size_t nelem,
                   int (*fcmp)(const ItemType&, const ItemType&) )
{
    unsigned pivot = 0;
    unsigned oe = nelem - 1;
    while (pivot != oe)
    {
        if (pivot > oe)
        {

        }
        else
        {

        }
    }
}

int fcmp(ItemType& i1, ItemType& i2)
{
    if (i1 > i2) return 1;
    else if (i1 < i2) return -1;
    else return 0;
}
