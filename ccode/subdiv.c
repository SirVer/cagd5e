#include <math.h>

void subdiv(degree,coeff,weight,t,bleft,bright,wleft,wright)
/*
	subdivides ratbez curve at parameter value t.
	Output: left and right polygon with respective weights.
	Ordering of right polygon is reversed.
*/
	float coeff[],weight[],bleft[],
		bright[],wleft[],wright[];
	float t;
	int degree; 
{
	int r,i;
	float t1,ww1,ww2;
	t1 = 1.0 - t;
	
/* 
	first, obtain right subpolygon from rat de Casteljau
*/

	for (i=0;i <= degree; i++) wright[i] = weight[i];
 
	for (i=0;i <= degree; i++) bright[i] = coeff[i];

	for (r=1; r<= degree; r++)
	for (i=0; i<= degree - r; i++)
	{
		ww1 = wright[i]; ww2= wright[i+1];
		wright[i] = t1*wright[i] + t*wright[i+1];
		bright[i]= ( t1*ww1 * bright[i]
			  +  t*ww2 * bright[i+1] ) / wright[i];
	}	

/* 
	use same as above in order to get left half. Idea:
	reverse ordering; then the above yields left half.
 */

	t = 1.0 - t; t1 = 1.0 - t;
	for (i=0;i <= degree; i++) wleft[degree -i] = weight[i];
 
	for (i=0;i <= degree; i++) bleft[degree-i] = coeff[i];

	for (r=1; r<= degree; r++)
	for (i=0; i<= degree - r; i++)
	{
		ww1 = wleft[i]; ww2= wleft[i+1];
		wleft[i] = t1*wleft[i] + t*wleft[i+1];
		bleft[i]= ( t1*ww1 * bleft[i]
			  +  t*ww2 * bleft[i+1] ) / wleft[i];
	}	

}

