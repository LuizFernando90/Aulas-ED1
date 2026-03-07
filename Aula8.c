#include <stdio.h>

int main()
{

    // Vetor representando a fase
    int fase[10] = {0, 1, 0, 0, 1, 1, 0, 1, 0, 0};

    // Ponteiro para inteiro (jogador)
    int *ponteiro_jogador;

    // Contador de moedas
    int moedas_coletadas = 0;

    // Ponteiro apontando para o início do vetor
    ponteiro_jogador = fase;

    // Percorrendo a fase
    for (int i = 0; i < 10; i++)
    {

        // Verificando se existe moeda
        if (*(ponteiro_jogador + i) == 1)
        {
            moedas_coletadas++;
        }
    }

    // Resultado final
    printf("O jogador coletou um total de %d moedas!\n", moedas_coletadas);

    return 0;
}