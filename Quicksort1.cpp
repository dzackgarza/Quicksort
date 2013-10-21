/*****************************************************

    Zack Garza
    CISP 430 - TTH 5:30 pm
    Programming Project 4 - Recursive Sorting
    24 October 2013

*****************************************************/

#include "Quicksort1.h"
#include <iostream>
#define tfcmp(a,b)  (a > b)

void Quicksort( ItemType* first_elem, size_t num_elem,
                int (*fcmp)(const ItemType&, const ItemType&) )
{
    if (num_elem <= 1) return;

    unsigned pivot = Partition(first_elem, num_elem, fcmp);

    Quicksort(first_elem, pivot, fcmp);
    Quicksort(first_elem + pivot + 1, num_elem-pivot-1, fcmp);
}

unsigned Partition(ItemType* it, size_t nelem,
                   int (*fcmp)(const ItemType&, const ItemType&) )
{
    unsigned pivot = 0;
    unsigned oe = (nelem - 1);

    while (pivot != oe)
    {
        if (OutOfOrder(it, pivot, oe, fcmp))
        {
            SwapItem(it, pivot, oe);    // Swap values
            SwapIndex(oe, pivot);       // Swap pointers/indices
        }
        MoveIndex(pivot, oe);           // Move OE toward Pivot
    }
    return pivot;
}

void MoveIndex(unsigned& pivot, unsigned& oe)
{
    if (pivot < oe) oe--; else oe++;
}

bool OutOfOrder (ItemType* it, unsigned pivot, unsigned oe,
                  int (*fcmp)(const ItemType&, const ItemType&) )
{
    return (pivot > oe && fcmp(it[pivot], it[oe]) > 0 ||
            pivot < oe && fcmp(it[oe], it[pivot]) > 0 );
}

int fcmp(ItemType& i1, ItemType& i2)
{
    if (i1 > i2) return 1;
    else if (i1 < i2) return -1;
    else return 0;
}

void SwapItem(ItemType* it, unsigned& i1, unsigned& i2)
{
    ItemType temp = it[i1];
    it[i1] = it[i2];
    it[i2] = temp;
}

void SwapIndex(unsigned& i1, unsigned& i2)
{
    unsigned temp = i1;
    i1 = i2;
    i2 = temp;
}
