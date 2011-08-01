/*
 * Routine: tri_decast()
 *
 * Function: Triangular de Casteljau algorithm for an n^th
 *           degree triangular Bezier patch. 
 *           Algorithm is applied once for a given (u,v,w) and works on one
 *           coordinate only. 
 *
 * Input:    bpts[i] ................. Bezier points (of one coordinate)
 *                                     as a linear array (see below). 
 *                                     i=0...tri_num  
 *           tri_num ................. Based on the degree of the patch.
 *                                     (n+1)(n+2)/2
 *           ndeg .................... Degree (n) of the patch. 
 *           u[i] .................... Barycentric coordinates (u,v,w) of 
 *                                     evaluation point.  i=0,2
 *           b[i]..................... A working array with dimension >= 
 *                                     to bpts[].
 *
 * Output:   patch_pt ................ One coordinate of the point on 
 *                                     the patch evaluated at (u,v,w).
 *           b[] ..................... Contents have been changed. 
 *
 * Linear array structure: It is assumed that the usual (i,k,j) structure
 *                         of the Bezier net has been put into a linear
 *                         array in the following manner.
 *                         (E.g., for n=3)
 *                         b_(300) --> bpts[0] (u=1)
 *                         b_(030) --> bpts[6] (v=1)
 *                         b_(003) --> bpts[9] (w=1)
 */

#include <stdio.h>
#include <math.h>


tri_decast(bpts, tri_num, ndeg, u, b, patch_pt ) 

    float	bpts[];
    int         tri_num;
    int         ndeg;

    float       u[3];

    float       b[];

    float       *patch_pt;
{

    int         i, j, k, l, m;
    int         r;

    /* ------------------------------ */


    /* 
     * To avoid writing over the original control points, 
     * copy into a working array.
     */

    for (i=0; i<tri_num; i++) 
        b[i] = bpts[i]; 


    /*
     * de Casteljau algorithm applied to the linear array. 
     * The element at the "top" of each mini-triangle in the
     * algorithm is over-written at each step.
     */

    for (r=1; r<=ndeg; r++) {

	m = -1;
	for (i=0; i<=ndeg-r; i++) {

	    for (l=0; l<=i; l++) {

		m = m + 1;
		b[m] = u[0]*b[m] 
                     + u[1]*b[m+1+i] 
                     + u[2]*b[m+2+i]; 
	    }
	}
    } 

    *patch_pt = b[0];

}


