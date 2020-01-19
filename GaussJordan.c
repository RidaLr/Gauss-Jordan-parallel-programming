/*
-----------DEVELOPPED BY RIDA LAKSIR & MANOA ANGELO  2019/2020 ISTY---------
*/

#include "GaussJordan.h"


//Allocation dynamique de la mtrice 
double **alloc_matrix(int nl, int nc)
{
	double **mat=(double**)malloc(nl*sizeof(double *));
	for( int i=0;i<nl;i++)
	{
		mat[i]=(double*)malloc(nc*sizeof(double));
	}
	
	return mat;
}

//desallocation de la matrice
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
void affich_systeme(double **A ,double *b, int size)
{
	int i , j ;
	printf(" <<<<<<<<<<<<<<<<< Affichage du systeme >>>>>>>>>>>>>>>>>> \n\n\n");
	
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



//La version sequentiel de la mÃ©thode d'elimination de gauss jordan
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
		if(A[N-1][N-1]==0)
		{
			printf("\n <<<<<<<<<<<<<<<<La matrice est singuliÃ¨re>>>>>>>>>>>>>> \n");
			exit(EXIT_FAILURE);
		}
		/*
		else
		{
			affich_systeme(A,b,N);//Affichage du rÃ©sultat
		}*/
	}
	
}


//Le version Parallel de la methode d'elimination e Gauss Jordan
void GaussJordanElimParallel(double **A, double *b, int N, int N_threads)
{

	int i,j,l,lignePivot,aux;
	double *T;//A temporary vector
	
	T = (double *) malloc (sizeof (double *) * N);
	//************************
	omp_set_num_threads(N_threads);
	
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
			
				//Permutation de la k-Ã¨me ligne avec la ligne de pivot de a matrice A
				#pragma omp for private(i) nowait schedule(static)
					for(i=0;i<N;i++)
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
			#pragma omp for private(l) nowait schedule(static)
				for(l=0;l<N;l++)
				{
					T[l]=A[l][k];
					aux = b[k];
					b[l] = b[l]-(T[l]/A[k][k])*b[k];
					b[k] = aux;
				}
			if(A[N-1][N-1]==0)
			{
				printf("\n La matrice est singuliÃ¨re!!\n");
				exit(EXIT_FAILURE);
			}
			/*
			else
			{
				affich_systeme(A,b,N);//Affichage du resultat final
			}*/
		}
	}
}


/* Saisie des Ã©lÃ©ments de la matrice A */
void saisie_mat(double **A, int N)
{ 
  
     printf(" <<<<<<<<<<<<< Saisie de la matrice >>>>>>>>>>>>>>>> \n\n\n");
     
     for(int i = 0 ; i < N ; i++)
     {
        for(int j = 0 ; j < N ; j++)
        {
           printf("  A[%d][%d] : ",i+1,j+1);
           scanf("%lf",&A[i][j]);
        }
     printf("\n");
     }
}

// Saisie du vecteur b
void saisie_vect(double *b, int N)
{ 
     
     printf(" <<<<<<<<<<<<< Saisie du vecteur >>>>>>>>>>>>>> \n\n\n");
     
     for(int i = 0 ; i < N ; i++)
     {
        printf("  b[%d] : ",i+1);
        scanf("%lf",&b[i]);
        printf("\n");
     }
}

//version sÃ©quentille
void ResulutionLinearSystem(double **D, double *y, int N)
{
	
	printf(" <<<<<<<<<<<< Show the solution (sequential) >>>>>>>>>>>>>>>\n\n");
	for(int i=0; i<N; i++)
	{
		
		printf("[X%d]   =",i+1);
		printf("\t%f",(y[i] / D[i][i]));
		printf("\n\n");
	}
	
}

//version parallÃ¨le
void ResulutionLinearSystemParallel(double **D, double *y, int N, int N_threads)
{
	omp_set_num_threads(N_threads);
	printf(" <<<<<<<<<<< Show the solution with parallelism >>>>>>>>>>>>>>>>\n\n\n");
	#pragma omp parallel
	{
		 #pragma omp for schedule(static) nowait
			for(int i=0; i<N; i++)
			{
				printf("[X%d]   =",i+1);
				printf("\t%f",(y[i] / D[i][i]));
				printf("\n\n");
			}
	}
}


/* Affichage du resultat final */
void affich_sol(double *x, int n)
{
    
	printf(" <<<<<<<<< Show the solution >>>>>>>>>>>>>>\n\n\n");
	
	for(int i = 0 ; i < n ; i++)
	{
        printf("[X%d]   =",i+1);
		printf("\t%.6f",x[i]);
		printf("\n\n");
	}
}

//Saisie de la matrice aleatoirement 
void saisie_mat_alea(double **A, int N)
{ 
     
     double nb_alea=0.0;
     srand(time(NULL));
     printf(" <<<<<<<<<Saisie de la matrice aleatoirement>>>>>>>>>> \n\n\n");
     
     for(int i = 0 ; i < N ; i++)
     {
        for(int j = 0 ; j < N ; j++)
        {
			if(i==j || (i>=1 && j==i-1) || (i>=0 && j==i+1) )
			{
			   nb_alea=(double)rand()/RAND_MAX*100.0-0.0;
			   A[i][j]=nb_alea;
			//	   printf("  A[%d][%d] : %d",i+1,j+1,nb_alea);
		   }
		   else
		   {
			   A[i][j]=0.0;
		   }
        }
     }
     
     for(int i = 0 ; i < N ; i++)
	{
		printf("  (");
		for(int j = 0 ; j < N ; j++)
		{
			printf("  %.3f  ",A[i][j]);
		}
		printf("\n\n");
	}
}


//Saisie du vecteur aleatoirement
void saisie_vect_alea(double *b, int N)
{ 
     
     double nb_alea=0.0;
     srand(time(NULL));
     printf(" <<<<<<<<<<<<<Saisie du vecteur aleatoirement>>>>>>>>>> \n\n\n");
     
     for(int i = 0 ; i < N ; i++)
     {
		nb_alea=(double)rand()/RAND_MAX*100.0-0.0;
		b[i]=nb_alea;
       // printf("  b[%d] : %d ",i+1,nb_alea);
      //  printf("\n");
     }
}
