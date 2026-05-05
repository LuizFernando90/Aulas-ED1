#include <stdio.h>

// Função de partição (Lomuto)
int particao(int v[], int inicio, int fim)
{
    int pivo = v[fim];
    int i = inicio - 1;

    for (int j = inicio; j < fim; j++)
    {
        if (v[j] <= pivo)
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
    v[i + 1] = v[fim];
    v[fim] = temp;

    return i + 1;
}

// Quick Sort recursivo
void quickSort(int v[], int inicio, int fim)
{
    if (inicio < fim)
    {
        int p = particao(v, inicio, fim);

        quickSort(v, inicio, p - 1);
        quickSort(v, p + 1, fim);
    }
}

int main()
{
    int N;

    scanf("%d", &N);

    int v[N];

    // leitura dos MMRs
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &v[i]);
    }

    // ordenação
    quickSort(v, 0, N - 1);

    // saída
    for (int i = 0; i < N; i++)
    {
        printf("%d ", v[i]);
    }

    printf("\n");

    return 0;
}