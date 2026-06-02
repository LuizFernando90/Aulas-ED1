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

// Inicializa a pilha
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

    printf("Feitico adicionado ao topo da pilha!\n");
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
        printf("\n===== PILHA DE COMANDOS =====\n");
        printf("1 - Adicionar Feitico\n");
        printf("2 - Finalizar e Sair\n");
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

    } while (opcao != 2);

    liberar_pilha(&comandos);

    printf("\nSequencia de comandos encerrada!\n");

    return 0;
}