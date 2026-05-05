#include <stdio.h>

int main()
{
    int placar[5] = {120, 125, 130, 142, 150};
    int novo_tempo;
    int i;

    // Ler novo tempo
    scanf("%d", &novo_tempo);

    // Verifica se entra no top 5
    if (novo_tempo < placar[4])
    {
        // Percorre de trás para frente
        for (i = 4; i > 0 && novo_tempo < placar[i - 1]; i--)
        {
            placar[i] = placar[i - 1]; // desloca para direita
        }

        // Insere na posição correta
        placar[i] = novo_tempo;
    }

    // Imprimir placar final
    for (i = 0; i < 5; i++)
    {
        printf("%d ", placar[i]);
    }

    printf("\n");

    return 0;
}