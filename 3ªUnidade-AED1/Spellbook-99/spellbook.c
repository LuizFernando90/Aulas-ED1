#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "spellbook.h"

// Criar grimório
Spellbook *create_spellbook()
{
    Spellbook *book =
        (Spellbook *)malloc(sizeof(Spellbook));

    book->inicio = NULL;

    return book;
}

// Adicionar feitiço
void add_spell(
    Spellbook *book,
    int id,
    const char *name,
    int mana_cost)
{
    No *novo =
        (No *)malloc(sizeof(No));

    novo->spell.id = id;

    strcpy(
        novo->spell.name,
        name);

    novo->spell.mana_cost =
        mana_cost;

    novo->prox = NULL;

    if (book->inicio == NULL)
    {
        book->inicio = novo;
        return;
    }

    No *aux = book->inicio;

    while (aux->prox != NULL)
    {
        aux = aux->prox;
    }

    aux->prox = novo;
}

// Mostrar grimório
void display_spellbook(
    Spellbook *book)
{
    if (book->inicio == NULL)
    {
        printf("Grimorio vazio!\n");
        return;
    }

    No *aux = book->inicio;

    printf("\n===== GRIMORIO =====\n");

    while (aux != NULL)
    {
        printf(
            "ID: %d, Feitico: %s, Custo de Mana: %d\n",
            aux->spell.id,
            aux->spell.name,
            aux->spell.mana_cost);

        aux = aux->prox;
    }
}

// Liberar memória
void destroy_spellbook(
    Spellbook *book)
{
    No *aux = book->inicio;

    while (aux != NULL)
    {
        No *temp = aux;

        aux = aux->prox;

        free(temp);
    }

    free(book);
}