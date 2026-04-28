#include <stdio.h>
#include <stdlib.h>

// Definição da struct
struct Moeda
{
    int posicao_x;
    int posicao_y;
    int valor;
};

int main()
{
    int n, i;
    int total_pontos = 0;

    // Pergunta quantidade de moedas
    printf("Quantas moedas existem no nivel? ");
    scanf("%d", &n);

    // Alocação dinâmica
    struct Moeda *moedas;
    moedas = (struct Moeda *)malloc(n * sizeof(struct Moeda));

    // Verificação de erro
    if (moedas == NULL)
    {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    // Cadastro das moedas
    for (i = 0; i < n; i++)
    {
        printf("Moeda %d\n", i + 1);
        printf("Posicao X: ");
        scanf("%d", &moedas[i].posicao_x);
        printf("Posicao Y: ");
        scanf("%d", &moedas[i].posicao_y);
        printf("Valor: ");
        scanf("%d", &moedas[i].valor);
    }

    // Soma dos pontos
    for (i = 0; i < n; i++)
    {
        total_pontos += moedas[i].valor;
    }

    // Exibição do total
    printf("Pontuacao maxima do nivel: %d\n", total_pontos);

    // Liberação de memória
    free(moedas);

    return 0;
}