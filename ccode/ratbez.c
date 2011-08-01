#include <math.h>

float ratbez(degree,coeff,weight,t)
/*
	uses rational de casteljau to compute
	point on ratbez curve for param. value t.
*/
	float coeff[],weight[];
	float t;
	int degree; 
	{
	int r,i;
	float t1,t2,ww1,ww2;
	float coeffa[20], weighta[20];
	t1 = 1.0 - t;

	
	for (i=0;i<=degree; i++)
	{
		coeffa[i]=coeff[i];
		weighta[i]=weight[i];
	}

	for (r=1; r<= degree; r++)
	for (i=0; i<= degree - r; i++)
	{
	/*	t1= (i+r-degree*t)/(float)r;
		t2= 1.0-t1;  ... makes it interpolatory ...
	*/
		t1=1.0-t; t2=t;
		ww1 = weighta[i]; ww2= weighta[i+1];
		weighta[i] = t1*ww1 + t2*ww2;
		coeffa[i]  = ( t1*ww1 * coeffa[i]
			    + t2*ww2 * coeffa[i+1] ) / weighta[i];

	}	
	return (coeffa[0]);
	}

