#ifndef BUSCA_H
#define BUSCA_H

#include "placas.h"
#include "hash.h"

/* Número de placas para teste de busca */
#define BUSCA_EXISTENTES 800
#define BUSCA_INEXISTENTES 200
#define TOTAL_BUSCAS (BUSCA_EXISTENTES + BUSCA_INEXISTENTES)

/* Estrutura para armazenar as placas de teste */
typedef struct {
    Placa existentes[BUSCA_EXISTENTES];
    Placa inexistentes[BUSCA_INEXISTENTES];
} ConjuntoBusca;

/* Seleciona 800 placas existentes e gera 200 inexistentes */
void preparar_buscas(ConjuntoBusca *cb, Placa base[], int n);

/* Busca sequencial em vetor não ordenado */
int busca_sequencial(Placa vetor[], int n, const char *alvo);

/* Busca binária em vetor ordenado */
int busca_binaria(Placa vetor[], int n, const char *alvo);

/* Executa testes e retorna tempo */
double testar_busca_sequencial(Placa vetor[], int n, ConjuntoBusca *cb);
double testar_busca_binaria(Placa vetor[], int n, ConjuntoBusca *cb);
double testar_busca_hash(TabelaHash *th, ConjuntoBusca *cb);

#endif
