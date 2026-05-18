#include <stdio.h>

// Definição da struct
typedef struct
{
    char nome[50];
    int pontuacao;
} Jogador;

int main()
{
    int N, i, j;

    // Ler quantidade de jogadores
    scanf("%d", &N);

    Jogador players[N];

    // Ler dados
    for (i = 0; i < N; i++)
    {
        scanf("%s %d", players[i].nome, &players[i].pontuacao);
    }

    // Insertion Sort (ordem decrescente)
    for (i = 1; i < N; i++)
    {
        Jogador chave = players[i];
        j = i - 1;

        // Ordena do MAIOR para o MENOR
        while (j >= 0 && players[j].pontuacao < chave.pontuacao)
        {
            players[j + 1] = players[j];
            j--;
        }

        players[j + 1] = chave;
    }

    // Imprimir ranking
    for (i = 0; i < N; i++)
    {
        printf("%d %s\n", players[i].pontuacao, players[i].nome);
    }

    return 0;
}