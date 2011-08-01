
void intersect_points(a,b,c,d,p)
/* finds the intersection p of the two straight lines [a,b] and
	[c,d]. No check for infinite p is made.
*/
	float a[2],b[2],c[2],d[2],p[2];

{
	float diff1[2],diff2[2];

	diff1[0]=b[0]-a[0]; diff1[1]=b[1]-a[1];
	diff2[0]=d[0]-c[0]; diff2[1]=d[1]-c[1];

	intersect_lines(a,d,diff1,diff2,p);

}



