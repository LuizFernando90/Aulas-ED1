#ifndef PERSONAGEM_H
#define PERSONAGEM_H

typedef struct personagem Personagem;

Personagem *cria_party(int num_membros);

void registra_membros(Personagem *party, int num_membros);

void exibe_relatorio(const Personagem *party, int num_membros);

void libera_party(Personagem *party);

#endif