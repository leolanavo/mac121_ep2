#include <stdio.h>
#include <stdlib.h>

/*Cria uma matriz com dimensões lin X col.*/
int** createMatrix (int lin, int col) {
    int** matrix, i;
    matrix = malloc(lin * sizeof(int*));
    for (i = 0; i < lin; i++) {
        matrix[i] = calloc(col, sizeof(int));
    }
    return (matrix);
}

/*Lê uma matriz lin X col da entrada padrão, entrada por entrada.*/
void readMatrix (int** matrix, int lin, int col) {
    int i, j;
    for (i = 0; i < lin; i++) {
        for (j = 0; j < col; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
}

/*Libera toda a memória usada para alocar a matriz.*/
void destroyMatrix (int** matrix, int lin) {
    int i;
    for (i = 0; i < lin; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

/*Imprime uma matriz lin X col.*/
void printMatrix (int** matrix, int lin, int col) {
    int i, j;
    
    for (i = 0; i < lin; i++) {
        for (j = 0; j < col; j++) {
            printf("%d ", matrix[i][j]);
        }
    printf("\n");
    }
}