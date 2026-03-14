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

problema* ConstruirProblemaBase(int n, int m, int g);
void ExibirProblema(problema* problema);
/*
void ExibirProblema(problema* problema){
    
    if (problema == NULL){
        printf("Problema NULO");
        return;
    }
    printf("Problema:\n");
    printf("Quantidade de Pontos: %d ==\n", problema->data_set.quantidade_pontos);
    for (int i = 0; i < problema->data_set.quantidade_pontos; i++){
        ponto p = problema->data_set.lista_pontos[i];
        printf("Ponto %d: (%.2f, %.2f)\n",i + 1, p.x, p.y);
    }
    printf("= Algoritmo Genetico ======\n");
    printf("Quantidade de Individuos: %d\n", problema->parametros_AG.quantidade_individuos);
    printf("Quantidade de Geracoes: %d\n", problema->parametros_AG.quantidade_individuos);
    
}
*/
// FUNÇOES IMPORTANTES ---------------------------------------------------
float calcularErroAbsolutoMedio(reta reta, dataset data_set);


#endif