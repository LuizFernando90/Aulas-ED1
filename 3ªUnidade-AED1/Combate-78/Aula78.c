#include "combate.h"

int calcular_ataque_total(int ataque_base, int bonus_arma)
{
    return ataque_base + bonus_arma;
}

int aplicar_dano(int vida_atual, int dano)
{
    int vida_restante = vida_atual - dano;

    if (vida_restante < 0)
    {
        vida_restante = 0;
    }

    return vida_restante;
}