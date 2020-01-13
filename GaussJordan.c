#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "GaussJordan.h"
#include <time.h>

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

/* Affichage du système */
void affich_systeme(double **A ,double *b, int size)
{
	int i , j ;
	printf(" ===>Affichage du systeme : \n\n\n");
	
	for(i = 0 ; i < size ; i++)
	{
		printf("  (");
		for(j = 0 ; j < size ; j++)
		{
			printf("  %.3f  ",A[i][j]);
		}
		printf(" )    (X%d)   =",i+1);
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
		//Permutation de la k-ème ligne avec la ligne de pivot de a matrice A
		for(int i=k;i<N;i++)
		{
			T2[i]=A[k][i];
			A[k][i]=A[lignePivot][i];
			A[lignePivot][i]=T2[i];
		}
		//Permutaion de la k-ème ligne avec la ligne de pivot du vecteur b
		aux=b[k];
		b[k]=b[lignePivot];
		b[lignePivot]=aux;
		
		//DIAGONALISATION DE LA MATRICE A
		
		
		//La mise à jours de la matrice A
		for(int i=k+1;i<N;i++)
		{
			printf("La mise à jours de la matrice A\n");
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
		 
		//La mise à jours du vecteur b
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

//Sequential version
void GaussJordanElim(double **A, double *b, int N)
{

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
		
			//Permutation de la k-ème ligne avec la ligne de pivot de a matrice A
			for(int i=0;i<N;i++)
			{
				T[i]=A[k][i];
				A[k][i]=A[lignePivot][i];
				A[lignePivot][i]=T[i];
			}
			//Permutaion de la k-ème ligne avec la ligne de pivot du vecteur b
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
		if(A[N-1][N-1]==0)
		{
			printf("\n La matrice est singulière!!\n");
			exit(EXIT_FAILURE);
		}
		else
		{
			affich_systeme(A,b,N);
		}
	}
	
}


//Parallel version
void GaussJordanElimParallel(double **A, double *b,int N)
{

	int i,j,l,lignePivot,aux;
	double *T;//A temporary vector
	
	T = (double *) malloc (sizeof (double *) * N);
	//************************
	
	#pragma omp parallel
	{
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
			
				//Permutation de la k-ème ligne avec la ligne de pivot de a matrice A
				#pragma omp parallel for
					for(i=0;i<N;i++)
					{
						T[i]=A[k][i];
						A[k][i]=A[lignePivot][i];
						A[lignePivot][i]=T[i];
					}
				//Permutaion de la k-ème ligne avec la ligne de pivot du vecteur b
				aux=b[k];
				b[k]=b[lignePivot];
				b[lignePivot]=aux;
			}
			//DIAGONALISATION DE LA MATRICE A
			#pragma omp for private(l,j) nowait schedule(static)
				for(l=0;l<N;l++)
				{
					T[l]=A[l][k];
					if(l!=k){
						for(j=k+1;j<N;j++)
						{
							A[l][j] = A[l][j]-(A[k][j]/A[k][k])*T[l];
						}
					}
				}
			#pragma omp for private(l) nowait
				for(l=0;l<N;l++)
				{
					T[l]=A[l][k];
					aux = b[k];
					b[l] = b[l]-(T[l]/A[k][k])*b[k];
					b[k] = aux;
				}
			if(A[N-1][N-1]==0)
			{
				printf("\n La matrice est singulière!!\n");
				exit(EXIT_FAILURE);
			}
			else
			{
				affich_systeme(A,b,N);
			}
		}
	}
}


/* Saisie des éléments de la matrice A */
void saisie_mat(double **A, int N)
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

void saisie_mat_alea(double **A, int N)
{ 
     int i , j ,nb_alea=0;
     srand(time(NULL));
     printf(" ===>Saisie de la matrice aleatoirement: \n\n\n");
     
     for(i = 0 ; i < N ; i++)
     {
        for( j = 0 ; j < N ; j++)
        {
		   nb_alea=rand();
           A[i][j]=nb_alea;
           printf("  A[%d][%d] : %d",i+1,j+1,nb_alea);
        }
     printf("\n");
     }
}

/* Saisie des éléments de la matrice B */
void saisie_vect(double *b, int N)
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

void saisie_vect_alea(double *b, int N)
{ 
     int i ,nb_alea=0;
     srand(time(NULL));
     printf(" ===>Saisie du vecteur aleatoirement : \n\n\n");
     
     for(i = 0 ; i < N ; i++)
     {
		nb_alea=rand();
		b[i]=nb_alea;
        printf("  b[%d] : %d ",i+1,nb_alea);
        printf("\n");
     }
}

//version séquentille
void ResulutionLinearSystem(double **D, double *y, int N)
{
	
	printf(" <========== Show the solution (sequential) ============>\n\n\n");
	for(int i=0; i<N; i++)
	{
		
		printf("[X%d]   =",i+1);
		printf("\t%.6f",(y[i] / D[i][i]));
		printf("\n\n");
	}
	
}

//version parallèle
void ResulutionLinearSystemParallel(double **D, double *y, int N)
{
	
	printf(" <======= Show the solution with parallelism =========>\n\n\n");
	#pragma omp parallel
	{
		 #pragma omp for schedule(static) nowait
			for(int i=0; i<N; i++)
			{
				printf("[X%d]   =",i+1);
				printf("\t%.6f",(y[i] / D[i][i]));
				printf("\n\n");
			}
	}
}


/* Show the solution */
void affich_sol(double *x, int n)
{
    int i ;
	printf(" <======= Show the solution ============>\n\n\n");
	
	for(i = 0 ; i < n ; i++)
	{
        printf("[X%d]   =",i+1);
		printf("\t%.6f",x[i]);
		printf("\n\n");
	}
}

int getThreadsNbr()
{
	int nbThreads=0;
	
	printf("Please enter the numbre of thread you want to create !\n");
	scanf("%d",&nbThreads);
	
	return nbThreads;
}
/*
double **GenerateRandomMatrix(int size)
{
	
	
}*/

double *GenerateRandomVector(int size)
{
	double *vector = malloc(sizeof(double)*size);
	
	for(int i = 0; i < size; i++)
	{
		//vector[i] = rand
	}
	return vector;
}
