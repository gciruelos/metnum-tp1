r_i = 10
r_e = 100


def imprimir_lista(l):
	st = ''
	for x in l:
		st+=str(x)
		st+=' '
	return st

# test de division de angulos
temperaturas_interiores = [1500]*30
temperaturas_exteriores = [0]*30
temperaturas_exteriores[-1] = 1000

for i in range(5):
	ints = temperaturas_interiores[::(i+1)]
	exts = temperaturas_exteriores[::(i+1)]
	f = open('comp_angulos'+str(i)+'.in','w')
	f.write(str(r_i))
	f.write(' ')
	f.write(str(r_e))
	f.write(' ')
	f.write(str(40)) # radios: podria variar
	f.write(' ')
	f.write(str(len(ints))) # angulos
	f.write(' ')
	f.write(str(500))
	f.write(' ')
	f.write(str(1))
	f.write('\n')
	f.write(imprimir_lista(ints))
	f.write(imprimir_lista(exts))
	f.write('\n')
	f.close()


# test de division de radios

temperaturas_interiores2 = [1500]*30
temperaturas_exteriores2 = [0]*30

for i in range(len(temperaturas_exteriores2)):
	if i%4==0 or i%4==1:
		temperaturas_exteriores2[i] = 1500
		temperaturas_interiores2[i] = 0
	else:
		temperaturas_exteriores2[i] = 0
		temperaturas_interiores2[i] = 1500
		



for i in range(5):
	ints = temperaturas_interiores2
	exts = temperaturas_exteriores2
	f = open('comp_radios'+str(i)+'.in','w')
	f.write(str(r_i))
	f.write(' ')
	f.write(str(r_e))
	f.write(' ')
	f.write(str((i+1)*20)) # radios
	f.write(' ')
	f.write(str(len(ints))) # angulos
	f.write(' ')
	f.write(str(500))
	f.write(' ')
	f.write(str(1))
	f.write('\n')
	f.write(imprimir_lista(ints))
	f.write(imprimir_lista(exts))
	f.write('\n')
	f.close()




