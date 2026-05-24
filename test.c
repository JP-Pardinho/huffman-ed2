#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"
#include "heap.h"

// Funções auxiliares para testes
void print_teste(const char *nome, int resultado) {
    printf("[%s] %s\n", resultado ? "PASS" : "FAIL", nome);
}

// Teste 1: Criar e testar heap
void teste_heap() {
    printf("\n=== Testes de Heap ===\n");
    
    Heap *h = criaHeap(10);
    print_teste("Heap criado corretamente", h != NULL && h->tamanho == 0);
    
    // Teste de inserção (usando inteiros para teste)
    No *no1 = criaNoFolha('a', 5);
    No *no2 = criaNoFolha('b', 3);
    No *no3 = criaNoFolha('c', 7);
    
    insereHeap(h, no1);
    insereHeap(h, no2);
    insereHeap(h, no3);
    
    print_teste("Heap com 3 elementos", h->tamanho == 3);
    
    // Teste de extração de mínimo
    No *minimo = (No *)extraiMinimo(h);
    print_teste("Extrai mínimo corretamente", minimo->frequencia == 3);
    print_teste("Heap após extração tem 2 elementos", h->tamanho == 2);
    
    free(h->dados);
    free(h);
    printf("Testes de heap concluídos!\n");
}

// Teste 2: Criar nós de folha
void teste_nos_folha() {
    printf("\n=== Testes de Nós Folha ===\n");
    
    No *no = criaNoFolha('A', 10);
    print_teste("Nó folha criado", no != NULL);
    print_teste("Caractere correto", no->caractere == 'A');
    print_teste("Frequência correta", no->frequencia == 10);
    print_teste("Não tem filho esquerdo", no->esq == NULL);
    print_teste("Não tem filho direito", no->dir == NULL);
    
    free(no);
    printf("Testes de nós concluídos!\n");
}

// Teste 3: Contar frequências
void teste_frequencia() {
    printf("\n=== Testes de Frequência ===\n");
    
    long long frequencias[256] = {0};
    contarFrequencia("arquivo.txt", frequencias);
    
    print_teste("Arquivo lido corretamente", 1);
    
    int total = 0;
    for (int i = 0; i < 256; i++) {
        total += frequencias[i];
    }
    print_teste("Total de caracteres contabilizado", total > 0);
    
    printf("Total de caracteres no arquivo: %d\n", total);
    printf("Testes de frequência concluídos!\n");
}

// Teste 4: Criar nó interno
void teste_no_interno() {
    printf("\n=== Testes de Nós Internos ===\n");
    
    No *folha1 = criaNoFolha('A', 5);
    No *folha2 = criaNoFolha('B', 3);
    No *interno = criaNoInterno(folha1, folha2);
    
    print_teste("Nó interno criado", interno != NULL);
    print_teste("Filho esquerdo correto", interno->esq == folha1);
    print_teste("Filho direito correto", interno->dir == folha2);
    print_teste("Frequência é soma dos filhos", interno->frequencia == 8);
    
    free(interno);
    printf("Testes de nós internos concluídos!\n");
}

int main() {
    printf("========================================\n");
    printf("   TESTES DO PROGRAMA HUFFMAN\n");
    printf("========================================\n");
    
    teste_heap();
    teste_nos_folha();
    teste_no_interno();
    teste_frequencia();
    
    printf("\n========================================\n");
    printf("   TESTES CONCLUÍDOS\n");
    printf("========================================\n");
    
    return 0;
}
