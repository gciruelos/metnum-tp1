#include <iostream>
#include <fstream>
#include <vector>
#include "sistema.h"
//#include "matriz.h"



void imprimir_vector(std::vector<double> v){
	std::cout << "[";
	for(int i = 0; i<v.size(); i++){
		std::cout << v[i];
		if(i!=v.size()-1)
			std::cout << ", ";
	}
	std::cout << "]" << std::endl;
}


int mi_atoi(char * a){
  if(a[0] == '0') return 0;
  else if(a[0] == '1') return 1;
  else if(a[0] == '2') return 2;
  else if(a[0] == '3') return 3;
  else return -1;
}
 


int main(int argc, char * argv[]){
  /* argv[0] es el nombre del programa
   * argv[1] es el archivo de input
   * argv[2] es el archivo de output soluciones
   * argv[3] es el archivo de output isoterma (opcional)
   */

  std::ifstream input_file(argv[1]);


  double r_i, r_e;
  unsigned int m_mas_uno, n;
  double iso;
  unsigned int ninst;

  std::vector<std::vector<double> > temperaturas_interiores;
  std::vector<std::vector<double> > temperaturas_exteriores;

  input_file >> r_i >> r_e >> m_mas_uno >> n >> iso >> ninst;

  double aux;
  for(unsigned int i = 0; i<ninst; i++){
    std::vector<double> temp_interior;
    std::vector<double> temp_exterior;
    
    for(unsigned j = 0; j<n; j++){ // la cantidad de temperaturas externas
      input_file >> aux;           // es n, o sea, la cantidad de angulos
      temp_interior.push_back(aux);
    }
    for(unsigned j = 0; j<n; j++){ // lo mismo que arriba
      input_file >> aux;            
      temp_exterior.push_back(aux);
    }

    temperaturas_interiores.push_back(temp_interior);
    temperaturas_exteriores.push_back(temp_exterior);
  }

  input_file.close();


  // ACA YA ESTA TODO LISTO PARA SER USADO

  std::ofstream f_soluciones(argv[2], std::ofstream::out);

  int metodo = mi_atoi(argv[3]);

  std::ofstream f_isotermas;
  if(argc>4){
    f_isotermas.open(argv[4], std::ofstream::out);
  }
  
  Sistema s(r_i, r_e, m_mas_uno, n, temperaturas_interiores, temperaturas_exteriores);
 
	if(metodo == 0) s.solve(f_soluciones, ELIM_GAUSSIANA);
  else if(metodo == 1) s.solve(f_soluciones, FACTORIZACION_LU);
  else if(metodo == 2) s.solve(f_soluciones, ELIM_GAUSSIANA_BANDA);
  else if(metodo == 3) s.solve(f_soluciones, FACTORIZACION_LU_BANDA);
	
  s.isotermas(f_isotermas, iso);

	imprimir_vector(s.tiempos);
  f_soluciones.close();

  return 0;
}

