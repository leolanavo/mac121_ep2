#include <stdio.h>
#include <stdlib.h>

/*Cria uma matriz com dimensões lin X col.*/
int** createMatrix (int lin, int col) {
    int** matrix, i;
    matrix = malloc(lin * sizeof(int*));
    for (i = 0; i < lin; i++) {
        matrix[i] = malloc(col * sizeof(int));
    }
    return (matrix);
}

/*Lê uma matriz lin X col da entrada padrão, entrada por entrada.*/
void readMatrix (int** matrix, int lin, int col) {
    int i, j;
    for (i = 0; i < lin; i++) {
        for (j = 0; j < col; j++) {
            if(scanf("%d", &matrix[i][j]) != 1) printf("pau no cu");
        }
    }
}

/*Compara duas matrizes e retorna 1 se elas forem iguais, 0
caso contrário*/
int cmpMatrix (int** matrix1, int** matrix2, int lin, int col) {
    int i, j;
    for (i = 0; i < lin; i++) {
        for (j = 0; j < col; j++) {
            if (matrix1[i][j] != matrix2[i][j]) return 0;
        }
    }
    return 1;
}

/*Libera toda a memória usada para alocar a matriz.*/
void destroyMatrix (int** matrix, int lin) {
    int i;
    
    for (i = 0; i < lin; i++) {
        free(matrix[i]);
        matrix[i] = NULL;
    }
    free(matrix);
    matrix = NULL;
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