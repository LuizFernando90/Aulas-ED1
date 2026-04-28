#include <stdio.h>
#include <string.h>

// Definição da struct
struct ItemColetavel
{
    char nome[50];
    int valor_pontos;
};

int main()
{

    struct ItemColetavel inventario[3];
    struct ItemColetavel mais_valioso;

    // Entrada de dados
    for (int i = 0; i < 3; i++)
    {
        printf("Digite o nome do item %d: ", i + 1);
        scanf(" %[^\n]", inventario[i].nome);

        printf("Digite o valor em pontos do item %d: ", i + 1);
        scanf("%d", &inventario[i].valor_pontos);
    }

    // Inicializando com o primeiro item
    mais_valioso = inventario[0];

    // Encontrando o item mais valioso
    for (int i = 1; i < 3; i++)
    {
        if (inventario[i].valor_pontos > mais_valioso.valor_pontos)
        {
            mais_valioso = inventario[i];
        }
    }

    // Saída
    printf("O item mais valioso coletado foi: %s\n", mais_valioso.nome);

    return 0;
}