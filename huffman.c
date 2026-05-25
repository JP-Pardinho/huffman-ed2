#include "huffman.h"


No *criaNoFolha(unsigned char caractere, long long freq) {
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

void contarFrequencia(const char *arquivo, long long *tabelaFreq) {
    long long vetor[256] = {0};
    
    FILE *file = fopen(arquivo, "r");
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
 
No *criaArvoreHuffman(long long *frequencias) {
    Heap *h = criaHeap(256);
    construirHeap(h, frequencias);

    if (h->tamanho == 1) {
        No *folha = extraiMinimo(h);
        No *raiz = criaNoInterno(folha, NULL);
        liberaHeap(h);
        return raiz;
    }

    while (h->tamanho > 1) {
        No *x = extraiMinimo(h);
        No *y = extraiMinimo(h);
        No *z = criaNoInterno(x, y);
        insereHeap(h, z);
    }

    No *raiz = extraiMinimo(h);
    liberaHeap(h);
    return raiz;
}

void imprimirTabelaFrequencias(long long *frequencias) {
    printf("Tabela de Frequências:\n");
    for (int i = 0; i < 256; i++) {
        if (frequencias[i] > 0) {
            printf("Caractere: '%c' (ASCII: %d) - Frequência: %lld\n", i, i, frequencias[i]);
        }
    }
}

void imprimirArvoreHuffman(No *raiz, int nivel) {
    if (raiz == NULL) {
        return;
    }

    imprimirArvoreHuffman(raiz->esq, nivel + 1);
    
    for (int i = 0; i < nivel; i++) {
        printf("  ");
    }
    if (raiz->caractere != '#') {
        printf("Caractere: '%c' (ASCII: %d) - Frequência: %lld\n", raiz->caractere, raiz->caractere, raiz->frequencia);
    } else {
        printf("Nó Interno - Frequência: %lld\n", raiz->frequencia);
    }
    
    imprimirArvoreHuffman(raiz->dir, nivel + 1);
}

void construirHeap(Heap *h, long long *frequencias) {
    for (int i = 0; i < 256; i++) {
        if (frequencias[i] > 0) {
            No *novoNo = criaNoFolha((unsigned char)i, frequencias[i]);
            insereHeap(h, novoNo);
        }
    }
}


// ...existing code...

// void imprimirArvoreHuffman(No *raiz, int nivel) {
//     if (raiz == NULL) {
//         return;
//     }

//     // Imprime filho direito primeiro (para visualizar melhor)
//     imprimirArvoreHuffman(raiz->dir, nivel + 1);
    
//     // Indenta baseado no nível
//     for (int i = 0; i < nivel; i++) {
//         printf("    ");
//     }
    
//     // Imprime o nó
//     if (raiz->caractere == '#') {
//         // Nó interno - mostra só a frequência
//         printf("(%lld)\n", raiz->frequencia);
//     } else {
//         // Nó folha - mostra caractere e frequência
//         if (raiz->caractere == '\n')
//             printf("\\n (%lld)\n", raiz->frequencia);
//         else if (raiz->caractere == '\t')
//             printf("\\t (%lld)\n", raiz->frequencia);
//         else if (raiz->caractere == ' ')
//             printf("ESP (%lld)\n", raiz->frequencia);
//         else
//             printf("%c (%lld)\n", raiz->caractere, raiz->frequencia);
//     }
    
//     // Imprime filho esquerdo depois
//     imprimirArvoreHuffman(raiz->esq, nivel + 1);
// }

void liberarArvore(No *raiz) {
    if (raiz == NULL)
        return;
    
    liberarArvore(raiz->esq);
    liberarArvore(raiz->dir);
    free(raiz);
}