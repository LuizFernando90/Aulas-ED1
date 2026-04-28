#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char nome[50];
    int vida;
    int ataque;
} Unidade;

int main()
{
    int n, i, maior;

    printf("Digite a quantidade de unidades: ");
    scanf("%d", &n);

    // Alocação dinâmica do vetor
    Unidade *esquadrao = (Unidade *)malloc(n * sizeof(Unidade));

    if (esquadrao == NULL)
    {
        printf("Erro na alocacao de memoria!\n");
        return 1;
    }

    // Leitura das unidades
    for (i = 0; i < n; i++)
    {
        printf("\nUnidade %d\n", i + 1);

        printf("Nome: ");
        scanf("%s", esquadrao[i].nome);

        printf("Vida: ");
        scanf("%d", &esquadrao[i].vida);

        printf("Ataque: ");
        scanf("%d", &esquadrao[i].ataque);
    }

    // Salvar no arquivo binário
    FILE *arquivo = fopen("squad.dat", "wb");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        free(esquadrao);
        return 1;
    }

    fwrite(esquadrao, sizeof(Unidade), n, arquivo);

    fclose(arquivo);

    // Encontrar unidade com maior ataque
    maior = 0;

    for (i = 1; i < n; i++)
    {
        if (esquadrao[i].ataque > esquadrao[maior].ataque)
        {
            maior = i;
        }
    }

    printf("\nUnidade com maior ATK: %s\n", esquadrao[maior].nome);

    // Liberar memória
    free(esquadrao);

    return 0;
}