#include <stdio.h>
#include <stdlib.h>

int main()
{

    // Ponteiro para armazenar a vida do inimigo
    int *vida_inimigo;

    // Alocando memória para um inteiro
    vida_inimigo = (int *)malloc(sizeof(int));

    // Verificando se a alocação funcionou
    if (vida_inimigo == NULL)
    {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    // Definindo a vida inicial
    *vida_inimigo = 80;

    // Imprimindo a invocação do inimigo
    printf("Um novo inimigo apareceu com %d de vida!\n", *vida_inimigo);

    // Simulando o ataque do jogador
    *vida_inimigo = *vida_inimigo - 35;

    // Imprimindo a vida restante
    printf("O jogador atacou! Vida restante do inimigo: %d\n", *vida_inimigo);

    // Liberando a memória alocada
    free(vida_inimigo);

    return 0;
}