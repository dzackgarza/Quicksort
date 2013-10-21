/*****************************************************

    Zack Garza
    CISP 430 - TTH 5:30 pm
    Programming Project 4 - Recursive Sorting
    24 October 2013

*****************************************************/

#include "Quicksort1.h"
#include <cstdlib>
#include <iostream>
#include <time.h>
#define elems 20
using namespace std;

int fcmp(const ItemType&, const ItemType&);

int main()
{
    int array[elems];
    srand (time(NULL));
    for (unsigned i = 0; i < elems; i++)
    {
        array[i] = rand() % elems;
    }
    size_t nelem = elems;
    Quicksort(array, nelem, *fcmp);
    cout << endl;
    for (unsigned i = 0; i < elems; i++)
    {
        cout << array[i] << "|";
    }
    return 0;
}

 int fcmp(const ItemType& i1, const ItemType& i2)
 {
     return i1 < i2;
 }
