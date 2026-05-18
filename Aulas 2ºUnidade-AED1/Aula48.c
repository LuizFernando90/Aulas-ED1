#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char nome[50];
    int vida;
    int ataque;
} Campeao;

int main()
{
    FILE *arquivo;
    Campeao squad[3];
    int i, tanque = 0;

    // Abrir arquivo binário para leitura
    arquivo = fopen("squad.dat", "rb");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    // Ler os 3 campeões de uma vez
    fread(squad, sizeof(Campeao), 3, arquivo);

    // Fechar arquivo
    fclose(arquivo);

    // Encontrar o campeão com maior vida
    for (i = 1; i < 3; i++)
    {
        if (squad[i].vida > squad[tanque].vida)
        {
            tanque = i;
        }
    }

    // Exibir resultado
    printf("%s: Tanque do esquadrao.\n", squad[tanque].nome);

    return 0;
}