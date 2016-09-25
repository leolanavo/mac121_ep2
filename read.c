#include <stdio.h>
#include <stdlib.h>

/*Struct usada para falicilitar o uso de posições na matriz*/
typedef struct {
    int l, c;
} pos;

typedef struct {
    int size;
    int top;
    short int *data; /*Vai receber números de 0 a 3, então short int*/
} stack;             /*é suficiente*/

/*Cria uma pilha nova*/
stack* createStack (int size) {
    stack *p;
    
    p = malloc(sizeof(stack));
    p->size = size;
    p->data = malloc(size * sizeof(short int));
    p->top = 0;

    return (p);
}

/*Empila um inteiro*/
void add (int num, stack* p) {
    p->data[p->top] = num;
    p->top++;
}

/*Desempilha um inteiro*/
int pop (stack* p) {
    p->top--;
    return (p->data[p->top]);
}

/*Verifica se a pilha está vazia*/
int emptyStack (stack* p) {
    return (p->top == 0);
}

/*Devolve qual elemento está no topo da pilha*/
int getTop (stack* p) {
    return (p->data[p->top - 1]);
}

/*Destrói a pilha*/
void destroyStack (stack* p) {
    free(p->data);
    p->data = NULL;
    p->size = 0;
    p->top = 0;
}

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
int availablePos (int** tab, pos* crt, int mov, int lin, int col) {

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
void movePiece (int** tab, pos* crt, int mov) {
    
    tab[crt.l][crt.c] = -1;

    switch (mov) {
        case 0:

            tab[crt->l][crt->c + 1] = -1;
            tab[crt->l][crt->c + 2] = 1;
            crt-> += 2;
            break;

        case 1:

            tab[crt->l - 1][crt->c] = -1;
            tab[crt->l - 2][crt->c] = 1;
            crt->l -= 2;
            break;

        case 2:

            tab[crt->l][crt->c - 1] = -1;
            tab[crt->l][crt->c - 2] = 1;
            crt->c -= 2;
            break;

        case 3:

            tab[crt->l + 1][crt->c] = -1;
            tab[crt->l + 2][crt->c] = 1;
            crt->l += 2;
            break;
    }
}

/*Imprime os movimentos*/
void printVector (int* v) {
    pos beg, end;
    printf("%d:%d-%d:%d\n", );
}

void pegSolitaire (int** tab, int lin, int col) {
    int ok, i, j, mov, index;
    stack *hist;    /*"hist" vem de "history" e "prt" de "print"*/
    pos* crt;       /*"crt" vem de "current"*/
    int *path;
    
    hist = createStack(lin*col); /*lin*col é o tamanho máximo de movimentos*/
                                 /*que podem ser empilhados.*/
    path = malloc(4*lin*col * sizeof(int)); /*Feito com a ciência de porra nenhuma*/

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
                    movePiece(tab, crt, mov);
                    add(mov, hist);
                }
                else { /*backtracking*/
                    if (emptyStack(hist)) {
                        destroyMatrix(tab, lin);
                        destroyStack(hist);
                        free(path);
                        printf("Impossivel\n");
                        return;
                    }
                    mov = pop(hist);
                    movePiece(tab, crt, (mov + 2)%4);
                    j--;
                }
            }
            j++;
        }
    }

    printfVector(path);
    destroyMatrix(tab, lin);
    destroyStack(hist);
    return;
}

int main () {
    int lin, col, **tab;

    scanf("%d %d", &lin, &col);
    tab = createMatrix(lin, col);
    readMatrix(matrix, lin, col);
    
    printMatrix(tab, lin, col);
    return 0;
}