/** ===========================================================================================
 *
 * Trabalho Aquecimento de Algoritmos e Estruturas de Dados
 * 
 *  Objetivo: Implementar um algoritmo genético para resolver um problema de ajuste de curva,
 *  onde o objetivo é encontrar os coeficientes de uma reta (y = ax + b) que melhor se ajusta
 *  a um conjunto de pontos (x, y) usando o Erro Absoluto Médio (MAE) como função de fitness.
 * 
 * Aluno: Alisson Henrique Gomes
 * Data: 05/04/2026
 * 
 * Prof: Michael Pires Silva
 * 
 * ========================================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "problema.h"
#include "leitor.h"
#include "algoritmoGenetico.h"

int main(){
    // INICIO ----------------------
    srand(73);
    clock_t tempo_inicial = clock();

    problema* problema = lerInputParaProblema();
    if (problema == NULL){
        printf("Algoritmo nao iniciado. \n");
        return 0;
    }
    // -----------------------------
    // EXECUÇÃO --------------------
    solucao* solucao = AlgoritmoGenetico(problema);
    // -----------------------------

    // FINAL -----------------------
    clock_t tempo_final = clock();
    double tempo_algoritmo = (double)(tempo_final - tempo_inicial) / CLOCKS_PER_SEC;

    criarOutput(solucao);

    printf("Tempo de execucao: %lf segundos\n", tempo_algoritmo);
    
    deletarSolucao(solucao);
    free(problema);
    // -----------------------------
    return 0;
}