#include "busca.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void preparar_buscas(ConjuntoBusca *cb, Placa base[], int n) {
    int i, j;
    
    for (i = 0; i < BUSCA_EXISTENTES; i++) {
        int idx = rand() % n;
        strcpy(cb->existentes[i].placa, base[idx].placa);
    }
    
    for (i = 0; i < BUSCA_INEXISTENTES; i++) {
        char temp[TAM_PLACA];
        int valido;
        do {
            gerar_placa(temp);
            valido = 1;
            for (j = 0; j < n; j++) {
                if (strcmp(temp, base[j].placa) == 0) {
                    valido = 0;
                    break;
                }
            }
        } while (!valido);
        strcpy(cb->inexistentes[i].placa, temp);
    }
}

int busca_sequencial(Placa vetor[], int n, const char *alvo) {
    int i;
    for (i = 0; i < n; i++) {
        if (strcmp(vetor[i].placa, alvo) == 0)
            return 1;
    }
    return 0;
}

int busca_binaria(Placa vetor[], int n, const char *alvo) {
    int esq = 0, dir = n - 1;
    while (esq <= dir) {
        int meio = esq + (dir - esq) / 2;
        int cmp = strcmp(vetor[meio].placa, alvo);
        if (cmp == 0) return 1;
        if (cmp < 0) esq = meio + 1;
        else dir = meio - 1;
    }
    return 0;
}

double testar_busca_sequencial(Placa vetor[], int n, ConjuntoBusca *cb) {
    int repeticoes = 1000;
    int i, r;
    volatile int encontrados = 0; /* força o compilador a não otimizar */
    
    clock_t inicio = clock();
    
    for (r = 0; r < repeticoes; r++) {
        for (i = 0; i < BUSCA_EXISTENTES; i++) {
            encontrados += busca_sequencial(vetor, n, cb->existentes[i].placa);
        }
        for (i = 0; i < BUSCA_INEXISTENTES; i++) {
            encontrados += busca_sequencial(vetor, n, cb->inexistentes[i].placa);
        }
    }
    
    clock_t fim = clock();
    (void)encontrados;
    return (double)(fim - inicio) / CLOCKS_PER_SEC / repeticoes;
}

double testar_busca_binaria(Placa vetor[], int n, ConjuntoBusca *cb) {
    int repeticoes = 1000;
    int i, r;
    volatile int encontrados = 0;
    
    clock_t inicio = clock();
    
    for (r = 0; r < repeticoes; r++) {
        for (i = 0; i < BUSCA_EXISTENTES; i++) {
            encontrados += busca_binaria(vetor, n, cb->existentes[i].placa);
        }
        for (i = 0; i < BUSCA_INEXISTENTES; i++) {
            encontrados += busca_binaria(vetor, n, cb->inexistentes[i].placa);
        }
    }
    
    clock_t fim = clock();
    (void)encontrados;
    return (double)(fim - inicio) / CLOCKS_PER_SEC / repeticoes;
}

double testar_busca_hash(TabelaHash *th, ConjuntoBusca *cb) {
    int repeticoes = 1000;
    int i, r;
    volatile int encontrados = 0;
    
    clock_t inicio = clock();
    
    for (r = 0; r < repeticoes; r++) {
        for (i = 0; i < BUSCA_EXISTENTES; i++) {
            encontrados += hash_buscar(th, cb->existentes[i].placa);
        }
        for (i = 0; i < BUSCA_INEXISTENTES; i++) {
            encontrados += hash_buscar(th, cb->inexistentes[i].placa);
        }
    }
    
    clock_t fim = clock();
    (void)encontrados;
    return (double)(fim - inicio) / CLOCKS_PER_SEC / repeticoes;
}
