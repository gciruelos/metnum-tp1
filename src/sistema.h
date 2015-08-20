#include "matriz.h"
#include <vector>
#include <cmath>
#include <fstream>
#include <iostream>

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
  FACTORIZACION_LU
};





class Sistema{

public:
  /* acordate de init */
  Sistema(double r_i, double r_e, int m_mas_uno, int n, double isoterma, std::vector<std::vector<double> > temps_interiores, std::vector<std::vector<double> > temps_exteriores, std::ofstream& output_file, enum metodo met ) {
    /* armo el sistema */

    n_ = n;
    m_mas_uno_ = m_mas_uno;
    int fila = 0;

    A = new Matriz(n*m_mas_uno, n*m_mas_uno, 0.0);
    for(int i = 0; i<n; i++, fila++){
      (*A)(fila, fila) = 1.0;
    }

    // Precomputo varias ctes 
    double d_r = (r_e - r_i) / (m_mas_uno - 1); // delta r
    double qd_r = d_r * d_r;          // (delta r)²
    double iqd_r = 1/qd_r;            // 1/(delta r)²
    double d_theta = (2*M_PI) / n;        // delta theta
    double qd_theta = d_theta * d_theta;    // (delta theta)²
    double iqd_theta = 1/qd_theta;        // 1/(delta theta)²

    for(int i = 1; i<=m_mas_uno-2; i++){    // m_mas_uno-2 = cant radios
      double r = r_i + i*d_r;
      double qr = r*r;
      double cociente = (qr * qd_r * qd_theta);
      double coef_ij = (r * d_r * qd_theta - 2*qr*qd_theta - 2*qd_r) / cociente;
      double coef_i = (1/qr) * iqd_theta;
      double coef_j = (r - d_r)/(r * qd_r);

      int j = 0;                            // salvo interior y exterior
      
      //resuelvo primer caso aparte;  
      // el mismo
      (*A)(fila, col_matriz(i, j)) = coef_ij;   
      
      (*A)(fila, col_matriz(i, j+1)) = coef_i;    // el siguiente
      (*A)(fila, col_matriz(i, n_-1)) = coef_i;   // el anterior, que es el ultimo

      (*A)(fila, col_matriz(i-1, j)) = coef_j;  // anterior nivel
      (*A)(fila, col_matriz(i+1, j)) = iqd_r;   // siguiente nivel

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
      (*A)(fila, col_matriz(i, j)) = coef_ij;
      
      (*A)(fila, col_matriz(i, 0)) = coef_i;  // el siguiente, que es el primero
      (*A)(fila, col_matriz(i, j-1)) = coef_i; // el anterior

      (*A)(fila, col_matriz(i-1, j)) = coef_j; // anterior nivel
      (*A)(fila, col_matriz(i+1, j)) = iqd_r; // siguiente nivel

      //j++;
      fila++;
    }
    
    for(int i = 0; i<n; i++, fila++){
      (*A)(fila, fila) = 1.0;
    }

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

    
    if(met == ELIM_GAUSSIANA){
      for(int i = 0; i<bs.size(); i++){
        std::vector<double> b = bs[i];
        std::vector<double> x = A->gaussian_elim(b);
        for(int j = 0; j<x.size(); j++){
          output_file << x[j] << std::endl;
        }
      }
    }
    /*
    if(metodo == FACTORIZACION_LU){
      Matriz L,U = dame_factorizacion_lu(A);
      for(adsf in temeraturas)
        resolv
        resolver;
    }*/

}


private:
  int m_mas_uno_, n_;
  Matriz * A;

  std::vector<std::vector<double> > bs;

  double r_i_, delta_r, delta_tita;

  
  int col_matriz(int i, int j){
    return j+n_*i;
  }
};
