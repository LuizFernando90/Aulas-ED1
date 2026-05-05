#include <stdio.h>

// Definição da struct
typedef struct
{
    int id;
    int pontuacao;
} Jogador;

int main()
{
    int N, i, j;
    Jogador temp;

    // Ler quantidade de jogadores
    scanf("%d", &N);

    Jogador jogadores[N];

    // Ler dados
    for (i = 0; i < N; i++)
    {
        scanf("%d %d", &jogadores[i].id, &jogadores[i].pontuacao);
    }

    // Bubble Sort (ordem decrescente)
    for (i = 0; i < N - 1; i++)
    {
        for (j = 0; j < N - 1 - i; j++)
        {
            if (jogadores[j].pontuacao < jogadores[j + 1].pontuacao)
            {
                // Troca de structs
                temp = jogadores[j];
                jogadores[j] = jogadores[j + 1];
                jogadores[j + 1] = temp;
            }
        }
    }

    // Imprimir resultado
    for (i = 0; i < N; i++)
    {
        printf("%d %d\n", jogadores[i].id, jogadores[i].pontuacao);
    }

    return 0;
}