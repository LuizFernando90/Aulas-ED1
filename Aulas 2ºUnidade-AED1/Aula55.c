#include <stdio.h>
#include <string.h>

// Struct do jogador
struct Jogador
{
    int id;
    char nickname[50];
    int reputacao;
};

// Função de busca binária
int buscaBinaria(struct Jogador vet[], int n, int id_busca)
{
    int inicio = 0, fim = n - 1;

    while (inicio <= fim)
    {
        int meio = (inicio + fim) / 2;

        if (vet[meio].id == id_busca)
        {
            return meio;
        }
        else if (vet[meio].id < id_busca)
        {
            inicio = meio + 1;
        }
        else
        {
            fim = meio - 1;
        }
    }

    return -1; // não encontrado
}

int main()
{
    int n;

    printf("Digite o numero de jogadores: ");
    scanf("%d", &n);

    struct Jogador jogadores[n];

    // Cadastro dos jogadores (já em ordem crescente de ID)
    for (int i = 0; i < n; i++)
    {
        printf("\nJogador %d\n", i + 1);

        printf("ID: ");
        scanf("%d", &jogadores[i].id);

        printf("Nickname: ");
        scanf("%s", jogadores[i].nickname);

        printf("Reputacao: ");
        scanf("%d", &jogadores[i].reputacao);
    }

    int opcao;

    // Menu
    do
    {
        printf("\n1 - Adicionar Reputacao\n");
        printf("2 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1)
        {
            int id_busca;
            printf("Digite o ID do jogador: ");
            scanf("%d", &id_busca);

            int pos = buscaBinaria(jogadores, n, id_busca);

            if (pos != -1)
            {
                jogadores[pos].reputacao += 100;

                printf("Nickname: %s, Nova Reputacao: %d\n",
                       jogadores[pos].nickname,
                       jogadores[pos].reputacao);
            }
            else
            {
                printf("Jogador com ID %d nao encontrado.\n", id_busca);
            }
        }

    } while (opcao != 2);

    return 0;
}