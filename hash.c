#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void hash_iniciar(TabelaHash *th, int tamanho) {
    th->tamanho = tamanho;
    th->num_elementos = 0;
    th->num_colisoes = 0;
    th->maior_lista = 0;
    th->tabela = (HashNo **)calloc(tamanho, sizeof(HashNo *));
}

unsigned int hash_funcao(const char *placa, int tam_tabela) {
    /* Função hash simples: soma dos caracteres */
    unsigned int hash = 0;
    int i;
    for (i = 0; placa[i] != '\0'; i++) {
        hash = hash * 31 + placa[i];
    }
    return hash % tam_tabela;
}

void hash_inserir(TabelaHash *th, const char *placa) {
    unsigned int indice = hash_funcao(placa, th->tamanho);
    
    /* Cria novo nó */
    HashNo *novo = (HashNo *)malloc(sizeof(HashNo));
    strcpy(novo->placa, placa);
    novo->prox = NULL;
    
    /* Se já existe elemento nessa posição, é colisão */
    if (th->tabela[indice] != NULL) {
        th->num_colisoes++;
    }
    
    /* Insere no início da lista (encadeamento externo) */
    novo->prox = th->tabela[indice];
    th->tabela[indice] = novo;
    th->num_elementos++;
}

int hash_buscar(TabelaHash *th, const char *placa) {
    unsigned int indice = hash_funcao(placa, th->tamanho);
    HashNo *atual = th->tabela[indice];
    
    while (atual != NULL) {
        if (strcmp(atual->placa, placa) == 0)
            return 1; /* Encontrou */
        atual = atual->prox;
    }
    return 0; /* Não encontrou */
}

void hash_calcular_estatisticas(TabelaHash *th, double *fator_carga,
                                 int *maior_lista, double *media) {
    int i;
    int max_lista = 0;
    int total_elementos = 0;
    
    for (i = 0; i < th->tamanho; i++) {
        int count = 0;
        HashNo *atual = th->tabela[i];
        while (atual != NULL) {
            count++;
            atual = atual->prox;
        }
        total_elementos += count;
        if (count > max_lista) max_lista = count;
    }
    
    *fator_carga = (double)th->num_elementos / th->tamanho;
    *maior_lista = max_lista;
    *media = (double)th->num_elementos / th->tamanho;
}

void hash_exibir_estatisticas(const char *label, TabelaHash *th) {
    double fator_carga, media;
    int maior_lista;
    
    hash_calcular_estatisticas(th, &fator_carga, &maior_lista, &media);
    
    printf("\n=== Estatísticas - %s ===\n", label);
    printf("Tamanho da tabela:  %d\n", th->tamanho);
    printf("Elementos inseridos: %d\n", th->num_elementos);
    printf("Número de colisões: %d\n", th->num_colisoes);
    printf("Fator de carga:     %.2f\n", fator_carga);
    printf("Maior lista encadeada: %d\n", maior_lista);
    printf("Média por posição:  %.2f\n", media);
}

void hash_liberar(TabelaHash *th) {
    int i;
    for (i = 0; i < th->tamanho; i++) {
        HashNo *atual = th->tabela[i];
        while (atual != NULL) {
            HashNo *prox = atual->prox;
            free(atual);
            atual = prox;
        }
    }
    free(th->tabela);
    th->tabela = NULL;
    th->num_elementos = 0;
}
