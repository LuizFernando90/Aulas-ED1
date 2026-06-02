#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int id;
    char nome[50];
} Monstro;

typedef struct No
{
    Monstro dado;
    struct No *prox;
} No;

typedef struct
{
    No *inicio;
} Lista;

// Adicionar no fim
void adicionarMonstro(Lista *lista, Monstro m)
{
    No *novo = (No *)malloc(sizeof(No));

    novo->dado = m;
    novo->prox = NULL;

    if (lista->inicio == NULL)
    {
        lista->inicio = novo;
        return;
    }

    No *aux = lista->inicio;

    while (aux->prox != NULL)
    {
        aux = aux->prox;
    }

    aux->prox = novo;
}

// Mostrar bestiário
void mostrarBestiario(Lista *lista)
{
    if (lista->inicio == NULL)
    {
        printf("\nBestiario vazio!\n");
        return;
    }

    No *aux = lista->inicio;

    printf("\n===== BESTIARIO =====\n");

    while (aux != NULL)
    {
        printf("Nivel Ameaca: %d | Nome: %s\n",
               aux->dado.id,
               aux->dado.nome);

        aux = aux->prox;
    }
}

// Bubble Sort na lista encadeada
void ordenarBestiario(Lista *lista)
{
    if (lista->inicio == NULL)
        return;

    int trocou;
    No *ptr1;
    No *lptr = NULL;

    do
    {
        trocou = 0;
        ptr1 = lista->inicio;

        while (ptr1->prox != lptr)
        {
            if (ptr1->dado.id > ptr1->prox->dado.id)
            {
                Monstro temp = ptr1->dado;
                ptr1->dado = ptr1->prox->dado;
                ptr1->prox->dado = temp;

                trocou = 1;
            }

            ptr1 = ptr1->prox;
        }

        lptr = ptr1;

    } while (trocou);

    printf("\nBestiario ordenado com sucesso!\n");
}

int main()
{
    Lista bestiario;
    bestiario.inicio = NULL;

    int opcao;

    do
    {
        printf("\n===== MENU =====\n");
        printf("1 - Adicionar Monstro\n");
        printf("2 - Ordenar Bestiario\n");
        printf("3 - Mostrar Bestiario\n");
        printf("4 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1)
        {
            Monstro m;

            printf("Nivel de Ameaca (ID): ");
            scanf("%d", &m.id);

            printf("Nome do Monstro: ");
            scanf(" %[^\n]", m.nome);

            adicionarMonstro(&bestiario, m);
        }

        else if (opcao == 2)
        {
            ordenarBestiario(&bestiario);
        }

        else if (opcao == 3)
        {
            mostrarBestiario(&bestiario);
        }

    } while (opcao != 4);

    return 0;
}