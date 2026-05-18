#include <stdio.h>

// Função recursiva
int danoCascata(int n)
{
    // Caso base
    if (n == 1)
    {
        return 1;
    }

    // Passo recursivo
    return n + danoCascata(n - 1);
}

int main()
{
    int nivel;

    printf("Digite o nivel do mago: ");
    scanf("%d", &nivel);

    int dano = danoCascata(nivel);

    printf("Dano total: %d\n", dano);

    return 0;
}