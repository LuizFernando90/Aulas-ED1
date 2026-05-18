#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct do jogador
typedef struct
{
    char nome[50];
    int pontuacao;
} Jogador;

int main()
{
    int n, i;

    // Ler quantidade de jogadores
    printf("Digite o numero de jogadores: ");
    scanf("%d", &n);

    // Vetor de jogadores (alocação dinâmica)
    Jogador *jogadores = (Jogador *)malloc(n * sizeof(Jogador));
    if (jogadores == NULL)
    {
        printf("Erro de memoria!\n");
        return 1;
    }

    // Ler dados dos jogadores
    for (i = 0; i < n; i++)
    {
        printf("Jogador %d:\n", i + 1);
        printf("Nome: ");
        scanf("%s", jogadores[i].nome);

        printf("Pontuacao: ");
        scanf("%d", &jogadores[i].pontuacao);
    }

    // Encontrar maior pontuação
    Jogador melhor = jogadores[0];

    for (i = 1; i < n; i++)
    {
        if (jogadores[i].pontuacao > melhor.pontuacao)
        {
            melhor = jogadores[i];
        }
    }

    // Abrir arquivo para escrita
    FILE *arquivo = fopen("highscore.txt", "w");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        free(jogadores);
        return 1;
    }

    // Escrever no arquivo
    fprintf(arquivo, "Nome: %s, Pontuacao: %d\n",
            melhor.nome,
            melhor.pontuacao);

    // Fechar arquivo
    fclose(arquivo);

    // Liberar memória
    free(jogadores);

    printf("Recorde salvo com sucesso!\n");

    return 0;
}