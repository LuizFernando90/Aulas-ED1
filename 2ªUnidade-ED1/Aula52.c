#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Definição da struct
struct Unidade
{
    int x;
    int y;
};

int main()
{
    int n;
    float raio;

    // Ler quantidade de unidades
    printf("Digite o numero de unidades: ");
    scanf("%d", &n);

    // Alocação dinâmica
    struct Unidade *unidades = (struct Unidade *)malloc(n * sizeof(struct Unidade));

    // Verificação
    if (unidades == NULL)
    {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    // Ler coordenadas
    for (int i = 0; i < n; i++)
    {
        printf("Digite as coordenadas (x y) da unidade %d: ", i + 1);
        scanf("%d %d", &unidades[i].x, &unidades[i].y);
    }

    // Ler raio
    printf("Digite o raio de explosao: ");
    scanf("%f", &raio);

    int contador = 0;

    // Comparar pares (evitando repetição)
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {

            float distancia = sqrt(
                pow(unidades[j].x - unidades[i].x, 2) +
                pow(unidades[j].y - unidades[i].y, 2));

            if (distancia <= raio)
            {
                contador++;
            }
        }
    }

    // Resultado final
    printf("Total de duplas proximas: %d\n", contador);

    // Liberar memória
    free(unidades);

    return 0;
}