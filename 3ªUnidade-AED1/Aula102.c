#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nome[50];
    int custo_mana;
} Feitico;

typedef struct no
{
    Feitico dado;
    struct no *prox;
} No;

typedef struct
{
    No *topo;
} Pilha;

// Inicializar pilha
void inicializar(Pilha *p)
{
    p->topo = NULL;
}

// Push
void push(Pilha *p, Feitico f)
{
    No *novo = (No *)malloc(sizeof(No));

    novo->dado = f;
    novo->prox = p->topo;

    p->topo = novo;
}

// Pop
Feitico pop(Pilha *p)
{
    Feitico erro;

    strcpy(erro.nome, "");
    erro.custo_mana = -1;

    if (p->topo == NULL)
    {
        printf("A pilha de comandos esta vazia!\n");
        return erro;
    }

    No *aux = p->topo;

    Feitico removido = aux->dado;

    p->topo = aux->prox;

    free(aux);

    return removido;
}

// Mostrar pilha
void mostrar_pilha(Pilha *p)
{
    if (p->topo == NULL)
    {
        printf("\nA pilha de comandos esta vazia.\n");
        return;
    }

    No *aux = p->topo;

    printf("\n=== PILHA DE COMANDOS ===\n");

    while (aux != NULL)
    {
        printf("Feitico: %s\n", aux->dado.nome);
        printf("Custo de Mana: %d\n\n", aux->dado.custo_mana);

        aux = aux->prox;
    }
}

// Liberar pilha
void liberar_pilha(Pilha *p)
{
    while (p->topo != NULL)
    {
        pop(p);
    }
}

int main()
{
    Pilha p;

    inicializar(&p);

    int opcao;

    do
    {
        printf("\n===== ARCANISTA =====\n");
        printf("1 - Adicionar Feitico\n");
        printf("2 - Lancar Proximo Feitico\n");
        printf("3 - Mostrar Pilha\n");
        printf("4 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1)
        {
            Feitico f;

            printf("Nome do feitico: ");
            scanf(" %[^\n]", f.nome);

            printf("Custo de mana: ");
            scanf("%d", &f.custo_mana);

            push(&p, f);

            printf("Feitico adicionado com sucesso!\n");
        }
        else if (opcao == 2)
        {
            Feitico f = pop(&p);

            if (f.custo_mana != -1)
            {
                printf("Feitico '%s' lancado com sucesso!\n", f.nome);
            }
        }
        else if (opcao == 3)
        {
            mostrar_pilha(&p);
        }

    } while (opcao != 4);

    liberar_pilha(&p);

    printf("Programa encerrado.\n");

    return 0;
}