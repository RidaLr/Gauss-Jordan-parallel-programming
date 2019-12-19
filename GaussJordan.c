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

//this method is not tested yet
void GaussJordanElimination (int **A[][], int *b[]){
	int i,lignePivot,aux;
	int *T[], *T1[], *T2[];//Vecteur temporaire
	
	//************************
	
	for(int j=1; j<n; j++)
	{
		i = j;
		if(A[i][j]!=0)
		{
			lignePivot = i;
		}
		else
		{
			i+=1;
			
			while(A[i][j]==0 && i<=n)
			{
				i+=1;
			}
			lignePivot = i;
		}
		//Permutation de la k-Ã¨me ligne avec la ligne de pivot de a matrice A
		//for(int i=0;i<n;i++)
		//{
			T2[k]=A[k][k];
			A[k][k]=A[lignePivot][k];
			A[lignePivot][k]=T2[k];
		//}
		//Permutaion de la k-Ã¨me ligne avec la ligne de pivot du vecteur b
		aux=b[k];
		b[k]=b[lignePivot];
		b[lignePivot]=aux;
		
		//DIAGONALISATION DE LA MATRICE A
		
		//La mise Ã  jours de la matrice A
		T[k+1]=-A[k][k+1]/A[k][k];
		for(int i=1;i=<k-1;i++)
		{
			A[i,k+1]=A[i][k+1]+T[k+1]*A[i][k];
		}
		 
		 //TRANSFORMATION DU VECTEUR b
		 
		 //La mise Ã  jours du vecteur b
		 T1[1]=A[1
		 aux = b[k];
		 b[1]=b[1]-T1[1]/A[k,k];
		 b[k]=aux;		
		
	}
	
}
