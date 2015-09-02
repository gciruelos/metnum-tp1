#ifndef SISTEMA_H
#define SISTEMA_H

#include "matriz.h"
#include <vector>   // para vector
#include <cmath>    // para pi
#include <fstream>  // 
#include <iostream> //  ---> para archivos
#include <iomanip>  // /

#include <ctime>


/* aca van a estar las funciones wrapper de las funciones de matriz.h
 *
 *
 * además va a estar la funcion que, a partir de un input, crea el sistema.
 *
 * se va a poder elegir que método se quiere usar de resolucion.
 * 
 */


enum metodo{
  ELIM_GAUSSIANA,
  FACTORIZACION_LU,
  ELIM_GAUSSIANA_BANDA,
  FACTORIZACION_LU_BANDA
};


class Sistema{

public:
  /* acordate de init */
  Sistema(double r_i,
          double r_e,
          int m_mas_uno,
          int n,
          std::vector<std::vector<double> > temps_interiores,
          std::vector<std::vector<double> > temps_exteriores);

  void solve(std::ofstream& f_soluciones, enum metodo met);

  void isotermas(std::ofstream& f_isotermas, double isoterma);

  ~Sistema();

	std::vector<double> tiempos;

private:
  int m_mas_uno_, n_;
  double r_i_, r_e_, delta_r, delta_tita;
  Matriz * A;

  std::vector<std::vector<double> > bs;
  std::vector<std::vector<double> > soluciones;

  
  int col_matriz(int i, int j);

	double resolver_isoterma(std::vector<double> radios, double isoterma, double eps = 0.0001){
	  for(int i = 0; i<radios.size()-1; i++){
	    if(radios[i+1]<isoterma && isoterma<radios[i]){
	      // la recta que une estos dos puntos tiene pendiente:
	      //     m = (radios[i+1]-radios[i])/delta_r
	      //
	      // entonces el fit lineal es:
	      // y = m * (x - (r_i + delta_r * i)) + radios[i]
	      //
	      // entonces, si me piden que y = isoterma, la solucion es:
	      //
	      //  isoterma = m * (x - (r_i + delta_r * i)) + radios[i]
	      //
	      //  (isoterma - radios[i]) / m + (r_i + delta_r * i)  =  x
	      //
	      //  x  = delta_r * (isoterma - radios[i]) / (radios[i+1]-radios[i]) 
	      //        + (r_i + delta_r * i)
	      //
	              
	    
	      // double x = delta_r * i + r_i_;

	      double x = delta_r * (isoterma-radios[i]) / (radios[i+1]-radios[i])
	                 + (r_i_+delta_r*i);  
	      return x;
	    }
	  }

	  if(isoterma<=radios[0]+eps){
	    return r_i_;
	  } else{
	    return r_e_;
	  }

	}
  
  double media(std::vector<double> v);
  
  double promedio(std::vector<double> v);

  double maximo(std::vector<double> v);

};

#endif // SISTEMA_H