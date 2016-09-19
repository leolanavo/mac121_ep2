#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int size;
    int top;
    int *data;
} pile;

pile* newPile (int size) {
    pile *p;
    
    p = malloc(sizeof(pile));
    p->size = size;
    p->data = malloc(size, sizeof(int));
    p->top = 0;

    return (p);
}

void add (char num, pile* p) {
    p->data[p->top] = num;
    p->top++;
}

char pop (pile* p) {
    p->top--;
    return (p->data[p->top]);
}

int emptyPile (pile* p) {
    return p->top == 0;
}

int main () {
	return 0;
}