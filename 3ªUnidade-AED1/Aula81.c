#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int id;
    char nome[50];
} Movimento;

typedef struct No
{
    Movimento dado;
    struct No *prox;
} No;

typedef struct
{
    No *inicio;
} Lista;

void inserir_inicio(Lista *l, Movimento m)
{
    No *novo = (No *)malloc(sizeof(No));

    novo->dado = m;
    novo->prox = l->inicio;

    l->inicio = novo;
}

int main()
{
    Lista combo;
    combo.inicio = NULL;

    int opcao;

    do
    {
        printf("1 - Inserir movimento\n");
        printf("2 - Sair\n");
        scanf("%d", &opcao);

        if (opcao == 1)
        {
            Movimento m;

            scanf("%d", &m.id);
            scanf(" %[^\n]", m.nome);

            inserir_inicio(&combo, m);
        }

    } while (opcao != 2);

    return 0;
}