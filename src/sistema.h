#include "matriz.h"
#include <vector>
#include <cmath>
#include <fstream>
#include <iostream>
#include <iomanip>

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
          std::vector<std::vector<double> > temps_exteriores) {
 
    n_ = n;
    m_mas_uno_ = m_mas_uno;
    r_i_ = r_i;
    delta_r = (r_e-r_i)/m_mas_uno;

    std::cerr << "Armando el sistema... " << std::flush;
    
    int fila = 0;
    A = new Matriz(n*m_mas_uno, n*m_mas_uno, 0.0);
    for(int i = 0; i<n; i++, fila++){
      (*A)(fila, fila) = 1.0;
    }

    // Precomputo varias ctes 
    double d_r = (r_e - r_i) / (m_mas_uno -1);  // delta r
    double qd_r = d_r * d_r;                    // (delta r)²
    double iqd_r = 1/qd_r;                      // 1/(delta r)²
    double d_theta = (2*M_PI) / n;              // delta theta
    double qd_theta = d_theta * d_theta;        // (delta theta)²
    double iqd_theta = 1/qd_theta;              // 1/(delta theta)²

    for(int i = 1; i<=m_mas_uno-2; i++){        // m_mas_uno-2 = cant radios
      double r = r_i + i*d_r;
      double qr = r*r;
      double cociente = (qr * qd_r * qd_theta);
      double coef_ij = (r * d_r * qd_theta - 2*qr*qd_theta - 2*qd_r) / cociente;
      double coef_i = (1/qr) * iqd_theta;
      double coef_j = (r - d_r)/(r * qd_r);

      int j = 0;                                 // salvo interior y exterior
      
      // resuelvo primer caso aparte;   
      (*A)(fila, col_matriz(i, j)) = coef_ij;    // el mismo   
      
      (*A)(fila, col_matriz(i, j+1)) = coef_i;   // el siguiente
      (*A)(fila, col_matriz(i, n_-1)) = coef_i;  // el anterior, que es el ultimo

      (*A)(fila, col_matriz(i-1, j)) = coef_j;   // anterior nivel
      (*A)(fila, col_matriz(i+1, j)) = iqd_r;    // siguiente nivel

      j++; fila++;

      // resuelvo todos los casos "buenos" juntos
      for(; j<n-1; j++, fila++){
        (*A)(fila, col_matriz(i, j)) = coef_ij;
        
        (*A)(fila, col_matriz(i, j+1)) = coef_i;
        (*A)(fila, col_matriz(i, j-1)) = coef_i;

        (*A)(fila, col_matriz(i-1, j)) = coef_j;
        (*A)(fila, col_matriz(i+1, j)) = iqd_r;
      }

      
      // resuelvo caso final aparte
      (*A)(fila, col_matriz(i, j)) = coef_ij;  // el mismo
      
      (*A)(fila, col_matriz(i, 0)) = coef_i;   // el siguiente, que es el primero
      (*A)(fila, col_matriz(i, j-1)) = coef_i; // el anterior

      (*A)(fila, col_matriz(i-1, j)) = coef_j; // anterior nivel
      (*A)(fila, col_matriz(i+1, j)) = iqd_r;  // siguiente nivel

      j++;
      fila++;
    }
    
    for(int i = 0; i<n; i++, fila++){
      (*A)(fila, fila) = 1.0;
    }
    
    std::cerr << "ok" << std::endl;


    std::cerr << "Armando b's... " << std::flush;
    // armo b's
    int cant_bs = temps_interiores.size();
    for(int i = 0; i<cant_bs; i++){
      std::vector<double> b(n*m_mas_uno, 0.0); //tiene tamanio n*(m+1)
      for(int j = 0; j<n; j++){
        b[j] = temps_interiores[i][j];
      }
      for(int j = 0; j<n; j++){
        b[j+n*m_mas_uno-n] = temps_exteriores[i][j];
      }
      bs.push_back(b);
    }
    std::cerr << "ok" << std::endl;

  }

  void solve(std::ofstream& f_soluciones, enum metodo met){ 
 
    std::vector<double> x, b, y;


    if(met == ELIM_GAUSSIANA){ 
      for(int i = 0; i<bs.size(); i++){
        b = bs[i];
        x = A->gaussian_elim(b);
        soluciones.push_back(x);
      }
    } else if(met == FACTORIZACION_LU){
      std::pair<Matriz*,Matriz*> LU = A->LU_fact();
      Matriz * L = LU.first;
      Matriz * U = LU.second;

      for(int i = 0; i<bs.size(); i++){
        b = bs[i];
        // Ax = b  -> LUx = b  -> Ly = b, donde Ux = y
        y = L->forward_subst(b);
        x = U->backward_subst(y);

        soluciones.push_back(x);
      }
    } if(met == ELIM_GAUSSIANA_BANDA){ 
      for(int i = 0; i<bs.size(); i++){
        b = bs[i]; 
        x = A->gaussian_elim_banda(b, m_mas_uno_);

        soluciones.push_back(x);
      }
    } else if(met == FACTORIZACION_LU_BANDA){
      std::pair<Matriz*,Matriz*> LU = A->LU_fact_banda(m_mas_uno_);
      Matriz * L = LU.first;
      Matriz * U = LU.second;

      for(int i = 0; i<bs.size(); i++){
        b = bs[i];
        // Ax = b  -> LUx = b  -> Ly = b, donde Ux = y
        y = L->forward_subst(b);
        x = U->backward_subst(y);

        soluciones.push_back(x);
      }
    }

    for(int i = 0; i<soluciones.size(); i++){ 
      for(int j = 0; j<soluciones[i].size(); j++){
        f_soluciones << std::fixed
                     << std::setprecision(8)
                     << soluciones[i][j] << std::endl;
      }
    }
  }

  void isotermas(std::ofstream& f_isotermas, double isoterma){
    

    for(int s = 0; s<soluciones.size(); s++){
      std::vector<double> isos;

      for(int i = 0; i<n_; i++){ // para cada uno de los angulos
        
        std::vector<double> radios;

        for(int j = 0; j<m_mas_uno_; j++){ // para cada uno de los radios
          radios.push_back(soluciones[s][i+j*n_]); //esto sale de una cuentita

          // radios tiene la temperatura de cada radio para un angulo fijo
          // (y solucion fija)
        }

        double iso = resolver_isoterma(radios, isoterma);
        isos.push_back(iso);
        if(f_isotermas.is_open()) f_isotermas << iso << std::endl;
      }
      //Analizo si la isoterma supera algun umbral peligroso.
      double med = media(isos);
      double prom = promedio(isos);
      double max = maximo(isos);
      
      double umbral_med = 60;
      double umbral_prom = 60;
      double umbral_max = 70;
      
      if (med > umbral_med || prom > umbral_prom || max > umbral_max){
		    std::cerr << "La isoterma del sistema numero" << s << "esta en peligro" << std::flush;
      }
    }
  }



  ~Sistema(){
    delete A;
  }

private:
  int m_mas_uno_, n_;
  double r_i_, delta_r, delta_tita;
  Matriz * A;

  std::vector<std::vector<double> > bs;
  std::vector<std::vector<double> > soluciones;

  
  int col_matriz(int i, int j){
    return j+n_*i;
  }

  double resolver_isoterma(std::vector<double> radios, double isoterma){
    for(int i = 0; i<radios.size()-1; i++){
      if(isoterma>radios[i+1] && isoterma<radios[i]){
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
  }
  
  double media(std::vector<double> v){
    double aux;
    for(int i = 0; i < v.size(); i++)
      for(int j = i; j < v.size(); j++){
        if(v[i] > v[i+1])
            aux = v[i];
            v[i] = v[i+1];
            v[i+1] = aux;
      }  
    return v[v.size()/2];    
  }
  
  double promedio(std::vector<double> v){
  	double res;
  	for(int i = 0; i < v.size(); i++){
  		res = res + v[i];
  		}
  	res = res/(v.size());
  	return res;
  }

  double maximo(std::vector<double> v){
  	double res = 0;
  	for(int i = 0; i<v.size(); i++){
  		if(res < v[i]){
  			res = v[i];
  			}
  		}
  	return res;
  }

};
