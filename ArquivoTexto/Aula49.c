#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *arquivo;

    // Tentar abrir o arquivo
    arquivo = fopen("level_1_map.dat", "r");

    // Verificar erro
    if (arquivo == NULL)
    {
        printf("ERRO CRITICO: Nao foi possivel carregar os dados do mapa.\n");
        perror("Detalhes do erro");
        exit(1);
    }

    // (Não deve chegar aqui, pois o arquivo não existe)
    fclose(arquivo);

    return 0;
}