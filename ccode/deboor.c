float deboor(degree,coeff,knot,u,i)
/*
	uses de Boor algorithm to compute one
	coordinate on B-spline curve for param. value u in interval i.
input:  degree:	polynomial degree of each piece of curve
	coeff:	B-spline control points
	knot:	knot sequence
	u:	evaluation abscissa
	i:	u's interval: u[i]<= u < u[i+1]
output:	coordinate value. 
*/

	float coeff[],knot[];
	float u;
	int degree,i;
{
	int k,j;
	float t1,t2;
	float coeffa[30];  /* might need adjustment! */
	
	for (j=i-degree+1; j<=i+1; j++)coeffa[j]=coeff[j];

	for (k=1; k<= degree; k++)
	for ( j=i+1 ;j>=i-degree+k+1; j--)
	{
		t1= (knot[j+degree-k] - u )/(knot[j+degree-k]-knot[j-1]);
		t2= 1.0-t1;

		coeffa[j]=t1* coeffa[j-1]+t2* coeffa[j];
	}	
	return (coeffa[i+1]);
}




