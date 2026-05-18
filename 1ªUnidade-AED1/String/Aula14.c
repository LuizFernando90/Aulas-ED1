#include <stdio.h>
#include <string.h>

int main()
{

    // Frase padrão do chefe
    char frase_inicio_luta[] = "Voce nunca saira daqui com vida!";

    // Caixa de diálogo do jogo
    char caixa_dialogo[100] = "(Silencio)";

    // Estado inicial
    printf("Chefe antes da luta: %s\n", caixa_dialogo);

    // Copiando a frase do chefe para a caixa de diálogo
    strcpy(caixa_dialogo, frase_inicio_luta);

    // Estado após ativar o diálogo
    printf("Chefe diz: %s\n", caixa_dialogo);

    return 0;
}