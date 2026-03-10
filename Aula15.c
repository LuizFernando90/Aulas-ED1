#include <stdio.h>
#include <string.h>

int main()
{

    // Variáveis para nome e título
    char nome_jogador[50];
    char titulo_conquistado[50];

    // Lendo o nome do herói
    printf("Digite o nome do heroi: ");
    scanf(" %[^\n]", nome_jogador);

    // Lendo o título conquistado
    printf("Digite o titulo conquistado: ");
    scanf(" %[^\n]", titulo_conquistado);

    // Adicionando um espaço ao final do nome
    strcat(nome_jogador, " ");

    // Concatenando o título ao nome
    strcat(nome_jogador, titulo_conquistado);

    // Exibindo o resultado final
    printf("O heroi agora e conhecido como: %s\n", nome_jogador);

    return 0;
}