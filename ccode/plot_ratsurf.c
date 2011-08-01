
extern FILE *psfile;    /* for postscript output */

void plot_ratsurf(bx,by,bw,degree_u,degree_v,u_points,v_points,scale_x,scale_y)
/*	plots v_points isoparametric 
        curves of the  rat Bez surface, each with u_points
        points on it.
	
Input:  bx, by:		 arrays with x- and y- coordinates of
	       		 control net.
        degree_u,degree_v: degrees in u- and v- direction
	u_points,v_points: plot resolution
	scale_x,scale_y:   scale factor for postscript.

Output: postscript file 
*/

	int degree_u,degree_v,u_points,v_points;
	float bx[20][20], by[20][20],bw[20][20],scale_x,scale_y;

{
	int i,j,u_points1;
	float u,v,del_u,del_v;
	float aux_x[5],aux_y[5],aux_w[5], arrax[5],array[5],arraw[5];
	float points_x[300], points_y[300];
	int iv;
	float ratbez(),decas(),hornbez();


	del_v= 1.0/((float)v_points);
	u_points1=u_points+1;
	v=0.0;

	for(iv=0; iv<= v_points; iv++)/* loop over all curves to be drawn*/
	{

		for(i=0;i<=degree_u; i++)/* create aux. arrays*/
		{
		for(j=0; j<= degree_v; j++)
			{
			arraw[j]=bw[i][j];
			arrax[j]=bx[i][j]*arraw[j];
			array[j]=by[i][j]*arraw[j];
			}

		aux_w[i]=hornbez(degree_v,arraw,v);
		aux_x[i]=hornbez(degree_v,arrax,v)/aux_w[i];
		aux_y[i]=hornbez(degree_v,array,v)/aux_w[i];

		}
		
		ratbez_to_points(degree_u,u_points,aux_x,aux_w,points_x);
		ratbez_to_points(degree_u,u_points,aux_y,aux_w,points_y);

	/******************* now ps: *******************************/	
			
		fprintf(psfile,"newpath\n");

		fprintf(psfile,"%f %f moveto\n",
			scale_x*points_x[0], scale_y*points_y[0]);


		for(j=1; j<= u_points; j++)
			fprintf(psfile,"%f %f lineto\n",scale_x*points_x[j], scale_y*points_y[j]);

		fprintf(psfile,"stroke\n");


		v = v+del_v;

	}
}



