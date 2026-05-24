#include "huffman.h"
#include "heap.h"

int main() {
    long long frequencias[256] = {0};
    contarFrequencia("arquivo.txt", frequencias);
    imprimirTabelaFrequencias(frequencias);

    return 0;
}