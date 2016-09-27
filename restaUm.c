/*Nome: Leonardo Lana Violin Oliveira
Nº USP: 9793735*/

#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "stack.h"
#include "matrix.h"

/*A função recebe o tabuleiro, e uma matriz na qual armazenará o tabuleiro
final, as dimensões dessas matrizes e dois ponteiros para contar o número de
buracos e peças que há no tabuleiro origiginal.
Retorna o tabuleiro final.*/
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

/*Recebe duas structs pos, acha o posição de origem da peça apartir do movimento
armazenado na primeira struct pos. Retorna a primeira pos com a coordenada
de origem da peça.*/
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

/*Recebe uma pilha de movimentos e imprime eles na ordem correta com devida
formatação e calcula a posição de origem usando a originPos.*/
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

/*Recebe o tabuleiro, uma pos e as dimensões do tabuleiro. Retorna o 1, se o
movimento a partir da coordenada fornecida pela pos é válido, 0 se não.*/
int availablePos (int** tab, pos* posi, int lin, int col) {

    switch (posi->m) {
        case 0:
            /*Cada case tem seu if para evitar segmentation fault.*/
            if (posi->c + 2 >= col) break;

            if (tab[posi->l][posi->c + 1] == 1 && tab[posi->l][posi->c + 2] == -1)
                return 1;

            break;

        case 1:

            if (posi->l - 2 < 0) break;

            if (tab[posi->l - 1][posi->c] == 1 && tab[posi->l - 2][posi->c] == -1)
                return 1;

            break;

        case 2:

            if (posi->c - 2 < 0) break;

            if (tab[posi->l][posi->c - 1] == 1 && tab[posi->l][posi->c - 2] == -1)
                return 1;

            break;

        case 3:

            if (posi->l + 2 >= lin) break;

            if (tab[posi->l + 1][posi->c] == 1 && tab[posi->l + 2][posi->c] == -1)
                return 1;
            
            break;

        default:
            
            break;
    }

    return 0;
}

/*Recebe o tabuleiro, uma pos, e uma flag. Movimenta a peça de acordo com a
flag e o movimento da pos. Altera a coordenada da pos, para pos ter a coordenada
da peça após o movimento.*/
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

/*Recebe o tabuleiro, suas dimensões, o número de peças, buracos e o tabuleiro
final. Simula o jogo, se for possível imprime a sequência de passos usando a
função printPath, se não imprime "Impossivel"*/
void pegSolitaire (int** tab, int lin, int col, int pieces, int holes, int** tab_f) {
    
    int ok, middle, back, equal, end;
    stack *hist;     /*"hist" vem de "history"*/
    pos *crt;        /*"crt" vem de "current"*/

    /*Se há mais buracos que peças, então é impossível*/
    if (pieces < holes) {
        printf("Impossivel\n");
        return;
    }

    crt = malloc(sizeof(pos));

    hist = createStack(3*(pieces-holes));

    back = 0;  /*Flag para saber se ocorreu ou não backtracking*/
    equal = 0; /*Flag para pieces == holes e tab_f é diferente de tab.*/
    end = 0;   /*Flag de final de loop, é acesa quando as matrizes tab e tab_f
               são iguais.*/

    /*Laço enquanto as matrizes forem diferentes*/
    while(end == 0) {

        /*Zera, se não precisa começar a analisar da posição forcecida
        pelo backtracking*/
        if (back == 0) crt->l = 0;

        /*Laço para varrer as linhas da matriz*/
        for (;crt->l < lin; crt->l++) {

            if (back == 0) crt->c = 0;

            /*Laço para varrer as colunas da matriz*/
            for (;crt->c < col; crt->c++) {
                
                if (back == 0) crt->m = 0;

                if (holes == pieces) {  
                    if (cmpMatrix(tab, tab_f, lin, col)) end = 1;
                    equal = 1;
                }

                /*Rastreia peças, ignorando buracos e lugares inválidos.
                Se holes == pieces, naõ entra nesse if, isso evita que faça 
                movimentos desnecessários.*/
                if(tab[crt->l][crt->c] == 1 && equal == 0) {

                    back = 0; /*Zera a flag do backtracking*/
                    ok = 0;   /*Flag para movimento válido*/

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
                printf("Impossivel\n");
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
            equal = 0;

            /*Acende a flag do backtracking*/
            back = 1;

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
    
    /*Lê uma matriz da entrada padrão*/
    readMatrix(tab, lin, col);

    /*A tab_f é o resultado esperado após o final da simulação.*/
    tab_f = finalMatrix(tab, tab_f, lin, col, p, h);

    pegSolitaire(tab, lin, col, pieces, holes, tab_f);
    
    destroyMatrix(tab, lin);
    destroyMatrix(tab_f, lin);
    return 0;
}