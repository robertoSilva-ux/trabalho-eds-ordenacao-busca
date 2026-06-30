#ifndef ORDENACAO_H
#define ORDENACAO_H

#include "placas.h"

#define NUM_ALGORITMOS 5

extern const char *nomes_alg[NUM_ALGORITMOS];

/* Cada função ordena o vetor in-place */
void selection_sort(Placa vetor[], int n);
void insertion_sort(Placa vetor[], int n);
void bubble_sort(Placa vetor[], int n);
void shell_sort(Placa vetor[], int n);
void quick_sort(Placa vetor[], int n);

/* Ponteiros para as funções */
extern void (*algoritmos[NUM_ALGORITMOS])(Placa [], int);

#endif
