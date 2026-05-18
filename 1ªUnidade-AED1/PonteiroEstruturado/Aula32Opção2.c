#include <stdio.h>

// Definição da struct
struct Personagem
{
    int posX;
    int posY;
    int moedas;
};

// Função que altera diretamente o original
void atualizarPersonagemComPonteiro(struct Personagem *p)
{
    p->posX = 10;
    p->posY = 5;
    p->moedas++;
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

    // Passando endereço
    atualizarPersonagemComPonteiro(&jogador);

    printf("Posicao atualizada: (%d, %d) - Moedas: %d\n",
           jogador.posX, jogador.posY, jogador.moedas);

    return 0;
}