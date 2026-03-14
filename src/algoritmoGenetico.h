#ifndef ALGORITMO_GENETICO_H
#define ALGORITMO_GENETICO_H

#include "geometria.h"

// CROMOSSOMO ------------------------------------------------------------
typedef struct {
    int quantidade_individuos;
    int quantidade_geracoes;
    float taxa_mutacao;
    float taxa_crossover;

} parametrosAG;

typedef struct {
    reta reta;
    float fitness;

}cromossomo;


#endif