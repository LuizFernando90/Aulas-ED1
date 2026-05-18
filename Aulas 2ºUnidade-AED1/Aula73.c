#include <stdio.h>

// Função de partição
void particao(int n, int v[])
{
    int pivo = v[n - 1];
    int s[n];

    int inicio = 0;
    int fim = n - 1;

    // percorre o vetor original
    for (int i = 0; i < n; i++)
    {
        if (v[i] <= pivo)
        {
            s[inicio++] = v[i];
        }
        else
        {
            s[fim--] = v[i];
        }
    }

    // copia de volta para o vetor original
    for (int i = 0; i < n; i++)
    {
        v[i] = s[i];
    }
}

int main()
{
    int N;

    scanf("%d", &N);

    int v[N];

    // leitura dos valores
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &v[i]);
    }

    // chama a partição
    particao(N, v);

    // imprime o vetor resultante
    for (int i = 0; i < N; i++)
    {
        printf("%d ", v[i]);
    }

    printf("\n");

    return 0;
}