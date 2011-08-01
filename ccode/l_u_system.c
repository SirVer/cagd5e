void l_u_system(alpha,beta,gamma,l,up,low)
/*	perform LU decomposition of tridiagonal system with
	lower diagonal alpha, diagonal beta, upper diagonal gamma.

input:	alpha,beta,gamma: the coefficient matrix entries
	l:	matrix size [0,l]x[0,l]
	low:	L-matrix entries
	up:	U-matrix entries
*/
	float alpha[],beta[],gamma[],low[],up[];
	int l;
{
	int i;

	up[0]=beta[0];
	for(i=1; i<=l; i++)
	{
		low[i]=alpha[i]/up[i-1];
		up[i] =beta[i]-low[i]*gamma[i-1];
	}
}

