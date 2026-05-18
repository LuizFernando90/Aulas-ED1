#include <stdio.h>
#include <stdlib.h>

int main()
{

    int quantidade;
    int *status_inimigos;

    // Lendo a quantidade de inimigos
    printf("Digite a quantidade de inimigos: ");
    scanf("%d", &quantidade);

    // Alocando memória com calloc (já inicializa com 0)
    status_inimigos = (int *)calloc(quantidade, sizeof(int));

    // Verificando se a alocação funcionou
    if (status_inimigos == NULL)
    {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    // Verificação inicial (todos devem estar 0)
    for (int i = 0; i < quantidade; i++)
    {
        printf("Inimigo %d: Inativo (%d)\n", i + 1, status_inimigos[i]);
    }

    // Ativando todos os inimigos (mudando para 1)
    for (int i = 0; i < quantidade; i++)
    {
        status_inimigos[i] = 1;
    }

    // Relatório final
    for (int i = 0; i < quantidade; i++)
    {
        printf("Inimigo %d: Ativo (%d)\n", i + 1, status_inimigos[i]);
    }

    // Liberando memória
    free(status_inimigos);

    return 0;
}