#include "placas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static const char LETRAS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const char DIGITOS[] = "0123456789";

void gerar_placa(char *placa) {
    placa[0] = LETRAS[rand() % 26];
    placa[1] = LETRAS[rand() % 26];
    placa[2] = LETRAS[rand() % 26];
    placa[3] = DIGITOS[rand() % 10];
    placa[4] = LETRAS[rand() % 10];
    placa[5] = DIGITOS[rand() % 10];
    placa[6] = DIGITOS[rand() % 10];
    placa[7] = '\0';
}

int cmp_placas(const void *a, const void *b) {
    return strcmp(((Placa *)a)->placa, ((Placa *)b)->placa);
}

void ordenar_placas(Placa vetor[], int n) {
    qsort(vetor, n, sizeof(Placa), cmp_placas);
}

void gerar_base_placas(Placa vetor[], int n) {
    int i;
    /* Gera n+20% placas, ordena, remove duplicatas */
    int extra = n + n / 5;
    Placa *temp = (Placa *)malloc(extra * sizeof(Placa));
    
    for (i = 0; i < extra; i++) {
        gerar_placa(temp[i].placa);
    }
    
    ordenar_placas(temp, extra);
    
    /* Remove duplicatas */
    int j = 0;
    for (i = 0; i < extra && j < n; i++) {
        if (i == 0 || strcmp(temp[i].placa, temp[i-1].placa) != 0) {
            strcpy(vetor[j].placa, temp[i].placa);
            j++;
        }
    }
    
    /* Se ainda faltarem, gera mais */
    while (j < n) {
        char placa[TAM_PLACA];
        int repetido;
        do {
            gerar_placa(placa);
            repetido = 0;
            int k;
            for (k = 0; k < j; k++) {
                if (strcmp(vetor[k].placa, placa) == 0) {
                    repetido = 1;
                    break;
                }
            }
        } while (repetido);
        strcpy(vetor[j].placa, placa);
        j++;
    }
    
    free(temp);
}

int carregar_placas(const char *arquivo, Placa vetor[], int max) {
    FILE *f = fopen(arquivo, "r");
    if (!f) return 0;
    
    int count = 0;
    char linha[32];
    while (count < max && fscanf(f, "%7s", linha) == 1) {
        if (strlen(linha) >= 7) {
            memcpy(vetor[count].placa, linha, TAM_PLACA - 1);
            vetor[count].placa[TAM_PLACA - 1] = '\0';
            count++;
        }
    }
    fclose(f);
    return count;
}
