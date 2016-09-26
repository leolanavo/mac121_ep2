#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "stack.h"
#include "matrix.h"

/*Gera o tabuleiro final, e enquanto isso acha quantas peças e buracos há*/
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

/*Rastreia a origem de uma posição*/
pos originPos (pos posi1, pos posi2) {
    
    switch (posi1.m) {
        case 0:
            posi2.l = posi1.l;
            posi2.c = posi1.c - 2;
            break;

        case 1:
            posi2.c = posi1.c;
            posi2.l = posi1.l + 2;
            break;

        case 2:
            posi2.l = posi1.l;
            posi2.c = posi1.c + 2;
            break;

        case 3:
            posi2.c = posi1.c;
            posi2.l = posi1.l - 2;
            break;

        default:
            break;
    }

    return (posi2);
}

/*Imprime os movimentos das peças*/
void printPath (stack* p) {
    int i;
    pos final, origin;

    for (i = 0; i < p->top; i += 3) {
        final.l = p->data[i];
        final.c = p->data[i + 1];
        final.m = p->data[i + 2];
        origin = originPos(final, origin);
        printf("%d:%d-%d:%d\n", origin.l, origin.c, final.l, final.c);
    }
}

/*Checa se o movimento da peça pode ser executado.*/
int availablePos (int** tab, pos* crt, int lin, int col) {

    switch (crt->m) {
        case 0:
            /*Cada case tem seu if para evitar segmentation fault.*/
            if (crt->c + 2 >= col) break;

            if (tab[crt->l][crt->c + 1] == 1 && tab[crt->l][crt->c + 2] == -1)
                return 1;

            break;

        case 1:

            if (crt->l - 2 < 0) break;

            if (tab[crt->l - 1][crt->c] == 1 && tab[crt->l - 2][crt->c] == -1)
                return 1;

            break;

        case 2:

            if (crt->c - 2 < 0) break;

            if (tab[crt->l][crt->c - 1] == 1 && tab[crt->l][crt->c - 2] == -1)
                return 1;

            break;

        case 3:

            if (crt->l + 2 >= lin) break;

            if (tab[crt->l + 1][crt->c] == 1 && tab[crt->l + 2][crt->c] == -1)
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
    
    tab[posi->l][posi->c] = -1;

    /*middle == 1, significa que o programa irá reverter um movimento*/
    if (middle == 1) mov = (posi->m + 2)%4;
    else mov = posi->m;

    switch (mov) {
        case 0:

            tab[posi->l][posi->c + 1] = middle;
            tab[posi->l][posi->c + 2] = 1;
            posi->c += 2;
            break;

        case 1:

            tab[posi->l - 1][posi->c] = middle;
            tab[posi->l - 2][posi->c] = 1;
            posi->l -= 2;
            break;

        case 2:

            tab[posi->l][posi->c - 1] = middle;
            tab[posi->l][posi->c - 2] = 1;
            posi->c -= 2;
            break;

        case 3:

            tab[posi->l + 1][posi->c] = middle;
            tab[posi->l + 2][posi->c] = 1;
            posi->l += 2;
            break;
        
        default:

            break;
    }
}

/*Simula o jogo para as configurações dadas*/
void pegSolitaire (int** tab, int lin, int col, int pieces, int holes, int** tab_f ) {
    
    int ok, middle, bck, eql, end;
    stack *hist;     /*"hist" vêm de "history"*/
    pos *crt;        /*"crt" vêm de "current"*/

    /*Se há mais buracos que peças, então é impossível*/
    if (pieces < holes) {
        printf("Impossivel\n");
        return;
    }

    crt = malloc(sizeof(pos));

    hist = createStack(3*lin*col);

    bck = 0;
    eql = 0; /*Flag para pieces == holes, para tab_f é diferente de tab.*/
    end = 0; /*Flag de final de loop, é acesa quando as matrizes tab e tab_f
               são iguais.*/

    /*Laço enquanto as matrizes forem diferentes*/
    while(end == 0) {

        /*Zera, se não precisa começar a analisar da posição forcecida
        pelo backtracking*/
        if (bck == 0) crt->l = 0;

        /*Laço para varrer as linhas da matriz*/
        for (;crt->l < lin && end == 0; crt->l++) {

            if (bck == 0) crt->c = 0;

            /*Laço para varrer as colunas da matriz*/
            for (;crt->c < col && end == 0; crt->c++) {
                
                if (bck == 0) crt->m = 0;

                if (holes == pieces) {
                    if (cmpMatrix(tab, tab_f, lin, col)) end = 1;
                    eql = 1;
                }

                /*Rastreia peças, ignorando buracos e lugares inválidos.
                Se holes == pieces, evita que faça movimentos desnecessários.*/
                if(tab[crt->l][crt->c] == 1 && eql == 0 && end == 0) {

                    bck = 0; /*Zera a flag do backtracking*/
                    ok = 0;  /*Flag para movimento válido*/

                    /*Checa se um dos 4 movimentos é válido*/
                    while(crt->m < 4 && ok == 0) {
                        if (availablePos(tab, crt, lin, col)) ok = 1;
                        else crt->m++;
                    }

                    /*Se um movimento é válido, ele move as peças e começa a
                    percorrer a matriz novamente.*/
                    if (ok == 1) {

                        /*Flag para a função MovePiece. Faz um movimento
                        normalmente*/
                        middle = -1;

                        holes++;

                        MovePiece(tab, crt, middle);

                        /*Empilha a struct, com a posição final, após o
                         movimento e o movimento feito.*/
                        add(crt, hist);

                        /*Reinicia a leitura da matriz.*/
                        crt->l = 0;
                        crt->c = -1;

                        /*O próximo buraco tem que começar a ser avaliado 
                        a partir do movimento 0.*/
                        crt->m = 0;
                    }
                }
            }
        }

        /*Cai no backtracking, caso não consiga fazer nenhum movimento
        após varrer a matriz toda.*/
        if (end == 0) {
            /*Backtrcking*/
            if(emptyStack(hist) == 1) {
                printf("Impossível\n");
                destroyStack(hist);
                free(crt);
                return;
            }

            free(crt);
            crt = pop(hist);
            
            /*middle == 1, para desfazer um movimento na MovePiece*/
            middle = 1;
            holes--;

            /*Reinicia a flag eql, pois se chegou aqui, pieces == holes, porém
            as matrizes são diferentes.*/
            eql = 0;

            /*Acende a flag do backtracking*/
            bck = 1;

            /*Desfaz o movimento desempilhado*/
            MovePiece(tab, crt, middle);

            /*Analisa a posição desempilhada a partir do próximo movimento*/
            crt->m++;
        }
    }

    printPath(hist);
    free(crt);
    crt = NULL;
    destroyStack(hist);
    return;
}

int main () {
    int lin, col, pieces, holes, *p, *h,**tab, **tab_f;
    pieces = 0;
    holes = 0;
    p = &pieces;
    h = &holes;

    scanf("%d", &lin);
    scanf("%d", &col);
    
    tab = createMatrix(lin, col);
    tab_f = createMatrix(lin, col);
    
    readMatrix(tab, lin, col);

    /*A tab_f é o resultado esperado após o final da simulação.*/
    tab_f = finalMatrix(tab, tab_f, lin, col, p, h);

    pegSolitaire(tab, lin, col, pieces, holes, tab_f);
    
    destroyMatrix(tab, lin);
    destroyMatrix(tab_f, lin);
    return 0;
}