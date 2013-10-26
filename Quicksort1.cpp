/*****************************************************

    Zack Garza
    CISP 430 - TTH 5:30 pm
    Programming Project 4 - Recursive Sorting / Quicksort
    24 October 2013

*****************************************************/

#include "Quicksort1.h"
#include <iostream>
#include <cstdlib>
using namespace std;


//  Function Prototypes
//  -----------------------------------------------------
void* Partition(void* it, size_t nelem, size_t width,
                   int (*fcmp)(const void*, const void*) );

void SwapIndex(void* &i1, void* &i2);

void SwapItem(void* &i1, void* &i2, size_t);

void ptrswap(int** a, int** b);

void MoveIndex(void* it, void* &oe, size_t width, bool, size_t);

bool OutOfOrder(void* p, void* other_end, bool pivot_first,
                  int (*fcmp)(const void*, const void*) );
//  -----------------------------------------------------

void Quicksort2( void* first_elem, size_t num_elem, size_t width,
                int (*fcmp)( const void*, const void* ) )
{
    if (num_elem <= 1) return;

    void* temp_pivot = Partition(first_elem, num_elem, width, fcmp);
    char* item = static_cast<char*>(first_elem);
    char* pivot = static_cast<char*>(temp_pivot);
    char* last_item = static_cast<char*>(item + (num_elem * width));
    char* temp = item;
    cout << endl;
    while (temp != last_item)
    {
        cout << *(ItemType*)temp;
        if (temp == pivot) cout << " (Pivot) ";
        cout << "|";
        temp += width;
    }
    cout << endl;
    int LHS_elems = ( pivot - item ) / width;
    std::cout << "\nNumber of LHS elements: " << LHS_elems << std::endl;

    int RHS_elems = (last_item - pivot - 1) / width;
    std::cout << "\nNumber of RHS elements: " << RHS_elems << std::endl;


    if (LHS_elems != 0)
    {
        cout << "Sorting LHS" << endl;
        Quicksort2( first_elem, LHS_elems, width, fcmp );
    }
    temp = item;
    cout << "After Sorting LHS: ";
    while (temp != last_item)
    {
        cout << *(ItemType*)temp;
        if (temp == pivot) cout << " (Pivot) ";
        cout << "|";
        temp += width;
    }
    cout << endl;

    if (RHS_elems != 0)
    {
        cout << "Sorting RHS" << endl;
        Quicksort2( (char*)first_elem + (LHS_elems*width) + width, RHS_elems, width, fcmp );
    }
    temp = item;
    cout << "After Sorting RHS: ";
    while (temp != last_item)
    {
        cout << *(ItemType*)temp;
        if (temp == pivot) cout << " (Pivot) ";
        cout << "|";
        temp += width;
    }
    cout << endl;

    std::cout << "Done." << std::endl;
}

void* Partition( void* it, size_t num_elems, size_t width,
                   int (*fcmp)(const void*, const void*) )
{
    void* pivot = it;
    void* oe = it + (width * (num_elems - 1));
    bool pivot_first = true;

    while (pivot != oe) // While pointers do not contain the same addresses - i.e., they do not point to the same thing.
    {
        if (OutOfOrder(pivot, oe, pivot_first, fcmp))
        {
            // Swap values
            SwapItem(pivot, oe, width);
            // Swap pointers
            SwapIndex(oe, pivot);
            // Pivot is now in the opposite position
            pivot_first = !pivot_first;
        }
        // Move OE toward Pivot
        MoveIndex(it, oe, width, pivot_first, num_elems);
    }
    return pivot;
}

bool OutOfOrder(void* p, void* other_end, bool pivot_first,
                  int (*fcmp)(const void*, const void*) )
{
    int cmp = fcmp(p, other_end);
    return ( pivot_first && cmp > 0 ||
             !pivot_first && cmp < 0 );
}

void MoveIndex(void* i1, void* &o1, size_t width, bool pivot_first, size_t num_elems)
{
    char* it = static_cast<char*>(i1);
    char* oe = static_cast<char*>(o1);

    if (pivot_first)
    {
        if (oe - width >= it)   // Don't move OE beyond the first element of the array.
            oe = oe - width;
    }
    else
    {
        if ( oe + width <= it + width*(num_elems-1) ) // Or beyond the last element. Somehow.
            oe = oe + width;
    }
    i1 = it;
    o1 = oe;
}

void SwapIndex(void* &i1, void* &i2)
{
    void* temp = i1;
    i1 = i2;
    i2 = temp;
}

void SwapItem(void* &item_1, void* &item_2, size_t width)
{
    char* i1 = static_cast<char*>(item_1);
    char* i2 = static_cast<char*>(item_2);

    for (unsigned i=0; i < width - 1; i++)
    {
     char temp = i1[i];
     i1[i] = i2[i];
     i2[i] = temp;
    }
    item_1 = i1;
    item_2 = i2;
}

//////////////
/*void Quicksort( ItemType* first_elem, size_t num_elem,
                int (*fcmp)(const ItemType&, const ItemType&) )
{
    if (num_elem <= 1) return;

    unsigned pivot = Partition(first_elem, num_elem, fcmp);

    Quicksort(first_elem, pivot, fcmp);
    Quicksort( (first_elem + pivot + 1), (num_elem - pivot - 1), fcmp);
}

unsigned Partition(ItemType* it, size_t nelem,
                   int (*fcmp)(const ItemType&, const ItemType&) )
{
    unsigned pivot = 0, oe = (nelem - 1);

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

*/
