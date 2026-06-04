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

// Inserir no fim (Enqueue)
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
        printf("ID: %d | Nickname: %s\n",
               aux->dado.id,
               aux->dado.nickname);

        aux = aux->prox;
    }
}

// Remover do início (Dequeue)
Jogador remover(Fila *f)
{
    Jogador erro;
    erro.id = -1;
    strcpy(erro.nickname, "ERRO");

    if (f->inicio == NULL)
    {
        printf("\nNao ha jogadores na fila!\n");
        return erro;
    }

    No *aux = f->inicio;

    Jogador removido = aux->dado;

    f->inicio = aux->prox;

    // Caso especial: havia apenas um jogador
    if (f->inicio == NULL)
    {
        f->fim = NULL;
    }

    free(aux);

    return removido;
}

// Liberar toda a fila
void liberar_fila(Fila *f)
{
    while (f->inicio != NULL)
    {
        remover(f);
    }
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
        printf("2 - Remover Jogador da Fila\n");
        printf("3 - Mostrar Fila\n");
        printf("4 - Sair\n");
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
            Jogador j = remover(&fila);

            if (j.id != -1)
            {
                printf("\nO jogador %s (ID: %d) foi removido da fila e entrou em uma partida.\n",
                       j.nickname,
                       j.id);
            }

            break;
        }

        case 3:
        {
            mostrar(&fila);
            break;
        }

        case 4:
        {
            printf("\nEncerrando sistema...\n");
            break;
        }

        default:
        {
            printf("\nOpcao invalida!\n");
        }
        }

    } while (opcao != 4);

    liberar_fila(&fila);

    return 0;
}