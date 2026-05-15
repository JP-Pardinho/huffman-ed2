#include "huffman.h"

No *criaNo(unsigned int freq, No *esq, No *dir)
{
    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL)
    {
        printf("\nNão foi possível aloccar o novo Nó!\n");
        exit(1);
    }

    novo->caractere = '#';
    novo->frequencia = freq;
    novo->esq = esq;
    novo->dir = dir;
    return novo;
}

unsigned int contafrequencia() {}

void *Huffman(char caracteres)
{
    int i, n;
    No x, y;

    n = strlen(caracteres);
    char auxCaracteres = caracteres;

    for (i = 0; i < n; i++)
    {
    }
}