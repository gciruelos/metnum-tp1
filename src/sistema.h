
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

  Sistema(double r_i, double r_e, int m_mas_uno, int n, double isoterma, double init, std::vector<std::vector<double> > temps_interiores, std::vector<std::vector<double> > temps_exteriores, enum metodo met ) {
		//armar el sistema

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
	int m_mas_uno, n;
	Matriz A;

	std::vector<std::vector<double> > bs;

};
