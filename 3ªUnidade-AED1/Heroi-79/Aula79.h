#ifndef HEROI_H
#define HEROI_H

// Struct incompleta (opaque type)
typedef struct heroi Heroi;

// Funções do módulo
Heroi *criar_herois(int n);

void ler_herois(Heroi *h, int n);

void imprimir_herois(Heroi *h, int n);

void liberar_herois(Heroi *h);

#endif