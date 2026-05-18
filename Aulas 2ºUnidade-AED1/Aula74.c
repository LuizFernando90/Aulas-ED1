#include <stdio.h>

// Função de partição in-place
void particao(int n, int v[])
{
    int pivo = v[n - 1];
    int i = -1;

    // reorganiza o vetor
    for (int j = 0; j < n - 1; j++)
    {
        if (v[j] < pivo)
        {
            i++;
            // troca v[i] com v[j]
            int temp = v[i];
            v[i] = v[j];
            v[j] = temp;
        }
    }

    // coloca o pivô na posição correta
    int temp = v[i + 1];
    v[i + 1] = v[n - 1];
    v[n - 1] = temp;
}

int main()
{
    int n;

    scanf("%d", &n);

    int v[n];

    // leitura dos dados
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &v[i]);
    }

    // aplica a partição
    particao(n, v);

    // imprime o vetor
    for (int i = 0; i < n; i++)
    {
        printf("%d ", v[i]);
    }

    printf("\n");

    return 0;
}