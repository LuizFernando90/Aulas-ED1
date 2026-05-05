#include <stdio.h>

// Função recursiva para encontrar o maior valor
int encontrarMaximo(int vetor[], int inicio, int fim)
{
    // Caso base: apenas um elemento
    if (inicio == fim)
    {
        return vetor[inicio];
    }

    // Divide o vetor ao meio
    int meio = (inicio + fim) / 2;

    // Conquista: encontra o máximo em cada metade
    int maxEsquerda = encontrarMaximo(vetor, inicio, meio);
    int maxDireita = encontrarMaximo(vetor, meio + 1, fim);

    // Combina: retorna o maior dos dois
    if (maxEsquerda > maxDireita)
    {
        return maxEsquerda;
    }
    else
    {
        return maxDireita;
    }
}

int main()
{
    int N;

    // Lê a quantidade de fragmentos
    scanf("%d", &N);

    int vetor[N];

    // Lê os valores
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &vetor[i]);
    }

    // Chama a função recursiva
    int maior = encontrarMaximo(vetor, 0, N - 1);

    // Exibe o resultado
    printf("%d\n", maior);

    return 0;
}