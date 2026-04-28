#include <stdio.h>

int main()
{

    // Vetores de munição [quantidade atual, capacidade máxima]
    int balas[2] = {30, 30};
    int granadas[2] = {5, 5};
    int foguetes[2] = {2, 2};

    // Vetor de ponteiros (inventário)
    int *inventario[3];

    // Conectando o inventário aos vetores
    inventario[0] = balas;
    inventario[1] = granadas;
    inventario[2] = foguetes;

    // Estado inicial
    printf("Inventario Inicial:\n");
    printf("Balas: %d\n", *inventario[0]);
    printf("Granadas: %d\n", *inventario[1]);
    printf("Foguetes: %d\n", *inventario[2]);

    // Simulando o uso de 1 unidade de cada munição
    for (int i = 0; i < 3; i++)
    {
        *(inventario[i]) = *(inventario[i]) - 1;
    }

    // Estado final
    printf("\nInventario Apos o Uso:\n");
    printf("Balas: %d\n", *inventario[0]);
    printf("Granadas: %d\n", *inventario[1]);
    printf("Foguetes: %d\n", *inventario[2]);

    return 0;
}