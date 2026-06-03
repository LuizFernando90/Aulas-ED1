#include <stdio.h>
#include "fila.h"

int main()
{
    Fila fila;

    inicializarFila(&fila);

    carregarFila(&fila, "matchmaking_queue.bin");

    int opcao;

    do
    {
        printf("\n===== MENU =====\n");
        printf("1 - Adicionar Jogador\n");
        printf("2 - Mostrar Fila\n");
        printf("3 - Remover Jogador\n");
        printf("4 - Verificar Fila Vazia\n");
        printf("5 - Ver Proximo Jogador\n");
        printf("6 - Salvar Fila\n");
        printf("7 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1:
            {
                Jogador j;

                printf("ID: ");
                scanf("%d", &j.id);

                printf("Nickname: ");
                scanf(" %[^\n]", j.nickname);

                inserir(&fila, j);

                printf("Jogador adicionado!\n");
                break;
            }

            case 2:
            {
                mostrar(&fila);
                break;
            }

            case 3:
            {
                Jogador j = remover(&fila);

                if(j.id != -1)
                {
                    printf("\nJogador %s (ID %d) entrou na partida!\n",
                           j.nickname,
                           j.id);
                }

                break;
            }

            case 4:
            {
                if(estaVazia(&fila))
                {
                    printf("\nSIM, a fila esta vazia.\n");
                }
                else
                {
                    printf("\nNAO, a fila contem jogadores.\n");
                }

                break;
            }

            case 5:
            {
                Jogador j = verInicio(&fila);

                if(j.id == -1)
                {
                    printf("\nFila vazia!\n");
                }
                else
                {
                    printf("\nProximo jogador:\n");
                    printf("ID: %d\n", j.id);
                    printf("Nickname: %s\n", j.nickname);
                }

                break;
            }

            case 6:
            {
                salvarFila(&fila,
                           "matchmaking_queue.bin");
                break;
            }

            case 7: