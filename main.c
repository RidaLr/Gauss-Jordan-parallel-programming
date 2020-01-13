#include <stdio.h>
#include <stdlib.h>
#include "GaussJordan.h"


int main() 
{ 
	
	int N_threads, choise, n;
	double **A = NULL; 
	double *b = NULL;
	double *r = NULL;
	
	//Le menu de notre programme 
	while(choise!=3){
        printf("           ---------------------------------------------------------\n");
        printf("          | Gauss-Jordan Elimination Project (Parallel programming) |\n");
        printf("           ---------------------------------------------------------\n");
        
        printf("  ------------------------------- MENU --------------------------------------- \n");
        printf(" |  1) Sequantial version.                                                    |\n");
        printf(" |  2) Parallel version.                                                      |\n");
        printf(" |  3) Quit.                                                                  |\n");
        printf("  ---------------------------------------------------------------------------- \n");
        printf("  -----------DEVELOPPED BY RIDA LAKSIR & MANOA ANGELO  2019/2020 ISTY--------- \n");
        printf("Your choice : ");
        scanf("%d",&choise);
        switch(choise)
        {
			case 1:{
				choise=0;
				while(choise!=7){
					printf("  --------------------------SEQUENTIAL VERSION-------------------------- \n");
					printf(" |  1) Enter the size of matrix A and vector b.                        |\n");
					printf(" |  2) Create the matrix A using your own values.                       |\n");
					printf(" |  3) Create the matrix A with a random values.                       |\n");
					printf(" |  4) Create the vector b using your own values.                       |\n");
					printf(" |  5) Create the vector v whith a random values.                       |\n");
					printf(" |  6) Show results.                                                    |\n");
					printf(" |  7) Quit.                                                            |\n");
					printf(" ----------------------------------------------------------------------- \n");
					printf("Your choice : ");
					scanf("%d",&choise);
					
					if(choise==1)
					{
						printf("Enter the size : ");
						scanf("%d",&n);
						A = alloc_matrix(n,n);
						b = (double *) malloc (sizeof (double) * n);
						//r = (double *) malloc (sizeof (double) * n);
					}
					
					if(choise==2)
					{
						saisie_mat(A, n) ;
					}
					
					if(choise==3)
					{
						//TODO create the random generator
						saisie_mat_alea(A,n);
					}
					
					if(choise==4)
					{
						saisie_vect(b, n) ;
					}
					
					if(choise==5)
					{
						//TODO create the random generator 
						saisie_vect_alea(b,n);
					}
					if(choise==6)
					{
						GaussJordanElim(A, b, n);
						ResulutionLinearSystem(A, b, n);
					}
					
				}
						break;}
			case 2:{
					//Insert the number of threads that you want to create 
				do{
					printf("Insert the number of threads that you want to create \n");
					scanf("%d",&N_threads);
				}while(N_threads<=1);
				choise=0;
				while(choise!=7){
					printf("  -----------------------PARALLEL VERSION------------------------------- \n");
					printf(" |  1) Enter the size of matrix A and vector b.                        |\n");
					printf(" |  2) Create the matrix A using your own values.                       |\n");
					printf(" |  3) Create the matrix A with a random values.                       |\n");
					printf(" |  4) Create the vector b using your own values.                       |\n");
					printf(" |  5) Create the vector v whith a random values.                       |\n");
					printf(" |  6) Show results.                                                    |\n");
					printf(" |  7) Quit.                                                            |\n");
					printf(" ----------------------------------------------------------------------- \n");
					printf("Your choice : ");
					scanf("%d",&choise);
					
					if(choise==1)
					{
						printf("Enter the size : ");
						scanf("%d",&n);
						A = alloc_matrix(n,n);
						b = (double *) malloc (sizeof (double) * n);
						r = (double *) malloc (sizeof (double) * n);
					}
					
					if(choise==2)
					{
						saisie_mat(A, n) ;
					}
					
					if(choise==3)
					{
						//TODO create the random generator
						saisie_mat_alea(A,n);
					}
					
					if(choise==4)
					{
						saisie_vect(b, n) ;
					}
					
					if(choise==5)
					{
						//TODO create the random generator 
						saisie_vect_alea(b,n);
					}
					if(choise==6)
					{
						GaussJordanElimParallel(A, b, n);
						ResulutionLinearSystemParallel(A, b, n);
					}
					
				}
				break;
				}
			case 3:{
				return 0; // Quitter le programme        
				break;
			}
			
		}
	}

	return 0; 
} 
