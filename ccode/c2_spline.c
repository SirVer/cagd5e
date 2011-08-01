void c2_spline(knot,l,data_x,data_y,bspl_x,bspl_y)
/* Finds the C2 cubic spline interpolant to
the data points in data_x, data_y.
Input:	knot:	the knot sequence  knot[0], ..., knot[l]
	l:	the number of intervals
	data_x, data_y: the data points data_x[0], ...,
		data[l+2]. Attention:
		data_x[1] and data_x[l+1] are filled
		by  Bessel end conditions and are
		thus ignored on input. Same for data_y.
Output:	bspl_x, bspl_y: the B-spline control polygon of
		the interpolant. Dimensions:
		bspl_x[0], ..., bspl_x[l+2]. Same for
		bspl_y.
*/
	float knot[],data_x[],data_y[],bspl_x[],bspl_y[];
	int l;
{
	float alpha[100], beta[100], gamma[100], up[100], low[100];
	set_up_system(knot,l,alpha,beta,gamma);

	l_u_system(alpha,beta,gamma,l,up,low);

	bessel_ends(data_x,knot,l);
	bessel_ends(data_y,knot,l);

	solve_system(up,low,gamma,l,data_x,bspl_x);
	solve_system(up,low,gamma,l,data_y,bspl_y);

}

