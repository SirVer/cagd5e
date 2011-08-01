#include <stdio.h>
#include <math.h>


	FILE *file, *outfile, *psfile;

main()
{

	int i,j,l,polygon,buttno,l2,dense,degree,l21,l2n;
	int index[2],numpts;
	float points_x[1000],points_y[1000];
	float mmbox[4], del_x, del_y;
	float bspl_x[200],bspl_y[200],knot[200];
  	float dum,x,y,xx,yy,tight,scale_x,scale_y;
	/* ----------------------------- */

	file = fopen("bspl.dat","r");
	outfile= fopen("dch.dat","w");
	psfile= fopen("db.ps","w");

	fscanf(file,"%d", &l);
	fscanf(file,"%d", &degree);
	fscanf(file,"%d", &polygon);
	fscanf(file,"%d", &dense);
	fscanf(file,"\n");
	
	l2=l+degree-1;
	for(i=0; i <= l2 ; i++)
	{
	        fscanf(file,"%f",&dum);
		bspl_x[i]= dum;
	        fscanf(file,"%f",&dum);
		bspl_y[i]= dum;	
 	}	 
	fscanf(file,"\n");

/*	for(i=0;i<=l2;i++)
		{
		printf("(%f,%f),(%d,%d) ",
		bspl_x[i],bspl_y[i],l,dense);
		printf("\n"); 
		}
*/

	l2n = l + 2*degree - 2;
	for(i=0; i <= l2n ; i++)
	{
	        fscanf(file,"%f",&dum);
		knot[i]= dum;	    
 	}	

	fclose(file);
	fclose(outfile);

	minmax(bspl_x,bspl_y,l2,mmbox);
	del_x=mmbox[1]-mmbox[0]; del_y=mmbox[3]-mmbox[2];
	if(del_x > del_y) mmbox[3]=mmbox[2]+del_x;
	else mmbox[1]=mmbox[0]+del_y;

	scale_x=350.0/(mmbox[1]-mmbox[0]);
	scale_y=350.0/(mmbox[3]-mmbox[2]);



	bspl_to_points(degree,l,bspl_x,knot,dense,points_x,&numpts);
	bspl_to_points(degree,l,bspl_y,knot,dense,points_y,&numpts);

/*************** ps output ********************************/


	/* macro to mark B-spline vertex:*/
		fprintf(psfile,"/blackbox\n");
		fprintf(psfile,"{0 setgray\n");
		fprintf(psfile,"-3.5 -3.5 rlineto\n");
		fprintf(psfile,"7 0 rlineto\n");
		fprintf(psfile,"0 7 rlineto\n");
		fprintf(psfile,"-7 0 rlineto\n");
		fprintf(psfile,"0 -7 rlineto\n");
		fprintf(psfile,"closepath fill} def\n");
	

		fprintf(psfile,"/whitebox\n");
		fprintf(psfile,"{1 setgray\n");
		fprintf(psfile,"-3 -3 rlineto\n");
		fprintf(psfile,"6 0 rlineto\n");
		fprintf(psfile,"0 6 rlineto\n");
		fprintf(psfile,"-6 0 rlineto\n");
		fprintf(psfile,"0 -6 rlineto\n");
		fprintf(psfile,"closepath fill} def\n");
	

/* plot curve */

	fprintf(psfile,"3 setlinewidth \n");
	fprintf(psfile,"0 setgray\n");

	fprintf(psfile,"200 400 translate\n");

		fprintf(psfile,"newpath \n");

		fprintf(psfile,"%f %f moveto\n",
			scale_x*(points_x[0]-mmbox[0]),
			scale_y*(points_y[0]-mmbox[2]));
		
		for( j=1; j<numpts ; j++)
		{
			fprintf(psfile,"%f %f lineto\n",
			scale_x*(points_x[j]-mmbox[0]),
			scale_y*(points_y[j]-mmbox[2]));
 		fprintf(psfile,"stroke \n");


	
	/**** fill in junction points  black: **********/
	fprintf(psfile,"1 setlinewidth \n");


	for(j=0; j<= numpts; j=j+dense)
			{
			fprintf(psfile,"%f %f %f %f %f arc fill\n",
			scale_x*(points_x[j]-mmbox[0]), 
			scale_y*(points_y[j]-mmbox[2]),
		 	3.0, 0.0, 360.0);
			j++; /* there in points twice */
			}

if (polygon == 0)
	{
		fprintf(psfile,"showpage \n");
		 return;
	}


if (polygon>0) /* plot B-spline polygon: */
	{
		fprintf(psfile,"0.0 setgray\n ");
		fprintf(psfile,"1 setlinewidth\n ");

		fprintf(psfile,"newpath \n");
		fprintf(psfile,"%f %f moveto\n",
			scale_x*(bspl_x[0]-mmbox[0]), 
			scale_y*(bspl_y[0]-mmbox[2]));

		for(j=1; j<=  l2; j++)
			{
			fprintf(psfile,"%f %f lineto\n",
			scale_x*(bspl_x[j]-mmbox[0]), 
			scale_y*(bspl_y[j]-mmbox[2]));
			}
		fprintf(psfile,"stroke \n");



	/***** plot  control vertices: ************/


	for(j=0; j<=l2; j++)
	{
		fprintf(psfile,"%f %f moveto\n",
		scale_x*(bspl_x[j]-mmbox[0]), 
		scale_y*(bspl_y[j]-mmbox[2]));
		fprintf(psfile,"blackbox \n");   

		if (j!=0 && j!=l2)
		{
			fprintf(psfile,"%f %f moveto\n",
			scale_x*(bspl_x[j]-mmbox[0]), 
			scale_y*(bspl_y[j]-mmbox[2]));
			fprintf(psfile,"whitebox \n");  
		}
	}

	}

		
		fprintf(psfile,"showpage \n");

	fclose(psfile);

/***********************************************************/


}


