#ifndef CENARIOS_H
#define CENARIOS_H

#include "placas.h"

/* Identificadores dos cenários */
#define CEN_ALEATORIO     0
#define CEN_QUASE_ORD     1
#define CEN_REVERSO       2
#define CEN_MUITA_REP     3
#define TOTAL_CENARIOS    4

extern const char *nomes_cenarios[TOTAL_CENARIOS];

/* Cria vetor aleatório (cópia da base desordenada) */
void criar_aleatorio(Placa vetor[], Placa base[], int n);

/* Cria vetor quase ordenado: ordena e embaralha ~5% */
void criar_quase_ordenado(Placa vetor[], Placa base[], int n);

/* Cria vetor em ordem reversa */
void criar_reverso(Placa vetor[], Placa base[], int n);

/* Cria vetor com muitas repetições (poucas placas distintas) */
void criar_muitas_repeticoes(Placa vetor[], Placa base[], int n);

/* Função auxiliar: embaralha Fisher-Yates */
void embaralhar(Placa vetor[], int n);

/* Função auxiliar: inverte vetor */
void inverter(Placa vetor[], int n);

#endif
