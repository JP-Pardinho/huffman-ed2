#ifndef HUFFMAN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct no
{
    unsigned char caractere;
    unsigned int frequencia;
    struct no *esq;
    struct no *dir;
} No;

#endif