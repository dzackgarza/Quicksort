/*****************************************************

    Zack Garza
    CISP 430 - TTH 5:30 pm
    Programming Project 4 - Recursive Sorting / Quicksort
    24 October 2013

*****************************************************/

#include "Quicksort1.h"
#include <iostream>
#include <time.h>
#include <sys/timeb.h>

#define elems 50000
#define trials 10
using namespace std;

//  Function Prototypes
//  -----------------------------------------------------
int item_cmp(const void*, const void*);
void fcmp_test();
void swap_test();
void swp(void*, void*, size_t);
void SwpIndex(void* &i1, void* &i2);
void test_swpind();
void test_ooo();
void test_ooo2(void*, void* &b, void* &c, unsigned, int);
bool ooo(void* p, void* other_end, bool pivot_first,
                  int (*fcmp)(const void*, const void*) );
double fRand(double fMin, double fMax);
string random_string( size_t length );
double iRand(int fMin, int fMax);
double TIME();
static ItemType array[elems];
void call_new_test();
//  -----------------------------------------------------

int main()
{
    //call_new_test();
    //return 0;
    srand (time(NULL));
    double TimeInit, TimeFinal, qs_Time_Total = 0, custom_qs_Time_Total = 0;

    // Qsort
    for(unsigned i = 0; i < trials; i++)
    {
        cout << "Trial " << i+1 << " started.\n";
        for (unsigned i = 0; i < elems; i++)
            array[i] = rand() % 100;

        double TimeInit = TIME();
        qsort(array, (size_t)elems, (size_t) sizeof(ItemType), *item_cmp);
        double TimeFinal = TIME();
        qs_Time_Total += TimeFinal - TimeInit;
        cout << "Trial " << i+1 << " completed.\n";
    }
    qs_Time_Total = qs_Time_Total/trials;
    cout << "Qsort completed. Average time: " << qs_Time_Total << "ms.\n\n";

    // Custom Quicksort
    for (unsigned i = 0; i < trials; i++)
    {
        cout << "Trial " << i+1 << " started.\n";
        for (unsigned i = 0; i < elems; i++)
            array[i] = rand() % 100;

        TimeInit = TIME();
        Quicksort2(array, (size_t)elems, (size_t) sizeof(ItemType), *item_cmp);
        TimeFinal = TIME();
        custom_qs_Time_Total += TimeFinal - TimeInit;
        cout << "Trial " << i+1 << " completed.\n";
    }
    custom_qs_Time_Total = custom_qs_Time_Total/trials;
    cout << "Custom Quicksort completed. Average time: " << custom_qs_Time_Total << "ms.\n\n";

    // Results
    cout << "Custom is " << custom_qs_Time_Total/qs_Time_Total << " times slower." << endl;
    return 0;
}

int item_cmp(const void* i1, const void* i2)
{
    const ItemType* a = static_cast<const ItemType*>(i1);
    const ItemType* b = static_cast<const ItemType*>(i2);

    if (*a > *b) return 1;
    else if (*a < *b) return -1;
    else return 0;
}

double TIME ( void )
{
    struct timeb t;
    ftime(&t);
    return ( ( (1000.0 * t.time) + t.millitm ) );
}

// Generates random doubles.
double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

// Generates random integers.
double iRand(int fMin, int fMax)
{
    int f = (int)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

// Generates random strings.
string random_string( size_t length )
{
    char alphanum[] =
    "abcdefghijklmnopqrstuvwxyz";
    int stringLength = sizeof(alphanum) - 1;
    std:string Str;

    for(unsigned int i = 0; i < 5; ++i)
    {
        Str += alphanum[rand() % stringLength];
    }
    return Str;
}

void call_new_test()
{
    string a[100];
    for(unsigned i = 0; i < 100; i++)
        a[i] = random_string(5);
    for (unsigned i = 0; i < 100; i++)
        cout << "String " << i << ": " << a[i] << endl;

    Quicksort2(a, (size_t) 100, (size_t) sizeof(string), *item_cmp);
    cout << "Sorted." << endl;
    for (unsigned i = 0; i < 100; i++)
        cout << "String " << i << ": " << a[i] << endl;
    cout << endl;
}
/*
#define item int
void test_ooo()
{
    item a[4];
    unsigned width = sizeof(item);
    int num_elems = 5;
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;
    a[3] = 4;
    a[4] = 5;

    void* pivot;
    void* oe;
    bool pivot_first = true;
    test_ooo2(a, pivot, oe, width, num_elems);

    for (unsigned i = 0; i < num_elems; i++)
    {
        cout << a[i];
        if (&a[i] == pivot) cout << " (Pivot)";
        if (&a[i] == oe) cout << " (OE)";
        cout << endl;
    }

    std::cout << "Value of pivot is: " << *(item*)pivot << std::endl;
    std::cout << "Value of OE is: " << *(item*)oe << std::endl;
    std::cout << "Out of order is ";
    std::cout << (ooo(pivot, oe, pivot_first, item_cmp) ? "True\n" : "False\n");
    cout<<"--------------------------------------------"<<endl;

    //SwapItem(pivot, oe, width);
    //SwapIndex(pivot, oe);
    pivot_first = !pivot_first;

    for (unsigned i = 0; i < num_elems; i++)
    {
        cout << a[i];
        if (&a[i] == pivot) cout << " (Pivot)";
        if (&a[i] == oe) cout << " (OE)";
        cout << endl;
    }

    std::cout << "\n\nValue of pivot is: " << *(item*)pivot << std::endl;
    std::cout << "Value of OE is: " << *(item*)oe << std::endl;
    std::cout << "Out of order is ";
    std::cout << (ooo(pivot, oe, pivot_first, item_cmp) ? "True\n" : "False\n");
    cout << endl;

    cout << "Is pivot (" << *(item*)pivot << ")  >  OE (" << *(item*)oe<< ") ?" << endl;
    int cmp = item_cmp(pivot, oe);
    cout << "fcmp says: ";
    switch(cmp)
    {
        case -1: cout << "False"; break;
        case 1: cout << "True"; break;
        case 0: cout << "Equal"; break;
    }
}

void test_ooo2(void* it, void* &pivot, void* &oe, unsigned width, int num_elems)
{
    pivot = it + (1 * width);
    if ( (it + (4 * width)) < (it + (num_elems * width)) )
        oe = it + (3 * width);
    else oe = it + (0 * width);
}

// Returns true if the pivot's position is before OE AND pivot's value is less than OE's.
// Has the effect of moving all values less than pivot to the left and
// values greater than pivot to the right.
bool ooo(void* p, void* other_end, bool pivot_first,
                  int (*fcmp)(const void*, const void*) )
{
    int cmp = fcmp(p, other_end);
    return ( pivot_first && cmp > 0 ||
             !pivot_first && cmp < 0 );
}

void test_swpind()
{
    cout << "Testing cmp function." << endl;
    int *a = new int;
    *a = 10;
    int *b = new int;
    *b = 11;
    cout << *a << " | " << *b << endl;
    void* v1 = (void*) a;
    void* v2 = (void*) b;
    SwpIndex( v1, v2 );
    a = static_cast<int*>(v1);
    b = static_cast<int*>(v2);
    cout << *a << " | " << *b << endl;
}

void SwpIndex(void* &i1, void* &i2)
{
    void* temp = i1;
    i1 = i2;
    i2 = temp;
}
// Tested, works.


void swap_test()
{
     cout << "Testing cmp function." << endl;
    int a[2];
    a[0] = 10;
    a[1] = 11;
    cout << a[0] << " | " << a[1] << endl;
    void* a1 = &a[0];
    void* a2 = &a[1];
    SwapItem( a1, a2, sizeof(int));
    cout << a[0] << " | " << a[1] << endl;
}


void fcmp_test()
{
    cout << "Testing cmp function.";
    int a[2];
    a[0] = 10;
    a[1] = 11;
    int res = item_cmp( (void*)a[0], (void*) a[1]);
    cout << endl;
    switch(res)
    {
        case 0: cout << a[0] << " = " << a[1] << endl; break;
        case 1: cout << a[0] << " < " << a[1] << endl; break;
        case -1: cout << a[0] << " > " << a[1] << endl; break;
    }

}
*/
