#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int id;
    int nivel_ameaca;
} Nave;

// Função para intercalar (merge)
void merge(Nave vetor[], int inicio, int meio, int fim)
{
    int i = inicio;
    int j = meio + 1;
    int k = 0;

    Nave temp[fim - inicio + 1];

    while (i <= meio && j <= fim)
    {
        if (vetor[i].nivel_ameaca <= vetor[j].nivel_ameaca)
        {
            temp[k++] = vetor[i++];
        }
        else
        {
            temp[k++] = vetor[j++];
        }
    }

    while (i <= meio)
    {
        temp[k++] = vetor[i++];
    }

    while (j <= fim)
    {
        temp[k++] = vetor[j++];
    }

    for (i = inicio, k = 0; i <= fim; i++, k++)
    {
        vetor[i] = temp[k];
    }
}

// Merge Sort
void mergeSort(Nave vetor[], int inicio, int fim)
{
    if (inicio < fim)
    {
        int meio = (inicio + fim) / 2;

        mergeSort(vetor, inicio, meio);
        mergeSort(vetor, meio + 1, fim);

        merge(vetor, inicio, meio, fim);
    }
}

int main()
{
    int N;

    scanf("%d", &N);

    Nave vetor[N];

    for (int i = 0; i < N; i++)
    {
        scanf("%d %d", &vetor[i].id, &vetor[i].nivel_ameaca);
    }

    mergeSort(vetor, 0, N - 1);

    // Imprime apenas os IDs ordenados
    for (int i = 0; i < N; i++)
    {
        printf("%d ", vetor[i].id);
    }

    printf("\n");

    return 0;
}