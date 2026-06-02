#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int id;
    char nome[100];
} Membro;

typedef struct No
{
    Membro dado;
    struct No *prox;
} No;

typedef struct
{
    No *inicio;
} Lista;

// Inserir no fim
void inserir_fim(Lista *lista, Membro m)
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

    printf("\n=== MEMBROS DA GUILDA ===\n");

    while (aux != NULL)
    {
        printf("ID: %d | Nome: %s\n",
               aux->dado.id,
               aux->dado.nome);

        aux = aux->prox;
    }
}

// Pesquisar por ID
No *pesquisar(Lista *lista, int id)
{
    No *aux = lista->inicio;

    while (aux != NULL)
    {
        if (aux->dado.id == id)
        {
            return aux;
        }

        aux = aux->prox;
    }

    return NULL;
}

// Alterar nome
void alterar_nome(Lista *lista, int id, char novo_nome[])
{
    No *encontrado = pesquisar(lista, id);

    if (encontrado == NULL)
    {
        printf("Membro nao encontrado.\n");
        return;
    }

    strcpy(encontrado->dado.nome, novo_nome);

    printf("Nome alterado com sucesso.\n");
}

int main()
{
    Lista lista;
    lista.inicio = NULL;

    int opcao;

    do
    {
        printf("\n===== MENU =====\n");
        printf("1 - Adicionar membro\n");
        printf("2 - Mostrar membros\n");
        printf("3 - Alterar nome\n");
        printf("4 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1)
        {
            Membro m;

            printf("ID: ");
            scanf("%d", &m.id);

            printf("Nome: ");
            scanf(" %[^\n]", m.nome);

            inserir_fim(&lista, m);
        }

        else if (opcao == 2)
        {
            mostrar_lista(&lista);
        }

        else if (opcao == 3)
        {
            int id;
            char novo_nome[100];

            printf("ID do membro: ");
            scanf("%d", &id);

            printf("Novo nome: ");
            scanf(" %[^\n]", novo_nome);

            alterar_nome(&lista, id, novo_nome);

            printf("\nLista atualizada:\n");
            mostrar_lista(&lista);
        }

    } while (opcao != 4);

    return 0;
}