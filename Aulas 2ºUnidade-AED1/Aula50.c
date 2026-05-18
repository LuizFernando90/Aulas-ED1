#include <stdio.h>

int main()
{
    float forca_base, bonus_arma, bonus_buff, dano_total;

    // Leitura dos valores
    scanf("%f %f %f", &forca_base, &bonus_arma, &bonus_buff);

    // Cálculo do dano total
    dano_total = forca_base + bonus_arma + bonus_buff;

    // Saída com duas casas decimais
    printf("Dano total: %.2f\n", dano_total);

    return 0;
}