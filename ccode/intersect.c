#include <stdio.h>
#include <math.h>
extern FILE *outfile, *psfile;

void intersect(bx,by,w,degree,tol)
/* Intersects bezier curve with x-axis  by  adaptive subdivision. 
   Subdivision is controlled by tolerance tol. There is
   no check for stack depth! Intersection points are not found  in
   `natural' order.  Results are written into file outfile.
	Input: bx,by,w:	rational Bezier curve
		degree:	its degree
		tol: 	accuracy for results
 */

	int degree; float tol;
	float bx[],by[],w[];
{
	float a[2],b[2],c[2],d[2],p[2];
	float bxleft[20],byleft[20],bxright[20],
		byright[20],wleft[20],wright[20];
	float box[4],xx,yy;
	int j;
	int check_flat();
	
	/********* does minmaxbox contain x-axis? **********/

	minmax(bx,by,degree,box);



	if (box[2]*box[3] > 0.0) return;

	/********* is polygon flat enough? ********/

	if( check_flat(bx,by,degree,tol)== 1 )
		{ 
		a[0]=bx[0];      a[1]=by[0];        /* intersect curve       */
		b[0]=bx[degree]; b[1]=by[degree];   /* endpoints with        */
		c[0]=0.0;        c[1]=0.0;          /* x- axis. Intersection */
		d[0]=1.0;	 d[1]=0.0;          /* is in p[0], p[1].     */
		intersect_points(a,b,c,d,p);

		fprintf(outfile,"%f  %f\n",p[0],p[1]);
		}
	/******** if not flat enough, subdivide: ********/
	else
		{

		subdiv(degree,bx,w,0.5,bxleft,bxright,wleft,wright);
		subdiv(degree,by,w,0.5,byleft,byright,wleft,wright);

	/******** ... and repeat for each half: **********/

		intersect(bxleft, byleft, wleft, degree,tol);
		intersect(bxright,byright,wright,degree,tol);
		}
}

