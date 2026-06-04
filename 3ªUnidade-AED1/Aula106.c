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

// Verifica se está vazia
int vazia(Pilha *p)
{
    return p->topo == NULL;
}

// Push
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

// Pop
Feitico pop(Pilha *p)
{
    Feitico erro;
    strcpy(erro.nome, "ERRO");
    erro.custo_mana = -1;

    if (vazia(p))
    {
        printf("\nA pilha de comandos esta vazia!\n");
        return erro;
    }

    No *aux = p->topo;

    Feitico removido = aux->dado;

    p->topo = aux->prox;

    free(aux);

    return removido;
}

// Top / Peek
Feitico top(Pilha *p)
{
    Feitico erro;
    strcpy(erro.nome, "ERRO");
    erro.custo_mana = -1;

    if (vazia(p))
    {
        printf("\nA pilha de comandos esta vazia!\n");
        return erro;
    }

    return p->topo->dado;
}

// Mostrar pilha
void mostrar_pilha(Pilha *p)
{
    if (vazia(p))
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

// Inverter pilha
void inverter_pilha(Pilha *p)
{
    if (vazia(p))
    {
        printf("\nNao ha nada para inverter!\n");
        return;
    }

    Pilha aux;
    inicializar(&aux);

    while (!vazia(p))
    {
        Feitico f = pop(p);
        push(&aux, f);
    }

    p->topo = aux.topo;

    printf("\nOrdem dos feiticos invertida!\n");
}

// Salvar pilha em arquivo binário
void salvar_pilha_em_arquivo(Pilha *p, const char *nome_arquivo)
{
    FILE *arquivo = fopen(nome_arquivo, "wb");

    if (arquivo == NULL)
    {
        printf("\nErro ao abrir o arquivo!\n");
        return;
    }

    No *aux = p->topo;

    while (aux != NULL)
    {
        fwrite(&(aux->dado), sizeof(Feitico), 1, arquivo);
        aux = aux->prox;
    }

    fclose(arquivo);

    printf("\nSequencia salva com sucesso em %s!\n",
           nome_arquivo);
}

// Liberar memória
void liberar_pilha(Pilha *p)
{
    while (!vazia(p))
    {
        pop(p);
    }
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
        printf("2 - Lancar Proximo Feitico (Pop)\n");
        printf("3 - Mostrar Pilha\n");
        printf("4 - Consultar Proximo Feitico (Top)\n");
        printf("5 - Salvar Sequencia no Grimorio\n");
        printf("6 - Verificar Status da Pilha\n");
        printf("7 - Inverter Ordem dos Feiticos\n");
        printf("8 - Sair\n");
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

            push(&comandos, f);

            printf("Feitico adicionado com sucesso!\n");

            break;
        }

        case 2:
        {
            Feitico f = pop(&comandos);

            if (f.custo_mana != -1)
            {
                printf("\nFeitico '%s' lancado com sucesso!\n",
                       f.nome);
            }

            break;
        }

        case 3:
        {
            mostrar_pilha(&comandos);
            break;
        }

        case 4:
        {
            Feitico f = top(&comandos);

            if (f.custo_mana != -1)
            {
                printf("\n===== PROXIMO FEITICO =====\n");
                printf("Nome: %s\n", f.nome);
                printf("Mana: %d\n", f.custo_mana);
            }

            break;
        }

        case 5:
        {
            salvar_pilha_em_arquivo(&comandos,
                                    "grimorio.bin");
            break;
        }

        case 6:
        {
            if (vazia(&comandos))
            {
                printf("\nA pilha de comandos esta vazia.\n");
            }
            else
            {
                printf("\nA pilha possui feiticos pendentes.\n");
            }

            break;
        }

        case 7:
        {
            inverter_pilha(&comandos);
            break;
        }

        case 8:
        {
            printf("\nEncerrando sistema...\n");
            break;
        }

        default:
        {
            printf("\nOpcao invalida!\n");
        }
        }

    } while (opcao != 8);

    liberar_pilha(&comandos);

    return 0;
}