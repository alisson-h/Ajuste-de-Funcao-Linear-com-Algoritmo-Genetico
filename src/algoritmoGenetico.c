#include "algoritmoGenetico.h"

#define EXIBIR_GERACOES 0
#define PRECISAO 1000
#define LIMITE 10
#define ALCANCE LIMITE * PRECISAO

#define PERC_ELETISMO 0.05
#define PERC_PRESELECAO 0.6

//Valor aleatório entre (-LIMITE, LIMITE), com até 5 casas decimais
#define VALOR_ALEATORIO ((rand() % (2 * ALCANCE + 1)) - ALCANCE) / (double) PRECISAO

solucao* AlgoritmoGenetico(problema* p){
    // Dados de Entrada --------------------------------------------------
    parametrosAG parametros_AG = p->parametros_AG;
    dataset data_set = p->data_set;

    int quantidade_individuos = parametros_AG.quantidade_individuos;
    int quantidade_individuos_selecionados = quantidade_individuos * PERC_PRESELECAO;
    int quantidade_eletismo = quantidade_individuos * PERC_ELETISMO;

    int quantidade_geracoes = parametros_AG.quantidade_geracoes;
    
    cromossomo populacao[parametros_AG.quantidade_individuos];
    gerarPopulacaoInicial(populacao, quantidade_individuos);
    avaliarPopulacaoMAE(populacao, quantidade_individuos, data_set);
    
    populacao[0].reta.a = 0.001;
    populacao[0].reta.b = 1;
    
    // Inicializando Solucao ---------------------------------------------
    solucao* sol = ConstruirSolucaoBase(quantidade_geracoes);
    cromossomo melhor_individuo = populacao[0];
    // Algoritmo ---------------------------------------------------------
    for (int geracao_atual = 0; geracao_atual < quantidade_geracoes; geracao_atual++){
        
        quickSelect(populacao, 0, quantidade_individuos - 1, quantidade_individuos_selecionados - 1);
        quickSelect(populacao, 0, (int) quantidade_individuos * 0.6 - 1, quantidade_eletismo - 1);

        gerarNovaPopulacao(populacao, parametros_AG, quantidade_eletismo, quantidade_individuos_selecionados);
        
        avaliarPopulacaoMAE(populacao, quantidade_individuos, data_set);
        
        melhor_individuo = populacao[0];
        if (EXIBIR_GERACOES){
            printf("Geracao: %d\n", geracao_atual + 1);
            printf("Melhor Fitness: %f\n\n", melhor_individuo.fitness);
            printf("Melhor Reta: %fx + %f\n\n", melhor_individuo.reta.a, melhor_individuo.reta.b);
        }

        sol->erros[geracao_atual] = calcularMAE(melhor_individuo.reta, data_set);
        sol->fitness[geracao_atual] = melhor_individuo.fitness;
        sol->retas[geracao_atual] = melhor_individuo.reta;

        //if  (sol->fitness[geracao_atual] == 0) break; //Encerra o algoritmo se encontrar a solução perfeita (fitness = 0)
    }
    
    printf("Algoritmo Finalizado...\n\n");
    printf("Melhor Fitness: %f\n\n", melhor_individuo.fitness);
    char sign = melhor_individuo.reta.b < 0 ? '-' : '+';
    printf("Melhor Reta: %fx %c %f\n\n", melhor_individuo.reta.a, sign, melhor_individuo.reta.b);
    
    return sol;
}

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

void avaliarPopulacaoMAE(cromossomo* populacao, int quantidade_individuos, dataset data_set){
    for (int i = 0; i < quantidade_individuos; i++){
        populacao[i].fitness = 1;
        populacao[i].fitness = calcularMAE(populacao[i].reta, data_set);
    }
}

void avaliarPopulacaoMSE(cromossomo* populacao, int quantidade_individuos, dataset data_set){
    int descarte = quantidade_individuos * 0.6;
    for (int i = 0; i < (quantidade_individuos - descarte); i++){
        populacao[i].fitness = calcularMSE(populacao[i].reta, data_set);
    }
}

int particiona(cromossomo* pop, int inicio, int fim){
    double pivo = pop[fim].fitness;
    int i = inicio;

    for(int j = inicio; j < fim; j++){
        if(pop[j].fitness < pivo){
            cromossomo aux = pop[i];
            pop[i] = pop[j];
            pop[j] = aux;
            i++;
        }
    }

    cromossomo aux = pop[i];
    pop[i] = pop[fim];
    pop[fim] = aux;

    return i;
}

void quickSelect(cromossomo* pop, int inicio, int fim, int k){

    if(inicio >= fim) return;

    int pos = particiona(pop, inicio, fim);

    if(pos == k) return;

    if(pos > k)
        quickSelect(pop, inicio, pos - 1, k);
    else
        quickSelect(pop, pos + 1, fim, k);
}


void crossoverPopulacao(cromossomo* populacao, int quantidade_individuos, int quantidade_selecionados, double taxa_crossover){
    for (int i = quantidade_selecionados; i < quantidade_individuos - 1; i += 2){

        int idx1 = rand() % quantidade_selecionados;
        int idx2;

        do {
            idx2 = rand() % quantidade_selecionados;
        } while (idx1 == idx2);

        cromossomo* pai1 = &populacao[idx1];
        cromossomo* pai2 = &populacao[idx2];

        cromossomo filho1 = populacao[i];
        cromossomo filho2 = populacao[i + 1];

        if ((double)rand() / RAND_MAX < taxa_crossover){

            double alpha = (double)rand() / RAND_MAX;

            filho1.reta.a = alpha * pai1->reta.a + (1 - alpha) * pai2->reta.a;
            filho1.reta.b = alpha * pai1->reta.b + (1 - alpha) * pai2->reta.b;

            filho2.reta.a = alpha * pai2->reta.a + (1 - alpha) * pai1->reta.a;
            filho2.reta.b = alpha * pai2->reta.b + (1 - alpha) * pai1->reta.b;

        } else {

            filho1.reta = pai1->reta;
            filho2.reta = pai2->reta;
        }

        populacao[i] = filho1;
        populacao[i + 1] = filho2;
    }
}

void mutacaoPopulacao(cromossomo* populacao, int quantidade_eletismo, int quantidade_individuos, double taxa_mutacao){
    for (int i = quantidade_eletismo; i < quantidade_individuos; i++){
        if ((double) rand() / RAND_MAX < taxa_mutacao){
            cromossomo* cromo = &populacao[i];
            if ((double) rand() / RAND_MAX < 0.5)
                cromo->reta.a +=  ((rand() % (2 * 200 + 1)) - 200) / (500.0);
            else{
                cromo->reta.b +=  ((rand() % (2 * 200 + 1)) - 200) / (500.0);
            }
        }
    }
}

void gerarNovaPopulacao(cromossomo* populacao, parametrosAG parametros_AG, int quantidade_eletismo, int quantidade_individuos_selecionados){
    int quantidade_individuos = parametros_AG.quantidade_individuos;    

    //crossover
    crossoverPopulacao(populacao, quantidade_individuos, quantidade_individuos_selecionados, parametros_AG.taxa_crossover);

    //mutacao
    mutacaoPopulacao(populacao, quantidade_eletismo, quantidade_individuos, parametros_AG.taxa_mutacao);

}