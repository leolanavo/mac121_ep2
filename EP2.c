#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "stack.h"
#include "matrix.h"


/*Checa se o movimento da peça pode ser executado.*/
int availablePos (int** tab, pos* crt, int mov, int lin, int col) {

    switch (mov) {
        case 0:
            /*Evita que o programa acesse a matriz além do que está alocado.
            Cada case tem seu if para evitar segmentation fault.*/
            if (crt->c + 2 > col) {
                break;
            }

            if (tab[crt->l][crt->c + 1] == 1 && tab[crt->l][crt->c + 2] == -1) {
                return 1;
            }
            break;

        case 1:

            if (crt->l - 2 < 0) {
                break;
            }

            if (tab[crt->l - 1][crt->c] == 1 && tab[crt->l - 2][crt->c] == -1) {
                return 1;
            }
            break;

        case 2:

            if (crt->c - 2 < 0) {
                break;
            }

            if (tab[crt->l][crt->c - 1] == 1 && tab[crt->l][crt->c - 2] == -1) {
                return 1;
            }
            break;

        case 3:

            if (crt->l + 2 > lin) { 
                break;
            }

            if (tab[crt->l + 1][crt->c] == 1 && tab[crt->l + 2][crt->c] == -1) {
                return 1;
            }
            break;

        default:
            break;
    }
    return 0;
}

/*Movee a peça no tabuleiro de acordo com o posimento da vez.*/
void MovePiece (int** tab, pos* crt, int mov) {
    
    tab[crt->l][crt->c] = 1;

    switch (mov) {
        case 0:

            tab[crt->l][crt->c + 1] = -1;
            tab[crt->l][crt->c + 2] = -1;
            crt->c += 2;
            break;

        case 1:

            tab[crt->l - 1][crt->c] = -1;
            tab[crt->l - 2][crt->c] = -1;
            crt->l -= 2;
            break;

        case 2:

            tab[crt->l][crt->c - 1] = -1;
            tab[crt->l][crt->c - 2] = -1;
            crt->c -= 2;
            break;

        case 3:

            tab[crt->l + 1][crt->c] = -1;
            tab[crt->l + 2][crt->c] = -1;
            crt->l += 2;
            break;
    }
}

/*Gera o tabuleiro final*/
void finalMatrix (int** tab, int lin, int col) {
    int i, j, x;
    for (i = 0; i < lin; i++) {
        for (j = 0; j < col; j++) {
            x = tab[i][j];
            if (x == 1) {
                tab[i][j] = -1;
            }
            else if (x == -1) {
                tab[i][j] = 1;
            }
        }
    }
    printMatrix(tab, lin, col);
}

/*Imprime os posimentos*/
/*void printVector (int* v) {
    pos beg, end;
    printf("%d:%d-%d:%d\n", );
}*/

void pegSolitaire (int** tab, int lin, int col) {
    int ok, i, j, mov;/* index; path;*/
    stack *hist;    /*"hist" vem de "history" e "prt" de "print"*/
    pos* crt;       /*"crt" vem de "current"*/

    crt = malloc(sizeof(pos));

    hist = createStack(lin*col); /*lin*col é o tamanho máximo de posimentos*/
                                 /*que podem ser empilhados.*/
    /*path = malloc(4*lin*col * sizeof(int)); Feito com a ciência de porra nenhuma*/

    for (i = 0; i < lin; i++) {
        j = 0;
        while (j < col) {
            if(tab[i][j] == 1) {
                crt->l = i;
                crt->c = j;
                mov = 0;
                while (ok == 0 && mov < 4) {
                    if (availablePos(tab, crt, mov, lin, col)) {
                        ok = 1;
                    }
                    else {
                        mov++;
                    }
                }
                if (ok == 1) {
                    MovePiece(tab, crt, mov);
                    crt->mov = mov;
                    add(crt, hist);
                }
                else { /*backtracking*/
                    if (emptyStack(hist)) {
                        destroyMatrix(tab, lin);
                        destroyStack(hist);
                        /*free(path);*/
                        printf("Impossivel\n");
                        return;
                    }
                    crt = pop(hist);
                    MovePiece(tab, crt, (crt->mov + 2)%4);
                    j--;
                }
            }
            j++;
        }
    }

    /*printfVector(path);*/
    destroyMatrix(tab, lin);
    destroyStack(hist);
    return;
}

int main () {
    int lin, col, **tab;

    scanf("%d %d", &lin, &col);
    tab = createMatrix(lin, col);
    readMatrix(tab, lin, col);

    printf("Entrada\n");
    printMatrix(tab, lin, col);
    
    printf("Saída\n");
    finalMatrix(tab, lin, col);
    
    destroyMatrix(tab, lin);
    return 0;
}