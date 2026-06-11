#include "huffman.h"

No *criaNoFolha(unsigned char caractere, long long freq){
    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL){
        printf("\nNão foi possível aloccar o novo Nó!\n");
        exit(1);
    }

    novo->caractere = caractere;
    novo->frequencia = freq;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

No *criaNoInterno(No *esq, No *dir){
    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL){
        printf("\nNão foi possível aloccar o novo Nó!\n");
        exit(1);
    }

    novo->caractere = '\0';
    novo->frequencia = esq->frequencia + dir->frequencia;
    novo->esq = esq;
    novo->dir = dir;
    return novo;
}

int comparar(No *pai, No *filho) {
    if (filho->frequencia < pai->frequencia)
        return 1;
    else 
        return 0;
} 

void contarFrequencia(const char *arquivo, long long *tabelaFreq){
    long long vetor[256] = {0};

    FILE *file = fopen(arquivo, "r");
    if (file == NULL){
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    int aux;
    while ((aux = fgetc(file)) != EOF){
        vetor[(unsigned char)aux]++;
    }
    fclose(file);

    for (int i = 0; i < 256; i++){
        tabelaFreq[i] = vetor[i];
    }
}

No *criaArvoreHuffman(long long *frequencias){
    Heap *h = criaHeap(256);
    construirHeap(h, frequencias);

    if (h->tamanho == 1){
        No *folha = extraiMinimo(h);
        // Criar um nó interno com a folha à esquerda E um nó vazio à direita
        No *noBranco = criaNoFolha('\0', 0);  // Nó auxiliar vazio
        No *raiz = criaNoInterno(folha, noBranco);
        liberaHeap(h);
        return raiz;
    }

    while (h->tamanho > 1){
        No *x = extraiMinimo(h);
        No *y = extraiMinimo(h);
        No *z = criaNoInterno(x, y);
        insereHeap(h, z);
    }

    No *raiz = extraiMinimo(h);
    liberaHeap(h);
    return raiz;
}

void imprimirTabelaFrequencias(long long *frequencias){
    for (int i = 0; i < 256; i++){
        if (frequencias[i] > 0){
            printf("Caractere: '%c' - Frequência: %lld\n", i, frequencias[i]);
        }
    }
}

void imprimirArvoreHuffman(No *raiz, int nivel){
    if (raiz == NULL){
        return;
    }

    imprimirArvoreHuffman(raiz->esq, nivel + 1);

    for (int i = 0; i < nivel; i++){
        printf("  ");
    }
    if (raiz->caractere != '\0'){
        printf("(%c) | (%lld)\n", raiz->caractere, raiz->frequencia);
    }
    else{
        printf("(%lld)\n", raiz->frequencia);
    }

    imprimirArvoreHuffman(raiz->dir, nivel + 1);
}

void construirHeap(Heap *h, long long *frequencias){
    for (int i = 0; i < 256; i++){
        if (frequencias[i] > 0){
            No *novoNo = criaNoFolha((unsigned char)i, frequencias[i]);
            insereHeap(h, novoNo);
        }
    }
}

void liberarArvore(No *raiz){
    if (raiz == NULL)
        return;

    liberarArvore(raiz->esq);
    liberarArvore(raiz->dir);
    free(raiz);
}

void gerarCodigosHuffman(No *raiz, char codigos[256][256], char *caminho, int nivel){
    if (raiz == NULL)
        return;

    if (raiz->esq == NULL && raiz->dir == NULL){
        caminho[nivel] = '\0';
        strcpy(codigos[raiz->caractere], caminho);
        return;
    }

    caminho[nivel] = '0';
    gerarCodigosHuffman(raiz->esq, codigos, caminho, nivel + 1);

    caminho[nivel] = '1';
    gerarCodigosHuffman(raiz->dir, codigos, caminho, nivel + 1);
}

void compactar(const char *arquivoEntrada, const char *arquivoSaida, char codigos[256][256], long long *frequencias){
    
    FILE *entrada = fopen(arquivoEntrada, "rb");
    if (entrada == NULL){
        printf("Erro ao abrir arquivo\n");
        return;
    }

    FILE *saida = fopen(arquivoSaida, "wb");
    if (saida == NULL){
        printf("Erro ao criar arquivo de saída\n");
        fclose(entrada);
        return;
    }

    // Salvar cabeçalho (frequências)
    for (int i = 0; i < 256; i++){
        fwrite(&frequencias[i], sizeof(long long), 1, saida);
    }

    // Contar caracteres originais
    long long totalCaracteres = 0;
    for (int i = 0; i < 256; i++){
        totalCaracteres += frequencias[i];
    }
    fwrite(&totalCaracteres, sizeof(long long), 1, saida);  // Salva total de chars

    // Compactar arquivo
    int c;
    unsigned char byteAtual = 0;
    int bits = 0;
    long long caractereLido = 0;

    while ((c = fgetc(entrada)) != EOF){
        caractereLido++;
        const char *codigo = codigos[(unsigned char)c];

        for (int i = 0; codigo[i] != '\0'; i++){
            byteAtual = (byteAtual << 1) | (codigo[i] == '1' ? 1 : 0);
            bits++;

            if (bits == 8){
                fputc(byteAtual, saida);
                byteAtual = 0;
                bits = 0;
            }
        }
    }

    // Salvar último byte se houver bits pendentes
    if (bits > 0){
        byteAtual = byteAtual << (8 - bits);
        fputc(byteAtual, saida);
    }

    fclose(entrada);
    fclose(saida);

    printf("Arquivo compactado com sucesso!\n");
}

void descompactar(const char *arquivoEntrada, const char *arquivoSaida){

    FILE *entrada = fopen(arquivoEntrada, "rb");
    if (entrada == NULL){
        printf("Erro ao abrir arquivo compactado\n");
        return;
    }

    FILE *saida = fopen(arquivoSaida, "wb");
    if (saida == NULL){
        printf("Erro ao criar arquivo de saída\n");
        fclose(entrada);
        return;
    }

    // Ler cabeçalho (frequências)
    long long frequencias[256] = {0};
    for (int i = 0; i < 256; i++){
        fread(&frequencias[i], sizeof(long long), 1, entrada);
    }

    // Ler total de caracteres originais
    long long totalCaracteres = 0;
    fread(&totalCaracteres, sizeof(long long), 1, entrada);

    // Reconstruir árvore de Huffman
    No *raiz = criaArvoreHuffman(frequencias);
    if (raiz == NULL){
        printf("Erro ao reconstruir árvore\n");
        fclose(entrada);
        fclose(saida);
        return;
    }

    // Descompactar arquivo
    int c;
    No *atual = raiz;
    long long caracteresEscritos = 0;

    while ((c = fgetc(entrada)) != EOF && caracteresEscritos < totalCaracteres){
        unsigned char byte = (unsigned char)c;

        // Processa cada bit do byte (de cima para baixo: 7 até 0)
        for (int i = 7; i >= 0 && caracteresEscritos < totalCaracteres; i--){
            int bit = (byte >> i) & 1;

            // Navega na árvore
            if (bit == 0){
                atual = atual->esq;
            } else{
                atual = atual->dir;
            }

            // Se chegou em uma folha, escreve o caractere
            if (atual != NULL && atual->caractere != '\0'){
                fputc(atual->caractere, saida);
                caracteresEscritos++; 
                atual = raiz;
            }
        }
    }

    fclose(entrada);
    fclose(saida);
    liberarArvore(raiz);

    printf("Arquivo descompactado com sucesso!\n");
}