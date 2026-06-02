void deletar_fim(Lista *plista)
{
    // Caso 1: lista vazia
    if (plista->inicio == NULL)
    {
        printf("Nao e possivel remover jogadores.\n");
        return;
    }

    // Caso 2: apenas um jogador
    if (plista->inicio->prox == NULL)
    {
        free(plista->inicio);
        plista->inicio = NULL;
        return;
    }

    // Caso 3: varios jogadores
    No *anterior = NULL;
    No *atual = plista->inicio;

    while (atual->prox != NULL)
    {
        anterior = atual;
        atual = atual->prox;
    }

    anterior->prox = NULL;
    free(atual);
}