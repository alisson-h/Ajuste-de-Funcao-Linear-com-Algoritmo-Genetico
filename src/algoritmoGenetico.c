#include "algoritmoGenetico.h"
#include <math.h>

#define EXIBIR_GERACOES 0
#define EXIBIR_INFORMACOES_FINAIS 1

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
    gerarPopulacaoInicial(populacao, data_set, quantidade_individuos);
    avaliarPopulacaoMAE(populacao, quantidade_individuos, 0, data_set);
    qsort(populacao, quantidade_individuos, sizeof(cromossomo), compararCromossomos);

    // Inicializando Solucao ---------------------------------------------
    solucao* sol = ConstruirSolucaoBase(quantidade_geracoes);
    cromossomo melhor_individuo = populacao[0];

    // Algoritmo ---------------------------------------------------------
    printf("\nIniciando AG...");
    int geracao_atual = 0;
    while(geracao_atual < quantidade_geracoes){
        gerarNovaPopulacao(populacao, parametros_AG, quantidade_eletismo, quantidade_individuos_selecionados);
        avaliarPopulacaoMAE(populacao, quantidade_individuos, quantidade_individuos_selecionados, data_set);
        qsort(populacao, quantidade_individuos, sizeof(cromossomo), compararCromossomos);

        melhor_individuo = populacao[0];
        if (EXIBIR_GERACOES){
            printf("G %3.d | fitness: %lf | reta: (a = %lf, b = %lf)\n",
            geracao_atual + 1, melhor_individuo.fitness, melhor_individuo.reta.a, melhor_individuo.reta.b);
        }

        sol->erros[geracao_atual] = melhor_individuo.fitness;
        sol->fitness[geracao_atual] = melhor_individuo.fitness;
        sol->retas[geracao_atual] = melhor_individuo.reta;

        geracao_atual++;
        //Encerrar o algoritmo se encontrar a solução perfeita (fitness = 0)
        //só funciona quando os pontos coincidem perfeitamente em uma reta
        if (fabs(sol->fitness[geracao_atual - 1]) < 1e-9) break;
    }
    sol->geracao_final = geracao_atual;

    printf(" Algoritmo Finalizado.\n");

    if (EXIBIR_INFORMACOES_FINAIS)
    {
       printf("Melhor Fitness: %f | ", melhor_individuo.fitness);
        char sign = '+';
        if (melhor_individuo.reta.b <= 0) { melhor_individuo.reta.b *= -1; sign = '-'; }
        if ( fabs(melhor_individuo.reta.a) < 1e-6) printf("Melhor Reta: y =  %c %g\n", sign, melhor_individuo.reta.b);
        else if ( fabs(melhor_individuo.reta.b) < 1e-6) printf("Melhor Reta: y = %gx\n", melhor_individuo.reta.a);
        else printf("Melhor Reta: %gx %c %g\n", melhor_individuo.reta.a, sign, melhor_individuo.reta.b);
    }
    
    return sol;
}

void aleatorizarCromossomo(cromossomo* cromossomo){
    cromossomo->reta.a = VALOR_ALEATORIO;
    cromossomo->reta.b = VALOR_ALEATORIO;
}

void gerarPopulacaoInicial(cromossomo* populacao, dataset data_set, int quantidade_individuos){
    //25% dos indivíduos são gerados a partir de pontos aleatórios do dataset, e os outros 75% são gerados aleatoriamente
    
    //caso o dataset tenha apenas 2 pontos, garante que pelo menos 1 indivíduo seja gerado a partir desses pontos
    //o que resulta no fitness 0, e o algoritmo termina imediatamente, como esperado :D
    int idx_part = data_set.quantidade_pontos == 2 ? quantidade_individuos / 4 + 1 : quantidade_individuos / 4; 

    for (int i = 0; i < idx_part; i++){
        ponto* p1 = &data_set.lista_pontos[rand() % data_set.quantidade_pontos];
        ponto* p2 = &data_set.lista_pontos[rand() % data_set.quantidade_pontos];

        double a = (p2->y - p1->y) / (p2->x - p1->x + 1e-12);
        double b = p1->y - a * p1->x;

        populacao[i].reta.a = a;
        populacao[i].reta.b = b;        
        populacao[i].fitness = -1;
    }

    for (int i = idx_part; i < quantidade_individuos; i++){
        aleatorizarCromossomo(&populacao[i]);
        populacao[i].fitness = -1;
    }
    

}

void avaliarPopulacaoMAE(cromossomo* populacao, int quantidade_individuos, int inicio, dataset data_set){

    for (int i = inicio; i < quantidade_individuos; i++){
        populacao[i].fitness = 1;
        populacao[i].fitness = calcularMAE(populacao[i].reta, data_set);
    }
}

int compararCromossomos(const void* a, const void* b){
    double fitness_a = ((cromossomo*)a)->fitness;
    double fitness_b = ((cromossomo*)b)->fitness;

    if (fitness_a < fitness_b) return -1;
    else if (fitness_a > fitness_b) return 1;
    else return 0;
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
            // Mutação: altera aleatoriamente o coeficiente a ou b, com um valor entre -0.2 e 0.2 (com até 5 casas decimais)
            if ((double) rand() / RAND_MAX < 0.5)
                cromo->reta.a +=  ((rand() % (2 * 20000 + 1)) - 20000) / (100000.0);
            else{
                cromo->reta.b +=  ((rand() % (2 * 20000 + 1)) - 20000) / (100000.0);
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