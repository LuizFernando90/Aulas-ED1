#ifndef FILA_H
#define FILA_H

// Estrutura para itens da fila (power-ups)
typedef struct
{
    int id; // tipo do power-up: 1 = moeda extra, etc.
    char nome[50];
    int valor; // pontos ganhos
} PowerUp;

// Nó da fila
typedef struct No
{
    PowerUp dado;
    struct No *prox;
} No;

// Estrutura da fila
typedef struct
{
    No *inicio;
    No *fim;
    int tamanho;
} Fila;

// Funções da fila
void inicializarFila(Fila *f);
void inserirPowerUp(Fila *f, PowerUp p);
PowerUp removerPowerUp(Fila *f);
int estaVazia(Fila *f);
PowerUp verInicio(Fila *f);
int tamanhoFila(Fila *f);
void mostrarFila(Fila *f);
void salvarFila(Fila *f, const char *nomeArquivo);
void carregarFila(Fila *f, const char *nomeArquivo);
void liberarFila(Fila *f);

#endif