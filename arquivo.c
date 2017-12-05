//
//  arquivo.c
//  ActivitySelectionAlgorithm
//
//  Created by Lucas Bressan on 11/23/17.
//  Matricula: 201335063
//  Copyright © 2017 Lucas Bressan. All rights reserved.
//

#include "arquivo.h"

int count_lines(char *file_name){
    /*
     *  Conta o número de atividades no arquivo de entrada
     */
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int num_lines = 0;
    
    fp = fopen(file_name, "r");
    if (fp == NULL){
        exit(EXIT_FAILURE);
    }
    
    read = getline(&line, &len, fp);
    while ((read = getline(&line, &len, fp)) != -1) {
        if (line[0] == '\n'){
            continue;
        }
        num_lines++;
    }
    
    fclose(fp);
    
    return num_lines;
}

struct grafo read_file(char *file_name){
    /*
     *  Lê o arquivo de entrada contendo as atividades a serem alocadas e retorna
     *  um grafo
     */
    
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int num_disciplinas = count_lines(file_name);
    char *pch;
    int i = 0;
    int j = 0;
    
    // struct vertice *disciplinas = malloc(num_disciplinas * sizeof(struct vertice));
    struct grafo g;
    g.matriz = get_matriz(num_disciplinas);
    g.num_vertices = num_disciplinas;
    g.vertices = malloc(num_disciplinas * sizeof(struct vertice));
    
    fp = fopen(file_name, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    
    read = getline(&line, &len, fp);
    while ((read = getline(&line, &len, fp)) != -1) {
        if (line[0] == '\n'){
            continue;
        }
        pch = strtok(line, ",");
        while (pch != NULL){
            if (i == 0){
                strcpy(g.vertices[j].ID_disciplina, pch);
            } else if (i == 1){
                g.vertices[j].ID_professor = atoi(pch);
            } else if (i == 2){
                g.vertices[j].encontros = atoi(pch);
            } else {
                g.vertices[j].periodo = atoi(pch);
            }
            pch = strtok(NULL, ",");
            i++;
        }
        g.vertices[j].cor = -1;
        i = 0;
        j++;
    }
    
    fclose(fp);
    
    return g;
}
