#include "huffman.h"

/*
    Utilidade:
    -> Essa função serve para criar o nó contendo o caractere,
    a frequência desse caractere no arquivo de entrada e os
    ponteiros para esquerda e para direita começando com NULL

    Parâmetros:
    -> Unsigned char caractere: numero correspondente a certo
    caractere com base na tabela ASCII

    -> long long freq: valor corresponde a frequência de determinado caractere

    Retorno:
    -> A função retorna o nó criado
*/
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

/*
    Utilidade:
    -> Função responsável por criar os nós que não são folhas
    e guardar a quantidade de frequência de caracteres dos dois
    nós filhos somadas. O caractere é marcado como '\0' para
    identificar nós internos

    Parâmetros:
    -> No* esq: Nó que será apontado pelo ponteiro esquerdo do nó interno
    -> No* dir: Nó que será apontado pelo ponteiro direito do nó interno

    Retorno: A função retorna o nó criado
*/
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

/*
    Utilidade:
    -> Verificar se o nó filho tem menor frequência de caractere
    do que o nó pai

    Parâmetros:
    -> No* pai: Ponteiro para o nó pai
    -> No* filho: Ponteiro para o nó filho

    Retorno:
    -> Retorna 1: Se a frequência de caractere do nó filho é menor
    do que o do nó pai

    -> Retorna 0: Se a frequência de caractere do nó pai é menor
    do que o do nó filho
*/
int comparar(No *pai, No *filho) {
    if (filho->frequencia < pai->frequencia)
        return 1;
    else 
        return 0;
} 

/*
    Utilidade:
    -> Percorre o arquivo de entrada caractere por caractere e contabiliza
    a frequência de cada caractere, incrementando a posição correspondente ao seu
    valor na tabela ASCII no vetor de frequências.

    Parâmetros:
    -> Const char *arquivo: Ponteiro para a string com o nome do arquivo
    de entrada

    -> long long *tabelaFreq: Ponteiro para o vetor de frequencias de cada
    caractere

    Retorno: A função não retorna nada
*/
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

/*
    Utilidade:
    ->  cria a árvore de Huffman 

    Parâmetros:
    -> long long* frequencias: ponteiro para dados do tipo long long

    Retorno:
    -> A função retorna o nó raiz da árvore de Huffman construída
*/
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

/*
    Utilidade:
    -> Imprime na tela a frequência de cada caractere no arquivo de entrada

    Parâmetros:
    -> long long *frequencias: Ponteiro para dados do tipo long long

    Retorno:
    -> A função não retorna nada
*/
void imprimirTabelaFrequencias(long long *frequencias){
    for (int i = 0; i < 256; i++){
        if (frequencias[i] > 0){
            if (i == '\n') {
                printf("Caractere: '\\n' - Frequência: %lld\n", frequencias[i]);
            } else if (i == '\t') {
                printf("Caractere: '\\t' - Frequência: %lld\n", frequencias[i]);
            } else if (i == ' ') {
                printf("Caractere: ' ' - Frequência: %lld\n", frequencias[i]);
            } else {
                printf("Caractere: '%c' - Frequência: %lld\n", i, frequencias[i]);
            }
        }
    }
}

/*
    Utilidade:
    -> A função imprime a árvore de Huffman de forma visual com estrutura
    de galhos, onde nós internos são representados por [NÓ] e
    nós folha por [FOLHA] com melhor identificação

    Parâmetros:
    -> No* raiz: ponteiro para o nó que será a raiz da árvore

    -> int nivel: variável utilizada para saber a profundidade do nó
    na árvore para imprimi-la corretamente com indentação

    -> int caminhos[]: Mapeia com 0´s e 1´s para saber o caminho que
    percorremos, de forma a imprimir os galhos corretamente.
    0 no vetor indica que fomos para a esquerda na árvore e
    1 indica que fomos para a direita

    Retorno:
    -> A função não retorna nada
*/
void imprimirArvoreHuffman(No *raiz, int nivel, int caminhos[]) {
    if (raiz == NULL)
        return;

    caminhos[nivel] = 0;
    imprimirArvoreHuffman(raiz->dir, nivel + 1, caminhos);

    printf("\n");

    for (int i = 0; i < nivel; i++) {
        printf("   ");
    }

    if (nivel > 0) {
        printf("├─ ");
    }

    if (raiz->caractere != '\0') {
        if (raiz->caractere == '\n') {
            printf("'\\n'(%lld)", raiz->frequencia);
        } else if (raiz->caractere == '\t') {
            printf("'\\t'(%lld)", raiz->frequencia);
        } else if (raiz->caractere == ' ') {
            printf("' '(%lld)", raiz->frequencia);
        } else {
            printf("'%c'(%lld)", raiz->caractere, raiz->frequencia);
        }
    } else {
        printf("[%lld]", raiz->frequencia);
    }

    caminhos[nivel] = 1;
    imprimirArvoreHuffman(raiz->esq, nivel + 1, caminhos);
}

/*
    Utilidade:
    -> Criação dos nós com as informações dos caracteres chamando a
    função CriaNoFolha e inserção desses nós no heap chamando a fun-
    ção insereHeap

    Parâmetros:
    -> Heap *h: Ponteiro para o nó do tipo Heap

    ->long long *frequencias: ponteiro que aponta para elementos do
    tipo long long

    Retorno:
    -> A função não retorna nada
*/
void construirHeap(Heap *h, long long *frequencias){
    for (int i = 0; i < 256; i++){
        if (frequencias[i] > 0){
            No *novoNo = criaNoFolha((unsigned char)i, frequencias[i]);
            insereHeap(h, novoNo);
        }
    }
}

/*
    Utilidade:
    -> Liberar toda a memória alocada para a árvore

    Parâmetros:
    -> No* raiz: Ponteiro para a raiz da árvore

    Retorno: A função não retorna nada
*/
void liberarArvore(No *raiz){
    if (raiz == NULL)
        return;

    liberarArvore(raiz->esq);
    liberarArvore(raiz->dir);
    free(raiz);
}

/*
    Utilidade:
    -> Função responsável por percorrer a árvore de Huffman, descobrir o
    código de cada caractere e guardar essas informações em uma matriz
    dicionário

    Parâmetros:
    -> No* raiz: Ponteiro que aponta para o nó raiz

    -> char codigos: Matriz do tipo char que guarda o código de cada caractere

    -> char* caminho: ponteiro para dados do tipo char que aponta para o vetor que
    guarda o código de cada caractere

    -> int nível: variável que auxilia a mapear onde está o nó acessado e a guardar
    os códigos no vetor corretamente

    Retorno:
    -> A função não retorna nada
*/
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

/*
    Utilidade:
    -> Escreve um cabeçalho no arquivo de saída e vai pegando o código
    de cada caractere juntando esses códigos ou completando eles para
    que dê bytes e faz a escrita byte a byte no arquivo de saída, tendo
    no final o arquivo compactado

    Parâmetros:
    -> const char* arquivoEntrada: ponteiro para a string que contêm o
    nome do arquivo de entrada

    -> const char* arquivoSaida: Ponteiro para a string que contém o no-
    me do arquivo de saída

    -> char codigos[256][256]: Matriz do tipo char que contém os códigos
    de cada caractere

    -> long long* frequencias: Ponteiro para o vetor com a frequência de
    cada caractere

    Retorno: A função não retorna nada
*/
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

    for (int i = 0; i < 256; i++){
        fwrite(&frequencias[i], sizeof(long long), 1, saida);
    }

    long long totalCaracteres = 0;
    for (int i = 0; i < 256; i++){
        totalCaracteres += frequencias[i];
    }
    fwrite(&totalCaracteres, sizeof(long long), 1, saida); 

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

    if (bits > 0){
        byteAtual = byteAtual << (8 - bits);
        fputc(byteAtual, saida);
    }

    fclose(entrada);
    fclose(saida);

    printf("Arquivo compactado com sucesso!\n");
}

/*
    Utilidade:
    -> A função é responsável por ler os bytes do arquivo binário e
    pegar bit a bit separadamente, percorrendo a árvore de
    Huffman criada com base nesses bits para descobrir o caractere,
    salvando cada caractere que é descoberto no arquivo de saída ".txt",
    descomprimindo assim o arquivo binário. Atualiza a árvore e a tabela
    de frequências com base no arquivo comprimido lido
    
    Parâmetros:
    -> const char* arquivoEntrada: Ponteiro para o tipo const char que recebe o
    nome do arquivo comprimido de entrada
    
    -> const char* arquivoSaida: Ponteiro para o tipo const char que recebe o
    nome do arquivo descomprimido de saída
    
    -> No** raiz: Ponteiro para ponteiro da raiz da árvore de Huffman.
    Será atualizado com a árvore reconstruída a partir das frequências
    lidas do arquivo comprimido
    
    -> long long* frequencias: Ponteiro para o vetor de frequências.
    Será preenchido com as frequências lidas do cabeçalho do arquivo
    comprimido

    Retorno:
    -> A função não retorna nada
*/
void descompactar(const char *arquivoEntrada, const char *arquivoSaida, No **raiz, long long *frequencias){

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

    for (int i = 0; i < 256; i++){
        frequencias[i] = 0;
    }

    for (int i = 0; i < 256; i++){
        fread(&frequencias[i], sizeof(long long), 1, entrada);
    }

    long long totalCaracteres = 0;
    fread(&totalCaracteres, sizeof(long long), 1, entrada);

    if (*raiz != NULL){
        liberarArvore(*raiz);
    }

    *raiz = criaArvoreHuffman(frequencias);
    if (*raiz == NULL){
        printf("Erro ao reconstruir árvore\n");
        fclose(entrada);
        fclose(saida);
        return;
    }

    int c;
    No *atual = *raiz;
    long long caracteresEscritos = 0;

    while ((c = fgetc(entrada)) != EOF && caracteresEscritos < totalCaracteres){
        unsigned char byte = (unsigned char)c;

        for (int i = 7; i >= 0 && caracteresEscritos < totalCaracteres; i--){
            int bit = (byte >> i) & 1;

            if (atual == NULL){
                printf("Erro: ponteiro nulo durante descompactação\n");
                fclose(entrada);
                fclose(saida);
                return;
            }

            if (bit == 0){
                atual = atual->esq;
            } else{
                atual = atual->dir;
            }

            if (atual != NULL && atual->caractere != '\0'){
                fputc(atual->caractere, saida);
                caracteresEscritos++;  
                atual = *raiz;
            } else if (atual == NULL){
                printf("Erro: caminho inválido na árvore de Huffman\n");
                fclose(entrada);
                fclose(saida);
                return;
            }
        }
    }

    fclose(entrada);
    fclose(saida);

    printf("Arquivo descompactado com sucesso!\n");
}