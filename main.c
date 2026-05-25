#include "huffman.h"
#include "heap.h"

void exibirMenu() {
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║   COMPACTADOR DE ARQUIVOS - HUFFMAN   ║\n");
    printf("╚════════════════════════════════════════╝\n");
    printf("\n1️⃣  Comprimir um arquivo\n");
    printf("2️⃣  Visualizar tabela de frequências\n");
    printf("3️⃣  Visualizar árvore de Huffman\n");
    printf("4️⃣  Descomprimir um arquivo\n");
    printf("5️⃣  Sair\n");
    printf("\nEscolha uma opção: ");
}

int main() {
    int opcao;
    char arquivoAtual[256] = {0};
    long long frequencias[256] = {0};
    No *raiz = NULL;
    char dicionario[256][256] = {0};

    while (1) {
        exibirMenu();
        scanf("%d", &opcao);
        getchar();  // Limpa o '\n' do buffer

        switch (opcao) {
            case 1: {
                // Comprimir um arquivo
                char entrada[256], saida[256];
                
                printf("\n📂 Nome do arquivo de entrada (.txt): ");
                fgets(entrada, sizeof(entrada), stdin);
                entrada[strcspn(entrada, "\n")] = '\0';  // Remove '\n'
                
                printf("📁 Nome do arquivo de saída (.huff): ");
                fgets(saida, sizeof(saida), stdin);
                saida[strcspn(saida, "\n")] = '\0';
                
                // Verificar se arquivo existe
                FILE *teste = fopen(entrada, "r");
                if (teste == NULL) {
                    printf("❌ Arquivo '%s' não encontrado!\n", entrada);
                    break;
                }
                fclose(teste);
                
                // Salvar nome do arquivo atual
                strcpy(arquivoAtual, entrada);
                
                // Contar frequências
                printf("📊 Contando frequências...\n");
                memset(frequencias, 0, sizeof(frequencias));
                contarFrequencia(entrada, frequencias);
                
                // Construir árvore
                printf("🌳 Construindo árvore de Huffman...\n");
                if (raiz != NULL)
                    liberarArvore(raiz);
                raiz = criaArvoreHuffman(frequencias);
                
                if (raiz == NULL) {
                    printf("❌ Erro ao construir árvore!\n");
                    break;
                }
                
                // Gerar dicionário
                printf("📝 Gerando dicionário de códigos...\n");
                memset(dicionario, 0, sizeof(dicionario));
                char codigo[256] = {0};
                gerarCodigosHuffman(raiz, dicionario, codigo, 0);
                
                // Compactar
                printf("🗜️  Compactando arquivo...\n");
                compactar(entrada, saida, dicionario, frequencias);
                
                printf("✅ Processo concluído!\n");
                break;
            }

            case 2: {
                // Visualizar tabela de frequências
                if (arquivoAtual[0] == '\0') {
                    printf("⚠️  Nenhum arquivo carregado ainda!\n");
                    printf("Pressione Enter para voltar ao menu...");
                    getchar();
                    break;
                }
                
                printf("\n📋 Tabela de Frequências do arquivo: %s\n", arquivoAtual);
                printf("════════════════════════════════════\n");
                imprimirTabelaFrequencias(frequencias);
                printf("════════════════════════════════════\n");
                
                printf("\nPressione Enter para voltar ao menu...");
                getchar();
                break;
            }

            case 3: {
                // Visualizar árvore de Huffman
                if (raiz == NULL) {
                    printf("⚠️  Nenhuma árvore construída ainda!\n");
                    printf("Pressione Enter para voltar ao menu...");
                    getchar();
                    break;
                }
                
                printf("\n🌲 Estrutura da Árvore de Huffman\n");
                printf("════════════════════════════════════\n");
                printf("(Nós internos: frequência)\n");
                printf("(Nós folha: caractere e frequência)\n");
                printf("════════════════════════════════════\n");
                imprimirArvoreHuffman(raiz, 0);
                printf("════════════════════════════════════\n");
                
                printf("\nPressione Enter para voltar ao menu...");
                getchar();
                break;
            }

            case 4: {
                // Descomprimir um arquivo
                char entrada[256], saida[256];
                
                printf("\n📂 Nome do arquivo comprimido (.huff): ");
                fgets(entrada, sizeof(entrada), stdin);
                entrada[strcspn(entrada, "\n")] = '\0';
                
                printf("📁 Nome do arquivo de saída (.txt): ");
                fgets(saida, sizeof(saida), stdin);
                saida[strcspn(saida, "\n")] = '\0';
                
                // Verificar se arquivo existe
                FILE *teste = fopen(entrada, "rb");
                if (teste == NULL) {
                    printf("❌ Arquivo '%s' não encontrado!\n", entrada);
                    break;
                }
                fclose(teste);
                
                printf("🗂️  Descompactando arquivo...\n");
                descompactar(entrada, saida);
                
                printf("✅ Arquivo descompactado com sucesso!\n");
                break;
            }

            case 5: {
                // Sair
                printf("\n👋 Encerrando o programa...\n");
                if (raiz != NULL)
                    liberarArvore(raiz);
                printf("✅ Até logo!\n\n");
                return 0;
            }

            default: {
                printf("❌ Opção inválida! Tente novamente.\n");
                break;
            }
        }
    }

    return 0;
}