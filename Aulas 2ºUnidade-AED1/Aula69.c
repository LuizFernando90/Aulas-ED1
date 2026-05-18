#include <stdio.h>

int main()
{
    int n, m, i, j, k;

    // Ler tamanho do vetor Alfa
    scanf("%d", &n);
    int alfa[n];

    // Ler elementos de Alfa
    for (i = 0; i < n; i++)
    {
        scanf("%d", &alfa[i]);
    }

    // Ler tamanho do vetor Beta
    scanf("%d", &m);
    int beta[m];

    // Ler elementos de Beta
    for (i = 0; i < m; i++)
    {
        scanf("%d", &beta[i]);
    }

    // Vetor resultado
    int resultado[n + m];

    i = 0; // índice de alfa
    j = 0; // índice de beta
    k = 0; // índice do resultado

    // Intercalação (merge)
    while (i < n && j < m)
    {
        if (alfa[i] <= beta[j])
        {
            resultado[k++] = alfa[i++];
        }
        else
        {
            resultado[k++] = beta[j++];
        }
    }

    // Copiar resto de Alfa (se sobrar)
    while (i < n)
    {
        resultado[k++] = alfa[i++];
    }

    // Copiar resto de Beta (se sobrar)
    while (j < m)
    {
        resultado[k++] = beta[j++];
    }

    // Imprimir resultado
    for (i = 0; i < n + m; i++)
    {
        printf("%d ", resultado[i]);
    }

    printf("\n");

    return 0;
}