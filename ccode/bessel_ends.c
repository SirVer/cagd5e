void bessel_ends(data,knot,l)
/*	Computes B-spline points data[1] and data[l+]
	according to Bessel end condition.

input:	data:	sequence of data coordinates data[0] to data[l+2].
		Note that data[1] and data[l+1] are expected to
		be empty, as they will be filled by this routine.
	knot:	knot sequence
	l:	number of intervals
 
output:	data:	completed, as above.
*/
	float data[], knot[];
	int l;
{
	float alpha, beta; int i;
	
	if (l==1)
	{/*  This is not really Bessel, but then what do you do
	     when you have only one interval? -- make it linear!
	 */
		data[1]= (2.0*data[0] + data[3])/3.0;
		data[2]= (2.0*data[3] + data[0])/3.0;
	}

	else if (l==2)
	{
		/* beginning:    */
		alpha= (knot[2]-knot[1])/(knot[2]-knot[0]);
		beta = 1.0 - alpha;

		data[1]=(data[2]-alpha*alpha*data[0]-beta*beta*data[4])
		/(2.0*alpha*beta);
		data[1]=2.0*(alpha*data[0]+beta*data[1])/3.0 + data[0]/3.0;

		/* end:  */
		alpha= (knot[2]-knot[1])/(knot[2]-knot[0]);
		beta = 1.0 - alpha;

		data[3]=(data[2]-alpha*alpha*data[0]-beta*beta*data[4])
		/(2.0*alpha*beta);

		data[3]=2.0*(alpha*data[3]+beta*data[4])/3.0+data[4]/3.0;	
	}
	
	else

	{


		/* beginning:    */
		alpha= (knot[2]-knot[1])/(knot[2]-knot[0]);
		beta = 1.0 - alpha;

		data[1]=(data[2]-alpha*alpha*data[0]-beta*beta*data[3])
		/(2.0*alpha*beta);
		data[1]=2.0*(alpha*data[0]+beta*data[1])/3.0 + data[0]/3.0;


		/* end:  */
		alpha= (knot[l]-knot[l-1])/(knot[l]-knot[l-2]);
		beta = 1.0 - alpha;

		data[l+1]=(data[l]-alpha*alpha*data[l-1]-beta*beta*data[l+2])
		/(2.0*alpha*beta);

		data[l+1]=2.0*(alpha*data[l+1]+beta*data[l+2])/3.0+data[l+2]/3.0;

	}

}

