#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função de partição com pivô aleatório
int particao(int v[], int inicio, int fim)
{
    // escolhe índice aleatório
    int indice_pivo = inicio + rand() % (fim - inicio + 1);

    // troca o pivô escolhido com o último elemento
    int temp = v[indice_pivo];
    v[indice_pivo] = v[fim];
    v[fim] = temp;

    int pivo = v[fim];
    int i = inicio - 1;

    for (int j = inicio; j < fim; j++)
    {
        if (v[j] <= pivo)
        {
            i++;
            // troca
            int aux = v[i];
            v[i] = v[j];
            v[j] = aux;
        }
    }

    // coloca o pivô na posição correta
    int aux = v[i + 1];
    v[i + 1] = v[fim];
    v[fim] = aux;

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

    // leitura
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &v[i]);
    }

    // inicializa o gerador de números aleatórios
    srand(time(NULL));

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