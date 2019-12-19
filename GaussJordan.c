#include <stdio.h>
#include <stdlib.h>
#include "GaussJordan.h"


void Init_Matrix(matrix mat){
	
}

double **alloc_matrix(int lig, int col)
{
	double **mat=(double**)malloc(nl*sizeof(double *));
	for( int i=0;i<nl;i++)
	{
		mat[i]=(double*)malloc(nc*sizeof(double));
	}
	
	return mat;
}

void desalloc_matrix(t_matrice* mat)
{
	for(int i=0;i<=nl;i++)
	{
		free(mat[i]);	
	}
	
	free(mat);
	
	return;
}
