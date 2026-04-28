#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nome[50];
    int vida;
    int ataque;
} Campeao;

int main()
{
    FILE *arquivo = fopen("squad.dat", "wb");

    if (arquivo == NULL)
    {
        printf("Erro ao criar arquivo!\n");
        return 1;
    }

    Campeao squad[3] = {
        {"Garen", 620, 69},
        {"Lux", 530, 55},
        {"Ashe", 590, 61}};

    fwrite(squad, sizeof(Campeao), 3, arquivo);

    fclose(arquivo);

    printf("Arquivo criado!\n");

    return 0;
}