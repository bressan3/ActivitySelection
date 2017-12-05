//
//  grafo.c
//  ActivitySelectionAlgorithm
//
//  Created by Lucas Bressan on 11/22/17.
//  Matricula: 201335063
//  Copyright © 2017 Lucas Bressan. All rights reserved.
//

#include "grafo.h"

bool **get_matriz(int num_vertices){
    bool **mat = malloc(num_vertices * sizeof(bool *));
    int i;
    int j;
    
    for (i = 0; i < num_vertices; i++){
        mat[i] = malloc(num_vertices * sizeof(bool));
    }
    
    for (i = 0; i < num_vertices; i++){
        for (j = 0; j < num_vertices; j++) {
            mat[i][j] = 0;
        }
    }
    
    return mat;
}

void gerar_incidencias(struct grafo* g){
    // Adiciona uma aresta entre dois vertices (disciplina) caso
    // duas discplinas possuam o mesmo professor ou o mesmo periodo
    
    int i;
    int j;
    
    for (i = 0; i < g->num_vertices; i++){
        for (j = 0; j < g->num_vertices; j++){
            if ((i != j && (g->vertices[i].ID_professor == g->vertices[j].ID_professor || g->vertices[i].periodo == g->vertices[j].periodo))){ //|| g->vertices[i].encontros != g->vertices[j].encontros){
                g->matriz[i][j] = true;
                g->num_arestas++;
            }
        }
    }
}

struct grafo novo_grafo(char *entrada){
    struct grafo g = read_file(entrada);
    gerar_incidencias(&g);
    
    return g;
}

int colorir_vertices(struct grafo *g){
    // Colore os vertices do grafo de forma gulosa com
    // backtracking (colorimos um vertice e depois checamos se algum vertice
    // incidente à ele já foi colorido com a cor atribuida).
    
    int i;
    int k;
    int num_slots_necessarios = 1;
    int num_cores = 1;
    int *cores_aux = malloc(g->num_vertices * sizeof(int));
    
    for (k = 0; k < g->num_vertices; k++){
        g->vertices[k].cor = 1;
        cores_aux[k] = 1;
        for(i = 0; i < k; i++){ //checking all k-1 vertices-backtracking
            if(g->matriz[i][k] != 0 && g->vertices[k].cor == g->vertices[i].cor){  //if connected and has same color
                g->vertices[k].cor = g->vertices[i].cor + 1;  //assign higher color than x[i]
                cores_aux[k] = cores_aux[i] + g->vertices[k].encontros;
                if (g->vertices[k].cor > num_cores){
                    num_cores = g->vertices[k].cor;
                    num_slots_necessarios = cores_aux[k];
                }
            }
        }
    }
    g->num_cores = num_cores;
    free(cores_aux);
    
    return num_slots_necessarios;
}

void print_matriz(struct grafo g){
    int i;
    int j;
    
    for (i = 0; i < g.num_vertices; i++) {
        for (j = 0; j < g.num_vertices; j++) {
            printf("%d ", g.matriz[i][j]);
        } printf("\n");
    }
}

void print_cores(struct grafo g){
    int i = 0;
    
    for (i = 0; i < g.num_vertices; i++) {
        printf("%d, ", g.vertices[i].cor);
    } printf("\n");
}

int get_variavel(int ID_vertice, int cor, int num_cores){
    return (ID_vertice * num_cores) + cor;
}

void grafo_para_SAT(struct grafo g, int num_cores, char* filename){
    /* Dado um numero de cores maximo esta funcao cria uma instancia SAT
     * para verificar se conseguimos colorir o dado grafo com até 'num_cores' cores
     */
    
    FILE *f = fopen(filename, "w");
    int i;
    int j;
    int k;
    
    int num_variaveis = num_cores * g.num_vertices;
    
    int num_clausulas_t1 = g.num_arestas * num_cores;
    int num_clausulas_t2 = g.num_vertices;
    int num_clausulas_t3 = g.num_vertices * num_cores;
    int num_total_clausulas = num_clausulas_t1 + num_clausulas_t2 + num_clausulas_t3;
    
    fprintf(f, "p cnf %d %d\n", num_variaveis, num_total_clausulas);
    
    // Clausulas tipo 1
    // 1 2 3  4 5 6  7 8 9
    for (i = 0; i < g.num_vertices; i++){
        for (j = i; j < g.num_vertices; j++){
            if (g.matriz[i][j] == 1){
                for (k = 1; k <= num_cores; k++){
                    fprintf(f, "-%d -%d 0\n", get_variavel(i, k, num_cores), get_variavel(j, k, num_cores));
                }
            }
        }
    }
    
    // Clausulas tipo 2
    for (i = 0; i < g.num_vertices; i++) {
        for (j = 1; j <= num_cores; j++){
            fprintf(f, "%d ", get_variavel(i, j, num_cores));
        } fprintf(f, "0\n");
    }
    
    // Clausulas tipo 3
    for (i = 0; i < g.num_vertices; i++) {
        for (j = 1; j < num_cores; j++){
            for (k = j ; k < num_cores; k++){
                fprintf(f, "-%d -%d 0\n", get_variavel(i, j, num_cores), get_variavel(i, k + 1, num_cores));
            }
        }
    }
    
    fclose(f);
}

void delete_matriz(bool **mat, int num_vertices){
    int i;
    
    for (i = 0; i < num_vertices; i++){
        free(mat[i]);
    }
    
    free(mat);
}
