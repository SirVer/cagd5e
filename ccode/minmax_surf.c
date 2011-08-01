 minmax_surf(bx,by,degree_u,degree_v,value)
	/* find minmax box of 2D polygon bx,by */

	int degree_u,degree_v;
	float bx[20][20],by[20][20],value[];
{
	int i,j;
	float xmin,xmax,ymin,ymax;

	xmin= bx[0][0]; ymin = by[0][0];
	xmax= bx[0][0]; ymax = by[0][0] ;

	for (i=0; i<=degree_u; i++)
	for (j=0; j<=degree_v; j++)
	{
		if (bx[i][j]<xmin)xmin=bx[i][j];
		if (bx[i][j]>xmax)xmax=bx[i][j];

		if (by[i][j]<ymin)ymin=by[i][j];
		if (by[i][j]>ymax)ymax=by[i][j];
	
	}
		value[0]=xmin;
		value[1]=xmax;
		value[2]=ymin;
		value[3]=ymax;

}

	

