#include <stdlib.h>
#include "types.h"

/*Cria uma pilha nova*/
stack* createStack (int size) {
    stack *p;
    
    p = malloc(sizeof(stack));
    p->size = size;
    p->data = malloc(size * sizeof(pos));
    p->top = 0;

    return (p);
}

/*Empila um posimento*/
void add (pos* num, stack* p) {
    p->data[p->top] = num;
    p->top++;
}

/*Desempilha um inteiro*/
pos* pop (stack* p) {
    p->top--;
    return (p->data[p->top]);
}

/*Verifica se a pilha está vazia*/
int emptyStack (stack* p) {
    return (p->top == 0);
}

/*Devolve qual elemento está no topo da pilha*/
pos* getTop (stack* p) {
    return (p->data[p->top - 1]);
}

/*Destrói a pilha*/
void destroyStack (stack* p) {
    free(p->data);
    p->data = NULL;
    p->size = 0;
    p->top = 0;
}