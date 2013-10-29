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

// Chooses the first item in the subset as a pivot point.
// Moves the pivot into its final position, with values less
// than it moved to the left and values greater to the right.
static void* Partition(void* it, size_t nelem, size_t width,
                   int (*fcmp)(const void*, const void*) );

// Returns true if the pivot's position is before OE AND pivot's value is less than OE's.
// Has the effect of moving all values less than pivot to the left and
// values greater than pivot to the right.
static bool OutOfOrder(void* p, void* other_end, bool pivot_first,
                  int (*fcmp)(const void*, const void*) );

// Swaps what two pointers point to.
static void SwapIndex(void* &i1, void* &i2);

// Swaps the values bit by bit at two addresses.
static void SwapItem(void* &i1, void* &i2, size_t);

// Moves to OE pointer toward the pivot pointer.
static void MoveIndex(void* it, void* &oe, size_t width, bool, size_t);
//  -----------------------------------------------------

void Quicksort2( void* first_elem, size_t num_elem, size_t width,
                int (*fcmp)( const void*, const void* ) )
{
    if (num_elem <= 1) return;

    void* temp_pivot = Partition(first_elem, num_elem, width, fcmp);
    // Pivot is now in its final position, so sort each remaining half.

    char* first_item = static_cast<char*>(first_elem);
    char* pivot = static_cast<char*>(temp_pivot);
    char* last_item = static_cast<char*>(first_item + (num_elem * width));

    // pivot - item = number of bytes between the pointers. Scale by width
    // to get number of elements.
    unsigned num_LHS_elems = (pivot - first_item) / width;
    unsigned num_RHS_elems = (last_item - pivot - 1) / width;

    // Should be the first element after the pivot.
    void* RHS_first_element = (char*)first_elem + (num_LHS_elems * width) + width;

    // From first element to element at (pivot - 1).
    if (num_LHS_elems != 0)
        Quicksort2( first_elem, num_LHS_elems, width, fcmp );

    // From element at (pivot + 1) to last.
    if (num_RHS_elems != 0)
        Quicksort2( RHS_first_element, num_RHS_elems, width, fcmp );
}

static void* Partition( void* it, size_t num_elems, size_t width,
                   int (*fcmp)(const void*, const void*) )
{
    // Choose the first item as the pivot.
    void* pivot = it;
    // The last item is the "other end".
    void* oe = (char*)it + (width * (num_elems - 1));
    // Keep track of the pivot's relative position to oe.
    bool pivot_first = true;

    while (pivot != oe) // While pointers do not contain the same addresses - i.e., they do not point to the same thing.
    {
        // Only move things if the pivot is on the left and its value is greater than oe,
        // or if pivot is on the right and its value is less than oe.
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

static bool OutOfOrder(void* p, void* other_end, bool pivot_first,
                  int (*fcmp)(const void*, const void*) )
{
    int cmp = fcmp(p, other_end);
    return ( (pivot_first && cmp > 0) ||
             (!pivot_first && cmp < 0) );
}

// Move OE toward Pivot.
static void MoveIndex(void* item, void* &other_end, size_t width, bool pivot_first, size_t num_elems)
{
    char* it = static_cast<char*>(item);
    char* oe = static_cast<char*>(other_end);

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
    item = it;
    other_end = oe;
}

// Swap two pointers.
static void SwapIndex(void* &i1, void* &i2)
{
    void* temp = i1;
    i1 = i2;
    i2 = temp;
}

// Swap the contents of two pointers byte by byte.
static void SwapItem(void* &item_1, void* &item_2, size_t width)
{
    // Cast to temp char* variables to read one byte at a time.
    char* i1 = static_cast<char*>(item_1);
    char* i2 = static_cast<char*>(item_2);

    // Walk through i bytes (the size of the item) and swap memory contents.
    for (unsigned i=0; i < width ; i++)
    {
     char temp = i1[i];
     i1[i] = i2[i];
     i2[i] = temp;
    }
    // Write swapped values back to original memory locations.
    item_1 = i1;
    item_2 = i2;
}
