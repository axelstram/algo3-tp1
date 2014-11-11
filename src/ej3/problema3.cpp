#include "problema3.h"



void CargarPiezas(list<const Pieza*>& piezas, const Nat n, const Nat m, const Nat cantColores) {
	//Agrego las piezas a una lista
	for (Nat nroPieza = 1; nroPieza <= n*m; nroPieza++) {
		Color sup, izq, der, inf;
		cin >> sup >> izq >> der >> inf;
		
		bool sonColores = (0 < sup && sup <= cantColores) && (0 < izq && izq <= cantColores) && 
						  (0 < der && der <= cantColores) && (0 < inf && inf <= cantColores);
		
		if (!sonColores) {
			cerr << "Hay colores invalidos en la pieza " << nroPieza << "." << endl;
			exit(EXIT_FAILURE);
		}
		
		const Pieza* pieza = new const Pieza(nroPieza, sup, izq, der, inf);
		InsertarOrdenado(piezas, pieza);
	}
	//Verifico que la cantidad de piezas es la correcta.
	assert((piezas.size() == n*m) && "La cantidad de piezas no coincide con la cantidad de casilleros.");
}


void Imprimir(list<PiezaYCoordenada>& solucion, Tablero& tablero) {

	for (list<PiezaYCoordenada>::iterator it = solucion.begin(); it != solucion.end(); it++) {
		const Pieza& pieza = *it->first;
		Coordenada posicion = it->second;
	
		tablero.Insertar(pieza, posicion);
	}

	tablero.Mostrar();
}

					
					
					 
timespec diff(timespec start, timespec end) {

    timespec temp;

    if ((end.tv_nsec-start.tv_nsec)<0) {

        temp.tv_sec = end.tv_sec-start.tv_sec-1;
        temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;

    } else {

        temp.tv_sec = end.tv_sec-start.tv_sec;
        temp.tv_nsec = end.tv_nsec-start.tv_nsec;

    }

    return temp;

}



void InsertarOrdenado(list<const Pieza*>& piezas, const Pieza* pieza) {
	for (list<const Pieza*>::iterator it = piezas.begin(); it != piezas.end(); ++it) {
		const Pieza* piezaEnLista = *it;
		if (*piezaEnLista == *pieza) {
			piezas.insert(it, pieza);
			return;
		}
	}
	
	piezas.push_back(pieza);
}	
