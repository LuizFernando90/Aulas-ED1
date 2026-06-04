#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// Inicializar pilha
void inicializar(Pilha *p)
{
    p->topo = NULL;
}

// Empilhar (Push)
void empilhar(Pilha *p, Feitico f)
{
    No *novo = (No *)malloc(sizeof(No));

    if (novo == NULL)
    {
        printf("Erro de memoria!\n");
        return;
    }

    novo->dado = f;
    novo->prox = p->topo;

    p->topo = novo;

    printf("Feitico adicionado com sucesso!\n");
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

    printf("\n===== PILHA DE COMANDOS =====\n");

    while (aux != NULL)
    {
        printf("Feitico: %s | Mana: %d\n",
               aux->dado.nome,
               aux->dado.custo_mana);

        aux = aux->prox;
    }
}

// Liberar memória
void liberar_pilha(Pilha *p)
{
    No *aux = p->topo;

    while (aux != NULL)
    {
        No *temp = aux;
        aux = aux->prox;
        free(temp);
    }

    p->topo = NULL;
}

int main()
{
    Pilha comandos;

    inicializar(&comandos);

    int opcao;

    do
    {
        printf("\n===== MENU =====\n");
        printf("1 - Adicionar Feitico\n");
        printf("2 - Mostrar Pilha de Comandos\n");
        printf("3 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1)
        {
            Feitico f;

            printf("Nome do Feitico: ");
            scanf(" %[^\n]", f.nome);

            printf("Custo de Mana: ");
            scanf("%d", &f.custo_mana);

            empilhar(&comandos, f);
        }
        else if (opcao == 2)
        {
            mostrar_pilha(&comandos);
        }

    } while (opcao != 3);

    liberar_pilha(&comandos);

    printf("\nPrograma encerrado!\n");

    return 0;
}