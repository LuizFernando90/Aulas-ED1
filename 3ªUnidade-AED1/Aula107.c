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

// Verificar se está vazia
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
        printf("A pilha de comandos esta vazia!\n");
        return erro;
    }

    No *aux = p->topo;

    Feitico removido = aux->dado;

    p->topo = aux->prox;

    free(aux);

    return removido;
}

// Top
Feitico top(Pilha *p)
{
    Feitico erro;

    strcpy(erro.nome, "ERRO");
    erro.custo_mana = -1;

    if (vazia(p))
    {
        printf("A pilha de comandos esta vazia!\n");
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
        printf("Nao ha nada para inverter!\n");
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

    printf("Ordem dos feiticos invertida!\n");
}

// Salvar em arquivo
void salvar_pilha_em_arquivo(Pilha *p, const char *nome_arquivo)
{
    FILE *arquivo = fopen(nome_arquivo, "wb");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    No *aux = p->topo;

    while (aux != NULL)
    {
        fwrite(&(aux->dado),
               sizeof(Feitico),
               1,
               arquivo);

        aux = aux->prox;
    }

    fclose(arquivo);

    printf("Grimorio salvo com sucesso!\n");
}

// Carregar arquivo
void carregar_pilha_de_arquivo(Pilha *p, const char *nome_arquivo)
{
    FILE *arquivo = fopen(nome_arquivo, "rb");

    if (arquivo == NULL)
    {
        printf("Nenhum grimorio encontrado. Iniciando vazio.\n");
        return;
    }

    Feitico f;

    while (fread(&f,
                 sizeof(Feitico),
                 1,
                 arquivo) == 1)
    {
        push(p, f);
    }

    fclose(arquivo);

    inverter_pilha(p);

    printf("Grimorio carregado com sucesso!\n");
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

    // Carrega automaticamente ao iniciar
    carregar_pilha_de_arquivo(&comandos,
                              "grimorio.bin");

    int opcao;

    do
    {
        printf("\n===== MENU =====\n");
        printf("1 - Adicionar Feitico\n");
        printf("2 - Lancar Proximo Feitico\n");
        printf("3 - Mostrar Pilha\n");
        printf("4 - Consultar Proximo Feitico\n");
        printf("5 - Salvar Grimorio\n");
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

            printf("Feitico adicionado!\n");

            break;
        }

        case 2:
        {
            Feitico f = pop(&comandos);

            if (f.custo_mana != -1)
            {
                printf("Feitico '%s' lancado!\n",
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
                printf("\nProximo Feitico:\n");
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
                printf("A pilha esta vazia.\n");
            }
            else
            {
                printf("Existem feiticos pendentes.\n");
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
            printf("Encerrando programa...\n");
            break;
        }

        default:
        {
            printf("Opcao invalida!\n");
        }
        }

    } while (opcao != 8);

    liberar_pilha(&comandos);

    return 0;
}