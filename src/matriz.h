#ifndef MATRIZ_H
#define MATRIZ_H

#include <vector>
#include <iostream>


class Matriz {


public:
  // n = filas, m = columnas
  Matriz(int n, int m, double init) : n_(n), m_(m) {
    
		for(int i = 0; i<n; i++){
			std::vector<double> row;
			for(int j = 0; j<m; j++){
				row.push_back(init);
			}
			mat.push_back(row);
		}

  }


  void mostrar(){
		for(int i = 0; i<n_; i++){
			for(int j = 0; j<m_; j++){
				std::cout << mat[i][j] << " ";
			}
			std::cout << std::endl;
		}
 }

  // una funcion que de columnas
  

  // una funcion que de filas
  

  // una funcion que devuelva referencia a un coeficiente de la matriz
  // de tal manera de poder cambiarlos a gusto.
  // ver overload de operator()
  // algo como
  double &operator()(const int &i, const int &j){
		return mat[i][j];
	}
  
	//Pre: A es triangular superior
	std::vector<double> backward_subst(std::vector<double> b){

		int n = b.size();
		std::vector<double> x(n, 0.0);
	
		  for(int k = n-1; k>=0; k--){
				double numer = b[k];
				for(int i = k+1; i<n; i++){
					numer -= (*this)(k, i) * x[i];
				}
				x[k] = numer / (*this)(k,k);
			}
		return x;
	}



  // una funcion que resuelva un sistema que es triangular inferior


  // una funcion que triangule la matriz usando gauss jordan


  // una funcion que devuelva un par de matrices  std::pair<Matriz,Matriz>(L,U),
  // (que sean la descomposicion LU)



private:
    int n_;
    int m_;
    std::vector<std::vector<double> > mat;
};

#endif