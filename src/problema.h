#ifndef PROBLEMA_H
#define PROBLEMA_H

#include <stdio.h>
#include <stdlib.h>

#include "algoritmoGenetico.h"
#include "geometria.h"

// PROBLEMA --------------------------------------------------------------
typedef struct {
    dataset data_set;
    parametrosAG parametros_AG;
    int tamanho_espacial;

} problema;

typedef struct {
    double* fitness;
    reta* retas;
    double* erros;

} solucao;

problema* ConstruirProblemaBase(int n, int m, int g);
void deletarSolucao(solucao* solucao);

float calcularMAE(reta reta, dataset data_set);
float calcularMSE(reta reta, dataset data_set);


void ExibirProblema(problema* problema);
// FUNÇOES IMPORTANTES ---------------------------------------------------
float calcularErroAbsolutoMedio(reta reta, dataset data_set);


#endif