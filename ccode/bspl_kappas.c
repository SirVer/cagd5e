#include <stdio.h>
#include <math.h>
extern FILE *outfile;

void bspl_kappas(bspl_x,bspl_y,bspl_w,knot,l,dense)
/*	writes curvatures of cubic rational  B-spline curve into 
	a file.
input:
	bspl_x,bspl_y:  2D rat. B-spline polygon
	bspl_w:	the  B-spline weights
	knot:   the knot sequence
	dense:	how many curvature values to compute per interval
	l:      no. of intervals
output:
	written into file outfile
*/

	float bspl_x[],bspl_y[],bspl_w[],knot[];
	int  dense,l;
{
	float bez_x[300],bez_y[300], bez_w[300];
	float bleftx[4],blefty[4],brightx[4],brighty[4];
	float wleft[4], wright[4],coeffx[4],coeffy[4],weight[4];
	float dist,t,delt,h,u,diff;
	int i,j,i3;
	float curvature_0(),curvature_1(),abs();

	/* first, convert B-spline to Bezier: */

	ratbspline_to_bezier(bspl_x,bspl_y,bspl_w,knot,l,
	                     bez_x,bez_y,bez_w);

	/* Now plot kappas for each interval. */

	fprintf(outfile,"%d  %d\n",dense*l,dense);
	for(i=0; i<l; i++)
	{	i3=i*3;
		u= knot[i];  /*starting value for i-th segment*/
		diff=knot[i+1]-knot[i];
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

		u=knot[i]+t*diff;
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
		u=knot[i]+t*diff;
		fprintf(outfile,"%2.3f    %f\n",u,h);
		}
	}
	/* print very last kappa: */
	t=1.0;
	h=curvature_1(coeffx,coeffy,weight,3);
	fprintf(outfile,"%2.3f    %f\n",knot[l],h);


}

