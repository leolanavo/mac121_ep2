#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "stack.h"
#include "matrix.h"

/*Gera o tabuleiro final, e enquanto isso acha quantas peças há*/
int** finalMatrix (int** tab, int** tab_f, int lin, int col, int* p, int* h) {
    int i, j, x;

    for (i = 0; i < lin; i++) {
        for (j = 0; j < col; j++) {
            x = tab[i][j];
            if (x == 1) {
                *(p) += 1;
                tab_f[i][j] = -1;
            }
            else if (x == -1) {
                *(h) += 1;
                tab_f[i][j] = 1;
            }
        }
    }
    return(tab_f);
}

/*Copia uma pos para outra*/
pos* copyPos (pos* posi1, pos* posi2) {
    posi2->l = posi1->l;
    posi2->c = posi1->c;
    posi2->m = posi1->m;
    return(posi2);
}

/*Printa uma pos*/
void printPos (pos* posi) {
    printf("%d:%d:%d\n", posi->l, posi->c, posi->m);
}

/*Checa se o movimento da peça pode ser executado.*/
int availablePos (int** tab, pos* crt, int lin, int col) {

    switch (crt->m) {
        case 0:
            /*Cada case tem seu if para evitar segmentation fault.*/
            if (crt->c + 2 >= col) break;

            if (tab[crt->l][crt->c + 1] == tab[crt->l][crt->c + 2] == 1)
                return 1;

            break;

        case 1:

            if (crt->l - 2 < 0) break;

            if (tab[crt->l - 1][crt->c] == tab[crt->l - 2][crt->c] == 1)
                return 1;

            break;

        case 2:

            if (crt->c - 2 < 0) break;

            if (tab[crt->l][crt->c - 1] == tab[crt->l][crt->c - 2] == 1)
                return 1;

            break;

        case 3:

            if (crt->l + 2 >= lin) break;

            if (tab[crt->l + 1][crt->c] == tab[crt->l + 2][crt->c] == 1)
                return 1;
            
            break;

        default:
            
            break;
    }

    return 0;
}

/*Move a peça no tabuleiro de acordo com o posimento da vez.*/
void MovePiece (int** tab, pos* posi, int middle) {
    
    int mov; /*Variável para manipular posi->m sem alterá-lo*/
    
    tab[posi->l][posi->c] = 1;

    /*middle == 1, significa que o programa irá reverter um movimento*/
    if (middle == 1) mov = (posi->m + 2)%4;
    else mov = posi->m;

    switch (mov) {
        case 0:

            tab[posi->l][posi->c + 1] = middle;
            tab[posi->l][posi->c + 2] = -1;
            posi->c += 2;
            break;

        case 1:

            tab[posi->l - 1][posi->c] = middle;
            tab[posi->l - 2][posi->c] = -1;
            posi->l -= 2;
            break;

        case 2:

            tab[posi->l][posi->c - 1] = middle;
            tab[posi->l][posi->c - 2] = -1;
            posi->c -= 2;
            break;

        case 3:

            tab[posi->l + 1][posi->c] = middle;
            tab[posi->l + 2][posi->c] = -1;
            posi->l += 2;
            break;
        
        default:

            break;
    }
}

void pegSolitaire (int** tab, int lin, int col, int pieces, int holes) {
    
    int ok, middle, count, check, flag;/* index; path;*/
    stack *hist;          /*"hist" vem de "history" e "prt" de "print"*/
    pos *crt, *aux;       /*"crt" vem de "current"*/

    if (pieces < holes) {
        printf("Impossivel\n");
        return;
    }

    crt = malloc(sizeof(pos));
    aux = malloc(sizeof(pos));

    hist = createStack(3*lin*col); /*lin*col é o tamanho máximo de posimentos*/
                                   /*que podem ser empilhados.*/
    
    flag = 0;
    while (holes < pieces) {
        crt->l = 0;
        check = 0;

        while (crt->l < lin && check == 0) {
            crt->c = 0;
            
            while(crt->c < col && check == 0) {

                if (crt->l == lin - 1 && crt->c == col - 1) {
                    flag = 1;
                }

                if(tab[crt->l][crt->c] == -1 || flag == 1) {
                    ok = 0;
                
                    while (crt->m < 4 && ok == 0 && tab[crt->l][crt->c] == -1) {
                        if (availablePos(tab, crt, lin, col)) ok = 1;
                        else crt->m += 1;
                    }

                    if (ok == 1) {

                        aux = copyPos(crt, aux);
                        middle = -1;
                        holes++;

                        MovePiece(tab, aux, middle);
                        printf("Ida: %d ", holes);
                        printPos(aux);
                        add(aux, hist);
                        
                        crt->m = 0;
                        check = 1;
                        count++;
                    }

                    /*backtracking*/
                    else if (ok == 0 && flag == 1) {

                        if(emptyStack(hist) == 1) {
                            printf("Impossível\n");
                            destroyStack(hist);
                            return;
                        }
                        crt = pop(hist);
                        middle = 1;

                        holes--;
                        MovePiece(tab, crt, middle);
                        printf("Volta: %d ", holes);
                        
                        crt->m++;
                        printPos(crt);
                        count++;
                        flag = 0;
                    }

                    else {
                        crt->m = 0;
                        crt->c += 1;
                    }
                }
                else {
                    crt->c += 1;
                }
            }
            crt->l += 1;
        }
    }
    printf("Saída da função\n");
    printMatrix(tab, lin, col);
    return;
}

int main () {
    int lin, col, pieces, holes, *p, *h,**tab, **tab_f;
    pieces = 0;
    holes = 0;
    p = &pieces;
    h = &holes;

    if (scanf("%d", &lin) != 1) printf("De porra\n");
    if (scanf("%d", &col) != 1) printf("De carai\n");
    
    tab = createMatrix(lin, col);
    tab_f = createMatrix(lin, col);
    
    readMatrix(tab, lin, col);    
    tab_f = finalMatrix(tab, tab_f, lin, col, p, h);

    printf("Entrada\n");
    printMatrix(tab, lin, col);

    pegSolitaire(tab, lin, col, pieces, holes);

    printf("Saída Ideal\n");
    printMatrix(tab_f, lin, col);
    
    destroyMatrix(tab, lin);
    destroyMatrix(tab_f, lin);
    return 0;
}