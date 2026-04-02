#ifndef LEITOR_H
#define LEITOR_H

#include <stdio.h>
#include <stdlib.h>

#include "problema.h"

/**
 * @brief Lê os dados de entrada (input.dat) para construir um problema.
 * @return O problema construído a partir dos dados de entrada.
 */
problema* lerInputParaProblema();

/**
 * @brief Cria o arquivo de saída (output.dat) com a solução encontrada.
 * @param prob O problema para o qual a solução foi encontrada.
 * @param sol A solução encontrada para o problema. 
 */
void criarOutput(problema* prob, solucao* sol);

#endif