#include <math.h>

void parameters(data_x,data_y,l,knot)
/*	Finds a centripetal parametrization for a given set
	of 2D data points. 
Input:	data_x, data_y:	input points, numbered from 0 to l+2. 
	l:		number of intervals.
Output:	knot:		knot sequence. Note: not (knot[l]=1.0)!
Note:	data_x[1], data_x[l+1] are not used! Same for data_y.
*/
	float data_x[], data_y[],knot[];
	int l;

{
	int i,  l1,l2;     /* In the following, special care must be    */
	float delta;       /* at the ends because of the data structure */
	                   /* used. See note above.                     */
	l1= l-1; l2 = l+2;
	knot[0] = 0.0;     /* initialize -- arbitrary */

	delta=sqrt((data_x[2]-data_x[0])*(data_x[2]-data_x[0])
		         +(data_y[2]-data_y[0])*(data_y[2]-data_y[0]));
	knot[1]= sqrt(delta);                /* leave out this sqrt
		                                if you want chord length.*/

	for(i=2; i<l; i++)
	{
	        delta=sqrt((data_x[i+1]-data_x[i])*(data_x[i+1]-data_x[i])
		         +(data_y[i+1]-data_y[i])*(data_y[i+1]-data_y[i]));

		knot[i]=knot[i-1]+sqrt(delta);/*leave out this sqrt
		                                if you want chord length.*/
	}

	delta=sqrt((data_x[l2]-data_x[l])*(data_x[l2]-data_x[l])
		         +(data_y[l2]-data_y[l])*(data_y[l2]-data_y[l]));
	knot[l]= knot[l-1]+sqrt(delta);      /* leave out this sqrt
		                                if you want chord length.*/

}

