#include <stdio.h>
#include <stdlib.h>

#define LINHAS 5
#define COLUNAS 10

int main()
{

    int *level_map;

    // Alocando memória para toda a matriz (LINHAS x COLUNAS)
    level_map = (int *)malloc(LINHAS * COLUNAS * sizeof(int));

    // Verificando se a alocação funcionou
    if (level_map == NULL)
    {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    // Construindo o mapa
    for (int i = 0; i < LINHAS; i++)
    {
        for (int j = 0; j < COLUNAS; j++)
        {

            if (i == LINHAS - 1)
            {
                *(level_map + i * COLUNAS + j) = 1; // chão
            }
            else
            {
                *(level_map + i * COLUNAS + j) = 0; // ar
            }
        }
    }

    // Exibindo o mapa
    printf("Mapa da fase:\n");

    for (int i = 0; i < LINHAS; i++)
    {
        for (int j = 0; j < COLUNAS; j++)
        {
            printf("%d ", *(level_map + i * COLUNAS + j));
        }
        printf("\n");
    }

    // Liberando memória
    free(level_map);

    return 0;
}