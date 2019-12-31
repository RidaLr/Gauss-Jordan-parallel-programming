#ifndef GAUSSJORDAN_H
#define GAUSSJORDAN_H


double **alloc_matrix(int nlig,int ncol);
void aff_matrice(double **mat);
void desalloc_matrix(double **mat, int nl);
void GaussJordanElim(double **A, double *b);
void GaussJordanElimination(double **A, double *b);
void ResulutionLinearSystem(double **D, double *y);
void affich_sol(double *x, int n);
void affich_systeme(double **A ,double *b);
void saisie_mat(double **A);
void saisie_vect(double *b);

void Init_Matrix();
void Show_Matrix();

#endif
