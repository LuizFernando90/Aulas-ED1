#include <stdio.h>
#include <string.h>

int main()
{

    // Vetor para armazenar o nome do jogador
    char nome_jogador[50];

    // Pedindo o nome ao usuário
    printf("Digite o nome do seu personagem: ");

    // Lendo o nome completo (incluindo espaços)
    scanf(" %[^\n]", nome_jogador);

    // Verificando o tamanho do nome
    if (strlen(nome_jogador) <= 15)
    {
        printf("Nome valido! Bem-vindo ao jogo, %s!\n", nome_jogador);
    }
    else
    {
        printf("Nome muito longo! Por favor, escolha um nome com ate 15 caracteres.\n");
    }

    return 0;
}