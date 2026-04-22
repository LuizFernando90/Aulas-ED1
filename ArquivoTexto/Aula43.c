#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nome[50];
    int vida;
    int ataque;
} Inimigo;

int main()
{
    FILE *arquivo;
    Inimigo inimigo_atual, mais_forte;

    // Abrir o arquivo
    arquivo = fopen("wave_data.txt", "r");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    int primeiro = 1;

    // Leitura do arquivo
    while (fscanf(arquivo, "%s %d %d", inimigo_atual.nome,
                  &inimigo_atual.vida, &inimigo_atual.ataque) != EOF)
    {

        if (primeiro == 1)
        {
            mais_forte = inimigo_atual;
            primeiro = 0;
        }
        else
        {
            if (inimigo_atual.ataque > mais_forte.ataque)
            {
                mais_forte = inimigo_atual;
            }
        }
    }

    // Exibir resultado
    printf("Maior Ameaca: %s, Vida: %d, Ataque: %d\n",
           mais_forte.nome,
           mais_forte.vida,
           mais_forte.ataque);

    // Fechar arquivo
    fclose(arquivo);

    return 0;
}