#include <stdio.h>

// Função que aplica o power-up de pontuação dupla
void aplicar_powerup_pontuacao_dupla(int *pontuacao)
{
    *pontuacao = (*pontuacao) * 2;
}

int main()
{

    // Pontuação inicial do jogador
    int pontuacao_jogador = 1500;

    // Pontuação antes do power-up
    printf("Pontuacao antes do power-up: %d\n", pontuacao_jogador);

    // Chamando a função e passando o endereço da variável
    aplicar_powerup_pontuacao_dupla(&pontuacao_jogador);

    // Pontuação após o power-up
    printf("Pontuacao apos o power-up: %d\n", pontuacao_jogador);

    return 0;
}