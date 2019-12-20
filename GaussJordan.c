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
void GaussJordanElimination (double **A[][], double *b[])
{
	int i,lignePivot,aux;
	int *T[], *T1[], *T2[];//Vecteur temporaire
	
	//************************
	
	for(int k=1; k<n; k++)
	{
		//i = j;
		if(A[k][k]!=0)
		{
			lignePivot = k;
		}
		else
		{
			i = k+1;
			
			while(A[i][k]==0)
			{
				i+=1;
			}
			lignePivot = i;
		}
		//Permutation de la k-Ã¨me ligne avec la ligne de pivot de a matrice A
		for(int i=0;i<n;i++)
		{
			T2[i]=A[i][i];
			A[i][i]=A[lignePivot][i];
			A[lignePivot][i]=T2[i];
		}
		//Permutaion de la k-Ã¨me ligne avec la ligne de pivot du vecteur b
		for(int i=0;i<n;i++)
		{
			aux=b[i];
			b[i]=b[lignePivot];
			b[lignePivot]=aux;
		}
		//DIAGONALISATION DE LA MATRICE A
		
		//La mise Ã  jours de la matrice A
		for(int i=0;i<n;i++)
		{
			T[i+1]=-A[i][i+1]/A[i][i];
		}
		
		for(int i=1;i=<k-1;i++)
		{
			A[i,k+1]=A[i][k+1]+T[k+1]*A[i][k];
		}
		 
		 //TRANSFORMATION DU VECTEUR b
		 
		 //La mise Ã  jours du vecteur b
		for(int i=1;i<=n;i++)
		{
			 T1[i]=A[i][k];
			 aux = b[k];
			 b[i]=b[i]-T1[i]/A[k,k];
			 b[k]=aux;		
		}
	}
	
}
