#include <stdio.h>
#include <math.h>


float height(px,py,ax,ay,bx,by)
/* find the height of point (px,py) over
   straight line thru (ax,ay) and (bx,by). 
*/
	float px,py,ax,ay,bx,by;
{
	float det,length;
	det = px*ay + ax*by + bx*py -ay*bx - by*px - py*ax;

	length = sqrt( (bx-ax)*(bx-ax) + (by-ay)*(by-ay) );

	if(length < 0.000001)   /* height doesn't make sense, hence: */
		return( sqrt( (px-ax)*(px-ax) + (py-ay)*(py-ay) ) );
	else
	return (det/length);
}


