#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>

typedef struct heap {
    void **dados;
    int tamanho;
    int capacidade;
} Heap;

typedef struct no {
    unsigned char caractere;
    long long frequencia;
    struct no *esq;
    struct no *dir;
} No;

Heap *criaHeap(int capacidade);
void insereHeap(Heap *h, void *dado);
void *extraiMinimo(Heap *h);

void corrigeSubindo(Heap *h, int i);
void corrigeDescendo(Heap *h, int i);
void troca(void **a, void **b);
int comparar(No *pai, No *filho);
void liberaHeap(Heap *h);

#endif
