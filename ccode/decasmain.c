#include <stdio.h>
#include <math.h>

/* to plot just one bez. curve */

	FILE *file, *outfile, *psfile;

main()
{

	int i,j,jj,l,pol,buttno,dense,degree,l21,l2n;
	int index[2],numpts;
	float points_x[1000],points_y[1000];
	float mmbox[4], del_x, del_y;
	float bez_x[200],bez_y[200],weight[20];
	float cez_x[200],cez_y[200];
	float coeff_x[200],coeff_y[200];
  	float x,y,scale_x,scale_y;
	float cx[100],cy[100],cw[100];
	float xx,yy,dum;
	/* ----------------------------- */

	file = fopen("bez.dat","r");
	outfile= fopen("dch.dat","w");
	psfile= fopen("decas.ps","w");

	fscanf(file,"%d", &degree);
	fscanf(file,"%d", &pol);
	fscanf(file,"%d", &dense);
	fscanf(file,"\n");
	
	for(i=0; i <= degree ; i++)
	{
	        fscanf(file,"%f",&dum);
		bez_x[i]= dum;
	        fscanf(file,"%f",&dum);
		bez_y[i]= dum;	   
		fscanf(file,"%f", &dum);
		weight[i]= dum;
 	}	 
	fscanf(file,"\n");
/*
	for(i=0;i<=degree;i++)
		{xx=bez_x[i]; yy=bez_y[i];
		printf("(%f,%f),(%d,%d) ",
		xx,yy,degree,dense);
		printf("\n"); 
		}
*/


	fclose(file);
	fclose(outfile);

	minmax(bez_x,bez_y,degree,mmbox);
	del_x=mmbox[1]-mmbox[0]; del_y=mmbox[3]-mmbox[2];
	if(del_x > del_y) mmbox[3]=mmbox[2]+del_x;
	else mmbox[1]=mmbox[0]+del_y;

	scale_x=350.0/(mmbox[1]-mmbox[0]);
	scale_y=350.0/(mmbox[3]-mmbox[2]);


	ratbez_to_points(degree,50,bez_x,weight,points_x,1);
	ratbez_to_points(degree,50,bez_y,weight,points_y,1);
/*************** ps output ********************************/

	
	fprintf(psfile,"200 400 translate\n");	
	/***** plot  bezier control polygon if pol=1: ************/
if (pol == 1)
	{
		fprintf(psfile,"0.0 setgray\n ");
		fprintf(psfile,"1  setlinewidth\n ");

		fprintf(psfile,"newpath \n");
		fprintf(psfile,"%f %f moveto\n",
			scale_x*(bez_x[0]-mmbox[0]), scale_y*(bez_y[0]-mmbox[2]));

		for(j=0; j<=  degree; j++)
			{
			fprintf(psfile,"%f %f lineto\n",
			scale_x*(bez_x[j]-mmbox[0]), scale_y*(bez_y[j]-mmbox[2]));
			}
		fprintf(psfile,"stroke \n");



	/***** plot  control vertices: ************/

	fprintf(psfile,"0.0 setgray\n ");

	for(j=1; j< degree ; j++)
		{
			xx=scale_x*(bez_x[j]-mmbox[0]);
		 	yy=scale_y*(bez_y[j]-mmbox[2]);
			fprintf(psfile,"%f %f %f %f %f arc stroke\n",
		 	xx,yy,3.0, 0.0, 360.0);
		}
	fprintf(psfile,"1.0 setgray\n ");

	for(j=1; j< degree; j++)
		{
			xx=scale_x*(bez_x[j]-mmbox[0]);
		 	yy=scale_y*(bez_y[j]-mmbox[2]);
			fprintf(psfile,"%f %f %f %f %f arc fill\n",
		 	xx,yy,2.80, 0.0, 360.0);
		}

	}	

	

/* plot curve */

	fprintf(psfile,"3 setlinewidth \n");
	fprintf(psfile,"0 setgray\n");

		fprintf(psfile,"newpath \n");
		xx = scale_x*(points_x[0]-mmbox[0]);
		yy = scale_y*(points_y[0]-mmbox[2]);

		fprintf(psfile,"%f %f moveto\n", xx,yy);

		for( j=1; j<=50 ; j++)
		{
			xx = scale_x*(points_x[j]-mmbox[0]);
			yy = scale_y*(points_y[j]-mmbox[2]);
			fprintf(psfile,"%f %f lineto\n", xx,yy);
		}
 		fprintf(psfile,"stroke \n");
	

/**** fill in junction points  black: **********/
	fprintf(psfile,"1 setlinewidth \n");

	fprintf(psfile,"0 setgray\n");
	for(j=0; j<= dense; j=j+dense)
		{
			xx = scale_x*(points_x[j]-mmbox[0]);
			yy = scale_y*(points_y[j]-mmbox[2]);
			fprintf(psfile,"%f %f %f %f %f arc fill\n",
			xx,yy, 3.0, 0.0, 360.0);
		}




		

	fprintf(psfile,"showpage\n");
	return;

}		

