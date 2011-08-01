
void intersect_lines(a,b,v,w,p)
/* finds the intersection p of the two straight lines a + tv and
	b+tw. No check for infinite p is made.
*/
	float a[2],b[2],v[2],w[2],p[2];

{
	float D,t;
	float diff[2];

	diff[0]=a[0]-b[0];  diff[1]=a[1]-b[1];

	D= w[1]*v[0] - w[0]*v[1]; 


	t= (diff[1]*w[0] - diff[0]*w[1]  )/D;

	p[0]=a[0]+t*v[0];  p[1]=a[1]+t*v[1];

}


