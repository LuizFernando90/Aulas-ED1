#include <stdio.h>
#include <stdlib.h>

// Definição da struct
typedef struct
{
    char nome[50];
    int eliminacoes;
} Jogador;

int main()
{
    int N, i, j, max;
    Jogador temp;

    // Ler quantidade de jogadores
    scanf("%d", &N);

    // Alocação dinâmica
    Jogador *players = (Jogador *)malloc(N * sizeof(Jogador));

    if (players == NULL)
    {
        printf("Erro de memoria!\n");
        return 1;
    }

    // Ler dados dos jogadores
    for (i = 0; i < N; i++)
    {
        scanf("%s %d", players[i].nome, &players[i].eliminacoes);
    }

    // Selection Sort (ordem decrescente)
    for (i = 0; i < N - 1; i++)
    {
        max = i;

        for (j = i + 1; j < N; j++)
        {
            if (players[j].eliminacoes > players[max].eliminacoes)
            {
                max = j;
            }
        }

        // Troca de structs
        temp = players[i];
        players[i] = players[max];
        players[max] = temp;
    }

    // Exibir leaderboard
    for (i = 0; i < N; i++)
    {
        printf("%s %d\n", players[i].nome, players[i].eliminacoes);
    }

    // Liberar memória
    free(players);

    return 0;
}