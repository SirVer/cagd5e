float horner(degree,coeff,t)
/*
     uses  Horner's scheme to compute one coordinate
     value of a curve in power form. Has to be called 
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
	float aux;

	aux=coeff[degree];      

	for(i=degree; i>0; i--)
		aux= t*aux + coeff[i-1];


	return(aux);
}


