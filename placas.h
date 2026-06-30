#ifndef PLACAS_H
#define PLACAS_H

#define TAM_PLACA 8
#define TOTAL_PLACAS 50000

typedef struct {
    char placa[TAM_PLACA];
} Placa;

/* Gera uma placa Mercosul aleatória (ABC1D23) */
void gerar_placa(char *placa);

/* Preenche um vetor com placas aleatórias, sem repetir */
void gerar_base_placas(Placa vetor[], int n);

/* Carrega placas de um arquivo texto (uma por linha) */
int carregar_placas(const char *arquivo, Placa vetor[], int max);

/* Ordena o vetor de placas (qsort wrapper) para busca binária */
void ordenar_placas(Placa vetor[], int n);

/* Comparação para qsort */
int cmp_placas(const void *a, const void *b);

#endif
