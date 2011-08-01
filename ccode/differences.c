void differences(degree,coeff,diffs)
/*
     Computes all forward differences Delta^i(b_0).
     Has to be called 
     for each coordinate  (x,y, and/or z) of a control polygon.
     Input:   degree: length (from 0) of coeff.
              coeff:  array of coefficients.
      Output: diffs:  diffs[i]= Delta^i(coeff[0]).
*/
     float coeff[],diffs[];
     int degree; 
     {
     int r,i;
	float diffs1[20];

	for(i=0; i<=degree; i++) diffs1[degree-i]=coeff[i]; 

	for (r=1; r<= degree; r++)
	for (i=0; i<= degree - r; i++)
		diffs1[i]=  diffs1[i] - diffs1[i+1] ;  

	for(i=0;i<=degree;i++) diffs[i]=diffs1[degree-i];   

     }


