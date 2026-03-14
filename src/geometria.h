#ifndef GEOMETRIA_H
#define GEOMETRIA_H

#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_ESPACIAL 50
#define QUANTIDADE_PONTOS 20

// PONTO (x, y) ----------------------------------------------------------
typedef struct geo_0{
    float x;
    float y;
}ponto;

ponto criarPonto(int x, int y);

ponto criarPontoAleatorio();

// RETA (y = ax + b) -----------------------------------------------------
typedef struct {
    float a;
    float b;
}reta;

float calcularXReta(reta reta, float y);

float calcularYReta(reta reta, float x);

// DATA SET --------------------------------------------------------------
typedef struct {
    ponto* lista_pontos;
    int quantidade_pontos;

} dataset;

//void adicionarPontoDataSet(dataset* data_set, ponto ponto);
#endif
