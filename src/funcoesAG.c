#include "funcoesAG.h"

#define PRECISAO 1000
#define LIMITE 10
#define ALCANCE LIMITE * PRECISAO

//Valor aleatório entre (-LIMITE, LIMITE), com até 5 casas decimais
#define VALOR_ALEATORIO ((rand() % (2 * ALCANCE + 1)) - ALCANCE) / (double) PRECISAO

void aleatorizarCromossomo(cromossomo* cromossomo){
    cromossomo->reta.a = VALOR_ALEATORIO;
    cromossomo->reta.b = VALOR_ALEATORIO;
}

void gerarPopulacaoInicial(cromossomo* populacao, int quantidade_individuos){
    for (int i = 0; i < quantidade_individuos; i++){
        aleatorizarCromossomo(&populacao[i]);
        populacao[i].fitness = -1;
    }
}

void avaliarPopulacao(cromossomo* populacao, int quantidade_individuos, dataset data_set){
    for (int i = 0; i < quantidade_individuos; i++){
        populacao[i].fitness = calcularErroAbsolutoMedio(populacao[i].reta, data_set);
    }
}

void ordernarPopulacao(cromossomo* populacao, int n){

    for(int i = 0; i < n-1; i++){

        int pior = i;

        for(int j = i+1; j < n; j++){
            if(populacao[pior].fitness > populacao[j].fitness){
                pior = j;
            }
        }

        if(pior != i){
            cromossomo aux = populacao[i];
            populacao[i] = populacao[pior];
            populacao[pior] = aux;
        }
    }
}

cromossomo* selecionarTorneio(cromossomo* populacao, int quantidade_individuos, int numero_participantes){

    cromossomo* melhor = NULL;

    for(int i = 0; i < numero_participantes; i++){
        int idx = rand() % quantidade_individuos;

        if(melhor == NULL || populacao[idx].fitness > melhor->fitness)
            melhor = &populacao[idx];
    }

    return melhor;
}

void mutacao(cromossomo* cromossomo){
    if (rand() % 2 == 0)
        cromossomo->reta.a +=  ((rand() % (2 * 1000 + 1)) - 1000) / 1000.0;
    else{
        cromossomo->reta.b +=  ((rand() % (2 * 1000 + 1)) - 1000) / 1000.0;
    }
}

void gerarNovaPopulacao(cromossomo* populacao, parametrosAG parametros_AG){
    int quantidade_individuos =parametros_AG.quantidade_individuos;    
    int elitismo = 5;
    int descarte = 1/60 * quantidade_individuos;

    //crossover
    for (int i = (quantidade_individuos - descarte); i < quantidade_individuos; i += 2){
        cromossomo pai1 = populacao[rand() % (descarte + 1)];
        cromossomo pai2 = populacao[rand() % (descarte + 1)];

        if (rand() % 101 < parametros_AG.taxa_crossover){
            populacao[i].reta.a = pai1.reta.a;
            populacao[i].reta.b = pai2.reta.b;
            
            populacao[i + 1].reta.a = pai2.reta.a;
            populacao[i + 1].reta.b = pai1.reta.b;
        }else{
            populacao[i].reta = pai1.reta;
            
            populacao[i + 1].reta = pai2.reta;
        }
    }

    //mutacao
    for (int i = elitismo; i < quantidade_individuos; i ++){
        if (rand() % 101 < parametros_AG.taxa_mutacao){
            mutacao(&populacao[i]);
        }
    }

}

void igualarPopulacoes(cromossomo* populacao_antiga, cromossomo* nova_populacao, int quantidade_individuos){
    for (int i = 0; i < quantidade_individuos; i++){
        populacao_antiga[i].reta.a = nova_populacao[i].reta.a;
        populacao_antiga[i].reta.b = nova_populacao[i].reta.b;
        populacao_antiga[i].fitness = nova_populacao[i].fitness;
    }
}

void AlgoritmoGenetico(problema* p){
    // Dados de Entrada --------------------------------------------------
    parametrosAG parametros_AG = p->parametros_AG;
    dataset data_set = p->data_set;

    int quantidade_individuos = parametros_AG.quantidade_individuos;
    int quantidade_geracoes = parametros_AG.quantidade_geracoes;
    
    cromossomo populacao[parametros_AG.quantidade_individuos];
    gerarPopulacaoInicial(populacao, quantidade_individuos);
    avaliarPopulacao(populacao, quantidade_individuos, data_set);
    
    populacao[0].reta.a = 0.001;
    populacao[0].reta.b = 1;

    // Algoritmo ---------------------------------------------------------
    for (int geracao_atual = 0; geracao_atual < quantidade_geracoes; geracao_atual++){
        ordernarPopulacao(populacao, quantidade_individuos);

        gerarNovaPopulacao(populacao, parametros_AG);
        
        avaliarPopulacao(populacao, quantidade_individuos, data_set);


        printf("Geracao: %d\n", geracao_atual + 1);
        printf("Melhor Fitness: %f\n\n", populacao[0].fitness);
        printf("Melhor Reta: %fx + %f\n\n", populacao[0].reta.a, populacao[0].reta.b);
    }
    
    printf("Algoritmo Finalizado...");

    
}
