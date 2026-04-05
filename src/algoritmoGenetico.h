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
void gerarPopulacaoInicial(cromossomo* populacao, dataset data_set, int quantidade_individuos);

/**
 * @brief Avalia a população de cromossomos usando o Erro Absoluto Médio (MAE).
 * @param populacao A lista dinâmica de cromossomos a ser avaliada.
 * @param quantidade_individuos O número de indivíduos na população.
 * @param data_set O conjunto de dados usado para avaliar os cromossomos.
 */
void avaliarPopulacaoMAE(cromossomo* populacao, int quantidade_individuos, int inicio, dataset data_set);

/**
 * @brief Compara dois cromossomos com base em seu fitness para ordenação quicksort.
 * @param a O primeiro cromossomo a ser comparado.
 * @param b O segundo cromossomo a ser comparado.
 * @return Um valor negativo se o primeiro cromossomo for melhor, um valor positivo se o segundo for melhor, ou zero se forem iguais.
 */
int compararCromossomos(const void* a, const void* b);

/**
 * @brief Realiza o crossover aritmético entre os cromossomos selecionados.
 * @param populacao A lista dinâmica de cromossomos que representa a população.
 * @param quantidade_individuos O número de indivíduos na população.
 * @param quantidade_selecionados O número de indivíduos selecionados para reprodução.
 * @param taxa_crossover A taxa de crossover.
 */
void crossoverPopulacao(cromossomo* populacao, int quantidade_individuos, int quantidade_selecionados, double taxa_crossover);

/**
 * @brief Realiza a mutação em um cromossomo, alterando seus genes de forma aleatória.
 * @param populacao A lista dinâmica de cromossomos que representa a população.
 * @param quantidade_eletismo O número de indivíduos a serem mantidos inalterados nanova população (elitismo).
 * @param quantidade_individuos O número total de indivíduos na população.
 * @param taxa_mutacao A taxa de mutação.
 */
void mutacaoPopulacao(cromossomo* populacao, int quantidade_eletismo, int quantidade_individuos, double taxa_mutacao);

/**
 * @brief Gera uma nova população de cromossomos a partir da população atual, aplicando seleção, crossover e mutação.
 * @param populacao A lista dinâmica de cromossomos que representa a população atual.
 * @param parametros_AG Os parâmetros do algoritmo genético.
 * @param quantidade_eletismo O número de indivíduos a serem mantidos inalterados na nova população (elitismo).
 * @param quantidade_individuos_selecionados O número de indivíduos a serem selecionados para reprodução na nova população.
 */
void gerarNovaPopulacao(cromossomo* populacao, parametrosAG parametros_AG, int quantidade_eletismo, int quantidade_individuos_selecionados);

#endif