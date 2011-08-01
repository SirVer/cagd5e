void netcoons(net,rows,columns)
/* Uses bilinear Coons blending to complete a control
net of which only the four boundary polygons are given.
Works for one coordinate only.
Input:	net:	control net - only boundaries are considered as input.
	rows, columns: dimensions of net.
Output:	net:	the completed net, with the old boundaries.
*/
	float net[20][20]; 
	int rows, columns; /*If either of these is >20, adjust dimensions*/
                           /*in previous statement!                      */
{
	int i,j;
	float u,v,u1,v1;

	for(i=0; i<=rows;    i++)
	for(j=0; j<=columns; j++)
	{

		u=((float)i)/rows;    u1=1.0-u;
		v=((float)j)/columns; v1=1.0-v;

		net[i][j]=u1*net[0][j] + u*net[rows][j]
			 +v1*net[i][0] + v*net[i][columns]
			 -u1*v1*net[0][0]    - u1*v*net[0][columns]
			 -u *v1*net[rows][0] - u *v*net[rows][columns];

	}
}

