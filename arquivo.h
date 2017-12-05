//
//  arquivo.h
//  ActivitySelectionAlgorithm
//
//  Created by Lucas Bressan on 11/23/17.
//  Matricula: 201335063
//  Copyright © 2017 Lucas Bressan. All rights reserved.
//

#ifndef arquivo_h
#define arquivo_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vertice.h"
#include "grafo.h"

int count_lines(char *file_name);
struct grafo read_file(char *file_name);

#endif /* arquivo_h */
