#include <math.h>
float curvature_0(bez_x,bez_y,weight,degree)
/* computes curvature of rational  Bezier curve at t=0 */
	float bez_x[], bez_y[], weight[];
	int degree;
{
	float b0[2],b1[2],b2[2];
	float dist;
	float area();

	b0[0]=bez_x[0]; b1[0]=bez_x[1]; b2[0]=bez_x[2];
	b0[1]=bez_y[0]; b1[1]=bez_y[1]; b2[1]=bez_y[2];

	dist = sqrt( (b1[0]-b0[0])*(b1[0]-b0[0])+
	             (b1[1]-b0[1])*(b1[1]-b0[1])  );


	return (2.0*(degree-1)*weight[0]*weight[2]*area(b0,b1,b2)
	       /(degree*weight[1]*weight[1]*dist*dist*dist));
}

