float hornbez(degree,coeff,t)
/*
     uses  Horner's scheme to compute one coordinate
     value of a  Bezier curve. Has to be called 
     for each coordinate  (x,y, and/or z) of a control polygon.
     Input:   degree: degree of curve.
              coeff:  array with coefficients of curve.
              t:      parameter value.
      Output: coordinate value.
*/
	int degree;
	float coeff[];
	float t;
{
	int i;
	int n_choose_i;          /* shouldn't be too large! */
	float fact,t1,aux;

	t1=1.0 - t;  fact=1.0;
	n_choose_i=1;

	aux=coeff[0]*t1;          /* starting the evaluation
                                  loop */
	for(i=1; i<degree; i++)
	{
		fact=fact*t;
		n_choose_i=n_choose_i*(degree-i+1)/i;  /* always int! */
		aux=(aux + fact*n_choose_i*coeff[i])*t1;
	}
	aux = aux + fact*t*coeff[degree];

	return aux;
}


