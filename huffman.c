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

    novo->caractere = '#';
    novo->frequencia = esq->frequencia + dir->frequencia;
    novo->esq = esq;
    novo->dir = dir;
    return novo;
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
        No *raiz = criaNoInterno(folha, NULL);
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
    printf("Tabela de Frequências:\n");
    for (int i = 0; i < 256; i++){
        if (frequencias[i] > 0){
            printf("Caractere: '%c' (ASCII: %d) - Frequência: %lld\n", i, i, frequencias[i]);
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
    if (raiz->caractere != '#'){
        printf("Caractere: '%c' (ASCII: %d) - Frequência: %lld\n", raiz->caractere, raiz->caractere, raiz->frequencia);
    }
    else{
        printf("Nó Interno - Frequência: %lld\n", raiz->frequencia);
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
        printf("Erro ao abrir o arquivo de entrada\n");
        return;
    }

    FILE *saida = fopen(arquivoSaida, "wb");
    if (saida == NULL){
        printf("Erro ao criar o arquivo de saída\n");
        fclose(entrada);
        return;
    }

    // PASSO 1: Salvar cabeçalho (frequências de cada caractere)
    printf("Salvando cabeçalho do arquivo...\n");
    for (int i = 0; i < 256; i++){
        fwrite(&frequencias[i], sizeof(long long), 1, saida);
    }

    // PASSO 2: Compactar o arquivo bit por bit
    printf("Compactando arquivo...\n");
    int c;
    unsigned char byte_atual = 0;
    int bits_no_buffer = 0;
    long long bytes_originais = 0;
    long long bits_escritos = 0;

    while ((c = fgetc(entrada)) != EOF){
        unsigned char ch = (unsigned char)c;
        bytes_originais++;

        // Pega o código do caractere do dicionário
        const char *codigo = codigos[ch];

        // Adiciona cada bit do código ao buffer
        for (int i = 0; codigo[i] != '\0'; i++){
            byte_atual = (byte_atual << 1) | (codigo[i] == '1' ? 1 : 0);
            bits_no_buffer++;
            bits_escritos++;

            // Se buffer cheio, escreve um byte
            if (bits_no_buffer == 8){
                fputc(byte_atual, saida);
                byte_atual = 0;
                bits_no_buffer = 0;
            }
        }
    }

    // PASSO 3: Salvar último byte (com padding)
    if (bits_no_buffer > 0){
        byte_atual = byte_atual << (8 - bits_no_buffer);
        fputc(byte_atual, saida);
        fputc(bits_no_buffer, saida); // Salva quantos bits válidos
    }
    else{
        fputc(0, saida); // Sem padding
    }

    // PASSO 4: Fechar arquivos
    fclose(entrada);
    fclose(saida);

    // // PASSO 5: Mostrar estatísticas
    // long long bytes_compactados = (bits_escritos + 7) / 8;
    // double taxa = (1.0 - (double)bytes_compactados / bytes_originais) * 100;

    // printf("\nArquivo compactado com sucesso!\n");
    // printf("Estatísticas:\n");
    // printf("Original: %lld bytes\n", bytes_originais);
    // printf("Compactado: ~%lld bytes\n", bytes_compactados);
    // printf("Taxa de compactação: %.2f%%\n", taxa);
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
    int bits_validos = 0;
    int eh_ultimo_byte = 0;

    // Lê todos os bytes
    while ((c = fgetc(entrada)) != EOF){
        unsigned char byte = (unsigned char)c;

        // Se é o penúltimo byte lido, o próximo é padding info
        int proximo = fgetc(entrada);
        if (proximo == EOF){
            // Este é o último byte, próximo indica padding
            bits_validos = byte;
            break;
        }
        else{
            // Coloca de volta o byte que leu
            ungetc(proximo, entrada);
        }

        // Processa cada bit do byte (de cima para baixo: 7 até 0)
        for (int i = 7; i >= 0; i--){
            int bit = (byte >> i) & 1;

            // Navega na árvore
            if (bit == 0){
                atual = atual->esq;
            }
            else{
                atual = atual->dir;
            }

            // Se chegou em uma folha, escreve o caractere
            if (atual != NULL && atual->caractere != '#'){
                fputc(atual->caractere, saida);
                atual = raiz; // Volta para a raiz
            }
        }
    }

    fclose(entrada);
    fclose(saida);
    liberarArvore(raiz);
}