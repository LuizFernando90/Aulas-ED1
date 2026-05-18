#include <stdio.h>

int main()
{
    int N, i, j, min, temp;

    // Ler quantidade de jogadores
    scanf("%d", &N);

    int scores[N];

    // Ler as pontuações
    for (i = 0; i < N; i++)
    {
        scanf("%d", &scores[i]);
    }

    // Selection Sort (ordem crescente)
    for (i = 0; i < N - 1; i++)
    {
        min = i;

        for (j = i + 1; j < N; j++)
        {
            if (scores[j] < scores[min])
            {
                min = j;
            }
        }

        // Troca
        temp = scores[i];
        scores[i] = scores[min];
        scores[min] = temp;
    }

    // Exibir resultado
    for (i = 0; i < N; i++)
    {
        printf("%d ", scores[i]);
    }

    printf("\n");

    return 0;
}