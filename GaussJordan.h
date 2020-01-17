#ifndef GAUSSJORDAN_H
#define GAUSSJORDAN_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

double **alloc_matrix(int nlig,int ncol);
void aff_matrice(double **mat);
void desalloc_matrix(double **mat, int nl);
void GaussJordanElim(double **A, double *b,int N);
void GaussJordanElimParallel(double **A, double *b, int N, int N_threads);
void GaussJordanElimination(double **A, double *b);
void ResulutionLinearSystem(double **D, double *y, int N);
void ResulutionLinearSystemParallel(double **D, double *y, int N, int N_threads);
void affich_sol(double *x, int n);
void affich_systeme(double **A ,double *b, int size);
void saisie_mat(double **A, int n);
void saisie_vect(double *b, int n);
void saisie_vect_alea(double *b, int N);
void saisie_mat_alea(double **A, int N);

#endif
