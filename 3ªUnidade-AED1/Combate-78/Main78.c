#include <stdio.h>
#include "combate.h"

int main()
{
    int ataque_base;
    int bonus_arma;
    int vida_inimigo;

    scanf("%d", &ataque_base);
    scanf("%d", &bonus_arma);
    scanf("%d", &vida_inimigo);

    int ataque_total =
        calcular_ataque_total(ataque_base, bonus_arma);

    int vida_restante =
        aplicar_dano(vida_inimigo, ataque_total);

    printf("Ataque total do heroi: %d\n", ataque_total);
    printf("Vida restante do inimigo: %d\n", vida_restante);

    return 0;
}