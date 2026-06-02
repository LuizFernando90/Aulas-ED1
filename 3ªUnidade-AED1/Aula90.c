#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int id;
    char nome[100];
} Ward;

typedef struct No
{
    Ward dado;
    struct No *prox;
} No;

typedef struct
{
    No *inicio;
} Lista;

// Inserir no fim
void adicionar_ward(Lista *lista, Ward w)
{
    No *novo = (No *)malloc(sizeof(No));

    novo->dado = w;
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

// Mostrar wards
void mostrar_wards(Lista *lista)
{
    if (lista->inicio == NULL)
    {
        printf("Nenhum ward ativo.\n");
        return;
    }

    No *aux = lista->inicio;

    printf("\n=== WARDS ATIVOS ===\n");

    while (aux != NULL)
    {
        printf("ID: %d | Nome: %s\n",
               aux->dado.id,
               aux->dado.nome);

        aux = aux->prox;
    }
}

// Ward Shatter
void deletar_apos(Lista *lista, int id)
{
    // Lista vazia
    if (lista->inicio == NULL)
    {
        printf("A lista esta vazia.\n");
        return;
    }

    No *aux = lista->inicio;

    // Procurar o ID
    while (aux != NULL && aux->dado.id != id)
    {
        aux = aux->prox;
    }

    // ID não encontrado
    if (aux == NULL)
    {
        printf("Ward de referencia nao encontrado.\n");
        return;
    }

    // É o último nó
    if (aux->prox == NULL)
    {
        printf("Nao existe ward apos este.\n");
        return;
    }

    No *remover = aux->prox;

    aux->prox = remover->prox;

    printf("Ward destruido: %s\n",
           remover->dado.nome);

    free(remover);
}

int main()
{
    Lista lista;
    lista.inicio = NULL;

    int opcao;

    do
    {
        printf("\n===== MENU =====\n");
        printf("1 - Adicionar Ward\n");
        printf("2 - Lancar Ward Shatter\n");
        printf("3 - Mostrar Wards Ativos\n");
        printf("4 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1)
        {
            Ward w;

            printf("ID: ");
            scanf("%d", &w.id);

            printf("Nome: ");
            scanf(" %[^\n]", w.nome);

            adicionar_ward(&lista, w);
        }

        else if (opcao == 2)
        {
            int id;

            printf("ID do ward de referencia: ");
            scanf("%d", &id);

            deletar_apos(&lista, id);
        }

        else if (opcao == 3)
        {
            mostrar_wards(&lista);
        }

    } while (opcao != 4);

    return 0;
}