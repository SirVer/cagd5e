#include <math.h>

float dist(a,b)
/* finds distance between 2D points a   and b.

Input: a,b:	points;
*/
	float a[], b[];
{
	return(sqrt((a[0]-b[0])*(a[0]-b[0])+
	            (a[1]-b[1])*(a[1]-b[1]) ) );
}

