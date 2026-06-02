#include <stdio.h>
#include <stdlib.h>
#include "heroi.h"

// Definição completa da struct
struct heroi
{
    char nome[50];
    int hp;
    int ataque;
};

Heroi *criar_herois(int n)
{
    return (Heroi *)malloc(n * sizeof(Heroi));
}

void ler_herois(Heroi *h, int n)
{
    for (int i = 0; i < n; i++)
    {
        scanf("%s", h[i].nome);
        scanf("%d", &h[i].hp);
        scanf("%d", &h[i].ataque);
    }
}

void imprimir_herois(Heroi *h, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%s %d %d\n",
               h[i].nome,
               h[i].hp,
               h[i].ataque);
    }
}

void liberar_herois(Heroi *h)
{
    free(h);
}