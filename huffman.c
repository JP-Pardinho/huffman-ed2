#include "huffman.h"

No *criaNoFolha(unsigned char caractere, int freq) {
    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL) {
        printf("\nNão foi possível aloccar o novo Nó!\n");
        exit(1);
    }

    novo->caractere = caractere;
    novo->frequencia = freq;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

No *criaNoInterno(No *esq, No *dir) {
    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL) {
        printf("\nNão foi possível aloccar o novo Nó!\n");
        exit(1);
    }

    novo->caractere = '#';
    novo->frequencia = esq->frequencia + dir->frequencia;
    novo->esq = esq;
    novo->dir = dir;
    return novo;
}

void contaFrequencia(const char *arquivo, long long *tabelaFreq) {
    long long vetor[256] = {0};
    
    FILE *file = fopen(arquivo, "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    int aux;
    while ((aux = fgetc(file)) != EOF) {
        vetor[(unsigned char)aux]++;
    }
    fclose(file);

    for (int i = 0; i < 256; i++) {
        tabelaFreq[i] = vetor[i];
    }
}

int *comparar(No *pai, No *filho) {
    if (filho->frequencia < pai->frequencia)
        return 1;
    else 
        return 0;
}
 
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