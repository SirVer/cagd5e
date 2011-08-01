 float minmax(bx,by,degree,value)
	/* find minmax box of 2D polygon bx,by */

	int degree;
	float bx[],by[],value[];
{
	int i;
	float xmin,xmax,ymin,ymax;

	xmin= bx[0]; ymin = by[0];
	xmax= bx[0]; ymax = by[0] ;

	for (i=0; i<=degree; i++)
	{
		if (bx[i]<xmin)xmin=bx[i];
		if (bx[i]>xmax)xmax=bx[i];

		if (by[i]<ymin)ymin=by[i];
		if (by[i]>ymax)ymax=by[i];
	
	}
		value[0]=xmin;
		value[1]=xmax;
		value[2]=ymin;
		value[3]=ymax;

}

	

