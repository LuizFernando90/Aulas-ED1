#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int id;
    char nome[50];
} Aventureiro;

typedef struct No
{
    Aventureiro dado;
    struct No *prox;
} No;

typedef struct
{
    No *inicio;
} Lista;

void inserir_inicio(Lista *l, Aventureiro a)
{
    No *novo = (No *)malloc(sizeof(No));

    novo->dado = a;
    novo->prox = l->inicio;

    l->inicio = novo;
}

void mostrar_grupo(Lista *l)
{
    No *aux = l->inicio;

    if (aux == NULL)
    {
        printf("Grupo vazio\n");
        return;
    }

    while (aux != NULL)
    {
        printf("%d %s\n",
               aux->dado.id,
               aux->dado.nome);

        aux = aux->prox;
    }
}

int main()
{
    Lista grupo;
    grupo.inicio = NULL;

    int opcao;

    do
    {
        printf("\n1 - Adicionar aventureiro\n");
        printf("2 - Mostrar grupo\n");
        printf("3 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1)
        {
            Aventureiro a;

            printf("ID: ");
            scanf("%d", &a.id);

            printf("Nome: ");
            scanf(" %[^\n]", a.nome);

            inserir_inicio(&grupo, a);
        }

        else if (opcao == 2)
        {
            mostrar_grupo(&grupo);
        }

    } while (opcao != 3);

    return 0;
}