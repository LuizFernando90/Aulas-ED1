#include <stdio.h>

typedef struct
{
    int id;
    int pontuacao;
} Jogador;

// Partição (Lomuto) para ordem DECRESCENTE
int particao(Jogador v[], int inicio, int fim)
{
    int pivo = v[fim].pontuacao;
    int i = inicio - 1;

    for (int j = inicio; j < fim; j++)
    {
        // Aqui muda: queremos MAIOR primeiro
        if (v[j].pontuacao >= pivo)
        {
            i++;

            // troca estruturas
            Jogador temp = v[i];
            v[i] = v[j];
            v[j] = temp;
        }
    }

    // coloca o pivô na posição correta
    Jogador temp = v[i + 1];
    v[i + 1] = v[fim];
    v[fim] = temp;

    return i + 1;
}

// Quick Sort recursivo
void quickSort(Jogador v[], int inicio, int fim)
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
    int n;

    scanf("%d", &n);

    Jogador v[n];

    // leitura dos dados
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &v[i].id, &v[i].pontuacao);
    }

    // ordenação
    quickSort(v, 0, n - 1);

    // saída
    for (int i = 0; i < n; i++)
    {
        printf("%d %d\n", v[i].id, v[i].pontuacao);
    }

    return 0;
}