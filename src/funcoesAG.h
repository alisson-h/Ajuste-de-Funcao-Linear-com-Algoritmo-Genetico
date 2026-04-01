#ifndef FUNCOES_AG_H
#define FUNCOES_AG_H

#include "problema.h"

solucao* AlgoritmoGenetico(problema* p);

void swap(cromossomo *a, cromossomo *b);
void quickSort(cromossomo* arr, int low, int high);
int partition(cromossomo arr[], int low, int high);

#endif