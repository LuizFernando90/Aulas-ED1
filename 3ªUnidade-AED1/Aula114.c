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

// Inicializar fila
void inicializar(Fila *f)
{
    f->inicio = NULL;
    f->fim = NULL;
}

// Verificar se está vazia
int estaVazia(Fila *f)
{
    return (f->inicio == NULL);
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

    if (estaVazia(f))
    {
        f->inicio = novo;
        f->fim = novo;
    }
    else
    {
        f->fim->prox = novo;
        f->fim = novo;
    }
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

// Remover jogador (Dequeue)
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

// Ver início da fila (Front/Peek)
Jogador verInicio(Fila *f)
{
    Jogador erro;
    erro.id = -1;
    strcpy(erro.nickname, "ERRO");

    if (estaVazia(f))
    {
        return erro;
    }

    return f->inicio->dado;
}

// Salvar fila em arquivo
void salvarFila(Fila *f, const char *nomeArquivo)
{
    FILE *arquivo = fopen(nomeArquivo, "wb");

    if (arquivo == NULL)
    {
        printf("\nErro ao abrir o arquivo!\n");
        return;
    }

    No *aux = f->inicio;

    while (aux != NULL)
    {
        fwrite(&(aux->dado), sizeof(Jogador), 1, arquivo);
        aux = aux->prox;
    }

    fclose(arquivo);

    printf("\nFila salva com sucesso em %s!\n",
           nomeArquivo);
}

// Carregar fila do arquivo
void carregarFila(Fila *f, const char *nomeArquivo)
{
    FILE *arquivo = fopen(nomeArquivo, "rb");

    if (arquivo == NULL)
    {
        printf("Nenhum arquivo de fila encontrado.\n");
        printf("Iniciando com uma fila vazia.\n");
        return;
    }

    Jogador j;

    while (fread(&j, sizeof(Jogador), 1, arquivo) == 1)
    {
        inserir(f, j);
    }

    fclose(arquivo);

    printf("Fila carregada com sucesso!\n");
}

// Liberar memória
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

    // Carrega automaticamente a fila salva
    carregarFila(&fila, "matchmaking_queue.bin");

    int opcao;

    do
    {
        printf("\n===== MENU =====\n");
        printf("1 - Adicionar Jogador\n");
        printf("2 - Remover Jogador\n");
        printf("3 - Mostrar Fila\n");
        printf("4 - Verificar se a Fila esta Vazia\n");
        printf("5 - Ver quem e o proximo da Fila\n");
        printf("6 - Salvar Fila em Arquivo\n");
        printf("7 - Sair\n");
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

            printf("Jogador adicionado com sucesso!\n");
            break;
        }

        case 2:
        {
            Jogador j = remover(&fila);

            if (j.id != -1)
            {
                printf("\nJogador %s (ID %d) entrou em uma partida!\n",
                       j.nickname, j.id);
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
            Jogador j = verInicio(&fila);

            if (j.id == -1)
            {
                printf("\nA fila esta vazia.\n");
            }
            else
            {
                printf("\nProximo jogador da fila:\n");
                printf("ID: %d\n", j.id);
                printf("Nickname: %s\n", j.nickname);
            }

            break;
        }

        case 6:
        {
            salvarFila(&fila, "matchmaking_queue.bin");
            break;
        }

        case 7:
        {
            printf("\nEncerrando sistema...\n");
            break;
        }

        default:
        {
            printf("\nOpcao invalida!\n");
        }
        }

    } while (opcao != 7);

    liberar_fila(&fila);

    return 0;
}