#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int id;
    char nome[50];
} Heroi;

typedef struct No
{
    Heroi dado;
    struct No *prox;
} No;

typedef struct
{
    No *inicio;
} Lista;

// Inserir no fim
void adicionar_heroi(Lista *lista, Heroi h)
{
    No *novo = (No *)malloc(sizeof(No));

    novo->dado = h;
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
void mostrar_herois(Lista *lista)
{
    No *aux = lista->inicio;

    if (aux == NULL)
    {
        printf("Guilda vazia!\n");
        return;
    }

    printf("\n=== HEROIS DA GUILDA ===\n");

    while (aux != NULL)
    {
        printf("ID: %d | Nome: %s\n",
               aux->dado.id,
               aux->dado.nome);

        aux = aux->prox;
    }
}

// Remover herói por ID
void dispensar_heroi(Lista *lista, int id)
{
    // Lista vazia
    if (lista->inicio == NULL)
    {
        printf("Nao ha herois cadastrados.\n");
        return;
    }

    No *atual = lista->inicio;
    No *anterior = NULL;

    // Procura o ID
    while (atual != NULL && atual->dado.id != id)
    {
        anterior = atual;
        atual = atual->prox;
    }

    // Não encontrou
    if (atual == NULL)
    {
        printf("Heroi com ID %d nao encontrado.\n", id);
        return;
    }

    // Remove primeiro nó
    if (anterior == NULL)
    {
        lista->inicio = atual->prox;
    }
    else
    {
        anterior->prox = atual->prox;
    }

    printf("Heroi %s removido da guilda.\n",
           atual->dado.nome);

    free(atual);
}

int main()
{
    Lista guilda;
    guilda.inicio = NULL;

    int opcao;

    do
    {
        printf("\n===== MENU =====\n");
        printf("1 - Adicionar Heroi\n");
        printf("2 - Mostrar Herois\n");
        printf("3 - Dispensar Heroi\n");
        printf("4 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1)
        {
            Heroi h;

            printf("ID: ");
            scanf("%d", &h.id);

            printf("Nome: ");
            scanf(" %[^\n]", h.nome);

            adicionar_heroi(&guilda, h);
        }

        else if (opcao == 2)
        {
            mostrar_herois(&guilda);
        }

        else if (opcao == 3)
        {
            int id;

            printf("Digite o ID do heroi: ");
            scanf("%d", &id);

            dispensar_heroi(&guilda, id);

            printf("\nLista atualizada:\n");
            mostrar_herois(&guilda);
        }

    } while (opcao != 4);

    return 0;
}