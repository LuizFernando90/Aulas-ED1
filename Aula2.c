#include <stdio.h>

int main()
{

    // Variável para indica se o tesouro apareceu
    int tesouro_local = 0;

    int *plataforma_secreta;

    // Ponteiro para guardar o endereço de tesouro_local
    plataforma_secreta = &tesouro_local;

    // Verificação do tesouro
    printf("O tesouro ainda nao apareceu. Valor: %d\n", tesouro_local);

    // Ativando o tesouro usando ponteiro
    *plataforma_secreta = 1;

    // Verificação final
    printf("O personagem pisou na plataforma secreta! O tesouro apareceu! Valor: %d\n", tesouro_local);

    return 0;
}