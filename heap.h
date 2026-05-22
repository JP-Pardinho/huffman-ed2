#ifndef HEAP_H
#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

typedef struct heap 
{
    void **dados;
    int tamanho;
    int capacidade;
} Heap;

Heap *criaHeap(Heap *h, int capacidade);
void insereHeap(Heap *h, void *dado);


/* 
void destroiHeap(Heap *h);
void insereHeap(Heap *h, void *item);
void extraiMinimo(Heap *h);
void heapFy(Heap *h, int indice);
*/

#endif
