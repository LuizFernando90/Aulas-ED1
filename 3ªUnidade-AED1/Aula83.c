#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int matricula;
    char nome[50];
} Jogador;

typedef struct No
{
    Jogador dado;
    struct No *prox;
} No;

typedef struct
{
    No *inicio;
} Lista;

void inserir_inicio(Lista *l, Jogador j)
{
    No *novo = (No *)malloc(sizeof(No));

    novo->dado = j;
    novo->prox = l->inicio;

    l->inicio = novo;
}

void inserir_fim(Lista *l, Jogador j)
{
    No *novo = (No *)malloc(sizeof(No));

    novo->dado = j;
    novo->prox = NULL;

    if (l->inicio == NULL)
    {
        l->inicio = novo;
        return;
    }

    No *aux = l->inicio;

    while (aux->prox != NULL)
    {
        aux = aux->prox;
    }

    aux->prox = novo;
}

void mostrar_fila(Lista *l)
{
    No *aux = l->inicio;

    if (aux == NULL)
    {
        printf("Fila vazia\n");
        return;
    }

    while (aux != NULL)
    {
        printf("%d %s\n",
               aux->dado.matricula,
               aux->dado.nome);

        aux = aux->prox;
    }
}

int main()
{
    Lista fila;
    fila.inicio = NULL;

    int opcao;

    do
    {
        printf("\n1 - Adicionar jogador no inicio\n");
        printf("2 - Adicionar jogador no fim\n");
        printf("3 - Mostrar fila\n");
        printf("4 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1)
        {
            Jogador j;

            printf("Matricula: ");
            scanf("%d", &j.matricula);

            printf("Nome: ");
            scanf(" %[^\n]", j.nome);

            inserir_inicio(&fila, j);
        }

        else if (opcao == 2)
        {
            Jogador j;

            printf("Matricula: ");
            scanf("%d", &j.matricula);

            printf("Nome: ");
            scanf(" %[^\n]", j.nome);

            inserir_fim(&fila, j);
        }

        else if (opcao == 3)
        {
            mostrar_fila(&fila);
        }

    } while (opcao != 4);

    return 0;
}