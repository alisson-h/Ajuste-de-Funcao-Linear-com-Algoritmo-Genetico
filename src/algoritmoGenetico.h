#ifndef ALGORITMO_GENETICO_H
#define ALGORITMO_GENETICO_H

#include "problema.h"

solucao* AlgoritmoGenetico(problema* p);

// CROMOSSOMO ------------------------------------------------------------
typedef struct {
    reta reta;
    float fitness;

}cromossomo;

/**
 * @brief Executa o algoritmo genético para resolver o problema fornecido.
 * @param p O problema para o qual o algoritmo genético será executado.
 * @return A solução encontrada pelo algoritmo genético.
 */
solucao* AlgoritmoGenetico(problema* p);

/**
 * @brief Gera um cromossomo aleatório.
 * @param cromossomo O cromossomo a ser aleatorizado.
 */
void aleatorizarCromossomo(cromossomo* cromossomo);

/**
 * @brief Gera a população inicial de cromossomos.
 * @param populacao A lista dinâmica de cromossomos que representa a população.
 * @param quantidade_individuos O número de indivíduos na população.
 */
void gerarPopulacaoInicial(cromossomo* populacao, int quantidade_individuos);

/**
 * @brief Avalia a população de cromossomos usando o Erro Absoluto Médio (MAE).
 * @param populacao A lista dinâmica de cromossomos a ser avaliada.
 * @param quantidade_individuos O número de indivíduos na população.
 * @param data_set O conjunto de dados usado para avaliar os cromossomos.
 */
void avaliarPopulacaoMAE(cromossomo* populacao, int quantidade_individuos, dataset data_set);

/**
 * @brief Avalia a população de cromossomos usando o Erro Quadrático Médio (MSE).
 * @param populacao A lista dinâmica de cromossomos a ser avaliada.
 * @param quantidade_individuos O número de indivíduos na população.
 * @param data_set O conjunto de dados usado para avaliar os cromossomos.
 */
void avaliarPopulacaoMSE(cromossomo* populacao, int quantidade_individuos, dataset data_set);

/**
 * @brief 
 */
void swap(cromossomo *a, cromossomo *b);

/**
 * @brief 
 */
void quickSort(cromossomo* arr, int low, int high);

/**
 * @brief
 */
int partition(cromossomo arr[], int low, int high);

int particiona(cromossomo* pop, int inicio, int fim);
/**
 * @brief Realiza o algoritmo de seleção QuickSelect para encontrar o k-ésimo menor elemento na população de cromossomos.
 * @param pop A lista dinâmica de cromossomos a ser processada.
 * @param inicio O índice de início do segmento da população a ser considerado.
 * @param fim O índice de fim do segmento da população a ser considerado.
 * @param k O índice do elemento a ser encontrado (0-based).
 */
void quickSelect(cromossomo* pop, int inicio, int fim, int k);

/**
 * @brief Realiza a mutação em um cromossomo, alterando seus genes de forma aleatória.
 * @param cromossomo O cromossomo a ser mutado.
 */
void mutacao(cromossomo* cromossomo);

/**
 * @brief Gera uma nova população de cromossomos a partir da população atual, aplicando seleção, crossover e mutação.
 * @param populacao A lista dinâmica de cromossomos que representa a população atual.
 * @param parametros_AG Os parâmetros do algoritmo genético.
 * @param geracao_atual O número da geração atual.
 */
void gerarNovaPopulacao(cromossomo* populacao, parametrosAG parametros_AG, int quantidade_eletismo, int quantidade_individuos_selecionados);

#endif