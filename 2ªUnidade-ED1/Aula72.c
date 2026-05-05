#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int posicao;
    char nome[50];
} Piloto;

// Função para intercalar (merge)
void intercala(Piloto v[], int inicio, int meio, int fim)
{
    int i = inicio;
    int j = meio + 1;
    int k = 0;

    Piloto temp[fim - inicio + 1];

    while (i <= meio && j <= fim)
    {
        if (v[i].posicao <= v[j].posicao)
        {
            temp[k++] = v[i++];
        }
        else
        {
            temp[k++] = v[j++];
        }
    }

    while (i <= meio)
    {
        temp[k++] = v[i++];
    }

    while (j <= fim)
    {
        temp[k++] = v[j++];
    }

    for (i = inicio, k = 0; i <= fim; i++, k++)
    {
        v[i] = temp[k];
    }
}

// Merge Sort recursivo
void mergeSort(Piloto v[], int inicio, int fim)
{
    if (inicio < fim)
    {
        int meio = (inicio + fim) / 2;

        mergeSort(v, inicio, meio);
        mergeSort(v, meio + 1, fim);

        intercala(v, inicio, meio, fim);
    }
}

int main()
{
    int N;

    scanf("%d", &N);

    Piloto pilotos[N];

    // leitura dos dados
    for (int i = 0; i < N; i++)
    {
        scanf("%d %s", &pilotos[i].posicao, pilotos[i].nome);
    }

    // ordenação
    mergeSort(pilotos, 0, N - 1);

    // saída
    for (int i = 0; i < N; i++)
    {
        printf("%d %s\n", pilotos[i].posicao, pilotos[i].nome);
    }

    return 0;
}