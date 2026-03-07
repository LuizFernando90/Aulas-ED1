#include <stdio.h>

// Função para ler o cenário
void ler_cenario(int n, int *cenario)
{
    for (int i = 0; i < n; i++)
    {
        scanf("%d", (cenario + i));
    }
}

int main()
{

    int n;

    // Ler o número de blocos
    printf("Digite o numero de blocos do cenario: ");
    scanf("%d", &n);

    int cenario[n];

    // Chamando a função para preencher o vetor
    ler_cenario(n, cenario);

    // Procurando o primeiro bloco de plataforma
    for (int i = 0; i < n; i++)
    {
        if (cenario[i] == 1)
        {
            cenario[i] = 2; // Coloca o power-up
            break;
        }
    }

    // Imprimindo o cenário modificado
    for (int i = 0; i < n; i++)
    {
        printf("%d ", cenario[i]);
    }

    return 0;
}