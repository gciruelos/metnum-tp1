r_i = 10
r_e = 100


def imprimir_lista(l):
	st = ''
	for x in l:
		st+=str(x)
		st+=' '
	return st

ints = [1500]*(40)
exts = [0]*(40)

# test de division de angulos
for i in range(7):
    f = open('tiempos_granul'+str(i)+'.in','w')
    f.write(str(r_i))
    f.write(' ')
    f.write(str(r_e))
    f.write(' ')
    f.write(str((i+1)*10)) # radios: podria variar
    f.write(' ')
    f.write(str(len(ints))) # angulos
    f.write(' ')
    f.write(str(500))
    f.write(' ')
    f.write(str(1)) # ninst
    f.write('\n')
    f.write(imprimir_lista(ints))
    f.write(imprimir_lista(exts))
    f.write('\n')
    f.close()


# test ninst>1

ints = []
exts = []

for i in range(30):
    int_ = [1500]*30
    ext_ = [0]*30
    ext_[i%30] = 450
    ext_[(i-1)%30] = 450
    ext_[(i+1)%30] = 450

    ints.append(int_)
    exts.append(ext_)


f = open('tiempos_ninst.in','w')
f.write(str(r_i))
f.write(' ')
f.write(str(r_e))
f.write(' ')
f.write(str(30)) # radios
f.write(' ')
f.write(str(len(ints[0]))) # angulos
f.write(' ')
f.write(str(500))
f.write(' ')
f.write(str(len(ints[0])))
f.write('\n')
for i in range(len(ints)):
    f.write(imprimir_lista(ints[i]))
    f.write(imprimir_lista(exts[i]))
f.write('\n')
f.close()


