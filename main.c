#include "huffman.h"
#include "heap.h"

void exibirMenu()
{
    printf("\n MENU \n");
    printf("\n1 - Comprimir um arquivo\n");
    printf("2 - Visualizar tabela de frequências\n");
    printf("3 - Visualizar árvore de Huffman\n");
    printf("4 - Descomprimir um arquivo\n");
    printf("5 - Sair\n");
    printf("\nEscolha uma opção: ");
}

int main()
{
    int opcao;
    char arquivoAtual[256] = {0};
    long long frequencias[256] = {0};
    No *raiz = NULL;
    char dicionario[256][256] = {0};

    while (1)
    {
        exibirMenu();
        scanf("%d", &opcao);
        getchar(); // Limpa o '\n' do buffer

        switch (opcao)
        {
        case 1:
        {
            // Comprimir um arquivo
            char entrada[256], saida[256];

            printf("\nNome do arquivo de entrada (.txt): ");
            fgets(entrada, sizeof(entrada), stdin);
            entrada[strcspn(entrada, "\n")] = '\0'; // Remove '\n'

            printf("Nome do arquivo de saída: ");
            fgets(saida, sizeof(saida), stdin);
            saida[strcspn(saida, "\n")] = '\0';

            // Verificar se arquivo existe
            FILE *teste = fopen(entrada, "r");
            if (teste == NULL)
            {
                printf("Arquivo '%s' não encontrado!\n", entrada);
                break;
            }
            fclose(teste);

            // Salvar nome do arquivo atual
            strcpy(arquivoAtual, entrada);

            // Contar frequências
            contarFrequencia(entrada, frequencias);

            // Construir árvore
            if (raiz != NULL)
                liberarArvore(raiz);
            raiz = criaArvoreHuffman(frequencias);

            if (raiz == NULL){
                printf("Erro ao construir árvore!\n");
                break;
            }

            // Gerar dicionário
            char codigo[256] = {0};
            gerarCodigosHuffman(raiz, dicionario, codigo, 0);

            // Compactar
            compactar(entrada, saida, dicionario, frequencias);

            printf("Arquivo compactado!\n");
            break;
        }

        case 2:
        {
            // Visualizar tabela de frequências
            if (arquivoAtual[0] == '\0')
            {
                printf("Nenhum arquivo foi comprimido ainda!\n");
                printf("Pressione Enter para voltar ao menu");
                getchar();
                break;
            }

            printf("\nTabela de Frequências do arquivo: %s\n", arquivoAtual);
            imprimirTabelaFrequencias(frequencias);

            printf("\nPressione Enter para voltar ao menu...");
            getchar();
            break;
        }

        case 3:
        {
            // Visualizar árvore de Huffman
            if (raiz == NULL)
            {
                printf("Nenhuma árvore construída ainda!\n");
                printf("Pressione Enter para voltar ao menu...");
                getchar();
                break;
            }

            printf("\nEstrutura da Árvore de Huffman\n");
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

        case 4:
        {
            // Descomprimir um arquivo
            char entrada[256], saida[256];

            printf("\nNome do arquivo comprimido: ");
            fgets(entrada, sizeof(entrada), stdin);
            entrada[strcspn(entrada, "\n")] = '\0';

            printf("Nome do arquivo de saída (.txt): ");
            fgets(saida, sizeof(saida), stdin);
            saida[strcspn(saida, "\n")] = '\0';

            // Verificar se arquivo existe
            FILE *teste = fopen(entrada, "rb");
            if (teste == NULL)
            {
                printf("Arquivo '%s' não encontrado!\n", entrada);
                break;
            }
            fclose(teste);

            printf("Descompactando arquivo...\n");
            descompactar(entrada, saida);

            printf("Arquivo descompactado com sucesso!\n");
            break;
        }

        case 5:
        {
            // Sair
            printf("\nPrograma encerrado\n");
            if (raiz != NULL)
                liberarArvore(raiz);
            return 0;
        }

        default:
        {
            printf("Opção inválida! Tente novamente.\n");
            break;
        }
        }
    }

    return 0;
}