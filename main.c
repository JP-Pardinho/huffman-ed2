/*
    Grupo 6
    - Gabriel dos Santos            |  Matricula: 2023201331
    - João Pedro Pardinho Rodrigues |  Matricula: 2023201073
    - Nicolas Leal Espindula        |  Matricula: 2023200798
*/

#include "huffman.h"
#include "heap.h"

/*
    Utilidade:
    -> A função exibe o menu com as opções possíveis de realizar

    Parâmetros:
    -> A função não recebe parâmetros

    Retorno:
    -> A função não retorna nada
*/
void exibirMenu()
{
    printf("\n+------------------------------------------------+\n");
    printf("|                      MENU                      | \n");
    printf("+------------------------------------------------+\n");
    printf("| 1 - Comprimir um arquivo                       |\n");
    printf("| 2 - Visualizar tabela de frequências           |\n");
    printf("| 3 - Visualizar árvore de Huffman               |\n");
    printf("| 4 - Descomprimir um arquivo                    |\n");
    printf("| 5 - Sair                                       |\n");
    printf("+------------------------------------------------+\n");
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
        getchar();

        switch (opcao)
        {
        case 1:
        {
            char entrada[256], saida[256];

            printf("\nNome do arquivo de entrada (Sem a extensão): ");
            fgets(entrada, sizeof(entrada), stdin);
            entrada[strcspn(entrada, "\n")] = '\0'; 

            strcat(entrada, ".txt");

            printf("Nome do arquivo de saída (Sem a extensão): ");
            fgets(saida, sizeof(saida), stdin);
            saida[strcspn(saida, "\n")] = '\0';

            strcat(saida, ".bin");

            FILE *teste = fopen(entrada, "r");
            if (teste == NULL)
            {
                printf("Arquivo '%s' não encontrado!\n", entrada);
                break;
            }
            fclose(teste);

            strcpy(arquivoAtual, entrada);

            contarFrequencia(entrada, frequencias);

            if (raiz != NULL)
                liberarArvore(raiz);
            raiz = criaArvoreHuffman(frequencias);

            if (raiz == NULL) {
                printf("Erro ao construir árvore!\n");
                break;
            }

            char codigo[256] = {0};
            gerarCodigosHuffman(raiz, dicionario, codigo, 0);

            compactar(entrada, saida, dicionario, frequencias);

            printf("Arquivo compactado!\n");
            break;
        }

        case 2:
        {
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
            int caminhos[100] = {0};

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
            imprimirArvoreHuffman(raiz, 0, caminhos);
            printf("\n════════════════════════════════════\n");

            printf("\nPressione Enter para voltar ao menu...");
            getchar();
            break;
        }

        case 4:
        {
            char entrada[256], saida[256];

            printf("\nNome do arquivo comprimido (Sem a extensão): ");
            fgets(entrada, sizeof(entrada), stdin);
            entrada[strcspn(entrada, "\n")] = '\0';

            strcat(entrada, ".bin");

            printf("Nome do arquivo de saída (Sem a extensão): ");
            fgets(saida, sizeof(saida), stdin);
            saida[strcspn(saida, "\n")] = '\0';

            strcat(saida, ".txt");

            FILE *teste = fopen(entrada, "rb");
            if (teste == NULL)
            {
                printf("Arquivo '%s' não encontrado!\n", entrada);
                break;
            }
            fclose(teste);

            printf("Descompactando arquivo...\n");
            descompactar(entrada, saida, &raiz, frequencias);

            strcpy(arquivoAtual, saida);

            printf("Arquivo descompactado com sucesso!\n");
            printf("Tabela de frequências e árvore atualizadas!\n");
            break;
        }

        case 5:
        {
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