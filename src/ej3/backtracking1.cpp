#include "backtracking1.h"


int main(int argc, char* argv[]) {
	
	//primer parametro: nombre de archivo para mediciones. Por default no toma mediciones.
	if (argc > 2) {
		cerr << "Demasiados parametros." << endl;
		exit(EXIT_FAILURE);
	}
	
	bool hayQueTomarMediciones = false;
	string nombreDeArchivo;
	
	if (argc == 2) {
		hayQueTomarMediciones = true;
		nombreDeArchivo = argv[1];
	}
	
	while (cin.peek() != EOF) {
		
		Nat n, m;
		cin >> n >> m;
			
		if (n == 0 || m == 0)
			break;

		Nat cantColores;
		cin >> cantColores;
		
		list<const Pieza*> piezas;
		CargarPiezas(piezas, n, m, cantColores);
		Tablero tablero(n,m, cantColores);
		list<PiezaYCoordenada> solucion;
		list<PiezaYCoordenada> solucionParcial;

		if (hayQueTomarMediciones) {

			timespec startT, endT; //Para calcular el tiempo

			ofstream fileMediciones;
			fileMediciones.open(nombreDeArchivo, ofstream::app); //append
			unsigned long long int sumaNanosegundos = 0;
			long double sumaSegundos = 0;
			Nat cantMediciones = 50;

			for(Nat medicion = 1; medicion <= cantMediciones; medicion++) {
				//Limpio las listas con soluciones ya obtenidas.
				solucion.clear();
				solucionParcial.clear();
				
				clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &startT); //comienzo a medir tiempo
				
				for (Nat nroPieza = 1; nroPieza <= n*m; nroPieza++) {
					
					Resolver(tablero, piezas, solucion, solucionParcial);
					
					Nat cantPiezasAIgnorar = ChequearColoresProximasPiezas(piezas);
					nroPieza += cantPiezasAIgnorar;
				
				}
				
				clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &endT);	//termino de medir
				
				timespec estaMedicion = diff(startT,endT);
				sumaNanosegundos += estaMedicion.tv_nsec;
				sumaSegundos += estaMedicion.tv_sec;
			
			}
			
			unsigned long long int promedioNanosegundos = sumaNanosegundos / cantMediciones;
			long double promedioSegundos = sumaSegundos / cantMediciones;

			fileMediciones << n*m << " " << promedioSegundos << " " << promedioNanosegundos << endl;
			fileMediciones.close();
			
		} else {
			
			for (Nat nroPieza = 1; nroPieza <= n*m; nroPieza++) {
				
				Resolver(tablero, piezas, solucion, solucionParcial);
				
				Nat cantPiezasAIgnorar = ChequearColoresProximasPiezas(piezas);
				
				nroPieza += cantPiezasAIgnorar;
			
			}
		
		}
		
		Imprimir(solucion, tablero);	

		//Borro las piezas
		for (list<const Pieza*>::iterator it = piezas.begin(); it != piezas.end(); it++)
			delete *it;
			
		cin.ignore(1);
			
	};
	
	return 0;
}



void Resolver(Tablero& tablero, list<const Pieza*>& piezas, list<PiezaYCoordenada>& solucion, list<PiezaYCoordenada>& solucionParcial) {
	//Si ya encontre una solucion con n*m piezas, no sigo buscando. Esta es una poda.
	if (solucion.size() < tablero.Ancho() * tablero.Altura()) {
		// Actualizo la mejor solucion que consegui hasta el momento.
		if (solucion.size() < solucionParcial.size())
			solucion = solucionParcial;
		// En cualquier caso sigo probando las piezas que me quedan.
		SeguirBuscandoUnaSolucion(tablero, piezas, solucion, solucionParcial);
	}
}



void SeguirBuscandoUnaSolucion(Tablero& tablero, list<const Pieza*>& piezas, list<PiezaYCoordenada>& solucion, list<PiezaYCoordenada>& solucionParcial) {
	
	Nat cantPiezasRestantes = piezas.size();

	if (cantPiezasRestantes > 0) {
		//Si ya encontre una solucion, pero la cantidad de piezas de la nueva solucion que estoy buscando ("solucionParcial") 
		//mas la cantidad de piezas restantes, es mayor que la cantidad de piezas en mi mejor solucion hasta el momento, entonces
		//sigo evaluando. En caso contrario, no tiene sentido seguir evaluando, ya que la solucion va a ser peor que la de "solucion"		
		if (solucion.size() < solucionParcial.size() + cantPiezasRestantes) {
			const Pieza& pieza = *(piezas.front());
			piezas.pop_front();
			
			//Voy recorriendo todo el tablero, viendo donde la puedo insertar.
			for (Nat fil = 0; fil < tablero.Altura(); fil++) {
			
				for (Nat col = 0; col < tablero.Ancho(); col++) {
					
					Coordenada posicion = make_pair(fil, col);
					
					if (tablero.SePuedeInsertar(pieza, posicion)) {
						
						tablero.Insertar(pieza, posicion);
						solucionParcial.push_back(make_pair(&pieza, posicion));

						Resolver(tablero, piezas, solucion, solucionParcial);
				
						//Cuando vuelvo de esta rama de la recursion, remuevo la pieza del tablero y de mi solucion parcial
						tablero.RemoverPieza(posicion);
						solucionParcial.pop_back();
					
					}
				
				}
			
			}
			
			//pieza, que inicialmente estaba al principio de la lista, es insertada ahora al final.
			piezas.push_back(&pieza);
		} //if	
	}
}




int ChequearColoresProximasPiezas(list<const Pieza*>& piezas) {
	
	Nat cantPiezasAIgnorar = 0;
	const Pieza* primeraPieza = piezas.front();
		
	piezas.pop_front();
	piezas.push_back(primeraPieza);
	
	const Pieza* siguientePieza = piezas.front();

	while (*primeraPieza == *siguientePieza && cantPiezasAIgnorar < piezas.size()) {
		
		piezas.pop_front();
		piezas.push_back(siguientePieza);
		siguientePieza = piezas.front();
	
		cantPiezasAIgnorar++;
	}
	
	return cantPiezasAIgnorar;
}
