#include <stdio.h>

int main()
{
    int N, i, j, temp;

    // Ler quantidade de jogadores
    scanf("%d", &N);

    int pontuacoes[N];

    // Ler pontuações
    for (i = 0; i < N; i++)
    {
        scanf("%d", &pontuacoes[i]);
    }

    // Bubble Sort (ordem decrescente)
    for (i = 0; i < N - 1; i++)
    {
        for (j = 0; j < N - 1 - i; j++)
        {
            if (pontuacoes[j] < pontuacoes[j + 1])
            {
                // Troca
                temp = pontuacoes[j];
                pontuacoes[j] = pontuacoes[j + 1];
                pontuacoes[j + 1] = temp;
            }
        }
    }

    // Imprimir resultado
    for (i = 0; i < N; i++)
    {
        printf("%d ", pontuacoes[i]);
    }

    printf("\n");

    return 0;
}