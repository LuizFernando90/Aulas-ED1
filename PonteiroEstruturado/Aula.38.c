#include <stdio.h>

// Definição da enum
enum EstadoPersonagem
{
    PARADO,
    CORRENDO,
    PULANDO
};

int main()
{
    enum EstadoPersonagem estado_atual;
    int entrada;

    // Entrada do usuário
    printf("Digite o estado do personagem (0 = PARADO, 1 = CORRENDO, 2 = PULANDO): ");
    scanf("%d", &entrada);

    // Atribuição
    estado_atual = entrada;

    // Lógica de decisão
    if (estado_atual == PARADO)
    {
        printf("O personagem esta parado.\n");
    }
    else if (estado_atual == CORRENDO)
    {
        printf("O personagem esta correndo!\n");
    }
    else if (estado_atual == PULANDO)
    {
        printf("O personagem esta pulando no ar!\n");
    }
    else
    {
        printf("Estado invalido!\n");
    }

    return 0;
}