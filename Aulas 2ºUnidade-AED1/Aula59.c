#include <stdio.h>
#include <string.h>

// Struct do monstro
struct Monstro
{
    int id;
    char nome[50];
    int hp;
    int ataque;
};

// Busca binária recursiva
int buscaBinariaRecursiva(struct Monstro vet[], int inicio, int fim, int id_busca)
{
    if (inicio > fim)
    {
        return -1; // não encontrado
    }

    int meio = (inicio + fim) / 2;

    if (vet[meio].id == id_busca)
    {
        return meio;
    }
    else if (id_busca < vet[meio].id)
    {
        return buscaBinariaRecursiva(vet, inicio, meio - 1, id_busca);
    }
    else
    {
        return buscaBinariaRecursiva(vet, meio + 1, fim, id_busca);
    }
}

int main()
{
    int n;

    printf("Digite o numero de monstros: ");
    scanf("%d", &n);

    struct Monstro monstros[n];

    // Cadastro (já ordenado por ID)
    for (int i = 0; i < n; i++)
    {
        printf("\nMonstro %d\n", i + 1);

        printf("ID: ");
        scanf("%d", &monstros[i].id);

        printf("Nome: ");
        scanf("%s", monstros[i].nome);

        printf("HP e Ataque: ");
        scanf("%d %d", &monstros[i].hp, &monstros[i].ataque);
    }

    int id_busca;

    // Loop de busca
    while (1)
    {
        printf("\nDigite o ID para buscar (0 para sair): ");
        scanf("%d", &id_busca);

        if (id_busca == 0)
        {
            break;
        }

        int pos = buscaBinariaRecursiva(monstros, 0, n - 1, id_busca);

        if (pos != -1)
        {
            printf("Monstro Encontrado: %s (ID: %d) - HP: %d, Ataque: %d\n",
                   monstros[pos].nome,
                   monstros[pos].id,
                   monstros[pos].hp,
                   monstros[pos].ataque);
        }
        else
        {
            printf("Monstro com ID %d nao encontrado.\n", id_busca);
        }
    }

    return 0;
}