#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"

int vazia(Pilha *p)
{
    return (p->topo == NULL);
}

void push(Pilha *p, Feitico f)
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
}

Feitico pop(Pilha *p)
{
    Feitico erro;

    strcpy(erro.nome, "");
    erro.custo_mana = -1;

    if (vazia(p))
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

void mostrar_pilha(Pilha *p)
{
    if (vazia(p))
    {
        printf("\nA pilha de comandos esta vazia.\n");
        return;
    }

    No *aux = p->topo;

    printf("\n=== PILHA DE COMANDOS ===\n");

    while (aux != NULL)
    {
        printf("Feitico: %s | Mana: %d\n",
               aux->dado.nome,
               aux->dado.custo_mana);

        aux = aux->prox;
    }
}

void liberar_pilha(Pilha *p)
{
    while (!vazia(p))
    {
        pop(p);
    }
}

int main()
{
    Pilha pilha;
    pilha.topo = NULL;

    int opcao;

    do
    {
        printf("\n===== MENU =====\n");
        printf("1 - Adicionar Feitico\n");
        printf("2 - Lancar Proximo Feitico\n");
        printf("3 - Mostrar Pilha\n");
        printf("4 - Verificar Status da Pilha\n");
        printf("5 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
        {
            Feitico f;

            printf("Nome do feitico: ");
            scanf(" %[^\n]", f.nome);

            printf("Custo de mana: ");
            scanf("%d", &f.custo_mana);

            push(&pilha, f);

            printf("Feitico adicionado com sucesso!\n");
            break;
        }

        case 2:
        {
            Feitico f = pop(&pilha);

            if (f.custo_mana != -1)
            {
                printf("Feitico '%s' lancado com sucesso!\n",
                       f.nome);
            }

            break;
        }

        case 3:
            mostrar_pilha(&pilha);
            break;

        case 4:
            if (vazia(&pilha))
            {
                printf("A pilha de comandos esta vazia.\n");
            }
            else
            {
                printf("A pilha de comandos possui feiticos pendentes.\n");
            }
            break;

        case 5:
            printf("Encerrando programa...\n");
            break;

        default:
            printf("Opcao invalida!\n");
        }

    } while (opcao != 5);

    liberar_pilha(&pilha);

    return 0;
}