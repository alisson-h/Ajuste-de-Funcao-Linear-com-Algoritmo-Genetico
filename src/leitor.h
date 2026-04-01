#ifndef LEITOR_H
#define LEITOR_H

#include <stdio.h>
#include <stdlib.h>

#include "problema.h"

problema* lerInputParaProblema();

void criarSaida(problema* prob, solucao* sol);

#endif