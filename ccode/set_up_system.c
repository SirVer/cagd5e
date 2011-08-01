void set_up_system(knot,l,alpha,beta,gamma)
/*	given the knot sequence, the linear system 
	for clamped end condition B-spline interpolation
	is set up.
input:	knot:	knot sequence
	points:	points to be interpolated
	l:	number of intervals
output:	alpha,beta,gamma: 1-D arrays that constitute
		the elements of the interpolation matrix.

	Note: no data points needed so far! 
*/
	int l;
	float knot[],alpha[],beta[],gamma[];

{
	int i,l1;
	float delta_im2,delta_im1, delta_i, delta_ip1,sum;
	l1=l-1;

	/* some special cases: */
	if(l==1)
	{alpha[0]=0.0; alpha[1]=0.0; beta[0]=1.0; beta[1]=1.0;
	 gamma[0]=0.0; gamma[1]=0.0; return;}

	if(l==2)
	{
		beta[0]=1.0;
		delta_im1=(knot[1]-knot[0]);
		delta_i  =(knot[2]-knot[1]);
		delta_ip1=(knot[3]-knot[2]);
		sum = delta_im1+delta_i;

		alpha[1]=delta_i*delta_i/sum;
		beta[1] =(delta_i*delta_im1)/sum
                + delta_im1*delta_i/ sum;
		gamma[1]=delta_im1*delta_im1/sum;

		alpha[1]=alpha[1]/sum;
		beta[1] =beta[1]/sum;
		gamma[1]=gamma[1]/sum;

		beta[2]=1.0;
		alpha[2]=0.0;
		gamma[2]=0.0;
		return;
	}

	/* the rest does the cases l>2.  */

	delta_im1=(knot[1]-knot[0]);
	delta_i  =(knot[2]-knot[1]);
	delta_ip1=(knot[3]-knot[2]);
	sum = delta_im1+delta_i;

	beta[0]=1.0; gamma[0]=0.0;

	alpha[1]=delta_i*delta_i/sum;
	beta[1] =(delta_i*delta_im1)/sum
                + delta_im1*(delta_i+delta_ip1)
		/ (sum+delta_ip1);
	gamma[1]=delta_im1*delta_im1/(sum+delta_ip1);

	alpha[1]=alpha[1]/sum;
	beta[1] =beta[1]/sum;
	gamma[1]=gamma[1]/sum;

	/*Now for the main loop:   */
	for(i=2; i<l1; i++)
	{
		/* compute delta_i_minus_2,...  */
		delta_im2=(knot[i-1]-knot[i-2]);
		delta_im1=(knot[i]  -knot[i-1]);
		delta_i  =(knot[i+1]-knot[i]);
		delta_ip1=(knot[i+2]-knot[i+1]);
	
		sum = delta_im1+delta_i;

		alpha[i]=delta_i*delta_i/(delta_im2 +sum);
		beta[i] =delta_i*(delta_im2+delta_im1) 
			/(delta_im2 + sum)
			+
			 delta_im1*(delta_i+delta_ip1)
			/(sum + delta_ip1);
		gamma[i]=delta_im1*delta_im1
			/(sum + delta_ip1);
		
		alpha[i]=alpha[i]/sum;
		beta[i] =beta[i]/sum;
		gamma[i]=gamma[i]/sum;
	}

	/*  special care at the end:  */
	delta_im2=knot[l-2]-knot[l-3];
	delta_im1=knot[l1]-knot[l-2];
	delta_i  =knot[l]-knot[l1];
	sum=delta_im1+delta_i;

	alpha[l1]=delta_i*delta_i/(delta_im2+sum);
	beta[l1] =delta_i*(delta_im2+delta_im1)/(delta_im2  + sum)
                 +
		  delta_im1*delta_i / sum;
	gamma[l1]=delta_im1*delta_im1/sum;

	alpha[l1]=alpha[l1]/sum;
	beta[l1] =beta[l1]/sum;
	gamma[l1]=gamma[l1]/sum;


	alpha[l]=0.0; beta[l]=1.0; gamma[l]=0.0;


}

