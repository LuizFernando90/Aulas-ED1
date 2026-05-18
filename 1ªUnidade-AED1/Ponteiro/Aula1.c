#include <stdio.h>

int main()
{

    // Variável da vida do jogador
    int vida_jogador = 100;

    int *ponteiro_vida;

    // Simulando o dano tomado
    vida_jogador = 50;

    // Exibir o dano sofrido pelo
    printf("O jogador sofreu dano! Vida atual: %d\n", vida_jogador);

    // Fazendo o ponteiro apontar para a vida do jogador
    ponteiro_vida = &vida_jogador;

    // Usando o power-up
    *ponteiro_vida = 100;

    // Exibir a restauração da vida
    printf("Power-up coletado! Vida restaurada: %d\n", vida_jogador);

    return 0;
}