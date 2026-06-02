#include <stdio.h>
#include "personagem.h"

int main()
{
    int num_membros;

    printf("Quantidade de membros da equipe: ");
    scanf("%d", &num_membros);

    Personagem *party = cria_party(num_membros);

    printf("\nDigite os dados dos personagens:\n");
    printf("Nome Classe Nivel HP\n\n");

    registra_membros(party, num_membros);

    printf("\n");
    exibe_relatorio(party, num_membros);

    libera_party(party);

    return 0;
}