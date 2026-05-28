#include "heap.h"
#include "huffman.h"

/*
Utilidade:
-> Cria o nó heap que possui os campos void** dados, int tamanho
e int capacidade alocando um vetor de ponteiros do tipo void
de tamanho 256 e atribuindo 0 a tamanho e 256 a capacidade

Parâmetros:
-> int capacidade: Numero inteiro que define o tamanho que terá
o vetor de ponteiros

Retorno:
-> A função retorna o endereço do nó heap criado

*/

Heap *criaHeap(int capacidade)
{
    Heap *h = (Heap *)malloc(sizeof(Heap));

    if (h == NULL)
    {
        printf("Erro ao criar heap.\n");
        exit(1);
    }

    h->dados = (void **)malloc(capacidade * sizeof(void *));

    if (h->dados == NULL)
    {
        printf("Erro ao criar o vetor void\n");
        free(h);
        exit(1);
    }

    h->tamanho = 0;
    h->capacidade = capacidade;
    return h;
}

/*
Utilidade:
-> Insere um novo nó no vetor de ponteiros que é o heap
e corrige o que quebra a condição de heap mínimo

Parâmetros:
-> Heap* h: Ponteiro para o nó do tipo heap

-> void *dado: Ponteiro para void que armazena
as informações do caractere

Retorno: 
-> A função não retorna nada

*/
void insereHeap(Heap *h, void *dado)
{
    if (h == NULL)
    {
        return;
    }

    if (h->tamanho >= h->capacidade)
    {
        printf("Heap cheio!\n");
        return;
    }

    h->dados[h->tamanho] = dado;
    h->tamanho++;
    corrigeSubindo(h, h->tamanho - 1);
}

void *extraiMinimo(Heap *h)
{
    if (h == NULL || h->tamanho == 0)
        return NULL;

    void *raiz = h->dados[0];
    h->dados[0] = h->dados[h->tamanho - 1];
    h->tamanho--;
    corrigeDescendo(h, 0);
    return raiz;
}

void liberaHeap(Heap *h)
{
    if (h != NULL)
    {
        free(h->dados);
        free(h);
    }
}

/*
Utilidade:
-> Função responsável por trocar o apontamento de dois ponteiros

Parâmetros:
-> void **a: Recebe o endereço do ponteiro
-> void **b: Recebe o endereço do outro ponteiro

Retorno: A função não retorna nada
*/

void troca(void **a, void **b)
{
    void *aux = *a;
    *a = *b;
    *b = aux;
}

void corrigeDescendo(Heap *h, int i)
{
    int menor = i;
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;

    if (esq < h->tamanho && comparar(h->dados[menor], h->dados[esq]))
        menor = esq;

    if (dir < h->tamanho && comparar(h->dados[menor], h->dados[dir]))
        menor = dir;

    if (menor != i)
    {
        troca(&h->dados[i], &h->dados[menor]);
        corrigeDescendo(h, menor);
    }
}

/*
Utilidade:
-> Manter a propriedade de heap mínimo quando se adiciona um novo nó

Paramêntros:
-> Heap *h: ponteiro que aponta para o nó do tipo Heap

-> int i: índice do último nó adicionado ao heap

Retorno: 
-> A função não retorna nada
*/

void corrigeSubindo(Heap *h, int i)
{
    int pai = (i - 1) / 2;

    if (i > 0 && h->dados[i] != NULL && comparar(h->dados[pai], h->dados[i]))
    {
        troca(&h->dados[i], &h->dados[pai]);
        corrigeSubindo(h, pai);
    }
}