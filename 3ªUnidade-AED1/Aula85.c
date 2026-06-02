#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int id;
    char nome[50];
} Item;

typedef struct No
{
    Item dado;
    struct No *prox;
} No;

typedef struct
{
    No *inicio;
} Lista;

void inserir_inicio(Lista *l, Item item)
{
    No *novo = (No *)malloc(sizeof(No));

    novo->dado = item;
    novo->prox = l->inicio;

    l->inicio = novo;
}

void inserir_fim(Lista *l, Item item)
{
    No *novo = (No *)malloc(sizeof(No));

    novo->dado = item;
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

int inserir_apos_id(Lista *l, Item item, int id)
{
    No *aux = l->inicio;

    while (aux != NULL)
    {
        if (aux->dado.id == id)
        {
            No *novo = (No *)malloc(sizeof(No));

            novo->dado = item;
            novo->prox = aux->prox;

            aux->prox = novo;

            return 1;
        }

        aux = aux->prox;
    }

    return 0;
}

void mostrar_inventario(Lista *l)
{
    No *aux = l->inicio;

    if (aux == NULL)
    {
        printf("Inventario vazio!\n");
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
    Lista inventario;
    inventario.inicio = NULL;

    int opcao;

    do
    {
        printf("\n1 - Inserir item no inicio\n");
        printf("2 - Inserir item no fim\n");
        printf("3 - Inserir catalisador apos fragmento\n");
        printf("4 - Mostrar inventario\n");
        printf("5 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1)
        {
            Item item;

            printf("ID: ");
            scanf("%d", &item.id);

            printf("Nome: ");
            scanf(" %[^\n]", item.nome);

            inserir_inicio(&inventario, item);
        }

        else if (opcao == 2)
        {
            Item item;

            printf("ID: ");
            scanf("%d", &item.id);

            printf("Nome: ");
            scanf(" %[^\n]", item.nome);

            inserir_fim(&inventario, item);
        }

        else if (opcao == 3)
        {
            Item catalisador;
            int id_fragmento;

            printf("ID do catalisador: ");
            scanf("%d", &catalisador.id);

            printf("Nome do catalisador: ");
            scanf(" %[^\n]", catalisador.nome);

            printf("Inserir apos o item de ID: ");
            scanf("%d", &id_fragmento);

            if (inserir_apos_id(&inventario,
                                catalisador,
                                id_fragmento))
            {
                printf("Catalisador inserido com sucesso!\n");
            }
            else
            {
                printf("Fragmento nao encontrado!\n");
            }
        }

        else if (opcao == 4)
        {
            mostrar_inventario(&inventario);
        }

    } while (opcao != 5);

    return 0;
}