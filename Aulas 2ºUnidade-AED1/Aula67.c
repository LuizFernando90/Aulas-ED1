#include <stdio.h>

int main()
{
    int n, i, j, temp;
    int trocou;

    // Ler quantidade
    scanf("%d", &n);

    int v[n];

    // Ler pontuações
    for (i = 0; i < n; i++)
    {
        scanf("%d", &v[i]);
    }

    // Bubble Sort otimizado (decrescente)
    for (i = 0; i < n - 1; i++)
    {
        trocou = 0; // flag

        for (j = 0; j < n - 1 - i; j++)
        {
            if (v[j] < v[j + 1])
            {
                // troca
                temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
                trocou = 1; // houve troca
            }
        }

        // Se não houve troca, já está ordenado
        if (trocou == 0)
        {
            break;
        }
    }

    // Imprimir resultado
    for (i = 0; i < n; i++)
    {
        printf("%d ", v[i]);
    }

    printf("\n");

    return 0;
}