#include <stdio.h>

int main()
{

    // Variável para armazenar a coordenada X do portal
    float coordenada_x;

    float *ponteiro_x;

    // Fazendo o ponteiro apontar para o endereço de coordenada_x
    ponteiro_x = &coordenada_x;

    // Ler a coordenada digitada pelo usuário
    printf("Digite a coordenada X do portal: ");
    scanf("%f", &coordenada_x);

    // Imprimindo o valor da coordenada
    printf("Posicao do portal no eixo X: %f\n", coordenada_x);

    // Imprimindo o endereço de memória da coordenada
    printf("Endereco do portal para teletransporte: %p\n", ponteiro_x);

    return 0;
}