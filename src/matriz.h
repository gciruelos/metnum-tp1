#include <vector>


class Matriz {


public:
  // n = filas, m = columnas
  Matriz(int n, int m) : N(n), M(m) {
    // hay que crearla y ponerla toda en 0.0
  };


  // una funcion que la pueda imprimir
  

  // una funcion que de columnas
  

  // una funcion que de filas
  

  // una funcion que devuelva referencia a un coeficiente de la matriz
  // de tal manera de poder cambiarlos a gusto.
  // ver overload de operator()
  // algo como
  // const double &operator()(const int &i, const int &j) const


  // una funcion que resuelva un sistema que es triangular superior
  

  // una funcion que resuelva un sistema que es triangular inferior


  // una funcion que triangule la matriz usando gauss jordan


  // una funcion que devuelva un par de matrices  std::pair<Matriz,Matriz>(L,U),
  // (que sean la descomposicion LU)



private:
    int N;
    int M;
    // hay que elegir la representacion
};

