#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int id;
    char descricao[100];
} Etapa;

typedef struct No
{
    Etapa dado;
    struct No *prox;
} No;

typedef struct
{
    No *inicio;
} Lista;

// Inserir no fim
void inserir_fim(Lista *lista, Etapa e)
{
    No *novo = (No *)malloc(sizeof(No));

    novo->dado = e;
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

// Mostrar etapas
void mostrar_etapas(Lista *lista)
{
    if (lista->inicio == NULL)
    {
        printf("Missao sem etapas.\n");
        return;
    }

    No *aux = lista->inicio;

    printf("\n=== ETAPAS DA MISSAO ===\n");

    while (aux != NULL)
    {
        printf("ID: %d | %s\n",
               aux->dado.id,
               aux->dado.descricao);

        aux = aux->prox;
    }
}

// Deletar antes de um ID
void deletar_antes(Lista *lista, int id)
{
    // Lista vazia
    if (lista->inicio == NULL)
    {
        printf("Lista vazia.\n");
        return;
    }

    // ID está no primeiro nó
    if (lista->inicio->dado.id == id)
    {
        printf("Nao existe etapa anterior.\n");
        return;
    }

    No *anterior = NULL;
    No *atual = lista->inicio;
    No *referencia = lista->inicio->prox;

    while (referencia != NULL && referencia->dado.id != id)
    {
        anterior = atual;
        atual = referencia;
        referencia = referencia->prox;
    }

    // ID não encontrado
    if (referencia == NULL)
    {
        printf("Etapa nao encontrada.\n");
        return;
    }

    // Caso especial:
    // remover o primeiro nó
    if (anterior == NULL)
    {
        lista->inicio = referencia;
        free(atual);

        printf("Etapa anterior removida.\n");
        return;
    }

    // Caso geral
    anterior->prox = referencia;
    free(atual);

    printf("Etapa anterior removida.\n");
}

int main()
{
    Lista lista;
    lista.inicio = NULL;

    int opcao;

    do
    {
        printf("\n===== MENU =====\n");
        printf("1 - Inserir etapa\n");
        printf("2 - Mostrar etapas\n");
        printf("3 - Deletar etapa ANTES de um ID\n");
        printf("4 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1)
        {
            Etapa e;

            printf("ID: ");
            scanf("%d", &e.id);

            printf("Descricao: ");
            scanf(" %[^\n]", e.descricao);

            inserir_fim(&lista, e);
        }

        else if (opcao == 2)
        {
            mostrar_etapas(&lista);
        }

        else if (opcao == 3)
        {
            int id;

            printf("Digite o ID de referencia: ");
            scanf("%d", &id);

            deletar_antes(&lista, id);

            printf("\nLista atualizada:\n");
            mostrar_etapas(&lista);
        }

    } while (opcao != 4);

    return 0;
}