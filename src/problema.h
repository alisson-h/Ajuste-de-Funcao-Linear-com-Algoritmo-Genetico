#ifndef PROBLEMA
#define PROBLEMA

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "algoritmoGenetico.h"
#include "geometria.h"

// PROBLEMA --------------------------------------------------------------
typedef struct{
    dataset data_set;
    parametrosAG parametros_AG;
    int tamanho_espacial;

} problema;

problema ConstruirProblema(int n, int m, int g, ponto* lista_pontos){
    problema p;

    p.data_set.lista_pontos = lista_pontos;
    p.data_set.quantidade_pontos = n;

    p.parametros_AG.quantidade_individuos = m;
    p.parametros_AG.quantidade_geracoes = g;
    
    //-- A ser decidido
    p.parametros_AG.taxa_mutacao = 0.05;
    p.parametros_AG.taxa_crossover = 0.9;


    return p;
}

// FUNÇOES IMPORTANTES ---------------------------------------------------
float calcularErroAbsolutoMedio(reta reta, dataset data_set){
    float MAE = 0;

   for (int i = 0; i < data_set.quantidade_pontos; i++)
    {
        ponto ponto = data_set.lista_pontos[i];
        MAE += abs(ponto.y - calcularYReta(reta, ponto.x));

    }

    MAE *= 1/data_set.quantidade_pontos;

    return MAE;
}



#endif