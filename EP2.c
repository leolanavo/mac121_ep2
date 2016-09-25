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

            if (tab[crt->l][crt->c + 1] == 1 && tab[crt->l][crt->c + 2] == 1)
                return 1;

            break;

        case 1:

            if (crt->l - 2 < 0) break;

            if (tab[crt->l - 1][crt->c] == 1 && tab[crt->l - 2][crt->c] == 1)
                return 1;

            break;

        case 2:

            if (crt->c - 2 < 0) break;

            if (tab[crt->l][crt->c - 1] == 1 && tab[crt->l][crt->c - 2] == 1)
                return 1;

            break;

        case 3:

            if (crt->l + 2 >= lin) break;

            if (tab[crt->l + 1][crt->c] == 1 && tab[crt->l + 2][crt->c] == 1)
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

void pegSolitaire (int** tab, int lin, int col, int pieces, int holes, int** tab_f ) {
    
    int ok, middle, mov, bck, eql, count;
    stack *hist;          
    pos *crt, *aux;       

    if (pieces < holes) {
        printf("Impossivel\n");
        return;
    }

    crt = malloc(sizeof(pos));
    aux = malloc(sizeof(pos));

    hist = createStack(3*lin*col);

    bck = 0;
    eql = 0;
    count = 0;

    while(cmpMatrix(tab, tab_f, lin, col) == 0) {
        printf("Lúcifer\n");
        if (holes == pieces) eql = 1;
        
        if (holes != pieces) {
            
            mov = 0;

            if (bck == 0) crt->l = 0;

            while (crt->l < lin) {
                printf("Príncipe das Trevas\n");
                if (bck == 0) crt->c = 0;

                while (crt->c < col) {
                    printf("Lorde Satã\n");
                    if(tab[crt->l][crt->c] == -1 || bck == 1) {
                        bck = 0;
                        ok = 0;
                    
                        while(crt->m < 4 && ok == 0) {
                            printf("Pata Rachada\n");
                            if (availablePos(tab, crt, lin, col)) ok = 1;
                            else crt->m++;
                        }

                        if (ok == 1) {
                            aux = copyPos(crt, aux);
                            middle = -1;
                            holes++;
                            mov = 1;
                            crt->c++;
                            count++;
                            
                            MovePiece(tab, aux, middle);
                            add(aux, hist);
                            crt->m = 0;
                        }
                        else {
                            crt->c++;
                            crt->m = 0;
                            count++;
                        }
                    }
                    else {
                        crt->c++;
                        crt->m = 0;
                        count++;
                    }
                }
                crt->l++;
            }
        }

        if (mov == 0 || eql == 1) {
            if(emptyStack(hist) == 1) {
                printf("Impossível\n");
                destroyStack(hist);
                return;
            }
            
            eql = 0;
            crt = pop(hist);
            middle = 1;
            holes--;
            bck = 1;
            count++;

            MovePiece(tab, crt, middle);
            if (crt->m == 0 || crt->m == 3)
                crt->l = crt->c = crt->m = 0;
            else crt->m++;
        } 
    }
    destroyStack(hist);

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

    pegSolitaire(tab, lin, col, pieces, holes, tab_f);

    printf("Saída da função\n");
    printMatrix(tab, lin, col);

    printf("Saída Ideal\n");
    printMatrix(tab_f, lin, col);
    
    destroyMatrix(tab, lin);
    destroyMatrix(tab_f, lin);
    return 0;
}