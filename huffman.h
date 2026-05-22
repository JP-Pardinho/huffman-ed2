#ifndef HUFFMAN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct no
{
    unsigned char caractere;
    int frequencia;
    struct no *esq;
    struct no *dir;
} No;

No *criaNo(unsigned char caractere, int frequencia);
No *criaNoInterno(No *esq, No *dir);
int contarFrequencia(const char *arquivo, long long *tamanho);
int comparar(No *raiz, No *novo);

// --- FUNÇÕES A IMPLEMENTAR --- 
// Imprimir arvore de huffman
// Imprimir tabela de frequencias 
// Construir a arvore de huffman
// Gerar codigos de huffman
// Compactar o arquivo 
// Descompactar o arquivo 
// (DEVE HAVER UM CABEÇALHO NO ARQUIVO COMPACTAR PARA QUE SEJA POSSÍVEL RECONSTRUIR A ÁRVORE DE HUFFMAN)

#endif