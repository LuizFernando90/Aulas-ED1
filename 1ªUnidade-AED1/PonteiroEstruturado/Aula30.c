#include <stdio.h>
#include <string.h>

// Definição da struct
struct Jogador
{
    char nome[50];
    int vidas;
    int pontuacao;
};

int main()
{

    struct Jogador player1;
    char nome_digitado[50];

    // Inicializando atributos
    player1.vidas = 3;
    player1.pontuacao = 0;

    // Pedindo o nome
    printf("Digite o nome do seu personagem: ");
    scanf(" %[^\n]", nome_digitado); // lê com espaços

    // Copiando para a struct
    strcpy(player1.nome, nome_digitado);

    // Exibindo os dados
    printf("Personagem criado! Bem-vindo, %s! Vidas: %d, Pontuacao: %d\n",
           player1.nome,
           player1.vidas,
           player1.pontuacao);

    return 0;
}