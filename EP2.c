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
void copyPos (pos* posi1, pos* posi2) {
    posi2->l = posi1->l;
    posi2->c = posi1->c;
    posi2->m = posi1->m;
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
    
    int ok, middle, mov, bck, eql;
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

    /*Laço enquanto as matrizes forem diferentes*/
    while(cmpMatrix(tab, tab_f, lin, col) == 0) {

        /*Evita que a função faça mais movimentos que o necessário*/
        if (holes == pieces) eql = 1;
        
        if (holes != pieces) {
            
            mov = 0; /*Flag para saber se ocorreu algum movimento*/

            if (bck == 0) crt->l = 0;

            /*Laço para varrer as linhas da matriz*/
            for (;crt->l < lin; crt->l++) {
                if (bck == 0) crt->c = 0;

                /*Laço para varrer as colunas da matriz*/
                for (;crt->c < col; crt->c++) {
                    
                    /*Rastreia buracos e ignora peças e lugares inválidos*/
                    if(tab[crt->l][crt->c] == -1) {
                        
                        bck = 0; /*Zera a flag do backtracking*/
                        
                        ok = 0; /*Flag para movimento válido*/
                        
                        /*Checa se um dos 4 movimentos é válido*/
                        while(crt->m < 4 && ok == 0) {
                            if (availablePos(tab, crt, lin, col)) ok = 1;
                            else crt->m++;
                        }

                        /*Se um movimento é válido, ele move as peças e continua
                        percorrendo a matriz.*/
                        if (ok == 1) {
                            
                            /*Flag para a função MovePiece. Faz um movimento
                            normalmente*/
                            middle = -1;
                            
                            holes++;

                            /*Reinicia o laço de leitura de matriz*/
                            mov = 1;
                            
                            MovePiece(tab, crt, middle);

                            /*Empilha a struct, com a posição final, após o
                            movimento.*/
                            add(crt, hist);

                            crt->l = crt->c = -1;

                            /*O próximo buraco tem que começar a ser avaliada, 
                            a partir do movimento 0.*/
                            crt->m = 0;
                        }
                        
                        else {
                            crt->m = 0;
                        }
                    }
                    else {
                        crt->m = 0;
                    }
                }
            }
        }

        /*Backtrcking*/
        /*mov == 0, terminou de varrer a matriz e não fez nenhum movimento*/
        /*eql == 1, holes == pieces, mas a matriz é diferente da matriz final*/
        if (mov == 0 || eql == 1) {
            

            if(emptyStack(hist) == 1) {
                printf("Impossível\n");
                destroyStack(hist);
                return;
            }
            
            eql = 0;

            /*Desempilha*/
            free(crt);
            crt = pop(hist);
            
            /*middle == 1, para desfazer um movimento na MovePiece*/
            middle = 1;
            holes--;

            /*Acende a flag para o backtracking*/
            bck = 1;

            /*Desfaz o movimento desempilhado*/
            MovePiece(tab, crt, middle);

            /*Analisa a posição desempilhada a partir do próximo movimento*/
            crt->m++;
        } 
    }

    free(crt);
    free(aux);
    crt = NULL;
    aux = NULL;
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