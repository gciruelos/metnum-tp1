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

  // constructor por copia
  Matriz(Matriz * vieja){
    n_ = vieja->n_;
    m_ = vieja->m_;
    mat = vieja->mat;
  }


  void mostrar(){
    for(int i = 0; i<n_; i++){
      for(int j = 0; j<m_; j++){
        std::cout << mat[i][j] << " ";
      }
      std::cout << std::endl;
    }
      std::cout << std::endl;
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
  

  //Pre: A es triangular superior y no tiene ceros en la diagonal
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


  //Pre: A es triangular inferior y no tiene ceros en la diagonal
  std::vector<double> forward_subst(std::vector<double> b){
    int n = b.size();
    std::vector<double> x(n, 0.0);
  
    for(int k = 0; k<n; k++){
      double numer = b[k];
      for(int i = 0; i<k; i++){
        numer -= (*this)(k, i) * x[i];
      }
      x[k] = numer / (*this)(k,k);
    }
    return x;
  }


  std::vector<double> gaussian_elim(std::vector<double> b){
    int n = b.size();
    Matriz gauss(this);

    for(int i = 0; i<n; i++){
      for(int fila = i+1; fila < n; fila++){
        // modifico la fila 
        // f_j - cte_fila * f_i 
        // cte_fila = prim/a_ii, donde prim es el primero de la fila
        double prim = gauss(fila,i);
       
        double coeff = prim/gauss(i,i);
        for(int j = i+1; j<n; j++){ 
          gauss(fila, j) -= gauss(i, j) * coeff;
        }
        //modifico b
        b[fila] -= b[i] * coeff;
        gauss(fila, i) = 0.0;
      }
    }

    // es triangular superior, aplicamos backward substitution
    return  gauss.backward_subst(b);
  }


  // una funcion que devuelva un par de matrices  std::pair<Matriz,Matriz>(L,U),
  // (que sean la descomposicion LU)



private:
    int n_;
    int m_;
    std::vector<std::vector<double> > mat;
};

