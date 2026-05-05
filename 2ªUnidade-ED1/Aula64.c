#include <stdio.h>

int main()
{
    int n, i, j, chave;

    // Ler quantidade de fragmentos
    scanf("%d", &n);

    int fragmentos[n];

    // Ler os valores
    for (i = 0; i < n; i++)
    {
        scanf("%d", &fragmentos[i]);
    }

    // Insertion Sort
    for (i = 1; i < n; i++)
    {
        chave = fragmentos[i];
        j = i - 1;

        // Move os elementos maiores para a direita
        while (j >= 0 && fragmentos[j] > chave)
        {
            fragmentos[j + 1] = fragmentos[j];
            j--;
        }

        // Insere na posição correta
        fragmentos[j + 1] = chave;
    }

    // Imprimir vetor ordenado
    for (i = 0; i < n; i++)
    {
        printf("%d ", fragmentos[i]);
    }

    printf("\n");

    return 0;
}