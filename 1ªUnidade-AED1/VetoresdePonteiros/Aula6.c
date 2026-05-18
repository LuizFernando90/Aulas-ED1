#include <stdio.h>

int main()
{

    // Vetor com os impulsos das plataformas
    int plataformas[] = {10, 20, 5, 15, 30};

    int *ponteiro_plataforma;

    // Variável para armazenar a altura total
    int altura_total = 0;

    // Fazendo o ponteiro apontar para o início do vetor
    ponteiro_plataforma = plataformas;

    // Percorrendo o vetor usando aritmética de ponteiros
    for (int i = 0; i < 5; i++)
    {
        altura_total += *(plataformas + i);
    }

    // Resultado final
    printf("Altura total do salto: %d metros!\n", altura_total);

    return 0;
}