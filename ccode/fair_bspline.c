void fair_kr_bspline(bspl,knot,l,from,to)
/* Fairs a cubic rational B-spline curve by knot removal/reinsertion.
 
Input:	bspl:      cubic B-spline control polygon (one coord.)
	knot:      knot sequence
	l:         no. of intervals
	from, to:  from where to where to fair
Output:	same as input, but hopefully fairer.
*/


	float bspl[], knot[];
	int l,from,to;
{
	int i, i3,  l2;
	float left,right, middle;
	float Knot[100]; /*to simulate multiple knots at ends */

	Knot[0]=Knot[1]=knot[0];

	for(i=0; i<=l; i++)Knot[i+2]=knot[i];
	Knot[l+3]=Knot[l+4]=knot[l];

	/* With new knot vector, bspl[i] is associated with Knot[i+1] */
	
	l2=l+2; 

	if(from <= 2) from = 2;
	if(to >=l) to=l;

	for (i=from; i<=to; i++) 
	{
		left=((Knot[i+2]-Knot[i-2])*bspl[i-1]
                       -(Knot[i+2]-Knot[i+1]  )*bspl[i-2]  )
                       /(Knot[i+1]-Knot[i-2] );

		
		right=((Knot[i+4]-Knot[i])*bspl[i+1]
                       -(Knot[i+1]-Knot[i]  )*bspl[i+2] )
                       /(Knot[i+4]-Knot[i+1] );

		
		bspl[i]=((Knot[i+3]-Knot[i+1])*left
		          +(Knot[i+1]-Knot[i-1])*right )
		          /(Knot[i+3]-Knot[i-1]) ;

	
	
	}
   
}
 

