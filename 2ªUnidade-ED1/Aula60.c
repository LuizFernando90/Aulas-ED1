#include <stdio.h>
#include <stdlib.h>

// Definição da struct
typedef struct
{
    int posicao_x;
    int posicao_y;
    int valor;
} Moeda;

int main()
{
    int n, i;
    int total_pontos = 0;

    // Quantidade de moedas
    printf("Digite a quantidade de moedas: ");
    scanf("%d", &n);

    // Alocação dinâmica
    Moeda *moedas = (Moeda *)malloc(n * sizeof(Moeda));

    // Verificação de erro
    if (moedas == NULL)
    {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    // Cadastro das moedas
    for (i = 0; i < n; i++)
    {
        printf("\nMoeda %d:\n", i + 1);

        printf("Posicao X: ");
        scanf("%d", &moedas[i].posicao_x);

        printf("Posicao Y: ");
        scanf("%d", &moedas[i].posicao_y);

        printf("Valor: ");
        scanf("%d", &moedas[i].valor);
    }

    // Cálculo do total de pontos
    for (i = 0; i < n; i++)
    {
        total_pontos += moedas[i].valor;
    }

    // Resultado final
    printf("\nPontuacao maxima do nivel: %d\n", total_pontos);

    // Liberação de memória
    free(moedas);

    return 0;
}