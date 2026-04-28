#include <stdio.h>

int main()
{
    int energia;

    // Ler energia inicial
    printf("Digite a energia inicial do Golem: ");
    scanf("%d", &energia);

    // Loop do ritual
    while (energia > 1)
    {
        printf("%d\n", energia);
        energia = energia / 2; // divisão inteira
    }

    return 0;
}