#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"

void inicializarFila(Fila *f)
{
    f->inicio = NULL;
    f->fim = NULL;
}

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
}

Jogador remover(Fila *f)
{
    Jogador erro;
    erro.id = -1;
    strcpy(erro.nickname, "ERRO");

    if (f->inicio == NULL)
    {
        printf("\nFila vazia!\n");
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

int estaVazia(Fila *f)
{
    return f->inicio == NULL;
}

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

void mostrar(Fila *f)
{
    if (estaVazia(f))
    {
        printf("\nA fila esta vazia.\n");
        return;
    }

    No *aux = f->inicio;

    printf("\n===== FILA =====\n");

    while (aux != NULL)
    {
        printf("ID: %d\n", aux->dado.id);
        printf("Nickname: %s\n\n", aux->dado.nickname);

        aux = aux->prox;
    }
}

void salvarFila(Fila *f, const char *nomeArquivo)
{
    FILE *arquivo = fopen(nomeArquivo, "wb");

    if (arquivo == NULL)
    {
        printf("\nErro ao abrir arquivo!\n");
        return;
    }

    No *aux = f->inicio;

    while (aux != NULL)
    {
        fwrite(&(aux->dado),
               sizeof(Jogador),
               1,
               arquivo);

        aux = aux->prox;
    }

    fclose(arquivo);

    printf("\nFila salva com sucesso!\n");
}

void carregarFila(Fila *f, const char *nomeArquivo)
{
    FILE *arquivo = fopen(nomeArquivo, "rb");

    if (arquivo == NULL)
    {
        printf("\nNenhum arquivo encontrado. Iniciando fila vazia.\n");
        return;
    }

    Jogador j;

    while (fread(&j,
                 sizeof(Jogador),
                 1,
                 arquivo) == 1)
    {
        inserir(f, j);
    }

    fclose(arquivo);

    printf("\nFila carregada com sucesso!\n");
}

void liberarFila(Fila *f)
{
    while (!estaVazia(f))
    {
        remover(f);
    }
}