#include "funcoesAG.h"

#define true 1
#define false 0

#define PRECISAO 1000
#define LIMITE 10
#define ALCANCE LIMITE * PRECISAO
#define EXIBIR_GERACOES false

//Valor aleatório entre (-LIMITE, LIMITE), com até 5 casas decimais
#define VALOR_ALEATORIO ((rand() % (2 * ALCANCE + 1)) - ALCANCE) / (double) PRECISAO

void aleatorizarCromossomo(cromossomo* cromossomo){
    cromossomo->reta.a = VALOR_ALEATORIO;
    cromossomo->reta.b = VALOR_ALEATORIO;
}

void gerarPopulacaoInicial(cromossomo* populacao, int quantidade_individuos){
    /*
    int quantidade_pontos = data_set.quantidade_pontos;
    int metade = quantidade_pontos/2;
    ponto* pontos = data_set.lista_pontos;

    if (metade > quantidade_individuos) metade = quantidade_individuos - (quantidade_individuos % 2);
    
    int resto = quantidade_individuos - metade;
    for (int i = 0; i < metade; i++){
        ponto ponto1 = pontos[2 * i];
        ponto ponto2 = pontos[2 * i + 1];
        double a = (ponto2.y - ponto1.y)/(ponto2.x - ponto1.x);
        double b = ponto1.y - a * ponto1.x;
        
        populacao[i].reta.a = a;
        populacao[i].reta.b = b;
    }
    
    for (int i = resto; i < quantidade_individuos; i++){
        aleatorizarCromossomo(&populacao[i]);
        populacao[i].fitness = -1;
    }
    */
   
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
    for (int i = 0; i < quantidade_individuos; i++){
        populacao[i].fitness = 1;
        populacao[i].fitness = calcularMSE(populacao[i].reta, data_set);
    }
}

/*
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
*/

// Quick Sort -------------------------------------------
void swap(cromossomo *a, cromossomo *b) {
    cromossomo temp = *a;
    *a = *b;
    *b = temp;
}

void quickSort(cromossomo* arr, int low, int high) {
    if(low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int partition(cromossomo arr[], int low, int high) {
    float pivot = arr[high].fitness; // pivô
    int i = low - 1;

    for(int j = low; j < high; j++) {
        // ordem decrescente (maior fitness primeiro)
        if(arr[j].fitness <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}
// ------------------------------------------------------

/*
cromossomo* selecionarTorneio(cromossomo* populacao, int quantidade_individuos, int numero_participantes){

    cromossomo* melhor = NULL;

    for(int i = 0; i < numero_participantes; i++){
        int idx = rand() % quantidade_individuos;

        if(melhor == NULL || populacao[idx].fitness > melhor->fitness)
            melhor = &populacao[idx];
    }

    return melhor;
}
*/

void mutacao(cromossomo* cromossomo){
    if (rand() % 2 == 0)
        cromossomo->reta.a +=  ((rand() % (2 * 200 + 1)) - 200) / (1000.0);
    else{
        cromossomo->reta.b +=  ((rand() % (2 * 200 + 1)) - 200) / (1000.0);
    }
}

void gerarNovaPopulacao(cromossomo* populacao, parametrosAG parametros_AG, int geracao_atual){
    int quantidade_individuos = parametros_AG.quantidade_individuos;    
    int elitismo = 5;
    int descarte = quantidade_individuos * 0.6;

    //crossover
    int prob_crossover = parametros_AG.taxa_crossover - (geracao_atual/parametros_AG.quantidade_geracoes)*25;
    for (int i = (quantidade_individuos - descarte); i < quantidade_individuos; i += 2){
        cromossomo pai1 = populacao[rand() % (descarte + 1)];
        cromossomo pai2 = populacao[rand() % (descarte + 1)];

        if (rand() % 101 < prob_crossover){
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
    int prob_mutacao = parametros_AG.taxa_mutacao + (geracao_atual/parametros_AG.quantidade_geracoes)*25;
    for (int i = elitismo; i < quantidade_individuos; i ++){
        if (rand() % 101 < prob_mutacao){
            mutacao(&populacao[i]);
        }
    }

}

/*
void igualarPopulacoes(cromossomo* populacao_antiga, cromossomo* nova_populacao, int quantidade_individuos){
    for (int i = 0; i < quantidade_individuos; i++){
        populacao_antiga[i].reta.a = nova_populacao[i].reta.a;
        populacao_antiga[i].reta.b = nova_populacao[i].reta.b;
        populacao_antiga[i].fitness = nova_populacao[i].fitness;
    }
}
*/

solucao* AlgoritmoGenetico(problema* p){
    // Dados de Entrada --------------------------------------------------
    parametrosAG parametros_AG = p->parametros_AG;
    dataset data_set = p->data_set;

    int quantidade_individuos = parametros_AG.quantidade_individuos;
    int quantidade_geracoes = parametros_AG.quantidade_geracoes;
    
    cromossomo populacao[parametros_AG.quantidade_individuos];
    gerarPopulacaoInicial(populacao, quantidade_individuos);
    avaliarPopulacaoMAE(populacao, quantidade_individuos, data_set);
    
    populacao[0].reta.a = 0.001;
    populacao[0].reta.b = 1;
    
    // Inicializando Solucao ---------------------------------------------
    solucao* sol = (solucao *) malloc(sizeof(solucao));
    sol->erros = (double *) malloc(sizeof(double) * quantidade_geracoes);
    sol->fitness = (double *) malloc(sizeof(double) * quantidade_geracoes);
    sol->retas = (reta *) malloc(sizeof(reta) * quantidade_geracoes); 
    
    // Algoritmo ---------------------------------------------------------
    for (int geracao_atual = 0; geracao_atual < quantidade_geracoes; geracao_atual++){
        //ordernarPopulacao(populacao, quantidade_individuos);
        quickSort(populacao, 0 ,quantidade_individuos - 1);

        gerarNovaPopulacao(populacao, parametros_AG, geracao_atual);
        
        avaliarPopulacaoMAE(populacao, quantidade_individuos, data_set);

        cromossomo melhor_individuo = populacao[0];
        if (EXIBIR_GERACOES){
            printf("Geracao: %d\n", geracao_atual + 1);
            printf("Melhor Fitness: %f\n\n", melhor_individuo.fitness);
            printf("Melhor Reta: %fx + %f\n\n", melhor_individuo.reta.a, melhor_individuo.reta.b);
        }

        sol->erros[geracao_atual] = calcularMAE(melhor_individuo.reta, data_set);
        sol->fitness[geracao_atual] = melhor_individuo.fitness;
        sol->retas[geracao_atual] = melhor_individuo.reta;
    }
    
    printf("Algoritmo Finalizado...\n\n");
    printf("Melhor Fitness: %f\n\n", populacao[0].fitness);
    char sign = '+';
    if (populacao[0].reta.b < 0){sign = '-'; populacao->reta.b *= -1;}
    printf("Melhor Reta: %fx %c %f\n\n", populacao[0].reta.a, sign, populacao[0].reta.b);
    
    return sol;
}
