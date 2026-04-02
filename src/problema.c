#include "problema.h"
#include <math.h>

#define TAMANHO_ESPACIAL 50

// PROBLEMA --------------------------------------------------------------
problema* ConstruirProblemaBase(int n, int m, int g){
    problema* p = (problema *) malloc(sizeof(problema));;

    //p.data_set.lista_pontos = lista_pontos;
    p->data_set.quantidade_pontos = n;

    p->parametros_AG.quantidade_individuos = m;
    p->parametros_AG.quantidade_geracoes = g;
    
    //-- A ser decidido
    p->parametros_AG.taxa_mutacao = 0.05;
    p->parametros_AG.taxa_crossover = 0.90;

    return p;
}
solucao* ConstruirSolucaoBase(int quantidade_geracoes){
    solucao* sol = (solucao *) malloc(sizeof(solucao));
    sol->erros = (double *) malloc(sizeof(double) * quantidade_geracoes);
    sol->fitness = (double *) malloc(sizeof(double) * quantidade_geracoes);
    sol->retas = (reta *) malloc(sizeof(reta) * quantidade_geracoes); 

    return sol;
}

void deletarSolucao(solucao* sol){
    free(sol->erros);
    free(sol->fitness);
    free(sol->retas);
    free(sol);
}

// FUNÇOES IMPORTANTES ---------------------------------------------------
float calcularMAE(reta reta, dataset data_set){
    float MAE = 0;

    for (int i = 0; i < data_set.quantidade_pontos; i++)
    {
        ponto ponto = data_set.lista_pontos[i];
        
        float resultado = ponto.y - calcularYReta(reta, ponto.x);
        if (resultado < 0) resultado *= -1;
        
        MAE += resultado;
    }

    MAE /= data_set.quantidade_pontos;

    return MAE;
}

float calcularMSE(reta reta, dataset data_set){
    float MSE = 0;

    for (int i = 0; i < data_set.quantidade_pontos; i++)
    {
        ponto ponto = data_set.lista_pontos[i];
        
        float resultado = ponto.y - calcularYReta(reta, ponto.x);
        resultado *= resultado;
        
        MSE += resultado;
    }

    MSE /= data_set.quantidade_pontos;

    return MSE;
}

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