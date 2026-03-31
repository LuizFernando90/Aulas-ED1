#include <stdio.h>
#include <stdlib.h>

int main()
{

    int *mochila;

    // Alocando espaço inicial para 3 itens
    mochila = (int *)malloc(3 * sizeof(int));

    if (mochila == NULL)
    {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    // Primeira coleta (3 itens)
    printf("Digite os 3 primeiros itens:\n");
    for (int i = 0; i < 3; i++)
    {
        scanf("%d", &mochila[i]);
    }

    // Mostrando itens atuais
    printf("Itens na mochila:\n");
    for (int i = 0; i < 3; i++)
    {
        printf("%d ", mochila[i]);
    }
    printf("\n");

    // Expandindo a mochila para 6 itens
    mochila = (int *)realloc(mochila, 6 * sizeof(int));

    if (mochila == NULL)
    {
        printf("Erro ao realocar memoria.\n");
        return 1;
    }

    // Segunda coleta (mais 3 itens)
    printf("Digite mais 3 itens:\n");
    for (int i = 3; i < 6; i++)
    {
        scanf("%d", &mochila[i]);
    }

    // Mostrando mochila completa
    printf("Mochila completa:\n");
    for (int i = 0; i < 6; i++)
    {
        printf("%d ", mochila[i]);
    }
    printf("\n");

    // Liberando memória
    free(mochila);

    return 0;
}