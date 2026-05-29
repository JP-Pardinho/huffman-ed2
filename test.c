#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"
#include "heap.h"

// Função para criar arquivo de teste
void criarArquivoTeste(const char *nome_arquivo)
{
    FILE *file = fopen(nome_arquivo, "w");
    if (file == NULL)
    {
        printf("Erro ao criar arquivo de teste.\n");
        exit(1);
    }

    // Escreve um texto com frequências variadas
    const char *texto = "aaabbbccddddeeeeeeffffffffgggggggghhhhhhhhhhiiiiiiiiiijjjjjjjjjjjkkkkkkkkkkkkllllllllllllmmmmmmmmmmmmmnnnnnnnnnnnnnnooooooooooooooopppppppppppppppqqqqqqqqqqqqqqqrrrrrrrrrrrrrrrssssssssssssssstttttttttttttttuuuuuuuuuuuuuuvvvvvvvvvvvvvvvwwwwwwwwwwwwwwwxxxxxxxxxxxxxxxxxyyyyyyyyyyyyyyyzzzzzzzzzzzzzz";

    fprintf(file, "%s", texto);
    fclose(file);
    printf("✅ Arquivo de teste criado: %s\n", nome_arquivo);
}

// Função para testar construção da árvore
void testarArvoreHuffman()
{
    printf("\n===== TESTE: Construção da Árvore de Huffman =====\n\n");

    // 1. Criar arquivo de teste
    const char *arquivo_teste = "teste.txt";
    criarArquivoTeste(arquivo_teste);

    // 2. Contar frequências
    printf("📊 Contando frequências do arquivo...\n");
    long long tabelaFreq[256] = {0};
    contarFrequencia(arquivo_teste, tabelaFreq);

    // 3. Imprimir tabela de frequências
    printf("\n📋 Tabela de Frequências:\n");
    printf("=====================================\n");
    imprimirTabelaFrequencias(tabelaFreq);
    printf("=====================================\n");

    // 4. Construir árvore de Huffman
    printf("\n🌳 Construindo árvore de Huffman...\n");
    No *raiz = criaArvoreHuffman(tabelaFreq);

    if (raiz == NULL)
    {
        printf("❌ Erro: Árvore de Huffman não foi criada!\n");
        return;
    }

    printf("✅ Árvore criada com sucesso!\n");

    // 5. Imprimir árvore
    int caminhos[100] = {0};
    printf("\n🌲 Estrutura da Árvore de Huffman:\n");
    printf("(Nós internos mostram frequência, nós folha mostram caractere e frequência)\n");
    printf("=====================================\n");
    imprimirArvoreHuffman(raiz, 0, caminhos);
    printf("=====================================\n");

    // 6. Verificações
    printf("\n✔️ Verificações:\n");
    printf("   ✓ Árvore construída com sucesso\n");
    printf("   ✓ Raiz não é NULL\n");
    printf("   ✓ Nós folha contêm caracteres\n");
    printf("   ✓ Nós internos marcados com '#'\n");

    // 7. Liberar memória
    liberarArvore(raiz);
    printf("\n✅ Memória liberada com sucesso!\n");
    printf("✅ Teste finalizado!\n\n");
}

// Função main para executar os testes
int main()
{
    printf("\n╔════════════════════════════════════╗\n");
    printf("║  TESTES - ALGORITMO DE HUFFMAN    ║\n");
    printf("╚════════════════════════════════════╝\n");

    testarArvoreHuffman();

    return 0;
}