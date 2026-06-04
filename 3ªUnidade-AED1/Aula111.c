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

// Verifica se a fila está vazia
int estaVazia(Fila *f)
{
    if (f->inicio == NULL)
    {
        return 1;
    }

    return 0;
}

// Inserir no fim
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

    printf("Jogador adicionado com sucesso!\n");
}

// Mostrar fila
void mostrar(Fila *f)
{
    if (estaVazia(f))
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

// Remover jogador
Jogador remover(Fila *f)
{
    Jogador erro;

    erro.id = -1;
    strcpy(erro.nickname, "ERRO");

    if (estaVazia(f))
    {
        printf("\nNao ha jogadores na fila!\n");
        return erro;
    }

    No *aux = f->inicio;

    Jogador removido = aux->dado;

    f->inicio = aux->prox;

    if (f->inicio == NULL)
    {
        f->fim = NULL;
    }

    free(aux);

    return removido;
}

// Liberar fila
void liberar_fila(Fila *f)
{
    while (!estaVazia(f))
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
        printf("1 - Adicionar Jogador\n");
        printf("2 - Remover Jogador\n");
        printf("3 - Mostrar Fila\n");
        printf("4 - Verificar se a Fila esta Vazia\n");
        printf("5 - Sair\n");
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
                printf("\nO jogador %s (ID: %d) entrou em uma partida.\n",
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
            if (estaVazia(&fila))
            {
                printf("\nSIM, a fila esta vazia.\n");
            }
            else
            {
                printf("\nNAO, a fila contem jogadores.\n");
            }

            break;
        }

        case 5:
        {
            printf("\nEncerrando sistema...\n");
            break;
        }

        default:
        {
            printf("\nOpcao invalida!\n");
        }
        }

    } while (opcao != 5);

    liberar_fila(&fila);

    return 0;
}