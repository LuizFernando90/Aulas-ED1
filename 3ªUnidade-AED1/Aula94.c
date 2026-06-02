#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int id;
    char nome[50];
} Mercenario;

typedef struct No
{
    Mercenario dado;
    struct No *prox;
} No;

typedef struct
{
    No *inicio;
} Lista;

// Inserir no fim
void inserir_fim(Lista *lista, Mercenario m)
{
    No *novo = (No *)malloc(sizeof(No));

    novo->dado = m;
    novo->prox = NULL;

    if (lista->inicio == NULL)
    {
        lista->inicio = novo;
        return;
    }

    No *aux = lista->inicio;

    while (aux->prox != NULL)
    {
        aux = aux->prox;
    }

    aux->prox = novo;
}

// Mostrar lista
void mostrar_lista(Lista *lista)
{
    if (lista->inicio == NULL)
    {
        printf("Guilda vazia.\n");
        return;
    }

    No *aux = lista->inicio;

    printf("\n=== MERCENARIOS ===\n");

    while (aux != NULL)
    {
        printf("ID: %d | Nome: %s\n",
               aux->dado.id,
               aux->dado.nome);

        aux = aux->prox;
    }
}

// Função tamanho
int tamanho(Lista *lista)
{
    int contador = 0;

    No *aux = lista->inicio;

    while (aux != NULL)
    {
        contador++;
        aux = aux->prox;
    }

    return contador;
}

int main()
{
    Lista guilda;
    guilda.inicio = NULL;

    int opcao;

    do
    {
        printf("\n===== MENU =====\n");
        printf("1 - Contratar mercenario\n");
        printf("2 - Mostrar mercenarios\n");
        printf("3 - Mostrar tamanho da guilda\n");
        printf("4 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1)
        {
            Mercenario m;

            printf("ID: ");
            scanf("%d", &m.id);

            printf("Nome: ");
            scanf(" %[^\n]", m.nome);

            inserir_fim(&guilda, m);
        }

        else if (opcao == 2)
        {
            mostrar_lista(&guilda);
        }

        else if (opcao == 3)
        {
            printf("Total de mercenarios: %d\n",
                   tamanho(&guilda));
        }

    } while (opcao != 4);

    return 0;
}