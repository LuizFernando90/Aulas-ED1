#include <stdio.h>

int main()
{

    // Variável de pontuação
    int pontuacao = 0;

    // Ponteiro para inteiro
    int *ponteiro_pontuacao;

    // Conectando o ponteiro ao endereço da pontuação
    ponteiro_pontuacao = &pontuacao;

    // Pontuação inicial
    printf("Pontuacao inicial: %d\n", pontuacao);

    // Simulando a coleta de 3 moedas (cada uma vale 10 pontos)
    for (int i = 0; i < 3; i++)
    {
        *ponteiro_pontuacao = *ponteiro_pontuacao + 10;
    }

    // Pontuação final
    printf("Pontuacao final apos coletar 3 moedas: %d\n", pontuacao);

    return 0;
}