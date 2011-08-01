float aitken(degree,coeff,t)
/*
     uses  Aitken's algorithm to compute one coordinate
     value of a  Lagrange curve. Has to be called 
     for each coordinate  (x,y, and/or z) of data set.
     Input:   degree: degree of curve.
              coeff:  array with coordinates to be interpolated.
              t:      parameter value where to interpolate.
      Output: coordinate value.

      Note: we  assume a uniform knot sequence!
*/
     float coeff[];
     float t;
     int degree; 
     {
     int r,i;
     float t1;
     float coeffa[30];
   
     for (i=0; i<=degree; i++) coeffa[i]=coeff[i]; /* save input */
     

     for (r=1; r<= degree; r++)
     for (i=0; i<= degree - r; i++)
     {
	  t1=(degree*t-i)/((float) r);
          coeffa[i]= (1.0-t1)* coeffa[i]  +   t1 * coeffa[i+1] ;
     }     

     return (coeffa[0]);
     }


