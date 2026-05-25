#include "heap.h"

Heap *criaHeap(int capacidade) {
    Heap *h = (Heap *)malloc(sizeof(Heap));

    if (h == NULL) {
        printf("Erro ao criar heap.\n");
        exit(1);
    }

    h->dados = (void **)malloc(capacidade * sizeof(void *));

    if (h->dados == NULL) {
        printf("Erro ao criar o vetor void\n");
        free(h);
        exit(1);
    }

    h->tamanho = 0;
    h->capacidade = capacidade;
    return h;
}

void insereHeap(Heap *h, void *dado) {
    if (h == NULL) {
        return;
    }

    if (h->tamanho >= h->capacidade) {
        printf("Heap cheio!\n");
        return;
    }

    h->dados[h->tamanho] = dado;
    h->tamanho++;
    corrigeSubindo(h, h->tamanho - 1);
}

void *extraiMinimo(Heap *h) {
    if (h == NULL || h->tamanho == 0) 
        return NULL;

    void *raiz = h->dados[0];
    h->dados[0] = h->dados[h->tamanho - 1];
    h->tamanho--;
    corrigeDescendo(h, 0);
    return raiz;
}

void liberaHeap(Heap *h) {
    if (h != NULL) {
        free(h->dados);
        free(h);
    }
}

void troca(void **a, void **b) {
    void *aux = *a;
    *a = *b;
    *b = aux;
}

void corrigeDescendo(Heap *h, int i) {
    int menor = i;
    int esq = 2*i + 1;
    int dir = 2*i + 2;

    if (esq < h->tamanho && comparar(h->dados[menor], h->dados[esq]))
        menor = esq;
    
    if (dir < h->tamanho && comparar(h->dados[menor], h->dados[dir]))
        menor = dir;

    if (menor != i) {
        troca(&h->dados[i], &h->dados[menor]);
        corrigeDescendo(h, menor);
    }
}

void corrigeSubindo(Heap *h, int i) {
    int pai = (i - 1) / 2;

    if (i > 0 && h->dados[i] != NULL && comparar(h->dados[pai], h->dados[i])) {
        troca(&h->dados[i], &h->dados[pai]);
        corrigeSubindo(h, pai);
    }
}

int comparar(No *pai, No *filho) {
    if (filho->frequencia < pai->frequencia)
        return 1;
    else 
        return 0;
} 