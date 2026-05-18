#include <stdio.h>

// Definição da struct
struct Posicao
{
    int x;
    int y;
};

// Função que move o personagem usando ponteiro
void mover_personagem(struct Posicao *p, int movimento_x, int movimento_y)
{
    p->x += movimento_x;
    p->y += movimento_y;
}

int main()
{

    // Variável do jogador
    struct Posicao posicao_jogador = {0, 0};

    // Ponteiro para a posição
    struct Posicao *ponteiro_posicao = &posicao_jogador;

    // Posição inicial
    printf("Posicao inicial do jogador: X=%d, Y=%d\n",
           posicao_jogador.x, posicao_jogador.y);

    // Movendo o personagem
    mover_personagem(ponteiro_posicao, 10, 5);

    // Posição final
    printf("Posicao final do jogador: X=%d, Y=%d\n",
           posicao_jogador.x, posicao_jogador.y);

    return 0;
}