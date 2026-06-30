#ifndef HASH_H
#define HASH_H

#include "placas.h"

/* Nó da lista simplesmente encadeada */
typedef struct HashNo {
    char placa[TAM_PLACA];
    struct HashNo *prox;
} HashNo;

typedef struct {
    HashNo **tabela;
    int tamanho;
    int num_elementos;
    int num_colisoes;
    int maior_lista;
} TabelaHash;

/* Inicializa tabela hash */
void hash_iniciar(TabelaHash *th, int tamanho);

/* Função hash para placa Mercosul */
unsigned int hash_funcao(const char *placa, int tam_tabela);

/* Insere uma placa na tabela */
void hash_inserir(TabelaHash *th, const char *placa);

/* Busca uma placa na tabela. Retorna 1 se encontrar, 0 caso contrário */
int hash_buscar(TabelaHash *th, const char *placa);

/* Calcula e armazena estatísticas (fator de carga, maior lista, média) */
void hash_calcular_estatisticas(TabelaHash *th, double *fator_carga, 
                                 int *maior_lista, double *media);

/* Exibe estatísticas da tabela */
void hash_exibir_estatisticas(const char *label, TabelaHash *th);

/* Libera toda a memória da tabela */
void hash_liberar(TabelaHash *th);

#endif
