#ifndef FILA_H
#define FILA_H

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

void inicializarFila(Fila *f);

void inserir(Fila *f, Jogador j);

Jogador remover(Fila *f);

int estaVazia(Fila *f);

Jogador verInicio(Fila *f);

void mostrar(Fila *f);

void salvarFila(Fila *f, const char *nomeArquivo);

void carregarFila(Fila *f, const char *nomeArquivo);

void liberarFila(Fila *f);

#endif