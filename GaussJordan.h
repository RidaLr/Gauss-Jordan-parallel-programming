#ifndef GAUSSJORDAN_H
#define GAUSSJORDAN_H


double **alloc_matrice(int nlig,int ncol);
void aff_matrice(double **mat);
void saisir_matrix(double **mat);
void desalloc_matrix(double **mat);
double GaussJordanElimination (double **A, double *b);

void Init_Matrix();
void Gauss_Jordan();
void Show_Matrix();
void Copy_Matrix();

#endif
