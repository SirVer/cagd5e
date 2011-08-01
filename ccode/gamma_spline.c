void  gamma_spline(bspl,l,gamma,bez)
/*From B-spline polygon and gammas, find interior
  Bezier points b3i+-1.
Input:	bspl:	control polygon (one coordinate only)
	l:	number of cubic pieces
	gamma:	gamma_i's
Output:	bez:	piecewise Bezier polygon,  but without the 
		junction points b3i
*/
	int l;
	float bspl[],gamma[],bez[];
{
	int i,i3,l3;

	bez[0]=bspl[0];
	bez[1]=bspl[1];
	if(l>1)
	{
	bez[2]=(gamma[2]*bspl[1]
		+bspl[2]    )/(gamma[2]+1.0);
	}   
	if(l>2)
	{
	bez[4]=( (1.0+gamma[3])*bspl[2]
	        +gamma[2]*bspl[3]  )/(1.0+gamma[2]+gamma[3]);
	}
/* Now the main part:   */

	for(i=2; i<l-1; i++)
	{		
	i3=3*i;
	bez[i3-1]=( gamma[i+1]*bspl[i]
	         +  (gamma[i]+1.0)*bspl[i+1])/(1.0+gamma[i]+gamma[i+1]);

	bez[i3+1]=( (gamma[i+2]+1.0)*bspl[i+1]
	         +  gamma[i+1]*bspl[i+2]  )/(1.0+gamma[i+1]+gamma[i+2]);

	}
	
/* The last points need special attention:  */

	l3=l*3;
	if(l>2)
	{
	bez[l3-4]=( gamma[l]*bspl[l-1]
	         +(1.0+gamma[l-1])*bspl[l]  )/(1.0+gamma[l-1]+gamma[l]);
	}
	if(l>1)
	{
	bez[l3-2]=( bspl[l]
		 +  gamma[l]*bspl[l+1]  )/(gamma[l]+1.0);
	}
	bez[l3-1]= bspl[l+1];
	bez[l3]  = bspl[l+2]; 

}

