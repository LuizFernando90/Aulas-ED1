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
        printf("\nGuilda vazia!\n");
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

// Salvar em arquivo binário
void salvar_guild_arquivo(Lista lista)
{
    FILE *arquivo;

    arquivo = fopen("guild_roster.bin", "wb");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    No *aux = lista.inicio;

    while (aux != NULL)
    {
        fwrite(&aux->dado,
               sizeof(Membro),
               1,
               arquivo);

        aux = aux->prox;
    }

    fclose(arquivo);

    printf("Guilda salva com sucesso!\n");
}

int main()
{
    Lista guilda;
    guilda.inicio = NULL;

    int opcao;

    do
    {
        printf("\n===== MENU =====\n");
        printf("1 - Adicionar membro\n");
        printf("2 - Mostrar guilda\n");
        printf("3 - Salvar guilda\n");
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

            inserir_fim(&guilda, m);
        }

        else if (opcao == 2)
        {
            mostrar_lista(&guilda);
        }

        else if (opcao == 3)
        {
            salvar_guild_arquivo(guilda);
        }

    } while (opcao != 4);

    return 0;
}