void fair_surf(bspl,lu,lv,knot_u, knot_v)
/* 	Fairs B-spline control net.
Input:	bspl:   B-spline control net (one coordinate only)
	lu,lv:  no. of intervals in u- and v-direction
	knots_u, knots_v:   knot vectors in u- and v-direction
Output:	as input

*/
	float bspl[20][20],knot_u[],knot_v[];
	int  lu,lv;
{
	int  i,j,lu2,lv2;
	float b[20];

	lu2=lu+2; lv2=lv+2; 
 

	for(i=0;  i<= lu2; i++)
	{

		for(j=0; j<=lv2; j++)  b[j]=bspl[i][j]; /* grab i-th row*/
		fair_bspline(b,knot_v,lv,0,lv);         /* fair row     */
		for(j=0; j<=lv2; j++)  bspl[i][j]=b[j]; /* put row back */
	}

	for(j=0;  j<= lv2; j++)
	{

		for(i=0; i<=lu2; i++)  b[i]=bspl[i][j]; /* grab j-th col*/
		fair_bspline(b,knot_u,lu,0,lu);         /* fair col     */
		for(i=0; i<=lu2; i++)  bspl[i][j]=b[i]; /* put col back */
	}


}

