#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int id;
    char nickname[100];
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

// Inserir no final da fila (Enqueue)
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

    printf("Jogador inserido na fila com sucesso!\n");
}

int main()
{
    Fila fila;
    inicializar(&fila);

    int opcao;

    do
    {
        printf("\n===== FILA DE MATCHMAKING =====\n");
        printf("1 - Adicionar jogador\n");
        printf("2 - Sair\n");
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
            printf("Encerrando programa...\n");
            break;
        }

        default:
        {
            printf("Opcao invalida!\n");
        }
        }

    } while (opcao != 2);

    // Liberação de memória
    No *aux;

    while (fila.inicio != NULL)
    {
        aux = fila.inicio;
        fila.inicio = fila.inicio->prox;
        free(aux);
    }

    return 0;
}