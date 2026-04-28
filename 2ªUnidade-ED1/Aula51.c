#include <stdio.h>

// Definição da struct
struct Inimigo
{
    char tipo[50];
    int hp;
};

int main()
{
    int n;

    // Ler quantidade de inimigos
    printf("Digite a quantidade de inimigos: ");
    scanf("%d", &n);

    // Criar vetor de inimigos
    struct Inimigo inimigos[n];

    // Ler dados e imprimir imediatamente
    for (int i = 0; i < n; i++)
    {
        printf("Digite o tipo e o HP do inimigo %d: ", i + 1);
        scanf("%s %d", inimigos[i].tipo, &inimigos[i].hp);

        // Impressão imediata (como o enunciado pede)
        printf("Inimigo: %s, HP: %d\n", inimigos[i].tipo, inimigos[i].hp);
    }

    return 0;
}