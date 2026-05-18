#include <stdio.h>
#include <stdlib.h>

int main()
{

    int linhas, colunas;
    int **mapa;
    int contador_tijolos = 0;

    // Pedindo as dimensões do mapa
    printf("Digite o numero de linhas do mapa: ");
    scanf("%d", &linhas);

    printf("Digite o numero de colunas do mapa: ");
    scanf("%d", &colunas);

    // Alocando memória para as linhas
    mapa = (int **)malloc(linhas * sizeof(int *));

    if (mapa == NULL)
    {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    // Alocando memória para cada linha
    for (int i = 0; i < linhas; i++)
    {
        mapa[i] = (int *)malloc(colunas * sizeof(int));

        if (mapa[i] == NULL)
        {
            printf("Erro ao alocar memoria.\n");
            return 1;
        }
    }

    // Preenchendo o mapa
    printf("Digite os valores do mapa (0 = vazio, 1 = tijolo, 2 = moeda):\n");

    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            scanf("%d", &mapa[i][j]);
        }
    }

    // Contando os blocos de tijolo
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            if (mapa[i][j] == 1)
            {
                contador_tijolos++;
            }
        }
    }

    // Mostrando o resultado
    printf("O mapa possui %d blocos de tijolo.\n", contador_tijolos);

    // Liberando memória (primeiro as linhas)
    for (int i = 0; i < linhas; i++)
    {
        free(mapa[i]);
    }

    // Liberando o vetor de ponteiros
    free(mapa);

    return 0;
}