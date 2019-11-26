#ifndef GAUSSJORDAN_H
#define GAUSSJORDAN_H


typedef struct{
	int nlign;
	int ncolo;
	int **tab;
}matrix;


matrix *alloc_matrice(int nlig,int ncol);
void aff_matrice(matrix *mat);
void saisir_matrice(matrix *mat);
void desalloc_matrice(matrix *mat);
matrix produit(matrix *mat1,matrix *mat2);

void Init_Matrix();
void Gauss_Jordan();
void Show_Matrix();
void Copy_Matrix();

#endif
