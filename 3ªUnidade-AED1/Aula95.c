#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int id;
    char tipo[50];
} Inimigo;

typedef struct No
{
    Inimigo dado;
    struct No *prox;
} No;

typedef struct
{
    No *inicio;
} Lista;

// Inserir no fim
void inserir_fim(Lista *lista, Inimigo inimigo)
{
    No *novo = (No *)malloc(sizeof(No));

    novo->dado = inimigo;
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
        printf("Nenhum inimigo ativo.\n");
        return;
    }

    No *aux = lista->inicio;

    printf("\n=== ONDA ATUAL ===\n");

    while (aux != NULL)
    {
        printf("ID: %d | Tipo: %s\n",
               aux->dado.id,
               aux->dado.tipo);

        aux = aux->prox;
    }
}

// Liberar lista antiga
void liberar_lista(Lista *lista)
{
    No *aux = lista->inicio;

    while (aux != NULL)
    {
        No *temp = aux;
        aux = aux->prox;
        free(temp);
    }

    lista->inicio = NULL;
}

// Criar nova lista
Lista criar_lista(int n)
{
    Lista nova_lista;
    nova_lista.inicio = NULL;

    Inimigo inimigo;

    for (int i = 0; i < n; i++)
    {
        printf("\nInimigo %d\n", i + 1);

        printf("ID: ");
        scanf("%d", &inimigo.id);

        printf("Tipo: ");
        scanf(" %[^\n]", inimigo.tipo);

        inserir_fim(&nova_lista, inimigo);
    }

    return nova_lista;
}

int main()
{
    Lista onda;
    onda.inicio = NULL;

    int opcao;

    do
    {
        printf("\n===== MENU =====\n");
        printf("1 - Iniciar nova onda\n");
        printf("2 - Mostrar inimigos\n");
        printf("3 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
        {
            int n;

            liberar_lista(&onda);

            printf("Quantidade de inimigos: ");
            scanf("%d", &n);

            onda = criar_lista(n);

            printf("Nova onda criada!\n");
            break;
        }

        case 2:
            mostrar_lista(&onda);
            break;

        case 3:
            printf("Encerrando...\n");
            break;

        default:
            printf("Opcao invalida!\n");
        }

    } while (opcao != 3);

    liberar_lista(&onda);

    return 0;
}