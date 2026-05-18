#include <stdio.h>

// Definição da struct
struct Inimigo
{
    int vida;
    int ataque;
    float velocidade;
};

int main()
{

    // Criando os inimigos
    struct Inimigo cogumelo_zumbi;
    struct Inimigo cavaleiro_esqueleto;

    // Atribuindo valores
    cogumelo_zumbi.vida = 20;
    cogumelo_zumbi.ataque = 5;
    cogumelo_zumbi.velocidade = 0.8;

    cavaleiro_esqueleto.vida = 80;
    cavaleiro_esqueleto.ataque = 15;
    cavaleiro_esqueleto.velocidade = 1.2;

    // Exibindo os dados do cogumelo zumbi
    printf("--- Atributos do Inimigo: Cogumelo Zumbi ---\n");
    printf("Vida: %d\n", cogumelo_zumbi.vida);
    printf("Ataque: %d\n", cogumelo_zumbi.ataque);
    printf("Velocidade: %.1f\n\n", cogumelo_zumbi.velocidade);

    // Exibindo os dados do cavaleiro esqueleto
    printf("--- Atributos do Inimigo: Cavaleiro Esqueleto ---\n");
    printf("Vida: %d\n", cavaleiro_esqueleto.vida);
    printf("Ataque: %d\n", cavaleiro_esqueleto.ataque);
    printf("Velocidade: %.1f\n", cavaleiro_esqueleto.velocidade);

    return 0;
}