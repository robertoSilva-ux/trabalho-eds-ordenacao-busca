#include "ordenacao.h"
#include <string.h>

const char *nomes_alg[NUM_ALGORITMOS] = {
    "Selection Sort",
    "Insertion Sort",
    "Bubble Sort",
    "Shell Sort",
    "Quick Sort"
};

void selection_sort(Placa vetor[], int n) {
    int i, j, min;
    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            if (strcmp(vetor[j].placa, vetor[min].placa) < 0)
                min = j;
        }
        if (min != i) {
            Placa tmp = vetor[i];
            vetor[i] = vetor[min];
            vetor[min] = tmp;
        }
    }
}

void insertion_sort(Placa vetor[], int n) {
    int i, j;
    Placa chave;
    for (i = 1; i < n; i++) {
        chave = vetor[i];
        j = i - 1;
        while (j >= 0 && strcmp(vetor[j].placa, chave.placa) > 0) {
            vetor[j + 1] = vetor[j];
            j--;
        }
        vetor[j + 1] = chave;
    }
}

void bubble_sort(Placa vetor[], int n) {
    int i, j;
    int trocou;
    for (i = 0; i < n - 1; i++) {
        trocou = 0;
        for (j = 0; j < n - i - 1; j++) {
            if (strcmp(vetor[j].placa, vetor[j + 1].placa) > 0) {
                Placa tmp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = tmp;
                trocou = 1;
            }
        }
        if (!trocou) break; /* Otimização: já está ordenado */
    }
}

void shell_sort(Placa vetor[], int n) {
    int gap, i, j;
    Placa temp;
    
    for (gap = n / 2; gap > 0; gap /= 2) {
        for (i = gap; i < n; i++) {
            temp = vetor[i];
            j = i;
            while (j >= gap && strcmp(vetor[j - gap].placa, temp.placa) > 0) {
                vetor[j] = vetor[j - gap];
                j -= gap;
            }
            vetor[j] = temp;
        }
    }
}

/* Quick Sort - versão recursiva com mediana de 3 para pivô */
static void qs_recursivo(Placa vetor[], int esq, int dir) {
    if (esq >= dir) return;
    
    /* Mediana de 3 */
    int meio = esq + (dir - esq) / 2;
    if (strcmp(vetor[esq].placa, vetor[meio].placa) > 0) {
        Placa tmp = vetor[esq]; vetor[esq] = vetor[meio]; vetor[meio] = tmp;
    }
    if (strcmp(vetor[esq].placa, vetor[dir].placa) > 0) {
        Placa tmp = vetor[esq]; vetor[esq] = vetor[dir]; vetor[dir] = tmp;
    }
    if (strcmp(vetor[meio].placa, vetor[dir].placa) > 0) {
        Placa tmp = vetor[meio]; vetor[meio] = vetor[dir]; vetor[dir] = tmp;
    }
    
    /* Pivô é o elemento do meio */
    Placa pivo = vetor[meio];
    int i = esq, j = dir;
    
    while (i <= j) {
        while (strcmp(vetor[i].placa, pivo.placa) < 0) i++;
        while (strcmp(vetor[j].placa, pivo.placa) > 0) j--;
        if (i <= j) {
            Placa tmp = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = tmp;
            i++;
            j--;
        }
    }
    
    if (esq < j) qs_recursivo(vetor, esq, j);
    if (i < dir) qs_recursivo(vetor, i, dir);
}

void quick_sort(Placa vetor[], int n) {
    if (n <= 1) return;
    qs_recursivo(vetor, 0, n - 1);
}

void (*algoritmos[NUM_ALGORITMOS])(Placa [], int) = {
    selection_sort,
    insertion_sort,
    bubble_sort,
    shell_sort,
    quick_sort
};
