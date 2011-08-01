float area(p1,p2,p3)
/* find area of 2D triangle p1,p2,p3 */

	float p1[2], p2[2], p3[2];
{
	return( (p2[0]-p1[0])*(p3[1]-p1[1])-(p2[1]-p1[1])*(p3[0]-p1[0]))/2.0;
}

