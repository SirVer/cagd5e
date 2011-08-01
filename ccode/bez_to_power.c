

void bezier_to_power(degree,bez,coeff)
/*	Converts Bezier form to power (monomial) form. Works on
	one coordinate only.
 
	Input:   degree:  degree of curve.
	         bez:	  coefficients of Bezier form
	Output:  coeff:   coefficients of power form.

	Remark: For a 2D curve, this routine needs to be called twice,
		once for the x-coordinates and once for y.
*/

	int degree;
	float coeff[], bez[];

{	
	float  i_factorial, n_r;
	int i;

	differences(degree,bez,coeff); /* compute forward differences    */
				       /* and store them in coeff.       */

					/* Note that i_factorial is int. */
					/* For high degrees: danger!     */
	coeff[0]=bez[0];
	i_factorial=1;	
	n_r=1;
	for (i=1; i<=degree; i++)
	{
		i_factorial=i_factorial*i;
		n_r= n_r*(degree-i+1);

		coeff[i]=n_r*coeff[i]/i_factorial;
	}


}





