//
//  grafo.h
//  ActivitySelectionAlgorithm
//
//  Created by Lucas Bressan on 11/22/17.
//  Matricula: 201335063
//  Copyright © 2017 Lucas Bressan. All rights reserved.
//

#ifndef grafo_h
#define grafo_h

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "vertice.h"
#include "arquivo.h"

// Grafo representado por uma matriz de adjacencia
struct grafo {
    int num_vertices;
    int num_arestas;
    int num_cores;
    struct vertice *vertices; // Lista de disciplinas presentes no grafo
    bool **matriz;
};

bool **get_matriz(int num_vertices);
void gerar_incidencias(struct grafo* g);
struct grafo novo_grafo(char *entrada);
int colorir_vertices(struct grafo *g);
void print_matriz(struct grafo g);
void print_cores(struct grafo g);
int get_variavel(int ID_vertice, int cor, int num_cores);
void grafo_para_SAT(struct grafo g, int num_cores, char* filename);
void delete_matriz(bool **mat, int num_vertices);

#endif /* grafo_h */
