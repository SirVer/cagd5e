#include <stdio.h>
#include <math.h>

extern FILE *psfile;

void psplot_net(lu,lv,bx,by,step_u,step_v,scale_x,scale_y,value)
/*	plots  control net     	into postscript-file.
Input:	lu,lv:		dimensions of net
	bx,by:		net vertices
	step_u,step_v:	subnet sizes (e.g. both=3 for pw bicubic net)
	scale_x,scale_y:scale factors for ps
	value:		window size in world coords
*/
	int lu,lv,step_u,step_v;
	float bx[20][20], by[20][20],value[4],scale_x,scale_y;

{
	int lv1;
	int i,j;

	
		fprintf(psfile,"0.0 setgray \n");
		fprintf(psfile,"1 setlinewidth\n");


	lv1= lv+1;
	for(i=0; i<= lu; i++)
	{
		fprintf(psfile,"newpath\n");
		fprintf(psfile," %f %f moveto\n",
			scale_x*(bx[i][0]-value[0]),
			scale_y*(by[i][0]-value[2]));
		for(j=1; j<= lv; j++)
			fprintf(psfile,"%f %f lineto\n",
			scale_x*(bx[i][j]-value[0]), 
			scale_y*(by[i][j]-value[2]));
			
		fprintf(psfile,"stroke\n");
	}

	for(j=0;j<= lv;j++)
	{
		fprintf(psfile,"newpath\n");
		fprintf(psfile," %f %f moveto\n",
			scale_x*(bx[0][j]-value[0]),
			scale_y*(by[0][j]-value[2]));

		for(i=1; i<= lu; i++) 
			fprintf(psfile," %f %f lineto\n",
			scale_x*(bx[i][j]-value[0]),
			scale_y*(by[i][j]-value[2]));
		
		fprintf(psfile,"stroke\n");
	}

	/***** now mark control points *****/


	for(i=0; i<= lu; i++)
	{
		for(j=0; j<= lv; j++)
			fprintf(psfile,"%f %f %f %f %f arc stroke\n",
			scale_x*(bx[i][j]-value[0]),
			 scale_y*(by[i][j]-value[2]),
			3.0, 0.0, 360.0);		
	}


	fprintf(psfile,"1 setgray\n"); /* to white out circles */

	for(i=0; i<= lu; i++)
	{
		for(j=0; j<= lv; j++)
			fprintf(psfile,"%f %f %f %f %f arc fill\n",
			scale_x*(bx[i][j]-value[0]),
			 scale_y*(by[i][j]-value[2]),
			2.9, 0.0, 360.0);		
	}


	/* subnet corners in black: */
	fprintf(psfile,"0.0 setgray\n");


	for(i=0; i<= lu; i+= step_u)
	{
		for(j=0; j<= lv; j+= step_v)
			fprintf(psfile,"%f %f %f %f %f arc fill\n",
			scale_x*(bx[i][j]-value[0]), 
			scale_y*(by[i][j]-value[2]),
			2.9, 0.0, 360.0);		
	}
	


}

