#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>

typedef struct no No;

typedef struct heap {
    void **dados;
    int tamanho;
    int capacidade;
} Heap;


Heap *criaHeap(int capacidade);
void insereHeap(Heap *h, void *dado);
void *extraiMinimo(Heap *h);
void corrigeSubindo(Heap *h, int i);
void corrigeDescendo(Heap *h, int i);
void troca(void **a, void **b);
void liberaHeap(Heap *h);
void imprimirArvoreHuffman(No *raiz, int nivel, int caminhos[]);

#endif
