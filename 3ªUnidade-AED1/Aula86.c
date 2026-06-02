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

void inserir_fim(Lista *l, Heroi h)
{
    No *novo = (No *)malloc(sizeof(No));

    novo->dado = h;
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

int inserir_antes(Lista *l, Heroi guarda, int id_vip)
{
    if (l->inicio == NULL)
    {
        return 0;
    }

    // VIP é o primeiro da lista
    if (l->inicio->dado.id == id_vip)
    {
        No *novo = (No *)malloc(sizeof(No));

        novo->dado = guarda;
        novo->prox = l->inicio;

        l->inicio = novo;

        return 1;
    }

    No *anterior = l->inicio;
    No *atual = l->inicio->prox;

    while (atual != NULL)
    {
        if (atual->dado.id == id_vip)
        {
            No *novo = (No *)malloc(sizeof(No));

            novo->dado = guarda;
            novo->prox = atual;

            anterior->prox = novo;

            return 1;
        }

        anterior = atual;
        atual = atual->prox;
    }

    return 0;
}

void mostrar_formacao(Lista *l)
{
    No *aux = l->inicio;

    if (aux == NULL)
    {
        printf("Formacao vazia!\n");
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
    Lista formacao;
    formacao.inicio = NULL;

    int opcao;

    do
    {
        printf("\n1 - Adicionar Heroi no Fim\n");
        printf("2 - Adicionar Guarda-Costas\n");
        printf("3 - Mostrar Formacao\n");
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

            inserir_fim(&formacao, h);
        }

        else if (opcao == 2)
        {
            Heroi guarda;
            int id_vip;

            printf("ID do Guarda-Costas: ");
            scanf("%d", &guarda.id);

            printf("Nome do Guarda-Costas: ");
            scanf(" %[^\n]", guarda.nome);

            printf("ID do VIP: ");
            scanf("%d", &id_vip);

            if (inserir_antes(&formacao, guarda, id_vip))
            {
                printf("Guarda-Costas inserido com sucesso!\n");
            }
            else
            {
                printf("VIP nao encontrado!\n");
            }
        }

        else if (opcao == 3)
        {
            mostrar_formacao(&formacao);
        }

    } while (opcao != 4);

    return 0;
}