#include <stdio.h>
#include <stdlib.h>

int main()
{

    // Ponteiro para armazenar a altura do salto duplo
    float *ponteiro_altura_salto_duplo = NULL;

    // Status inicial
    printf("Jogador ainda nao possui o Salto Duplo.\n");

    // Coletando o power-up (alocando memória)
    ponteiro_altura_salto_duplo = (float *)malloc(sizeof(float));

    // Verificando se a alocação foi bem-sucedida
    if (ponteiro_altura_salto_duplo != NULL)
    {

        // Definindo a altura do salto duplo
        *ponteiro_altura_salto_duplo = 15.5;

        // Mostrando o novo poder adquirido
        printf("Pena Dourada coletada! Altura do Salto Duplo: %.2f\n", *ponteiro_altura_salto_duplo);

        // Liberando a memória (boa prática)
        free(ponteiro_altura_salto_duplo);
        // Em um jogo real, isso seria usado quando o power-up não fosse mais necessário
    }

    return 0;
}