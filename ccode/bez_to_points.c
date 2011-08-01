void bez_to_points(degree,npoints,coeff,points)
/*	Converts Bezier curve into point sequence. Works on
	one coordinate only.
 
	Input:   degree:  degree of curve.
	         npoints: # of coordinates to be generated. (counting
		          from 0!)
	         coeff:   coordinates of control polygon.
	Output:  points:  coordinates of points on curve.

	Remark: For a 2D curve, this routine needs to be called twice,
		once for the x-coordinates and once for y.
*/

	int degree, npoints;
	float coeff[],points[];

{	
	float t,delt;
	int i;
	float hornbez();
	int k;

	delt=1.0/(float)npoints;
	t=0.0;
	for(i=0; i<=npoints; i++) 
	{
		points[i]=hornbez(degree,coeff,t);
		t = t+delt;
	}
}

