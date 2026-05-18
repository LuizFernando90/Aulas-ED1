#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char nome[50];
    int nivel;
    int highScore;
} PlayerProfile;

int main()
{
    FILE *arquivo;
    PlayerProfile p;

    arquivo = fopen("profiles.dat", "rb");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    // Lê até o fim do arquivo
    while (fread(&p, sizeof(PlayerProfile), 1, arquivo) == 1)
    {

        printf("Jogador: %s - Rank: ", p.nome);

        if (p.highScore > 10000)
        {
            printf("Mestre do Jogo\n");
        }
        else if (p.highScore > 5000)
        {
            printf("Veterano\n");
        }
        else
        {
            printf("Aspirante\n");
        }
    }

    fclose(arquivo);

    return 0;
}