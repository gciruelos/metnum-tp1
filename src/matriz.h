#include <vector>
#include <iostream>
#include <utility> // std::pair

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

  int columnas(){
    return m_;
  }

  int filas(){
    return n_;
  }
  
  // esta funcion nos permite asignar y obtener los coeficientes
  // de la matriz
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
        gauss(fila, i) = 0.0;
        
        //modifico b
        b[fila] -= b[i] * coeff; 
      } 
    }

    // es triangular superior, aplicamos backward substitution
    return  gauss.backward_subst(b);
  }


  std::pair<Matriz *, Matriz *> LU_fact(){
    Matriz * U = new Matriz(this);
    Matriz * L = new Matriz(this->n_, this->m_, 0);

    int n = n_;

    // muy parecida a la eliminacion gaussiana, un poco cambiada
    for(int i = 0; i<n; i++){
      for(int fila = i+1; fila < n; fila++){
        // modifico la fila 
        // f_j - cte_fila * f_i 
        // cte_fila = prim/a_ii, donde prim es el primero de la fila
        double prim = (*U)(fila,i);
       
        double coeff = prim/(*U)(i,i);
        for(int j = i+1; j<n; j++){ 
          (*U)(fila, j) -= (*U)(i, j) * coeff;
        }
        (*U)(fila, i) = 0.0;
        
        // pongo el valor correspondiente en L
        (*L)(fila, i) = coeff;
      }
      (*L)(i,i) = 1.0; 
    }
    return std::make_pair(L, U);
  }

//Factorizacion LU mejorada, haciendo la resta entre filas hasta que empiezan a haber ceros en f_i.

  std::vector<double> gaussian_elim_banda(std::vector<double> b, int n__){
    int n = b.size();
    int radios = n__;
    Matriz gauss(this);

    for(int i = 0; i<n; i++){
      for(int fila = i+1; fila < n && fila < (i + 1 + radios); fila++){
        // modifico la fila
        // lo hago hasta que termine la banda de la fila (i + 1 + radios) o que termine de restar todo.
        // f_j - cte_fila * f_i 
        // cte_fila = prim/a_ii, donde prim es el primero de la fila
        double prim = gauss(fila,i);
       
        double coeff = prim/gauss(i,i);
        for(int j = i+1; j<n; j++){ 
          gauss(fila, j) -= gauss(i, j) * coeff;
        }
        gauss(fila, i) = 0.0;
        
        //modifico b
        b[fila] -= b[i] * coeff; 
      } 
    }

    // es triangular superior, aplicamos backward substitution
    return  gauss.backward_subst(b);
  }

//Factorizacion LU mejorada, haciendo la resta entre filas hasta que empiezan a haber ceros en f_i.

  std::pair<Matriz *, Matriz *> LU_fact_banda(int  n__){
    Matriz * U = new Matriz(this);
    Matriz * L = new Matriz(this->n_, this->m_, 0);

    int n = n_;
	int radios = n__;
    // muy parecida a la eliminacion gaussiana, un poco cambiada
    for(int i = 0; i<n; i++){
      for(int fila = i+1; fila < n && fila < i + 1 + radios; fila++){
        // modifico la fila 
        // f_j - cte_fila * f_i 
        // cte_fila = prim/a_ii, donde prim es el primero de la fila
        double prim = (*U)(fila,i);
       
        double coeff = prim/(*U)(i,i);
        for(int j = i+1; j<n; j++){ 
          (*U)(fila, j) -= (*U)(i, j) * coeff;
        }
        (*U)(fila, i) = 0.0;
        
        // pongo el valor correspondiente en L
        (*L)(fila, i) = coeff;
      }
      (*L)(i,i) = 1.0; 
    }
    return std::make_pair(L, U);
  }

private:
    int n_;
    int m_;
    std::vector<std::vector<double> > mat;
};

