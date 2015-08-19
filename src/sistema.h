#include "matriz.h"
#include <vector>
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
  Sistema(double r_i, double r_e, int m_mas_uno, int n, double isoterma, std::vector<std::vector<double> > temps_interiores, std::vector<std::vector<double> > temps_exteriores, enum metodo met ) {
		/* armo el sistema */

		n_ = n;
		m_mas_uno_ = m_mas_uno;
		int fila = 0;

	  A = new Matriz(n*m_mas_uno, n*m_mas_uno, 0.0);
		for(int i = 0; i<n; i++, fila++){
			(*A)(fila, fila) = 1.0;
		}

		for(int i = 1; i<=m_mas_uno-2; i++){ // m_mas_uno-2 = cantidad de
			int j = 0;                         // radios salvo interior y exterior
			
			//resuelvo primer caso aparte;	
			(*A)(fila, col_matriz(i, j)) = 8.0;  // el mismo
			
			(*A)(fila, col_matriz(i, j+1)) = 8.0;  // el siguiente
			(*A)(fila, col_matriz(i, n_-1)) = 8.0; // el anterior, que es el ultimo

			(*A)(fila, col_matriz(i-1, j)) = 8.0; // anterior nivel
			(*A)(fila, col_matriz(i+1, j)) = 8.0; // siguiente nivel

			j++; fila++;

			
			
			// resuelvo todos los casos "buenos" juntos
			for(; j<n-1; j++, fila++){
				(*A)(fila, col_matriz(i, j)) = 8.0;
				
				(*A)(fila, col_matriz(i, j+1)) = 8.0;
				(*A)(fila, col_matriz(i, j-1)) = 8.0;

				(*A)(fila, col_matriz(i-1, j)) = 8.0;
				(*A)(fila, col_matriz(i+1, j)) = 8.0;
			}

			
			// resuelvo caso final aparte
			(*A)(fila, col_matriz(i, j)) = 8.0;  // el mismo
			
			(*A)(fila, col_matriz(i, 0)) = 8.0;  // el siguiente, que es el primero
			(*A)(fila, col_matriz(i, j-1)) = 8.0; // el anterior

			(*A)(fila, col_matriz(i-1, j)) = 8.0; // anterior nivel
			(*A)(fila, col_matriz(i+1, j)) = 8.0; // siguiente nivel


			j++; fila++;
		}
					
		for(int i = 0; i<n; i++, fila++){
			(*A)(fila, fila) = 1.0;
		}
		A->mostrar();


    //armo bs
/*
		if(metodo == FACTORIZACION_LU){
			Matriz L,U = dame_factorizacion_lu(A);
			for(adsf in temeraturas)
				resolv
				resolver;
		} if(metodo == ELIM_GAUSSIANA){
			for(as in temperaturas){
				resolver;
			}
		}
*/

}


private:
	int m_mas_uno_, n_;
	Matriz * A;

	std::vector<std::vector<double> > bs;


	
	int col_matriz(int i, int j){
		return j+n_*i;
	}

};
