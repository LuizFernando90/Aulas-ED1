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
void contratar_mercenario(Lista *lista, Mercenario m)
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
void exibir_companhia(Lista *lista)
{
    if (lista->inicio == NULL)
    {
        printf("Companhia vazia.\n");
        return;
    }

    No *aux = lista->inicio;

    printf("\n=== COMPANHIA DE MERCENARIOS ===\n");

    while (aux != NULL)
    {
        printf("ID: %d | Nome: %s\n",
               aux->dado.id,
               aux->dado.nome);

        aux = aux->prox;
    }
}

// Liberar lista inteira
void demitir_todos_mercenarios(Lista *lista)
{
    No *atual = lista->inicio;
    No *proximo;

    while (atual != NULL)
    {
        proximo = atual->prox;

        free(atual);

        atual = proximo;
    }

    lista->inicio = NULL;

    printf("Todos os mercenarios foram demitidos.\n");
}

int main()
{
    Lista companhia;
    companhia.inicio = NULL;

    int opcao;

    do
    {
        printf("\n===== MENU =====\n");
        printf("1 - Contratar mercenario\n");
        printf("2 - Exibir companhia\n");
        printf("3 - Declarar falencia\n");
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

            contratar_mercenario(&companhia, m);
        }

        else if (opcao == 2)
        {
            exibir_companhia(&companhia);
        }

        else if (opcao == 3)
        {
            demitir_todos_mercenarios(&companhia);

            printf("Estado atual da companhia:\n");
            exibir_companhia(&companhia);
        }

    } while (opcao != 4);

    return 0;
}