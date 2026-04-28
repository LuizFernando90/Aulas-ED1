#include <stdio.h>

// Função recursiva
int calcularDanoEco(int n)
{
    // Casos base
    if (n == 1)
    {
        return 0;
    }
    if (n == 2)
    {
        return 1;
    }

    // Recursão múltipla
    return calcularDanoEco(n - 1) + calcularDanoEco(n - 2);
}

int main()
{
    int N;

    printf("Digite o numero do golpe: ");
    scanf("%d", &N);

    int dano = calcularDanoEco(N);

    printf("Dano bonus: %d\n", dano);

    return 0;
}