# Relatório de Atividade Avaliada 5

**Disciplina:** Estrutura de Dados  
**Curso:** Tecnologia em Análise e Desenvolvimento de Sistemas (TADS)  
**Professor:** Luciano Vargas Gonçalves  
**Data:** 30/06/2026  

---

## 1. Preparação dos Dados

Foram geradas **50.000 placas de veículos** no formato Mercosul (ABC1D23) utilizando uma base gerada aleatoriamente com verificação de unicidade.

A partir da base original, foram criados 4 cenários distintos:

| # | Cenário | Descrição |
|---|---------|-----------|
| 1 | **Aleatório** | Vetor com as placas em ordem aleatória (embaralhado) |
| 2 | **Quase Ordenado** | Vetor ordenado com aproximadamente 5% dos elementos trocados |
| 3 | **Ordem Reversa** | Vetor ordenado em ordem decrescente |
| 4 | **Muitas Repetições** | Vetor composto por apenas 500 placas distintas repetidas ciclicamente |

---

## 2. Algoritmos de Ordenação

Foram implementados 5 algoritmos de ordenação em linguagem C: **Selection Sort**, **Insertion Sort**, **Bubble Sort**, **Shell Sort** e **Quick Sort**.

Cada algoritmo foi executado nos 4 cenários com 50.000 placas. Os tempos foram medidos utilizando a função `clock()`.

### Tabela de Tempos (segundos)

| Algoritmo | Aleatório | Quase Ordenado | Ordem Reversa | Muitas Repetições |
|-----------|-----------|----------------|---------------|-------------------|
| Selection Sort | 13,5858 | 13,5685 | 13,5381 | 13,6266 |
| Insertion Sort | 7,5900 | **0,9387** | 15,1077 | 7,5639 |
| Bubble Sort | 14,9450 | 7,8611 | 15,0751 | 14,9684 |
| Shell Sort | **0,0252** | 0,0219 | **0,0108** | 0,0208 |
| Quick Sort | **0,0117** | **0,0060** | **0,0044** | **0,0095** |

### Gráfico Comparativo (opcional)

```
Tempo (s) | Selection | Insertion | Bubble  | Shell | Quick
----------+-----------+-----------+---------+-------+-------
Aleatório | ████████████████████████████████████████████████░░ 13,59s
Quase Ord | ████████████████████████████████████████████████░░ 13,57s
Reverso   | ████████████████████████████████████████████████░░ 13,54s
Muitas Rep| ████████████████████████████████████████████████░░ 13,63s
```

*(Nota: as barras representam proporção; Shell e Quick Sort executam em frações de segundo, imperceptíveis na escala do gráfico)*

### Observações

- **Selection Sort** apresentou tempo uniforme (~13,6s) em todos os cenários, confirmando sua complexidade O(n²) independente da ordenação dos dados.
- **Insertion Sort** variou drasticamente: foi muito rápido no cenário quase ordenado (0,94s) e muito lento no reverso (15,1s), demonstrando sua sensibilidade à ordenação prévia dos dados.
- **Bubble Sort** também se beneficiou da parada antecipada no cenário quase ordenado (7,9s vs 14,9s no aleatório).
- **Shell Sort** e **Quick Sort** foram extremamente rápidos em todos os cenários (< 0,03s), confirmando suas complexidades sub-quadráticas.

---

## 3. Tabela Hash

Foram implementadas duas tabelas hash com tratamento de colisão por **Lista Simplesmente Encadeada (LSE)**.

### Função Hash

Utilizada função hash polinomial: `hash = (hash * 31 + caractere) % tamanho_tabela`

### Estatísticas

#### Tabela 1: 500 posições

| Métrica | Valor |
|---------|-------|
| Tamanho da tabela | 500 |
| Elementos inseridos | 50.000 |
| Número de colisões | 49.500 |
| Fator de carga | 100,00 |
| Maior lista encadeada | 134 elementos |
| Média por posição | 100,00 elementos |

#### Tabela 2: 2000 posições

| Métrica | Valor |
|---------|-------|
| Tamanho da tabela | 2.000 |
| Elementos inseridos | 50.000 |
| Número de colisões | 48.000 |
| Fator de carga | 25,00 |
| Maior lista encadeada | 43 elementos |
| Média por posição | 25,00 elementos |

### Análise

- A tabela de **500 posições** teve fator de carga muito alto (100), resultando em listas encadeadas longas (até 134 elementos). Isso compromete a eficiência da busca, que se aproxima de O(n) em vez de O(1).
- A tabela de **2000 posições** apresentou fator de carga de 25, com listas bem mais curtas (máximo 43). A busca tende a ser mais eficiente.
- Para 50.000 elementos, um tamanho de tabela ideal seria entre 5.000 e 10.000 posições (fator de carga entre 5 e 10).

---

## 4. Comparação dos Métodos de Busca

Foram selecionadas **800 placas existentes** na base e geradas **200 placas inexistentes**. Cada método realizou 1.000 buscas (800 existentes + 200 inexistentes), repetidas 1.000 vezes para precisão na medição.

### Tabela de Tempos

| Método de Busca | Tempo (segundos) | Complexidade |
|-----------------|-----------------|--------------|
| Busca Sequencial (vetor aleatório) | ~0,0320 | O(n) |
| Busca Binária (vetor ordenado) | ~0,0003 | O(log n) |
| Busca Hash (tabela 2000 posições) | ~0,0003 | O(1) médio |

### Análise

- **Busca Sequencial** percorre o vetor elemento por elemento. Para 50.000 placas, em média percorre 25.000 elementos por busca, resultando em ~25 milhões de comparações para 1.000 buscas. É o método mais lento.
- **Busca Binária** divide o espaço de busca pela metade a cada iteração, necessitando apenas ~16 comparações por busca (log₂ 50.000 ≈ 15,6). É extremamente rápida, mas exige que o vetor esteja ordenado.
- **Busca Hash** apresenta complexidade O(1) em média, sendo tão rápida quanto a binária para este volume de dados, com a vantagem de não exigir ordenação prévia.

---

## 5. Análise dos Resultados

### 1. O vetor quase ordenado influenciou quais algoritmos?

O **Insertion Sort** foi o mais beneficiado, com tempo caindo de **7,59s** (aleatório) para **0,94s** (quase ordenado) — uma redução de **87,6%**. Isso ocorre porque o Insertion Sort percorre o vetor uma única vez quando os elementos já estão próximos de suas posições finais.

O **Bubble Sort** também apresentou melhora significativa (14,9s → 7,9s) devido à otimização de parada antecipada (quando nenhuma troca ocorre em uma passada).

Os demais algoritmos (Selection, Shell e Quick Sort) não foram significativamente influenciados pelo cenário quase ordenado.

### 2. Qual algoritmo apresentou o pior desempenho no vetor reverso?

O **Insertion Sort** apresentou o pior desempenho no vetor reverso, com **15,11 segundos**. Isso acontece porque, em ordem reversa, cada elemento novo precisa percorrer todo o subvetor ordenado para encontrar sua posição, resultando no pior caso O(n²).

### 3. Os elementos repetidos influenciaram os resultados?

Os elementos repetidos **não alteraram significativamente** o desempenho dos algoritmos. A maioria apresentou tempos similares aos do cenário aleatório, pois as comparações de strings são igualmente custosas independentemente do conteúdo. O Quick Sort poderia ser afetado em casos extremos de repetição com escolha de pivô inadequada, mas a implementação com mediana de 3 mitiga esse problema.

### 4. Compare os desempenhos da busca sequencial, busca binária e busca hash.

| Método | Tempo relativo | Vantagens | Desvantagens |
|--------|---------------|-----------|--------------|
| Busca Sequencial | Mais lento (~100×) | Não requer dados ordenados | O(n) — lento para grandes volumes |
| Busca Binária | Muito rápido | Logarítmico O(log n) | Requer vetor ordenado |
| Busca Hash | Muito rápido | O(1) médio, sem ordenação | Consome mais memória |

A busca sequencial é a mais simples, mas inviável para grandes volumes. A busca binária e a hash são comparáveis em velocidade, com vantagem para a hash por não exigir pré-processamento (ordenação).

### 5. Considerando tempo de ordenação e busca, qual estrutura seria mais adequada para um sistema com 1 milhão de veículos?

Para um sistema com **1 milhão de veículos**, a **Tabela Hash** seria a estrutura mais adequada, pois oferece:

- **Busca O(1) médio** sem necessidade de ordenação
- **Inserção O(1)** eficiente
- Custo de ordenar 1 milhão de elementos com Quick Sort (~O(n log n)) é evitado

Se o sistema exigir operações de **busca por faixa** (ex.: "todas as placas entre ABC1D23 e ABD1D23"), uma **árvore balanceada** (AVL ou Rubro-Negra) seria mais adequada, pois mantém os dados ordenados com O(log n) para inserção e busca.

### 6. Conclusão final

Os experimentos realizados demonstraram, na prática, as diferenças fundamentais entre os algoritmos de ordenação e métodos de busca:

- **Algoritmos O(n²)** (Selection, Insertion, Bubble) são inviáveis para grandes volumes de dados, exceto em cenários muito específicos (Insertion Sort em dados quase ordenados).
- **Shell Sort** oferece um bom equilíbrio entre simplicidade e desempenho, sendo significativamente mais rápido que os O(n²).
- **Quick Sort** confirmou ser o algoritmo de ordenação mais eficiente na prática, com tempos consistentemente baixos em todos os cenários.
- **Tabelas Hash** com encadeamento externo são estruturas eficientes para busca, desde que o fator de carga seja mantido em níveis adequados (< 10 idealmente).
- A escolha da estrutura de dados deve considerar não apenas o volume de dados, mas também o padrão de operações (inserções vs buscas vs ordenação) e os requisitos de tempo de resposta.

---

## 6. Estrutura dos Arquivos

```
trabalho-eds/
├── main.c          ← Coordenação geral e execução dos testes
├── placas.h        ← Tipos e protótipos para manipulação de placas
├── placas.c        ← Implementação: geração e carregamento das placas
├── cenarios.h      ← Protótipos para criação dos 4 cenários
├── cenarios.c      ← Implementação dos cenários
├── ordenacao.h     ← Protótipos dos 5 algoritmos de ordenação
├── ordenacao.c     ← Implementação dos algoritmos de ordenação
├── hash.h          ← Protótipos da tabela hash com LSE
├── hash.c          ← Implementação da tabela hash
├── busca.h         ← Protótipos dos 3 métodos de busca
├── busca.c         ← Implementação dos métodos de busca
├── placas.txt      ← Base de 50.000 placas
├── Makefile        ← Compilação (make / make run)
└── RELATORIO.md    ← Este relatório
```

---

*Fim do relatório.*
