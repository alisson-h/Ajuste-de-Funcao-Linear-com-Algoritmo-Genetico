#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "geometria.h"

// PONTO (x, y) ----------------------------------------------------------

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

float calcularXReta(reta reta, float y){
    if (reta.a) return 9999999; //Tratar depois
    return (y - reta.b)/reta.a;
}

float calcularYReta(reta reta, float x){
    return reta.a * x + reta.b;
}