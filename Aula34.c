#include <stdio.h>

// Definição da struct
struct Heroi
{
    int saude;
    int pontuacao;
    int posX;
    int posY;
};

int main()
{

    // Criando e inicializando o herói
    struct Heroi meuHeroi;
    meuHeroi.saude = 100;
    meuHeroi.pontuacao = 0;
    meuHeroi.posX = 0;
    meuHeroi.posY = 0;

    // Estado inicial
    printf("Estado inicial:\n");
    printf("Saude: %d, Pontuacao: %d, PosX: %d, PosY: %d\n",
           meuHeroi.saude,
           meuHeroi.pontuacao,
           meuHeroi.posX,
           meuHeroi.posY);

    // Criando ponteiro
    struct Heroi *ptrHeroi = &meuHeroi;

    // Sofrer dano
    ptrHeroi->saude -= 25;
    printf("Apos dano, Saude: %d\n", ptrHeroi->saude);

    // Coletar moedas
    ptrHeroi->pontuacao += 50;
    printf("Apos coletar moedas, Pontuacao: %d\n", ptrHeroi->pontuacao);

    // Mover herói
    ptrHeroi->posX += 10;
    ptrHeroi->posY -= 5;
    printf("Nova posicao: X=%d, Y=%d\n", ptrHeroi->posX, ptrHeroi->posY);

    // Estado final (usando apenas ponteiro)
    printf("Estado final:\n");
    printf("Saude: %d, Pontuacao: %d, PosX: %d, PosY: %d\n",
           ptrHeroi->saude,
           ptrHeroi->pontuacao,
           ptrHeroi->posX,
           ptrHeroi->posY);

    return 0;
}