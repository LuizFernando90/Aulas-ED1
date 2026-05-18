#include <stdio.h>
#include <stdlib.h>

int main()
{

    // Ponteiro para armazenar a duração da fumaça
    int *duracao_fumaca;

    // Alocando memória para um inteiro
    duracao_fumaca = (int *)malloc(sizeof(int));

    // Verificando se a alocação funcionou
    if (duracao_fumaca == NULL)
    {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    // Definindo a duração da fumaça
    *duracao_fumaca = 5;

    // Imprimindo ativação da bomba
    printf("Bomba de fumaca ativada! Duracao: %d segundos.\n", *duracao_fumaca);

    // Liberando a memória (a fumaça desaparece)
    free(duracao_fumaca);

    // Evitando ponteiro pendurado
    duracao_fumaca = NULL;

    // Mensagem final
    printf("A fumaca se dissipou.\n");

    return 0;
}