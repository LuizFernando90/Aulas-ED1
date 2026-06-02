#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int id;
    char titulo[50];
    char status[20];
} Missao;

typedef struct No
{
    Missao dado;
    struct No *prox;
} No;

typedef struct
{
    No *inicio;
} Lista;

void inserir_fim(Lista *l, Missao m)
{
    No *novo = (No *)malloc(sizeof(No));

    novo->dado = m;
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

void mostrar_missoes(Lista *l)
{
    No *aux = l->inicio;

    if (aux == NULL)
    {
        printf("Nenhuma missao cadastrada!\n");
        return;
    }

    while (aux != NULL)
    {
        printf("ID: %d\n", aux->dado.id);
        printf("Titulo: %s\n", aux->dado.titulo);
        printf("Status: %s\n\n", aux->dado.status);

        aux = aux->prox;
    }
}

No *pesquisar_missao(Lista *l, int id)
{
    No *aux = l->inicio;

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

int main()
{
    Lista diario;
    diario.inicio = NULL;

    int opcao;

    do
    {
        printf("\n1 - Adicionar Missao\n");
        printf("2 - Mostrar Missoes\n");
        printf("3 - Buscar Missao por ID\n");
        printf("4 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1)
        {
            Missao m;

            printf("ID: ");
            scanf("%d", &m.id);

            printf("Titulo: ");
            scanf(" %[^\n]", m.titulo);

            printf("Status: ");
            scanf(" %[^\n]", m.status);

            inserir_fim(&diario, m);
        }

        else if (opcao == 2)
        {
            mostrar_missoes(&diario);
        }

        else if (opcao == 3)
        {
            int id;

            printf("Digite o ID da missao: ");
            scanf("%d", &id);

            No *resultado = pesquisar_missao(&diario, id);

            if (resultado != NULL)
            {
                printf("\nMissao encontrada!\n");
                printf("ID: %d\n", resultado->dado.id);
                printf("Titulo: %s\n", resultado->dado.titulo);
                printf("Status: %s\n", resultado->dado.status);
            }
            else
            {
                printf("Missao nao encontrada!\n");
            }
        }

    } while (opcao != 4);

    return 0;
}