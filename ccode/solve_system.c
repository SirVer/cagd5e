 void solve_system(up,low,gamma,l,rhs,d)
/*	solve  tridiagonal linear system
	of size (l+1)(l+1) whose LU decompostion has entries up and low,
	and whose right hand side is rhs, and whose original matrix
	had upper diagonal gamma. Solution is d[0],...,d[l+2];
Input: up,low,gamma:  as above.
       l:             size of system: l+1 eqs in l+1 unknowns.
       rhs:           right hand side, i.e, data points with end
                      `tangent Bezier points' in rhs[1] and rhs[l+1].
Output:d:             solution vector.

Note:	Both rhs and d are from 0 to l+2.
*/
	float up[],low[],gamma[],rhs[],d[];
	int l;
{
	int i;
	float aux[100];

	d[0] = rhs[0];
	d[1] = rhs[1];

	/* forward substitution:  */
	aux[0]=rhs[1];
	for(i=1; i<=l; i++) aux[i]=rhs[i+1]-low[i]*aux[i-1];
	
	/* backward substitution:  */
	d[l+1]=aux[l]/up[l];
	for(i=l-1; i>0; i--) d[i+1]=(aux[i]-gamma[i]*d[i+2])/up[i];
	d[l+2]=rhs[l+2];
}
		

