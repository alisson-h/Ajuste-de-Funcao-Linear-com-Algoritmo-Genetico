#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "problema.h"
#include "leitor.h"
#include "algoritmoGenetico.h"

int main(){
    // INICIO ----------------------
    srand(73);
    clock_t tempo_inicial = clock();

    problema* problema = lerInputParaProblema();
    if (problema == NULL){
        printf("Algoritmo nao iniciado. \n");
        return 0;
    }
    // -----------------------------

    // EXECUÇÃO --------------------
    solucao* solucao = AlgoritmoGenetico(problema);
    // -----------------------------

    // FINAL -----------------------
    clock_t tempo_final = clock();
    double tempo_algoritmo = (double)(tempo_final - tempo_inicial) / CLOCKS_PER_SEC;

    criarOutput(solucao);

    printf("Tempo de execucao: %g segundos\n", tempo_algoritmo);
    
    deletarSolucao(solucao);
    free(problema);
    // -----------------------------
    return 0;
}