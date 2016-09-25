/*Este arquivo definirá as funções de matriz*/
#ifndef MATRIX_H
#define MATRIX_H

/*Cria uma matriz com dimensões lin X col.*/
int** createMatrix (int lin, int col);

/*Lê uma matriz lin X col da entrada padrão, entrada por entrada.*/
void readMatrix (int** matrix, int lin, int col);

/*Libera toda a memória usada para alocar a matriz.*/
void destroyMatrix (int** matrix, int lin);

/*Imprime uma matriz lin X col.*/
void printMatrix (int** matrix, int lin, int col);

/*Compara duas matrizes e retorna 1 se elas forem iguais, 0
caso contrário*/
int cmpMatrix (int** matrix1, int** matrix2, int lin, int col);

#endif