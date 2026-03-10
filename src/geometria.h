#ifndef GEOMETRIA_H
#define GEOMETRIA_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_ESPACIAL 50
#define QUANTIDADE_PONTOS 20

// PONTO (x, y) ----------------------------------------------------------
typedef struct{
    int x;
    int y;
}ponto;

ponto criarPonto(int x, int y){
    ponto novoPonto;
    novoPonto.x = x;
    novoPonto.y = y;

    return novoPonto;
}

ponto criarPontoAleatorio(){
    ponto novoPonto;
    novoPonto.x = (rand() % (2 * TAMANHO_ESPACIAL + 1)) - TAMANHO_ESPACIAL;
    novoPonto.y = (rand() % (2 * TAMANHO_ESPACIAL + 1)) - TAMANHO_ESPACIAL;

    return novoPonto;
}

// RETA (y = ax + b) -----------------------------------------------------
typedef struct{
    float a;
    float b;
}reta;

float calcularXReta(reta reta, float y){
    if (reta.a) return 9999999; //Tratar depois
    return (y - reta.b)/reta.a;
}

float calcularYReta(reta reta, float x){
    return reta.a * x + reta.b;
}

#endif

// DATA SET --------------------------------------------------------------
typedef struct{
    ponto* lista_pontos;
    int quantidade_pontos;

} dataset;