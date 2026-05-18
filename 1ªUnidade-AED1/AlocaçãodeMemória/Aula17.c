#include <stdio.h>

int main() {

    // Matriz que representa o mapa da fase
    int mapa_fase1[5][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 0, 0, 2, 0, 1, 1},
        {0, 0, 1, 1, 0, 1, 0, 0},
        {1, 1, 1, 1, 2, 2, 1, 1}
    };

    // Percorrendo a matriz
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 8; j++) {

            // Verificando se existe espinho
            if(mapa_fase1[i][j] == 2) {
                printf("Espinho encontrado na linha %d, coluna %d\n", i, j);
            }

        }
    }

    return 0;
}