#include <stdio.h>
#include <string.h>

int main()
{

    // Palavra secreta
    char palavra_secreta[] = "LUX";

    // Tentativa do jogador
    char tentativa_jogador[50];

    // Mensagem para o jogador
    printf("Uma voz ancestral ecoa... 'Diga a palavra e passe': ");

    // Lendo a palavra digitada
    scanf("%s", tentativa_jogador);

    // Comparando as palavras
    if (strcmp(palavra_secreta, tentativa_jogador) == 0)
    {
        printf("A porta magica se abre!\n");
    }
    else
    {
        printf("Nada acontece... Parece que a palavra esta incorreta.\n");
    }

    return 0;
}