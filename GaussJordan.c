#include <stdio.h>
#include <stdlib.h>
#include "GaussJordan.h"
#define N 3

double **alloc_matrix(int nl, int nc)
{
	double **mat=(double**)malloc(nl*sizeof(double *));
	for( int i=0;i<nl;i++)
	{
		mat[i]=(double*)malloc(nc*sizeof(double));
	}
	
	return mat;
}

void desalloc_matrix(double **mat, int nl)
{
	for(int i=0;i<nl;i++)
	{
		free(mat[i]);	
	}
	
	free(mat);
	
	return;
}

/* Affichage du systÃ¨me */
void affich_systeme(double **A ,double *b)
{
	int i , j ;
	printf(" ===>Affichage du systeme : \n\n\n");
	
	for(i = 0 ; i < N ; i++)
	{
		printf("  [");
		for(j = 0 ; j < N ; j++)
		{
			printf("  %.3f  ",A[i][j]);
		}
		printf(" ]    [X%d]   =",i+1);
		printf("\t%.3f",b[i]);
		printf("\n\n");
	}
}


/*
void GaussJordanElimination(double **A, double *b){
	int i,lignePivot,aux;
	double *T, *T1, *T2;//Vecteur temporaire
	
	T = (double *) malloc (sizeof (double *) * N);
	T1 = (double *) malloc (sizeof (double *) * N);
	T2 = (double *) malloc (sizeof (double *) * N);
	
	
	for(int k=0; k<N; k++)
	{
		if(A[k][k]!=0)
		{
			lignePivot = k;
			printf("here %d %d\n",k,k);
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
		for(int i=k;i<N;i++)
		{
			T2[i]=A[k][i];
			A[k][i]=A[lignePivot][i];
			A[lignePivot][i]=T2[i];
		}
		//Permutaion de la k-Ã¨me ligne avec la ligne de pivot du vecteur b
		aux=b[k];
		b[k]=b[lignePivot];
		b[lignePivot]=aux;
		
		//DIAGONALISATION DE LA MATRICE A
		
		
		//La mise Ã  jours de la matrice A
		for(int i=k+1;i<N;i++)
		{
			printf("La mise Ã  jours de la matrice A\n");
			T[i]=-A[k][i]/A[k][k];
		}
		
		for(int i=0;i<N;i++)
		{
			for(int j=k+1;j<N;j++){
				A[i][j]=A[i][j]+T[j]*A[i][k];
			}
		}
		for(int i=k+1;i<N;i++)
		{
			for(int j=k+1;j<N;j++){
				A[i][j]=A[i][j]+T[j]*A[i][k];
			}
		}
		//TRANSFORMATION DU VECTEUR b
		 
		//La mise Ã  jours du vecteur b
		for(int i=0;i<N;i++)
		{
			 T1[i]=A[i][k];
			 aux = b[k];
			 b[i]=b[i]-(T1[i]/A[k][k]);
			 b[k]=aux;		
		}
		//affich_systeme(A ,b);
		printf("jhgjhgj\n");
	}
	
}*/


void GaussJordanElim(double **A, double *b){
	int i,lignePivot,aux;
	double *T;//Vecteur temporaire
	
	T = (double *) malloc (sizeof (double *) * N);
	//************************
	
	for(int k=0; k<N; k++)
	{
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
		
			//Permutation de la k-Ã¨me ligne avec la ligne de pivot de a matrice A
			for(int i=0;i<N;i++)
			{
				T[i]=A[k][i];
				A[k][i]=A[lignePivot][i];
				A[lignePivot][i]=T[i];
			}
			//Permutaion de la k-Ã¨me ligne avec la ligne de pivot du vecteur b
			aux=b[k];
			b[k]=b[lignePivot];
			b[lignePivot]=aux;
		}
		//DIAGONALISATION DE LA MATRICE A
		
		for(int i=0;i<N;i++)
		{
			T[i]=A[i][k];
			if(i!=k){
				for(int j=k+1;j<N;j++)
				{
					A[i][j] = A[i][j]-(A[k][j]/A[k][k])*T[i];
				}
			}
		}
		
		for(int i=0;i<N;i++)
		{
			T[i]=A[i][k];
			aux = b[k];
			b[i] = b[i]-(T[i]/A[k][k])*b[k];
			b[k] = aux;
		}
		affich_systeme(A,b);
	}
	
}


/* Saisie des Ã©lÃ©ments de la matrice A */
void saisie_mat(double **A)
{ 
     int i , j ;
     printf(" ===>Saisie de la matrice : \n\n\n");
     
     for(i = 0 ; i < N ; i++)
     {
        for( j = 0 ; j < N ; j++)
        {
           printf("  A[%d][%d] : ",i+1,j+1);
           scanf("%lf",&A[i][j]);
        }
     printf("\n");
     }
}

/* Saisie des Ã©lÃ©ments de la matrice B */
void saisie_vect(double *b)
{ 
     int i ;
     printf(" ===>Saisie du vecteur : \n\n\n");
     
     for(i = 0 ; i < N ; i++)
     {
        printf("  b[%d] : ",i+1);
        scanf("%lf",&b[i]);
        printf("\n");
     }
}

void ResulutionLinearSystem(double **D, double *y)
{
	
	printf(" ===>Affichage de la solution : \n\n\n");
	for(int i=0; i<N; i++)
	{
		
		printf("(X%d)   =",i+1);
		printf("\t%.6f",(y[i] / D[i][i]));
		printf("\n\n");
	}
	
}



/* Affichage de la solution du systÃ¨me */
void affich_sol(double *x, int n)
{
	printf(" ===>Affichage de la solution : \n\n\n");
	
	for(int i = 0 ; i < n ; i++)
	{
        printf("[X%d]   =",i+1);
		printf("\t%.6f",x[i]);
		printf("\n\n");
	}
}
