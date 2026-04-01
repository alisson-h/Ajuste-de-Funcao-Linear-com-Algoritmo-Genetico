#include "leitor.h"
#include "problema.h"

#include <stdio.h>
#include <stdlib.h>

problema* lerInputParaProblema(){
    problema* prob = NULL;
    int n;
    int m;
    int g;

    FILE *arq = fopen("config/input.dat", "rb");

    if (arq == NULL) {
        printf("Erro ao abrir arquivo\n");
        return prob;
    }
    
    if (fscanf(arq, "%d %d %d", &n, &m, &g) == EOF){
        printf("Erro ao ler arquivo\n");
        return prob;
    }
    prob = ConstruirProblemaBase(n, m , g);

    ponto* lista_ponto = (ponto *) malloc(n * sizeof(ponto));
    ponto p_aux;

    for (int i = 0; i < prob->data_set.quantidade_pontos; i++){
        if(fscanf(arq, "%lf %lf", &p_aux.x, &p_aux.y) != EOF){
            lista_ponto[i] = p_aux;
        }
    }
    prob->data_set.lista_pontos = lista_ponto;

    fclose(arq);

    return prob;
}

void criarSaida(problema* prob, solucao* sol){
    FILE *arq = fopen("config/output.dat", "w");

    if (arq == NULL) {
        printf("Erro ao criar/ediar arquivo\n");
        return;
    }
    
    for (int i = 0; i < prob->parametros_AG.quantidade_geracoes; i++){
        fprintf(arq,"Geracao %i:\nMelhor fitness: %lf\nErro: %lf\nReta: (a = %lf,b= %lf)\n\n",
        i, sol->fitness[i], sol->erros[i], sol->retas[i].a, sol->retas[i].b);
    }

    fclose(arq);
}
