#include<stdio.h>
#include <math.h>
extern FILE *psfile;


void psplot_curve(bez_x,bez_y,bez_w,bspl_x,bspl_y,l,degree,value,pol,dense,scale_x,scale_y)
/* plots piecewise rational cubic  Bezier curve, dense points each segment,
  into the postscript-file   psfile. B-spline polygon can also be plotted.
Input:	bez_x, bez_y, bez_w: piecewise control polygons and weights
	bspl_x,bspl_y:B-spline controll polygon 
	l:            number of curve pieces
	degree:       degree of each piece
	value:	      minmax-box of polygon. xmin,xmax,...
	pol:	      which polygon to plot:
		      0: nothing, 1: Bezier, 2: B-spline,
	dense:	      how many points per segment
*/
	float bez_x[],bez_y[],bez_w[],value[],bspl_x[],bspl_y[],scale_x, scale_y;
	int l,degree,pol,dense;
{
	int i,k,j, ldeg,l2,l31,i3;
	float weight[5];

	float points_x[70],points_y[70], q_x[60], q_y[60];
	float aux_x[5], aux_y[5],aux_w[5];
	

	l2 = l+2;

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
	
	/* macro to mark weight point:*/
		fprintf(psfile,"/diamond\n");
		fprintf(psfile,"{0  -5 rlineto\n");
		fprintf(psfile,"5 5 rlineto\n");
		fprintf(psfile,"-5 5 rlineto\n");
		fprintf(psfile,"-5 -5 rlineto\n");
		fprintf(psfile,"5 -5 rlineto\n");
		fprintf(psfile,"closepath} def\n");


/* plot curve */

	fprintf(psfile,"3 setlinewidth \n");
	

	/* for each segment, convert to points  and plot: */
	ldeg=degree*l;
	for(i=0; i< ldeg; i+=degree)
	{

	for(k=0; k<=degree; k++)
			{
			aux_x[k]=bez_x[i+k];
			aux_y[k]=bez_y[i+k];
			aux_w[k]=bez_w[i+k];
			}


		ratbez_to_points(degree,dense,aux_x,aux_w,points_x);
		ratbez_to_points(degree,dense,aux_y,aux_w,points_y);

		fprintf(psfile,"newpath \n");

		fprintf(psfile,"%f %f moveto\n",
			scale_x*(points_x[0]-value[0]),
			scale_y*(points_y[0]-value[2]));
		
		for( j=1; j<=dense ; j++)
		{
			fprintf(psfile,"%f %f lineto\n",
			scale_x*(points_x[j]-value[0]),
			scale_y*(points_y[j]-value[2]));				}
 		fprintf(psfile,"stroke \n");

	}

	



	/**** fill in junction points  black: **********/
	fprintf(psfile,"1 setlinewidth \n");


	for(j=0; j<= ldeg; j=j+degree)
			{
			fprintf(psfile,"%f %f %f %f %f arc fill\n",
			scale_x*(bez_x[j]-value[0]), 
			scale_y*(bez_y[j]-value[2]),
		 	3.0, 0.0, 360.0);
			}


if (pol == 0)
	{
		fprintf(psfile,"showpage \n");
		 return;
	}


if (pol>0) /* plot B-spline polygon: */
	{
		fprintf(psfile,"0.0 setgray\n ");
		fprintf(psfile,"2 setlinewidth\n ");

		fprintf(psfile,"newpath \n");
		fprintf(psfile,"%f %f moveto\n",
			scale_x*(bez_x[0]-value[0]), 
			scale_y*(bez_y[0]-value[2]));

		for(j=1; j<=  l2; j++)
			{
			fprintf(psfile,"%f %f lineto\n",
			scale_x*(bspl_x[j]-value[0]), 
			scale_y*(bspl_y[j]-value[2]));
			}
		fprintf(psfile,"stroke \n");



	/***** plot  control vertices: ************/


	for(j=0; j<=l2; j++)
	{
		fprintf(psfile,"%f %f moveto\n",
		scale_x*bspl_x[j], scale_y*bspl_y[j]);
		fprintf(psfile,"blackbox \n");

		if (j!=0 && j!=l2)
		{
			fprintf(psfile,"%f %f moveto\n",
			scale_x*(bspl_x[j]-value[0]),
			 scale_y*(bspl_y[j]-value[2]));
			fprintf(psfile,"whitebox \n");
		}
	}

	}

		
	
	/***** plot  bezier control polygon if pol=1: ************/
if (pol == 1)
	{
		fprintf(psfile,"0.0 setgray\n ");
		fprintf(psfile,"0.5 setlinewidth\n ");

		fprintf(psfile,"newpath \n");
		fprintf(psfile,"%f %f moveto\n",
			scale_x*(bez_x[0]-value[0]),
			 scale_y*(bez_y[0]-value[2]));

		for(j=0; j<=  ldeg; j++)
			{
			fprintf(psfile,"%f %f lineto\n",
			scale_x*(bez_x[j]-value[0]), 
			scale_y*(bez_y[j]-value[2]));
			}
		fprintf(psfile,"stroke \n");



	/***** plot  control vertices: ************/

	fprintf(psfile,"0.0 setgray\n ");

	for(j=1; j< ldeg ; j++)
			{
		if(j !=(j/degree)*degree)
			fprintf(psfile,"%f %f %f %f %f arc stroke\n",
			scale_x*(bez_x[j]-value[0]), 
			scale_y*(bez_y[j]-value[2]),
		 	3.0, 0.0, 360.0);
			}

	fprintf(psfile,"1.0 setgray\n ");

	for(j=1; j< ldeg; j++)
			{
		if( j!=(j/degree)*degree)	
		fprintf(psfile,"%f %f %f %f %f arc fill\n",
			scale_x*(bez_x[j]-value[0]), 
			scale_y*(bez_y[j]-value[2]),
		 	2.80, 0.0, 360.0);
			}


/*		fprintf(psfile,"showpage\n");  
		return;
*/
	


	/***** plot  weight points: ************

	fprintf(psfile,"0.3 setgray\n ");
	l31 = 3*l -1;

	for (j=0; j<= l31; j++)
	{
		q_x[j]=(bez_w[j]*bez_x[j] + bez_w[j+1]*bez_x[j+1])
			/(bez_w[j] + bez_w[j+1]);

		q_y[j]=(bez_w[j]*bez_y[j] + bez_w[j+1]*bez_y[j+1])
			/(bez_w[j] + bez_w[j+1]);
	}
	for(j=0; j<=l31; j++)
	{
		fprintf(psfile,"%f %f moveto\n",
		scale_x*(q_x[j]-value[0]), scale_y*(q_y[j]-value[2]));
		fprintf(psfile,"diamond fill\n");

	}
	
	************************** weight points plotted  */
	}


	fprintf(psfile,"showpage\n");
	return;

}		

