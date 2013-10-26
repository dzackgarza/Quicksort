
#include "DEFtime.h"
#include <time.h>
#include <sys\timeb.h>
#include <iostream>


// returns time in milliseconds since January 1 1970.
double TIME ( void )
{
	struct timeb t;
   ftime(&t);
   return ( ( (1000.0 * t.time) + t.millitm ) );
}


