#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int id;
    char nickname[50];
} Jogador;

typedef struct No
{
    Jogador dado;
    struct No *prox;
} No;

typedef struct
{
    No *inicio;
    No *fim;
} Fila;

// Inicializa a fila
void inicializar(Fila *f)
{
    f->inicio = NULL;
    f->fim = NULL;
}

// Inserir no fim da fila (Enqueue)
void inserir(Fila *f, Jogador j)
{
    No *novo = (No *)malloc(sizeof(No));

    if (novo == NULL)
    {
        printf("Erro de memoria!\n");
        return;
    }

    novo->dado = j;
    novo->prox = NULL;

    // Fila vazia
    if (f->inicio == NULL)
    {
        f->inicio = novo;
        f->fim = novo;
    }
    else
    {
        f->fim->prox = novo;
        f->fim = novo;
    }

    printf("Jogador adicionado na fila com sucesso!\n");
}

// Mostrar fila
void mostrar(Fila *f)
{
    if (f->inicio == NULL)
    {
        printf("\nA fila de matchmaking esta vazia.\n");
        return;
    }

    No *aux = f->inicio;

    printf("\n===== FILA DE MATCHMAKING =====\n");

    while (aux != NULL)
    {
        printf("ID: %d\n", aux->dado.id);
        printf("Nickname: %s\n", aux->dado.nickname);
        printf("------------------------\n");

        aux = aux->prox;
    }
}

// Liberar memória da fila
void liberar_fila(Fila *f)
{
    No *aux;

    while (f->inicio != NULL)
    {
        aux = f->inicio;
        f->inicio = f->inicio->prox;
        free(aux);
    }

    f->fim = NULL;
}

int main()
{
    Fila fila;
    inicializar(&fila);

    int opcao;

    do
    {
        printf("\n===== MENU =====\n");
        printf("1 - Adicionar Jogador na Fila\n");
        printf("2 - Mostrar Fila\n");
        printf("3 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
        {
            Jogador j;

            printf("ID do jogador: ");
            scanf("%d", &j.id);

            printf("Nickname: ");
            scanf(" %[^\n]", j.nickname);

            inserir(&fila, j);

            break;
        }

        case 2:
        {
            mostrar(&fila);
            break;
        }

        case 3:
        {
            printf("\nEncerrando sistema...\n");
            break;
        }

        default:
        {
            printf("\nOpcao invalida!\n");
        }
        }

    } while (opcao != 3);

    liberar_fila(&fila);

    return 0;
}