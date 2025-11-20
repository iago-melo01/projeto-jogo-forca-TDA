#pragma once
#ifndef BANCO_H
#define BANCO_H


typedef struct {
    char palavra[20];
    char dica[100];
} Palavra;

Palavra banco[] = {
    {"mouse",   "Ponteiro"},
    {"teclado", "Digitação"},
    {"monitor", "Imagem"},
    {"fone",    "Musica"},
};

const int banco_tamanho = sizeof(banco) / sizeof(banco[0]);

#endif
