#include <stdio.h>

// Definição da struct
struct Jogador
{
    float pos_x;
    int pontuacao;
    int tem_pulo_duplo;
};

int main()
{

    // Criando o jogador
    struct Jogador heroi;

    // Estado inicial
    heroi.pos_x = 50.0;
    heroi.pontuacao = 0;
    heroi.tem_pulo_duplo = 0;

    // Imprimindo estado inicial
    printf("Inicio da fase! Posicao X: %.1f, Pontos: %d, Pulo Duplo: %s\n",
           heroi.pos_x,
           heroi.pontuacao,
           heroi.tem_pulo_duplo ? "Sim" : "Nao");

    // Simulando ações
    heroi.pontuacao += 10;    // coletar moeda
    heroi.tem_pulo_duplo = 1; // coletar power-up

    // Imprimindo estado final
    printf("Itens coletados! Posicao X: %.1f, Pontos: %d, Pulo Duplo: %s\n",
           heroi.pos_x,
           heroi.pontuacao,
           heroi.tem_pulo_duplo ? "Sim" : "Nao");

    return 0;
}