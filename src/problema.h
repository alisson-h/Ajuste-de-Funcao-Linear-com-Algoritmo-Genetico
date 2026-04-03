#ifndef PROBLEMA_H
#define PROBLEMA_H

#include <stdio.h>
#include <stdlib.h>

// PARAMETROS ALGORITMO GENETICO -----------------------------------------
typedef struct {
    int quantidade_individuos;
    int quantidade_geracoes;
    float taxa_mutacao;
    float taxa_crossover;

} parametrosAG;

// PONTO (x, y) ----------------------------------------------------------
typedef struct geo_0{
    double x;
    double y;
}ponto;

// RETA (y = ax + b) -----------------------------------------------------
typedef struct {
    double a;
    double b;
}reta;

// DATA SET --------------------------------------------------------------
typedef struct {
    ponto* lista_pontos;
    int quantidade_pontos;

} dataset;

// PROBLEMA --------------------------------------------------------------
typedef struct {
    dataset data_set;
    parametrosAG parametros_AG;
    int tamanho_espacial;

} problema;

// SOLUCAO ---------------------------------------------------------------
typedef struct {
    double* fitness;
    reta* retas;
    double* erros;
    int geracao_final;
    
} solucao;

/**
 * @brief Constrói um problema base com os parâmetros fornecidos.
 */
problema* ConstruirProblemaBase(int n, int m, int g);

/**
 * @brief Exibe as informações do problema, incluindo os pontos do conjunto de dados e os parâmetros do algoritmo genético.
 */
void ExibirProblema(problema* problema);

/**
 * @brief Constrói uma solução base com os parâmetros fornecidos.
 */
solucao* ConstruirSolucaoBase();

/**
 * @brief Libera a memória alocada para a solução.
 */
void deletarSolucao(solucao* solucao);

/**
 * @brief Calcula o Erro Absoluto Médio (MAE) para uma reta e um conjunto de dados.
 */
float calcularMAE(reta reta, dataset data_set);

/**
 * @brief Calcula o Erro Quadrático Médio (MSE) para uma reta e um conjunto de dados.
 */
float calcularMSE(reta reta, dataset data_set);

/**
 * @brief Cria um ponto com as coordenadas x e y fornecidas.
 * @return O ponto criado.
 */
ponto criarPonto(int x, int y);

/**
 * @brief Cria um ponto aleatório.
 * @return O ponto criado.
 */
ponto criarPontoAleatorio();

/**
 * @brief Calcula o valor de x para uma reta com o valor de y fornecido.
 * @return O valor de x calculado.
 */
float calcularXReta(reta reta, float y);

/**
 * @brief Calcula o valor de y para uma reta com o valor de x fornecido.
 * @return O valor de y calculado.
 */
float calcularYReta(reta reta, float x);

#endif