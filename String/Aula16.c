#include <stdio.h>
#include <string.h>

int main()
{

    // Inventário com 5 itens (cada item até 19 caracteres)
    char inventario[5][20];
    char item_necessario[20];
    int encontrou = 0;

    // Preenchendo o inventário
    printf("Digite os 5 itens do inventario:\n");
    for (int i = 0; i < 5; i++)
    {
        scanf(" %19[^\n]", inventario[i]);
    }

    // Lendo o item necessário
    printf("Digite o item necessario para abrir a porta:\n");
    scanf(" %19[^\n]", item_necessario);

    // Verificando se o item está no inventário
    for (int i = 0; i < 5; i++)
    {
        if (strcmp(inventario[i], item_necessario) == 0)
        {
            encontrou = 1;
            break;
        }
    }

    // Exibindo resultado
    if (encontrou)
    {
        printf("Porta aberta!\n");
    }
    else
    {
        printf("Voce nao tem o item necessario.\n");
    }

    return 0;
}