#include <stdio.h>
#include <string.h>

// Estrutura de atributos
struct Atributos
{
    int vida;
    int pontuacao;
};

// Estrutura do personagem
struct Personagem
{
    char nome[50];
    struct Atributos stats;
};

int main()
{
    struct Personagem jogador;

    // Ler nome do jogador (com espaço)
    printf("Digite o nome do personagem: ");
    scanf(" %[^\n]", jogador.nome);

    // Inicialização dos atributos
    jogador.stats.vida = 100;
    jogador.stats.pontuacao = 0;

    // Status inicial
    printf("Status Inicial -> Nome: %s | Vida: %d | Pontuacao: %d\n",
           jogador.nome, jogador.stats.vida, jogador.stats.pontuacao);

    // Simular coleta de moeda
    jogador.stats.pontuacao += 10;

    // Simular dano
    jogador.stats.vida -= 25;

    // Status final
    printf("Status Final -> Nome: %s | Vida: %d | Pontuacao: %d\n",
           jogador.nome, jogador.stats.vida, jogador.stats.pontuacao);

    return 0;
}