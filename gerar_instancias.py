from random import randint
import random

f = open("input2", "w")
id_atual = 0
encontros = [1] * 15 + [2] * 85


for i in xrange(0, 750):
    professor = randint(1,25)
    periodo = randint(1,8)
    encontros_aux = random.choice(encontros)
    f.write("DCC" + str(id_atual) + "," + str(professor) + ",1," + str(periodo) + "\n")
    if encontros_aux == 2:
        f.write("DCC" + str(id_atual) + "," + str(professor) + ",1," + str(periodo) + "\n")
    f.write("\n")
    id_atual += 1
