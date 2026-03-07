#include <stdio.h>

int main()
{

    // Vetor com os valores das moedas coletadas
    int moedas_coletadas[] = {10, 50, 20, 5, 100};

    // Pontuação total
    int pontuacao_total = 0;

    // Ponteiro para moedas
    int *ponteiro_moeda;

    // Ponteiro apontando para o início do vetor
    ponteiro_moeda = moedas_coletadas;

    // Percorrendo o vetor usando apenas o ponteiro
    while (ponteiro_moeda < moedas_coletadas + 5)
    {

        pontuacao_total += *ponteiro_moeda; // soma o valor da moeda atual
        ponteiro_moeda++;                   // avança para a próxima moeda
    }

    // Imprimindo o resultado final
    printf("Pontuação total do nível: %d\n", pontuacao_total);

    return 0;
}