#include <stdio.h>

#include "spellbook.h"

int main()
{
    Spellbook *grimorio;

    grimorio =
        create_spellbook();

    add_spell(
        grimorio,
        1,
        "Bola de Fogo",
        30);

    add_spell(
        grimorio,
        2,
        "Raio de Gelo",
        20);

    add_spell(
        grimorio,
        3,
        "Tempestade Arcana",
        50);

    display_spellbook(grimorio);

    destroy_spellbook(grimorio);

    return 0;
}