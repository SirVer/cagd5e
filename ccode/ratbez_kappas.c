#include <stdio.h>
#include <math.h>
extern FILE *outfile;

void ratbez_kappas(bez_x,bez_y,bez_w,l,dense)
/*	writes curvatures of  piecewise cubic rational curve into 
	a file.
input:
	bez_x,bez_y:  2D rat. cubic spline polygon
	bez_w:	the  weights
	dense:	how many curvature values to compute per interval
	l:      no. of intervals
output:		 written into file outfile
Note:		this plots curvatures vs. a uniform u-spacing
*/

	float bez_x[],bez_y[],bez_w[];
	int  dense,l;
{
	float bleftx[4],blefty[4],brightx[4],brighty[4];
	float wleft[4], wright[4],coeffx[4],coeffy[4],weight[4];
	float dist,t,delt,h,u,diff;
	int i,j,i3;
	float curvature_0(),curvature_1(),abs();

	/* Plot kappas for each interval. */
	fprintf(outfile,"%d  %d\n",dense*l,dense);
	for(i=0; i<l; i++)
	{	i3=i*3;
		u= (float)i;  /*starting value for i-th segment*/
		diff=1.0;
		for(j=0;j<=3;j++)
		{       /* create i-th cubic Bezier curve: */ 
			coeffx[j]=bez_x[i3+j]; 
			coeffy[j]=bez_y[i3+j];
			weight[j]=bez_w[i3+j];
		}


		delt=1.0/(float)dense;

		for(t=0.0; t<0.5; t=t+delt)
		{
		subdiv(3,coeffx,weight,t,bleftx,brightx,wleft,wright);
		subdiv(3,coeffy,weight,t,blefty,brighty,wleft,wright);
		h=curvature_0(brightx,brighty,wright,3);
		/* to print file, we'll have to use the GLOBAL
		   parameter u!   */
		u=(float)i+t*diff;
		fprintf(outfile,"%2.3f  %f\n",u,h);
		}

		for(t=0.5; t<0.999; t=t+delt)
		{
		subdiv(3,coeffx,weight,t,bleftx,brightx,wleft,wright);
		subdiv(3,coeffy,weight,t,blefty,brighty,wleft,wright);

		h=curvature_0(bleftx,blefty,wleft,3);
		h=0.0-h;
		/* minus sign since order of polygon 
		   traversal is reversed!
		*/
		u=(float)i+t*diff;
		fprintf(outfile,"%2.3f    %f\n",u,h);
		}
	}
	/* print very last kappa: */
	t=1.0;
	h=curvature_1(coeffx,coeffy,weight,3);
	fprintf(outfile,"%2.3f    %f\n",(float)l,h);


}

