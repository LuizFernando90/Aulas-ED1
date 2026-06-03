#ifndef PILHA_H
#define PILHA_H

typedef struct
{
    char nome[50];
    int custo_mana;
} Feitico;

typedef struct No
{
    Feitico dado;
    struct No *prox;
} No;

typedef struct
{
    No *topo;
} Pilha;

void push(Pilha *p, Feitico f);
Feitico pop(Pilha *p);
void mostrar_pilha(Pilha *p);
int vazia(Pilha *p);
void liberar_pilha(Pilha *p);

#endif