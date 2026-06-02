#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int id;
    char nome[100];
    int nivel;
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

// Mostrar guilda
void mostrar_guilda(Lista lista)
{
    No *aux = lista.inicio;

    if (aux == NULL)
    {
        printf("\nGuilda vazia!\n");
        return;
    }

    printf("\n===== GUILDA =====\n");

    while (aux != NULL)
    {
        printf("ID: %d\n", aux->dado.id);
        printf("Nome: %s\n", aux->dado.nome);
        printf("Nivel: %d\n\n", aux->dado.nivel);

        aux = aux->prox;
    }
}

// Criar arquivo de teste
void salvar_guilda_teste()
{
    FILE *arquivo;

    arquivo = fopen("guild_roster.b", "wb");

    if (arquivo == NULL)
    {
        printf("Erro ao criar arquivo!\n");
        return;
    }

    Membro m;

    m.id = 101;
    strcpy(m.nome, "Arthur");
    m.nivel = 25;
    fwrite(&m, sizeof(Membro), 1, arquivo);

    m.id = 102;
    strcpy(m.nome, "Luna");
    m.nivel = 30;
    fwrite(&m, sizeof(Membro), 1, arquivo);

    m.id = 103;
    strcpy(m.nome, "Ragnar");
    m.nivel = 40;
    fwrite(&m, sizeof(Membro), 1, arquivo);

    fclose(arquivo);
}

// Carregar guilda
Lista carregar_guilda()
{
    Lista lista;
    lista.inicio = NULL;

    FILE *arquivo;

    arquivo = fopen("guild_roster.b", "rb");

    if (arquivo == NULL)
    {
        printf("Arquivo nao encontrado!\n");
        return lista;
    }

    Membro m;

    while (fread(&m, sizeof(Membro), 1, arquivo) == 1)
    {
        inserir_fim(&lista, m);
    }

    fclose(arquivo);

    return lista;
}

// Liberar memória
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

int main()
{
    Lista guilda;

    // Cria o arquivo de teste
    salvar_guilda_teste();

    // Carrega o arquivo para a lista
    guilda = carregar_guilda();

    // Mostra os membros carregados
    mostrar_guilda(guilda);

    liberar_lista(&guilda);

    return 0;
}