//
//  main.c
//  ActivitySelectionAlgorithm
//
//  Created by Lucas Bressan on 11/22/17.
//  Matricula: 201335063
//  Copyright © 2017 Lucas Bressan. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

// Em horas
#define DURACAO_DIA_ESCOLAR 12
#define DURACAO_AULA 2

#define DIAS_ESCOLARES 5

int main(int argv, char **argc){
    char *entrada = "input2";
    char *saida_SAT = "sat_out";
    struct grafo g = novo_grafo(entrada);
    int num_slots_necessarios = colorir_vertices(&g);
    int num_maximo_de_slots = (DURACAO_DIA_ESCOLAR / DURACAO_AULA) * DIAS_ESCOLARES; // Numero de slots que temos em uma semana para encaixar as disciplinas
    
    printf("Numero de slots necessarios: %d\n", g.num_cores);
    printf("Numero maximo de slots: %d\n", num_maximo_de_slots);
    
    if (g.num_cores > num_maximo_de_slots){
        printf("NÃO SERA POSSIVEL ALOCAR TODAS AS DISCIPLINAS!\n");
    } else {
        printf("SERA POSSIVEL ALOCAR TODAS AS DISCIPLINAS!\n");
    }
    
    grafo_para_SAT(g, 30, saida_SAT);
    
    return 0;
}
