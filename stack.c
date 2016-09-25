#include <stdio.h>
#include <stdlib.h>
#include "types.h"

/*Cria uma pilha nova*/
stack* createStack (int size) {
    stack *p;
    
    p = malloc(sizeof(stack));
    p->size = size;
    p->data = malloc(size * sizeof(int));
    p->top = 0;

    return (p);
}

/*Empila um posimento*/
void add (pos* posi, stack* p) {
    
    p->data[p->top] = posi->l;
    p->data[p->top + 1] = posi->c;
    p->data[p->top + 2] = posi->m;
    
    p->top += 3;
}

/*Desempilha um inteiro*/
pos* pop (stack* p) {
    pos* posi;
    
    posi = malloc(sizeof(posi));

    posi->m = p->data[p->top - 1];
    posi->c = p->data[p->top - 2];
    posi->l = p->data[p->top - 3];
    
    p->top -= 3;
    return (posi);
}

/*Verifica se a pilha está vazia*/
int emptyStack (stack* p) {
    return (p->top == 0);
}

/*Destrói a pilha*/
void destroyStack (stack* p) {
    free(p->data);
    p->data = NULL;
    p->size = 0;
    p->top = 0;
}