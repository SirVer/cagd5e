#include <stdio.h>
#include <math.h>
 

main() /* program to plot curvature of a rational 
	  B-spline curve, expressed in piecewise
 	  rational cubic form. All curvatures are expected
	  in the input file b_kappas.dat. */
{
	FILE *file, *plotfile;

	int i,j,degree,degree1,degree2,istep,tol,buttno,howmany,dense;
	float t,shoulder,width,xmin1,ymin1,xmax1,ymax1,x,y,xx,yy,
		kappa_min, kappa_max, scale_x,scale_y, setline;
	float coeffx[1000],value[4];
	float coeffy[1000];
	float abs();
	char min[20],max[20];

	file = fopen("b_kappas.dat","r");
	plotfile= fopen("psplot.ps","w");
	fscanf(file,"%d", &howmany);
	fscanf(file,"%d", &dense);

	for(i=0; i <= howmany ; i++)
	{
		fscanf(file,"%f",&coeffx[i]);
		fscanf(file,"%f",&coeffy[i]);
 	}	
	minmax(coeffx,coeffy,howmany,value);
	sprintf(min,"%4.2f",value[2]);
	sprintf(max,"%4.2f",value[3]);
	kappa_max=value[3];
	kappa_min=value[2];

	width=value[3]-value[2];  /*to scale kappa printouts  */




	minmax(coeffx,coeffy,howmany,value); /* Setting the window:   */
	if (value[2] > 0.0) value[2]=0.0;  /* make sure kappa=0 is  */
	if (value[3] < 0.0) value[3]=0.0;  /* drawn. Give some room */
	width=(value[3]-value[2])/20.0;    /* in y-direction.       */
	value[2]=value[2]-width;
	value[3]=value[3]+width;


	degree1 = degree+1;






/*********************creating a postscript file for the curvatures: *******************/


		/* rotate, so paper is used sideways */

		fprintf(plotfile,"90 rotate\n");           
		fprintf(plotfile,"70 -602 translate\n");  
		fprintf(plotfile,"10 300 translate\n");

		scale_x=450.0/(value[1]-value[0]);
		scale_y=300.0/(value[3]-value[2]);

	
		fprintf(plotfile,"0.6 setgray \n");
		fprintf(plotfile,"%f setlinewidth\n",0.1);

		fprintf(plotfile,"%f %f translate\n",
			-1.0*scale_x*value[0], -1.0*scale_y*value[2]);

	
		fprintf(plotfile,"newpath \n");
		fprintf(plotfile," %f %f moveto\n",
			0.0,0.0);
		fprintf(plotfile," %3.2f %3.2f lineto\n",
			scale_x*value[1],0.0);
		fprintf(plotfile,"stroke\n");

		fprintf(plotfile,"newpath \n");

		
		fprintf(plotfile," %f %f moveto\n",
			scale_x*value[1],0.0);
		fprintf(plotfile," %f %f lineto\n",
			scale_x*value[0],0.0);
		fprintf(plotfile," %f %f lineto\n",
			scale_x*coeffx[0],scale_y*coeffy[0]);


			for(j=1; j<= howmany; j++)
			{
			fprintf(plotfile," %f %f lineto\n",
			scale_x*coeffx[j], scale_y*coeffy[j]);
			}
		fprintf(plotfile," %f %f lineto\n",
			scale_x*coeffx[howmany],scale_y*coeffy[howmany]);
		fprintf(plotfile,"fill\n");



		/******* plot box : *************/
	
		fprintf(plotfile,"0.0 setgray\n");
		fprintf(plotfile,"0.3 setlinewidth\n");
		fprintf(plotfile,"newpath\n");
		fprintf(plotfile,"%f %f moveto\n",
			scale_x*value[0],scale_y*value[2]);
		fprintf(plotfile,"%f %f lineto\n",
			scale_x*value[0],scale_y*value[3]);
		fprintf(plotfile,"%f %f lineto\n",
			scale_x*value[1],scale_y*value[3]);
		fprintf(plotfile,"%f %f lineto\n",
			scale_x*value[1],scale_y*value[2]);
		fprintf(plotfile,"%f %f lineto\n",
			scale_x*value[0],scale_y*value[2]);
		fprintf(plotfile,"stroke\n");

	/***** plot markers: ************/

	fprintf(plotfile,"0.0 setgray\n ");

	if(howmany > dense)
	for(j=0; j<= howmany; j=j+dense)
			{
			if(j >= 0) /*to keep numbering right */
	/*			    but to skip first point */
			fprintf(plotfile,"%f %f %f %f %f arc stroke\n",
			scale_x*coeffx[j], scale_y*coeffy[j],
		 	3.0, 0.0, 360.0);
			}

	fprintf(plotfile,"1.0 setgray\n ");

	if(howmany > dense)
	for(j=0; j<= howmany; j=j+dense)
			{
			if(j >= 0)  /* see above  */ 
			fprintf(plotfile,"%f %f %f %f %f arc fill\n",
			scale_x*coeffx[j], scale_y*coeffy[j],
		 	2.6, 0.0, 360.0);
			}

	/***** print min-max values: *************/

	fprintf(plotfile,"0.0 setgray\n ");

	fprintf(plotfile,"/Times-Roman findfont 15 scalefont setfont\n");

	fprintf(plotfile,"%f %f moveto\n",
		scale_x*value[1]+10, scale_y*kappa_max);

	fprintf(plotfile,"(max: %3.3f)show\n",kappa_max);

	fprintf(plotfile,"%f %f moveto\n",
		scale_x*value[1]+10, scale_y*kappa_min);

	fprintf(plotfile,"(min: %3.3f)show\n",kappa_min);

		fprintf(plotfile,"showpage");
/*********************************************************************/		
	

	fclose(file);
	fclose(plotfile);
}

