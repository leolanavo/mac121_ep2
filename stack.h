/*Este arquivo contém as funções de pilhas*/
#include "types.h"

#ifndef STACK_H
#define STACK_H

/*Cria uma pilha nova*/
stack* createStack (int size);

/*Empila uma pos*/
void add (pos* num, stack* p);

/*Desempilha uma pos*/
pos* pop (stack* p);

/*Verifica se a pilha está vazia*/
int emptyStack (stack* p);

/*Destrói a pilha*/
void destroyStack (stack* p);

#endif