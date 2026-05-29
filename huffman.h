#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

typedef struct no
{
    unsigned char caractere;
    long long frequencia;
    struct no *esq;
    struct no *dir;
} No;

No *criaNoFolha(unsigned char caractere, long long freq);
No *criaNoInterno(No *esq, No *dir);
No *criaArvoreHuffman(long long *frequencias);
int comparar(No *pai, No *filho);
void liberarArvore(No *raiz);
void construirHeap(Heap *h, long long *frequencias);
void imprimirTabelaFrequencias(long long *frequencias);
void imprimirArvoreHuffman(No *raiz, int nivel, int caminhos[]);
void contarFrequencia(const char *arquivo, long long *tamanho);
void gerarCodigosHuffman(No *raiz, char codigos[256][256], char *caminho, int nivel);
void compactar(const char *arquivoEntrada, const char *arquivoSaida, char codigos[256][256], long long *frequencias);
void descompactar(const char *arquivoEntrada, const char *arquivoSaida);

#endif