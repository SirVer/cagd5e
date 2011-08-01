#include <math.h>
float length_2(a)

/* computes length of vector a
input:	a
output:	length
*/
float a[];

{float x;
	x=sqrt(a[0]*a[0]+a[1]*a[1]);
	return(x);
}

