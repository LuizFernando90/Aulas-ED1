#include <stdio.h>

// Definição da struct
struct Personagem
{
    int posX;
    int posY;
    int moedas;
};

// Função que recebe uma cópia e retorna atualizada
struct Personagem atualizarPersonagem(struct Personagem p)
{
    p.posX = 10;
    p.posY = 5;
    p.moedas++;
    return p;
}

int main()
{

    struct Personagem jogador;

    // Estado inicial
    jogador.posX = 0;
    jogador.posY = 0;
    jogador.moedas = 0;

    printf("Posicao inicial: (%d, %d) - Moedas: %d\n",
           jogador.posX, jogador.posY, jogador.moedas);

    // Atualizando (precisa receber o retorno)
    jogador = atualizarPersonagem(jogador);

    printf("Posicao atualizada: (%d, %d) - Moedas: %d\n",
           jogador.posX, jogador.posY, jogador.moedas);

    return 0;
}