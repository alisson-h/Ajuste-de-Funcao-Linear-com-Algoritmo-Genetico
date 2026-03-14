#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "problema.h"
#include "leitor.h"
#include "funcoesAG.h"

int main(){
    // INICIO ---------------
    srand(time(NULL));
    problema* problema = lerInputParaProblema();
    if (problema == NULL){
        printf("Algoritmo nao iniciado. \n");
        return 0;
    }
    // -----------------------------

    ExibirProblema(problema);

    // EXECUÇÃO --------------------
    AlgoritmoGenetico(problema);
    // -----------------------------


    // FINAL -----------------
    //deletarDados(dados);
    free(problema);
    // -----------------------------
    return 0;
}