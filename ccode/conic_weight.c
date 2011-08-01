#include <math.h>
float conic_weight(b0,b1,b2,p)
/* 
Input:	b0,b1,b2:	conic control polygon
	p:		point on conic
Output:	weight of b1 (assuming standard form).

For method, check Farin  14.5, 14.6.
*/

	float b0[],b1[],b2[],p[];
{
	float area(),length_2();
	float tau0,  tau2 , t,t1, d, dist, weight;
	float b11[2], b10[2];

	tau0=area(b1,p,b2);
	tau2=area(b1,b0,p);
	return(area(b0,b2,p)/(2.0*sqrt(tau0*tau2))); /* weight of b1         */

}

