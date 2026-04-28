#include <stdio.h>

// Função recursiva para contar cristais positivos
int contarPositivos(int vet[], int n, int i)
{
    // Caso base: terminou o vetor
    if (i == n)
    {
        return 0;
    }

    // Se o valor atual é positivo, conta +1
    if (vet[i] > 0)
    {
        return 1 + contarPositivos(vet, n, i + 1);
    }
    else
    {
        return contarPositivos(vet, n, i + 1);
    }
}

int main()
{
    int n;

    printf("Digite a quantidade de cristais: ");
    scanf("%d", &n);

    int cristais[n];

    // Leitura dos valores
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &cristais[i]);
    }

    // Chamada da função recursiva
    int total = contarPositivos(cristais, n, 0);

    printf("Quantidade de cristais carregados: %d\n", total);

    return 0;
}