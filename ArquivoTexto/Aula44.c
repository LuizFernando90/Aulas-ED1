#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int id;
    int pontos;
} Conquista;

int main()
{
    FILE *arquivo;
    int N, i;
    int total_exp = 0;

    // Abrir para leitura e escrita
    arquivo = fopen("player_log.txt", "r+");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    // Ler quantidade de conquistas
    fscanf(arquivo, "%d", &N);

    Conquista c;

    // Ler as conquistas
    for (i = 0; i < N; i++)
    {
        fscanf(arquivo, "%d %d", &c.id, &c.pontos);
        total_exp += c.pontos;
    }

    // Mostrar total
    printf("Total de experiencia: %d\n", total_exp);

    //  IMPORTANTE: ir para o final do arquivo antes de escrever
    fseek(arquivo, 0, SEEK_END);

    // Escrever marcador
    fprintf(arquivo, "\n--- SESSION CONCLUDED ---");

    // Fechar arquivo
    fclose(arquivo);

    return 0;
}