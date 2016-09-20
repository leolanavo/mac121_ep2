#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int l, c;
} pos;

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
    
    destroyMatrix(matrix, lin);
}

/*Checa se o movimento da peça pode ser executado.*/
int availablePos (int** tab, pos crt, int mov, int lin, int col) {

    switch (mov) {
        case 0:
            /*Evita que o programa acesse a matriz além do que está alocado.
            Cada case tem seu if para evitar segmentation fault.*/
            if (crt.c + 2 => col) {
                break;
            }

            if (tab[crt.l][crt.c + 1] == 1 && tab[crt.l][crt.c + 2] == -1) {
                return 1;
            }

        case 1:

            if (crt.l - 2 < 0) {
                break;
            }

            if (tab[crt.l - 1][crt.c] == 1 && tab[crt.l - 2][crt.c] == -1) {
                return 1;
            }

        case 2:

            if (crt.c - 2 < 0) {
                break;
            }

            if (tab[crt.l][crt.c - 1] == 1 && tab[crt.l][crt.c - 2] == -1) {
                return 1;
            }

        case 3:

            if (crt.l + 2 => lin) { 
                break;
            }

            if (tab[crt.l + 1][crt.c] == 1 && tab[crt.l + 2][crt.c] == -1) {
                return 1;
            }
    
    return 0;
    
    }
}

/*Move a peça no tabuleiro de acordo com o movimento da vez.*/
void movePiece (int** tab, pos crt, int mov) {
    
    tab[crt.l][crt.c] = 0;

    switch (mov) {
        case 0:

            tab[crt.l][crt.c + 1] = -1;
            tab[crt.l][crt.c + 2] = 1;
            break;

        case 1:

            tab[crt.l - 1][crt.c] = -1;
            tab[crt.l - 2][crt.c] = 1;
            break;

        case 2:

            tab[crt.l][crt.c - 1] = -1;
            tab[crt.l][crt.c - 2] = 1;
            break;

        case 3:

            tab[crt.l + 1][crt.c] = -1;
            tab[crt.l + 2][crt.c] = 1;
            break;
    }

}

int pegSolitaire (int** tab, int lin, int col) {
    int ok;

}

int main () {
    int lin, col, **tab;

    scanf("%d %d", &lin, &col);
    tab = createMatrix(lin, col);
    readMatrix(matrix, lin, col);
    
    printMatrix(tab, lin, col);
    return 0;
}