#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

// typedef struct no {
//     unsigned char caractere;
//     int frequencia;
//     struct no *esq;
//     struct no *dir;
// } No;

No *criaNoFolha(unsigned char caractere, int freq);
No *criaNoInterno(No *esq, No *dir);
void contarFrequencia(const char *arquivo, long long *tamanho);
void imprimirTabelaFrequencias(long long *frequencias);
No *criaArvoreHuffman(long long *frequencias);
void construirHeap(Heap *h, long long *frequencias);

// --- FUNÇÕES A IMPLEMENTAR --- 
// Imprimir arvore de huffman
// Imprimir tabela de frequencias 
// Construir a arvore de huffman
// Gerar codigos de huffman
// Compactar o arquivo 
// Descompactar o arquivo 
// (DEVE HAVER UM CABEÇALHO NO ARQUIVO COMPACTAR PARA QUE SEJA POSSÍVEL RECONSTRUIR A ÁRVORE DE HUFFMAN)

#endif