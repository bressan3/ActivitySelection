//
//  vertice.h
//  ActivitySelectionAlgorithm
//
//  Created by Lucas Bressan on 11/22/17.
//  Matricula: 201335063
//  Copyright © 2017 Lucas Bressan. All rights reserved.
//

#ifndef vertice_h
#define vertice_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct vertice {
    char ID_disciplina[7];
    int ID_professor;
    int encontros; // Numero de vezes que a turma se encontra por semana
    int periodo;
    int cor;
};

struct vertice novo_vertice(char *ID_disciplina, int ID_professor, int periodo, int encontros);

#endif /* vertice_h */
