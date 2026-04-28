#include <stdio.h>
#include <stdlib.h>

// Struct de configuração
typedef struct
{
    int resolucao_x;
    int resolucao_y;
    float volume_som;
} Configuracao;

int main()
{
    FILE *arquivo;

    // Tentar abrir o arquivo
    arquivo = fopen("config.txt", "r");

    // Verificação de erro
    if (arquivo == NULL)
    {
        printf("Erro: Arquivo config.txt nao encontrado!\n");
        return 1;
    }

    // Variável para armazenar os dados
    Configuracao config;

    // Ler os dados do arquivo
    fscanf(arquivo, "%d %d %f",
           &config.resolucao_x,
           &config.resolucao_y,
           &config.volume_som);

    // Exibir os dados
    printf("Configuracoes carregadas:\n");
    printf("Resolucao: %dx%d\n",
           config.resolucao_x,
           config.resolucao_y);
    printf("Volume: %.1f\n", config.volume_som);

    // Fechar arquivo
    fclose(arquivo);

    return 0;
}