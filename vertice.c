//
//  vertice.c
//  ActivitySelectionAlgorithm
//
//  Created by Lucas Bressan on 11/22/17.
//  Matricula: 201335063
//  Copyright © 2017 Lucas Bressan. All rights reserved.
//

#include "vertice.h"

struct vertice novo_vertice(char *ID_disciplina, int ID_professor, int periodo, int encontros){
    struct vertice v;
    
    strcpy(v.ID_disciplina, ID_disciplina);
    v.ID_professor = ID_professor;
    v.periodo = periodo;
    v.encontros = encontros;
    v.cor = -1;
    
    return v;
}
