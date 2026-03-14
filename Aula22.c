#include <stdio.h>
#include <stdlib.h>

int main()
{

    int n_inimigos;
    int *ponteiro_onda;

    // Pedindo a quantidade de inimigos
    printf("Digite a quantidade de inimigos da onda: ");
    scanf("%d", &n_inimigos);

    // Alocando memória para o vetor de inimigos
    ponteiro_onda = (int *)malloc(n_inimigos * sizeof(int));

    // Verificando se a alocação funcionou
    if (ponteiro_onda == NULL)
    {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    // Pedindo o ID de cada inimigo
    for (int i = 0; i < n_inimigos; i++)
    {
        printf("Digite o ID do inimigo %d: ", i + 1);
        scanf("%d", &ponteiro_onda[i]);
    }

    // Listando os IDs da onda
    printf("Onda de inimigos criada com sucesso! IDs: ");

    for (int i = 0; i < n_inimigos; i++)
    {
        printf("%d ", ponteiro_onda[i]);
    }

    printf("\n");

    // Liberando memória
    free(ponteiro_onda);

    return 0;
}