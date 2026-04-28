#include <stdio.h>
#include <string.h>

// Struct do personagem
struct Personagem
{
    int id;
    char nome[50];
    int forca;
    int agilidade;
    int inteligencia;
};

// Função de busca linear
int buscarPersonagem(struct Personagem vet[], int n, int id_busca)
{
    for (int i = 0; i < n; i++)
    {
        if (vet[i].id == id_busca)
        {
            return i; // retorna posição
        }
    }
    return -1; // não encontrado
}

int main()
{
    int n;

    printf("Digite o numero de personagens: ");
    scanf("%d", &n);

    struct Personagem personagens[n];

    // Cadastro dos personagens
    for (int i = 0; i < n; i++)
    {
        printf("\nPersonagem %d\n", i + 1);

        printf("ID: ");
        scanf("%d", &personagens[i].id);

        printf("Nome: ");
        scanf("%s", personagens[i].nome);

        printf("Forca, Agilidade e Inteligencia: ");
        scanf("%d %d %d",
              &personagens[i].forca,
              &personagens[i].agilidade,
              &personagens[i].inteligencia);
    }

    int opcao;

    // Menu
    do
    {
        printf("\n1 - Consultar Personagem\n");
        printf("2 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1)
        {
            int id_busca;
            printf("Digite a ID do personagem: ");
            scanf("%d", &id_busca);

            int pos = buscarPersonagem(personagens, n, id_busca);

            if (pos != -1)
            {
                float media = (personagens[pos].forca +
                               personagens[pos].agilidade +
                               personagens[pos].inteligencia) /
                              3.0;

                printf("Nome: %s\n", personagens[pos].nome);
                printf("Media de atributos: %.2f\n", media);
            }
            else
            {
                printf("Personagem nao encontrado.\n");
            }
        }

    } while (opcao != 2);

    return 0;
}