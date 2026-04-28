#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nome[50];
    int nivel;
    float vida;
    float mana;
} Personagem;

int main()
{
    int opcao;

    do
    {
        printf("\n1 - Criar Novo Personagem\n");
        printf("2 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1)
        {
            Personagem p;

            printf("Nome: ");
            scanf("%s", p.nome);

            printf("Nivel: ");
            scanf("%d", &p.nivel);

            printf("Vida: ");
            scanf("%f", &p.vida);

            printf("Mana: ");
            scanf("%f", &p.mana);

            FILE *arquivo = fopen("savegame.sav", "wb");

            if (arquivo == NULL)
            {
                printf("Erro ao abrir arquivo!\n");
                return 1;
            }

            fwrite(&p, sizeof(Personagem), 1, arquivo);

            fclose(arquivo);

            printf("Personagem salvo com sucesso!\n");
        }

    } while (opcao != 2);

    return 0;
}