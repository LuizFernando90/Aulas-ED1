#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Fila.h"

void inicializarFila(Fila *f)
{
    f->inicio = NULL;
    f->fim = NULL;
    f->tamanho = 0;
}

void inserirPowerUp(Fila *f, PowerUp p)
{
    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL)
    {
        printf("Erro de memoria!\n");
        return;
    }

    novo->dado = p;
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
    f->tamanho++;
}

PowerUp removerPowerUp(Fila *f)
{
    PowerUp erro;
    erro.id = -1;
    strcpy(erro.nome, "VAZIO");
    erro.valor = 0;

    if (f->inicio == NULL)
    {
        printf("Fila vazia!\n");
        return erro;
    }

    No *aux = f->inicio;
    PowerUp removido = aux->dado;
    f->inicio = aux->prox;

    if (f->inicio == NULL)
        f->fim = NULL;

    free(aux);
    f->tamanho--;

    return removido;
}

int estaVazia(Fila *f)
{
    return f->inicio == NULL;
}

PowerUp verInicio(Fila *f)
{
    PowerUp erro;
    erro.id = -1;
    strcpy(erro.nome, "VAZIO");
    erro.valor = 0;

    if (estaVazia(f))
        return erro;
    return f->inicio->dado;
}

int tamanhoFila(Fila *f)
{
    return f->tamanho;
}

void mostrarFila(Fila *f)
{
    if (estaVazia(f))
    {
        printf("\nFila de power-ups vazia.\n");
        return;
    }

    No *aux = f->inicio;
    printf("\n===== POWER-UPS NA FILA =====\n");
    while (aux != NULL)
    {
        printf("ID: %d | Nome: %s | Valor: %d\n",
               aux->dado.id, aux->dado.nome, aux->dado.valor);
        aux = aux->prox;
    }
    printf("Total: %d item(s)\n", f->tamanho);
}

void salvarFila(Fila *f, const char *nomeArquivo)
{
    FILE *arquivo = fopen(nomeArquivo, "wb");
    if (arquivo == NULL)
    {
        printf("Erro ao salvar fila!\n");
        return;
    }

    No *aux = f->inicio;
    while (aux != NULL)
    {
        fwrite(&(aux->dado), sizeof(PowerUp), 1, arquivo);
        aux = aux->prox;
    }

    fclose(arquivo);
    printf("Fila salva com sucesso em %s\n", nomeArquivo);
}

void carregarFila(Fila *f, const char *nomeArquivo)
{
    FILE *arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL)
    {
        printf("Nenhum arquivo de fila encontrado. Iniciando fila vazia.\n");
        return;
    }

    PowerUp p;
    while (fread(&p, sizeof(PowerUp), 1, arquivo) == 1)
        inserirPowerUp(f, p);

    fclose(arquivo);
    printf("Fila carregada com sucesso de %s\n", nomeArquivo);
}

void liberarFila(Fila *f)
{
    while (!estaVazia(f))
        removerPowerUp(f);
}