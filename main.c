#include <stdio.h>
#include <stdlib.h>
#include "GaussJordan.h"
#define N 3

int main() 
{ 
	int n = 3;
	double **A = alloc_matrix(n,n);
	double *b = (double *) malloc (sizeof (double) * n);
	double *r = (double *) malloc (sizeof (double) * n);
	saisie_mat(A) ;
    saisie_vect(b) ;
 
	
	//GaussJordanElimination(A, b);
	GaussJordanElim(A, b);
	ResulutionLinearSystem(A,b);
	//affich_sol(r,n);

	return 0; 
} 
