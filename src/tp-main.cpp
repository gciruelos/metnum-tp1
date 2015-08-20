#include <iostream>
#include <fstream>
#include <vector>
#include "sistema.h"
//#include "matriz.h"

int main(int argc, char * argv[]){
  /* argv[0] es el nombre del programa
   * argv[1] es el archivo de input
   * argv[2] es el archivo de output
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


  std::ofstream output_file(argv[2], std::ofstream::out);
  Sistema s(r_i, r_e, m_mas_uno, n, 500.0, temperaturas_interiores, temperaturas_exteriores);
  s.solve(output_file, FACTORIZACION_LU);
  output_file.close();

/*
  std::cerr << "r_i   = " << r_i << std::endl
            << "r_e   = " << r_e << std::endl
            << "m+1   = " << m_mas_uno << std::endl
            << "n     = " << n << std::endl
            << "iso   = " << iso << std::endl
            << "ninst = " << ninst << std::endl;
*/
/*

  Matriz m(3,3,0.0);
  m(0,0) = 2.0;
  m(0,1) = 3.0;
  m(0,2) = 8.0;
  
  m(1,0) = 4.0;
  m(1,1) = 5.0;
  m(1,2) = 1.0;

  m(2,0) = 6.0;
  m(2,1) = 1.0;
  m(2,2) = 2.0;
  
  m.mostrar();

  std::pair<Matriz*,Matriz*> LU = m.LU_fact();
  LU.first->mostrar();
  LU.second->mostrar();
*/
return 0;
}

