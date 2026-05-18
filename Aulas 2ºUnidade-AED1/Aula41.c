#include <stdio.h>
#include <stdlib.h>

int main()
{
    int opcao;
    char evento[100];

    do
    {
        printf("\n=== MENU ===\n");
        printf("1 - Registrar novo evento\n");
        printf("2 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1)
        {
            FILE *arquivo = fopen("game_log.txt", "a"); // modo append

            if (arquivo == NULL)
            {
                printf("Erro ao abrir o arquivo!\n");
                return 1;
            }

            printf("Digite o evento (sem espacos): ");
            scanf("%s", evento);

            // escreve no arquivo
            fprintf(arquivo, "%s\n", evento);

            fclose(arquivo);

            printf("Evento registrado com sucesso!\n");
        }

    } while (opcao != 2);

    printf("Encerrando o programa...\n");

    return 0;
}