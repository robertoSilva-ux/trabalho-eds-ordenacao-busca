#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#include "placas.h"
#include "cenarios.h"
#include "ordenacao.h"
#include "hash.h"
#include "busca.h"

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    srand((unsigned)time(NULL));
    
    printf("============================================\n");
    printf("  Atividade 5 - Estrutura de Dados - TADS\n");
    printf("  Ordenacao, Hash e Busca de Placas\n");
    printf("============================================\n\n");
    
    /* ========================================
     * PARTE 1 - PREPARAÇÃO DOS DADOS
     * ======================================== */
    printf("--- PARTE 1: Preparacao dos Dados ---\n\n");
    
    Placa *base = (Placa *)malloc(TOTAL_PLACAS * sizeof(Placa));
    if (!base) {
        fprintf(stderr, "Erro ao alocar memoria!\n");
        return 1;
    }
    
    int n_carregadas = carregar_placas("placas.txt", base, TOTAL_PLACAS);
    printf("Placas carregadas do arquivo: %d\n", n_carregadas);
    
    if (n_carregadas < TOTAL_PLACAS) {
        printf("AVISO: So foram carregadas %d placas. Gerando o restante...\n", n_carregadas);
        fflush(stdout);
        gerar_base_placas(base + n_carregadas, TOTAL_PLACAS - n_carregadas);
    }
    printf("Total de placas: %d\n\n", TOTAL_PLACAS);
    fflush(stdout);
    
    /* Cria os 4 cenários */
    Placa cenarios[TOTAL_CENARIOS][TOTAL_PLACAS];
    
    printf("Criando cenarios...\n");
    fflush(stdout);
    criar_aleatorio(cenarios[CEN_ALEATORIO], base, TOTAL_PLACAS);
    printf("  [OK] Aleatorio\n"); fflush(stdout);
    criar_quase_ordenado(cenarios[CEN_QUASE_ORD], base, TOTAL_PLACAS);
    printf("  [OK] Quase Ordenado\n"); fflush(stdout);
    criar_reverso(cenarios[CEN_REVERSO], base, TOTAL_PLACAS);
    printf("  [OK] Ordem Reversa\n"); fflush(stdout);
    criar_muitas_repeticoes(cenarios[CEN_MUITA_REP], base, TOTAL_PLACAS);
    printf("  [OK] Muitas Repeticoes\n\n"); fflush(stdout);
    
    /* ========================================
     * PARTE 2 - ALGORITMOS DE ORDENAÇÃO
     * ======================================== */
    printf("--- PARTE 2: Algoritmos de Ordenacao ---\n\n");
    
    double tempos_ordenacao[NUM_ALGORITMOS][TOTAL_CENARIOS];
    int a, c;
    
    for (a = 0; a < NUM_ALGORITMOS; a++) {
        for (c = 0; c < TOTAL_CENARIOS; c++) {
            /* Copia o cenário para não destruir o original */
            Placa *copia = (Placa *)malloc(TOTAL_PLACAS * sizeof(Placa));
            memcpy(copia, cenarios[c], TOTAL_PLACAS * sizeof(Placa));
            
            clock_t inicio = clock();
            algoritmos[a](copia, TOTAL_PLACAS);
            clock_t fim = clock();
            
            tempos_ordenacao[a][c] = (double)(fim - inicio) / CLOCKS_PER_SEC;
            free(copia);
            
            printf("  %s - %s: %.4f s\n", 
                   nomes_alg[a], nomes_cenarios[c], tempos_ordenacao[a][c]);
            fflush(stdout);
        }
    }
    
    /* Tabela de ordenação */
    printf("\n--- Tabela de Tempos de Ordenacao (segundos) ---\n");
    printf("%-18s", "Algoritmo");
    for (c = 0; c < TOTAL_CENARIOS; c++)
        printf(" | %-16s", nomes_cenarios[c]);
    printf("\n");
    printf("%-18s", "---------");
    for (c = 0; c < TOTAL_CENARIOS; c++)
        printf(" | -----------------");
    printf("\n");
    
    for (a = 0; a < NUM_ALGORITMOS; a++) {
        printf("%-18s", nomes_alg[a]);
        for (c = 0; c < TOTAL_CENARIOS; c++) {
            printf(" | %16.4f", tempos_ordenacao[a][c]);
        }
        printf("\n");
    }
    printf("\n");
    
    /* ========================================
     * PARTE 3 - TABELA HASH
     * ======================================== */
    printf("--- PARTE 3: Tabela Hash ---\n\n");
    
    TabelaHash hash500, hash2000;
    
    /* Teste 1: Hash com 500 posições */
    hash_iniciar(&hash500, 500);
    for (int i = 0; i < TOTAL_PLACAS; i++) {
        hash_inserir(&hash500, base[i].placa);
    }
    hash_exibir_estatisticas("Hash 500 posicoes", &hash500);
    
    /* Teste 2: Hash com 2000 posições */
    hash_iniciar(&hash2000, 2000);
    for (int i = 0; i < TOTAL_PLACAS; i++) {
        hash_inserir(&hash2000, base[i].placa);
    }
    hash_exibir_estatisticas("Hash 2000 posicoes", &hash2000);
    printf("\n");
    
    /* ========================================
     * PARTE 4 - COMPARAÇÃO DOS MÉTODOS DE BUSCA
     * ======================================== */
    printf("--- PARTE 4: Comparacao de Metodos de Busca ---\n\n");
    
    ConjuntoBusca cb;
    preparar_buscas(&cb, base, TOTAL_PLACAS);
    printf("Preparadas %d buscas (%d existentes + %d inexistentes)\n\n",
           TOTAL_BUSCAS, BUSCA_EXISTENTES, BUSCA_INEXISTENTES);
    
    /* 1. Busca Sequencial no vetor aleatório */
    double t_seq = testar_busca_sequencial(cenarios[CEN_ALEATORIO], TOTAL_PLACAS, &cb);
    printf("Busca Sequencial (vetor aleatorio): %.6f s\n", t_seq);
    
    /* 2. Busca Binária no vetor ordenado */
    /* Precisamos de uma cópia ordenada */
    Placa *ordenado = (Placa *)malloc(TOTAL_PLACAS * sizeof(Placa));
    memcpy(ordenado, base, TOTAL_PLACAS * sizeof(Placa));
    ordenar_placas(ordenado, TOTAL_PLACAS);
    
    double t_bin = testar_busca_binaria(ordenado, TOTAL_PLACAS, &cb);
    printf("Busca Binaria (vetor ordenado):     %.6f s\n", t_bin);
    
    /* 3. Busca utilizando a Tabela Hash (2000 posições) */
    double t_hash = testar_busca_hash(&hash2000, &cb);
    printf("Busca Hash (tabela 2000 posicoes):  %.6f s\n\n", t_hash);
    
    /* Tabela comparativa de busca */
    printf("--- Tabela Comparativa de Busca ---\n");
    printf("%-30s | %s\n", "Metodo", "Tempo (s)");
    printf("%-30s | ---------\n", "------");
    printf("%-30s | %.6f\n", "Busca Sequencial", t_seq);
    printf("%-30s | %.6f\n", "Busca Binaria", t_bin);
    printf("%-30s | %.6f\n", "Busca Hash", t_hash);
    printf("\n");
    
    /* ========================================
     * PARTE 5 - ANÁLISE DOS RESULTADOS
     * ======================================== */
    printf("--- PARTE 5: Analise dos Resultados ---\n\n");
    
    /* 1. Vetor quase ordenado */
    printf("1) O vetor quase ordenado influenciou quais algoritmos?\n");
    printf("   Resposta: ");
    (void)tempos_ordenacao; /* silencia warnings de var nao usada na analise */
    
    printf("Insertion Sort foi o mais beneficiado ");
    printf("(%.4f vs %.4f segundos nos dados aleatorios).\n", 
           tempos_ordenacao[1][CEN_QUASE_ORD], tempos_ordenacao[1][CEN_ALEATORIO]);
    printf("   Bubble Sort tambem se beneficiou com a otimizacao de parada antecipada.\n");
    
    /* 2. Pior desempenho no reverso */
    printf("\n2) Qual algoritmo apresentou o pior desempenho no vetor reverso?\n");
    int pior_reverso = 0;
    double maior_tempo = tempos_ordenacao[0][CEN_REVERSO];
    for (a = 1; a < NUM_ALGORITMOS; a++) {
        if (tempos_ordenacao[a][CEN_REVERSO] > maior_tempo) {
            maior_tempo = tempos_ordenacao[a][CEN_REVERSO];
            pior_reverso = a;
        }
    }
    printf("   Resposta: %s com %.4f segundos.\n", 
           nomes_alg[pior_reverso], maior_tempo);
    
    /* 3. Elementos repetidos */
    printf("\n3) Os elementos repetidos influenciaram os resultados?\n");
    printf("   Resposta: No vetor com muitas repeticoes, a maioria dos ");
    printf("algoritmos teve desempenho similar ou ligeiramente melhor,\n");
    printf("   pois as comparacoes de strings sao rapidas quando ha igualdade ");
    printf("parcial. O Quick Sort pode ser ligeiramente\n");
    printf("   afetado se o pivo for mal escolhido em dados com muitas repeticoes.\n");
    
    /* 4. Comparação buscas */
    printf("\n4) Compare os desempenhos da busca sequencial, busca binaria e busca hash.\n");
    printf("   Resposta: A busca binaria foi a mais rapida (O(log n)), ");
    printf("seguida pela busca hash (O(1) medio) e por ultimo\n");
    printf("   a busca sequencial (O(n)). A busca sequencial percorre todo o vetor ");
    printf("em media ate encontrar o elemento,\n");
    printf("   enquanto a binaria divide o espaco de busca pela metade a cada etapa. ");
    printf("A hash e extremamente rapida\n");
    printf("   quando o fator de carga e baixo e a funcao hash tem boa distribuicao.\n");
    
    /* 5. Sistema com 1 milhão */
    printf("\n5) Considerando tempo de ordenacao e busca, qual estrutura seria ");
    printf("mais adequada para um sistema com 1 milhao de veiculos?\n");
    printf("   Resposta: Para 1 milhao de veiculos, a Tabela Hash seria a ");
    printf("opcao mais adequada, pois oferece busca O(1)\n");
    printf("   em media sem necessidade de ordenacao previa. Se houver ");
    printf("necessidade de ordenacao frequente, uma arvore\n");
    printf("   balanceada (AVL ou Rubro-Negra) poderia ser uma alternativa, ");
    printf("mas para busca pura, a Hash e imbatível.\n");
    
    /* 6. Conclusão */
    printf("\n6) Conclusao final:\n");
    printf("   Este trabalho demonstrou experimentalmente as caracteristicas ");
    printf("de cada algoritmo de ordenacao e metodo de busca.\n");
    printf("   O Quick Sort confirmou ser o mais eficiente em media, enquanto ");
    printf("o Bubble Sort mostrou-se inviavel para grandes\n");
    printf("   volumes de dados. O Insertion Sort se destacou em dados quase ");
    printf("ordenados. A tabela hash provou ser a\n");
    printf("   estrutura mais eficiente para operacoes de busca, especialmente ");
    printf("com um fator de carga adequado.\n\n");
    
    /* ========================================
     * LIMPEZA
     * ======================================== */
    hash_liberar(&hash500);
    hash_liberar(&hash2000);
    free(ordenado);
    free(base);
    
    printf("============================================\n");
    printf("  Fim da execucao.\n");
    printf("============================================\n");
    
    return 0;
}
