#include <stdio.h>
#include <stdlib.h>

// Struct do inimigo
typedef struct
{
    char nome[50];
    float hp;
    float atk;
} Inimigo;

int main()
{
    FILE *arquivo;
    Inimigo inimigos[3];
    int i;

    // Abrir arquivo
    arquivo = fopen("inimigos.txt", "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    // Ler os dados do arquivo
    for (i = 0; i < 3; i++)
    {
        fscanf(arquivo, "%s %f %f",
               inimigos[i].nome,
               &inimigos[i].hp,
               &inimigos[i].atk);
    }

    // Processar e mostrar inimigos elite
    printf("Inimigos Elite:\n");

    for (i = 0; i < 3; i++)
    {
        float nivel_ameaca = inimigos[i].hp + inimigos[i].atk;

        if (nivel_ameaca >= 200)
        {
            printf("%s - Nivel de Ameaca: %.1f\n",
                   inimigos[i].nome,
                   nivel_ameaca);
        }
    }

    // Fechar arquivo
    fclose(arquivo);

    return 0;
}