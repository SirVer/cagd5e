void reparam(wold,degree,s,wnew)
/*	reparametrizes ratbez curve: only the weights,
	stored in wold, are changed. New weights are in
	wnew. Parametrization is determined by shoulder
	point s. For s=0.5, nothing changes. Also,
	s should be in (0,1).
*/

	float wold[],wnew[];
	int degree;	float s;
{
	int i;
	float c;

	c = s / (1.0 - s);

	wnew[0] = wold[0];

	for (i=1; i<= degree; i++)
		wnew[i] = c*wnew[i-1]*wold[i]/wold[i-1];
}

