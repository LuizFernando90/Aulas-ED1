#include <stdio.h>
#include <stdlib.h>
#include "personagem.h"

struct personagem
{
    char nome[50];
    char classe[50];
    int nivel;
    int hp;
};

Personagem *cria_party(int num_membros)
{
    return (Personagem *)malloc(num_membros * sizeof(Personagem));
}

void registra_membros(Personagem *party, int num_membros)
{
    for (int i = 0; i < num_membros; i++)
    {
        scanf("%s", party[i].nome);
        scanf("%s", party[i].classe);
        scanf("%d", &party[i].nivel);
        scanf("%d", &party[i].hp);
    }
}

void exibe_relatorio(const Personagem *party, int num_membros)
{
    printf("\n=== EQUIPE DE HEROIS ===\n");

    for (int i = 0; i < num_membros; i++)
    {
        printf("Nome: %s\n", party[i].nome);
        printf("Classe: %s\n", party[i].classe);
        printf("Nivel: %d\n", party[i].nivel);
        printf("HP: %d\n", party[i].hp);
        printf("\n");
    }
}

void libera_party(Personagem *party)
{
    free(party);
}