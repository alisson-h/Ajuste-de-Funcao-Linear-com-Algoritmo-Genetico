#include "problema.h"
#include <math.h>

// PROBLEMA --------------------------------------------------------------
problema* ConstruirProblemaBase(int n, int m, int g){
    problema* p = (problema *) malloc(sizeof(problema));;

    //p.data_set.lista_pontos = lista_pontos;
    p->data_set.quantidade_pontos = n;

    p->parametros_AG.quantidade_individuos = m;
    p->parametros_AG.quantidade_geracoes = g;
    
    //-- A ser decidido
    p->parametros_AG.taxa_mutacao = 5;
    p->parametros_AG.taxa_crossover = 90;

    return p;
}

// FUNÇOES IMPORTANTES ---------------------------------------------------
float calcularErroAbsolutoMedio(reta reta, dataset data_set){
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