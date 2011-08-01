#include <math.h>

int check_flat(bx,by,degree,tol)
/* Checks if a polygon is flat. If all points
   are closer  than tol to the connection of the 
   two endpoints, then it is flat. Crashes if the endpoints  
   are identical.

Input:	bx,by, degree: the Bezier curve
	tol:            tolerance

*/
	float bx[],by[];
	int degree; float tol;
{
	float dist;
	int i;
	float height();

	for (i=1; i<degree; i++)
	{
		dist = height(bx[i],by[i],bx[0],by[0],
			bx[degree],by[degree]);
		if (fabs(dist) > tol)  return(0);
	}
	
	return(1);
}

