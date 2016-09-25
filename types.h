/*Este arquivo contém as structs usadas nos outros arquivos do ep.*/

#ifndef TYPES_H
#define TYPES_H

/*Struct de movimentos*/
typedef struct {
    short int l, c, m;
} pos;

/*Struct de pilha*/
typedef struct {
    int size, top;
    short int *data;
} stack;

#endif