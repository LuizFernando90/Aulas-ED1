#include <stdio.h>
#include <stdlib.h>

int main()
{

    // Ponteiro genérico para armazenar a duração do power-up
    void *ponteiro_duracao;

    // Alocando memória para um inteiro
    ponteiro_duracao = malloc(sizeof(int));

    // Verificando se a alocação funcionou
    if (ponteiro_duracao == NULL)
    {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    // Ativando o power-up (definindo duração inicial)
    *((int *)ponteiro_duracao) = 10;

    // Imprimindo a duração inicial
    printf("Power-up 'Super Salto' ativado! Duracao: %d segundos.\n", *((int *)ponteiro_duracao));

    // Simulando passagem do tempo (3 segundos)
    *((int *)ponteiro_duracao) -= 3;

    // Imprimindo duração restante
    printf("3 segundos se passaram... Duracao restante: %d segundos.\n", *((int *)ponteiro_duracao));

    // Liberando a memória
    free(ponteiro_duracao);

    return 0;
}