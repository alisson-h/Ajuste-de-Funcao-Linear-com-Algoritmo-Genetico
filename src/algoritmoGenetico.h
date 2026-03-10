#ifndef ALGORTIMO_GENETICO
#define ALGORITMO_GENETICO


// CROMOSSOMO ------------------------------------------------------------
typedef struct{
    reta reta;
    float fitness;

}cromossomo;

typedef struct{
    int quantidade_individuos;
    int quantidade_geracoes;
    float taxa_mutacao;
    float taxa_crossover;

} parametrosAG;

void AlgoritmoGenetico(problema p){
    // Dados de Entrada --------------------------------------------------
    parametrosAG parametros_AG = p.parametros_AG;

    int quantidade_individuos = parametros_AG.quantidade_individuos;
    int quantidade_geracoes = parametros_AG.quantidade_geracoes;
    float taxa_mutacao = parametros_AG.taxa_mutacao;
    float taxa_crossover = parametros_AG.taxa_crossover;
    
    cromossomo* populacao[parametros_AG.quantidade_individuos] = {};


    // Algoritmo ---------------------------------------------------------
    for (int geracao_atual = 0; geracao_atual < quantidade_geracoes; geracao_atual++){
        
    }
}
#endif