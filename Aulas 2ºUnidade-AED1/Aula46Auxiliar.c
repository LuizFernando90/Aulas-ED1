#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nome[50];
    int nivel;
    int highScore;
} PlayerProfile;

int main()
{
    FILE *arquivo = fopen("profiles.dat", "wb");

    if (arquivo == NULL)
    {
        printf("Erro ao criar arquivo!\n");
        return 1;
    }

    PlayerProfile jogadores[3] = {
        {"Arthur", 10, 12000},
        {"Luna", 8, 7000},
        {"Kai", 5, 3000}};

    fwrite(jogadores, sizeof(PlayerProfile), 3, arquivo);

    fclose(arquivo);

    printf("Arquivo criado com sucesso!\n");

    return 0;
}