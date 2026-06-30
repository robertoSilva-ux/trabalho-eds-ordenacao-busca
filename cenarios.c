#include "cenarios.h"
#include <stdlib.h>
#include <string.h>

const char *nomes_cenarios[TOTAL_CENARIOS] = {
    "Aleatório",
    "Quase Ordenado",
    "Ordem Reversa",
    "Muitas Repetições"
};

void criar_aleatorio(Placa vetor[], Placa base[], int n) {
    memcpy(vetor, base, n * sizeof(Placa));
    /* Se a base já está ordenada, embaralha */
    embaralhar(vetor, n);
}

void criar_quase_ordenado(Placa vetor[], Placa base[], int n) {
    /* Copia a base e ordena */
    memcpy(vetor, base, n * sizeof(Placa));
    ordenar_placas(vetor, n);
    
    /* Embaralha ~5% dos elementos */
    int qtd = (int)(n * 0.05);
    if (qtd < 2) qtd = 2;
    
    int i;
    for (i = 0; i < qtd; i++) {
        int a = rand() % n;
        int b = rand() % n;
        Placa tmp = vetor[a];
        vetor[a] = vetor[b];
        vetor[b] = tmp;
    }
}

void criar_reverso(Placa vetor[], Placa base[], int n) {
    memcpy(vetor, base, n * sizeof(Placa));
    ordenar_placas(vetor, n);
    inverter(vetor, n);
}

void criar_muitas_repeticoes(Placa vetor[], Placa base[], int n) {
    /* Pega 500 placas distintas da base e repete */
    int num_distintas = 500;
    if (num_distintas > n) num_distintas = n;
    
    Placa distintas[500];
    int i;
    for (i = 0; i < num_distintas; i++) {
        int idx = rand() % n;
        strcpy(distintas[i].placa, base[idx].placa);
    }
    
    for (i = 0; i < n; i++) {
        strcpy(vetor[i].placa, distintas[rand() % num_distintas].placa);
    }
}

void embaralhar(Placa vetor[], int n) {
    int i;
    for (i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Placa tmp = vetor[i];
        vetor[i] = vetor[j];
        vetor[j] = tmp;
    }
}

void inverter(Placa vetor[], int n) {
    int i, j;
    for (i = 0, j = n - 1; i < j; i++, j--) {
        Placa tmp = vetor[i];
        vetor[i] = vetor[j];
        vetor[j] = tmp;
    }
}
