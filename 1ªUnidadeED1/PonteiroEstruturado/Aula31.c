#include <stdio.h>

// Definindo o tipo Coletavel
typedef struct
{
    int pontos;
    float pos_x;
    float pos_y;
} Coletavel;

int main()
{

    // Declarando a variável
    Coletavel gema_rara;

    // Entrada de dados
    printf("Digite o valor em pontos: ");
    scanf("%d", &gema_rara.pontos);

    printf("Digite a posicao X: ");
    scanf("%f", &gema_rara.pos_x);

    printf("Digite a posicao Y: ");
    scanf("%f", &gema_rara.pos_y);

    // Saída de dados
    printf("Coletavel criado! Valor: %d pontos. Posicao: (X=%.2f, Y=%.2f)\n",
           gema_rara.pontos,
           gema_rara.pos_x,
           gema_rara.pos_y);

    return 0;
}