#include "backtracking2.h"

bool usarPoda1 = true;
bool usarPoda2 = true;
bool usarPoda3 = true;
bool usarPoda4 = true;

int main(int argc, char* argv[]) {
	
	//primer parametro: nombre del archivo para guardar mediciones. Esta opcion  Por default no toma mediciones.
	//Los siguientes parametros controlan las podas usadas. Se activan con 1 y se desactivan con 0.
	//Por default, todas las podas estan activadas. Solo se acepta recibir 1, 2 o 5 parametros.
	//Si alguna poda no esta explicitada el programa termina con error. La poda 4 la utilizamos siempre.
	//segundo parametro: poda 1
	//tercero parametro: poda 2
	//cuarto parametro: poda 3
	if (argc > 5) {
		cerr << "Demasiados parametros." << endl;
		exit(EXIT_FAILURE);
	}
	else if (argc > 2 && argc < 5) {
		cerr << "Las podas deben explicitarse todas." << endl;
		exit(EXIT_FAILURE);
	}
	
	
	bool hayQueTomarMediciones = false;
	string nombreDeArchivo;
	if (argc >= 2) {
		hayQueTomarMediciones = true;
		nombreDeArchivo = argv[1];
		nombreDeArchivo += " podas ";
		if (argc == 5) {
			nombreDeArchivo += argv[2];
			nombreDeArchivo += " ";
			nombreDeArchivo += argv[3];
			nombreDeArchivo += " ";
			nombreDeArchivo += argv[4];
		} else {
			nombreDeArchivo += "1 1 1";
		}
	}
		
	if (argc == 5) {
		if (strcmp(argv[2],"0") == 0)
			usarPoda1 = false;
		else
			usarPoda1 = true;
		if (strcmp(argv[3],"0") == 0)
			usarPoda2 = false;
		else
			usarPoda2 = true;
		if (strcmp(argv[4],"0") == 0)
			usarPoda3 = false;
		else
			usarPoda3 = true;
	}
	
	while (cin.peek() != EOF) {
		
		if (hayQueTomarMediciones) {
						
			MedirTiempo(nombreDeArchivo);
				
		} else {
			
			ResolverNormalmente();
			
		}
		
		cin.ignore(1);
		
	}
	
	return 0;
	
}


void MedirTiempo(string& nombreDeArchivo) {
	
	Nat n;
	Nat m;
	Nat cantColores;

	cin >> n; //Si hubiera un cero aca, deberia haber terminado.
	cin >> m;
	cin >> cantColores;
	
	
	list<const Pieza*> piezas;
	CargarPiezas(piezas, n, m, cantColores);
	Tablero tablero(n, m, cantColores);
	list<PiezaYCoordenada> solucion;
	list<PiezaYCoordenada> solucionParcial;

	ofstream fileMediciones;
	fileMediciones.open(nombreDeArchivo, ofstream::app); //append
	timespec startT, endT; //Para calcular el tiempo
	unsigned long long int sumaNanosegundos = 0;
	long double sumaSegundos = 0;
	Nat cantMediciones = 50;

	for(Nat medicion = 1; medicion <= cantMediciones; medicion++) {
		//Limpio las listas con soluciones ya obtenidas.
		solucion.clear();
		solucionParcial.clear();
		//Reseteo la poda 4.
		usarPoda4 = true;
		
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &startT); //comienzo a medir tiempo
		BacktrackPorFilas(tablero, piezas, solucion, solucionParcial, 0);
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &endT);	//termino de medir
					
		timespec estaMedicion = diff(startT,endT);
		sumaNanosegundos += estaMedicion.tv_nsec;
		sumaSegundos += estaMedicion.tv_sec;
	}
	unsigned long long int promedioNanosegundos = sumaNanosegundos / cantMediciones;
	long double promedioSegundos = sumaSegundos / cantMediciones;

	fileMediciones << n*m << " " << promedioSegundos << " " << promedioNanosegundos << endl;
	fileMediciones.close();
	Imprimir(solucion, tablero); //Con esto sabemos que esta trabajando.

	//Borro las piezas
	for (list<const Pieza*>::iterator it = piezas.begin(); it != piezas.end(); it++)
		delete *it;
}

void ResolverNormalmente() {
	
	Nat n;
	Nat m;
	Nat cantColores;

	cin >> n;
	cin >> m;	
	cin >> cantColores;

	
	//Inicializamos las listas y el tablero.
	list<const Pieza*> piezas;
	CargarPiezas(piezas, n, m, cantColores);
	Tablero tablero(n, m, cantColores);
	list<PiezaYCoordenada> solucion;
	list<PiezaYCoordenada> solucionParcial;

	BacktrackPorFilas(tablero, piezas, solucion, solucionParcial, 0);
	//BacktrackPorFilasSinPodas(tablero, piezas, solucion, solucionParcial, 0);
	
	//Coloco las piezas en el tablero y llamo a mostrar del tablero.
	Imprimir(solucion, tablero);

	//Borro las piezas
	for (list<const Pieza*>::iterator it = piezas.begin(); it != piezas.end(); it++)
		delete *it;
		
}




//Con esta funcion, se recorre casillero por casillero probando todas las piezas de las que se dispone.
void BacktrackPorFilasSinPodas(Tablero& tablero, list<const Pieza*>& piezas, list<PiezaYCoordenada>& solucion, list<PiezaYCoordenada>& solucionParcial, Nat casillero) {
	//En este ciclo pruebo todas las piezas que tengo en un determinado casillero.
	Nat cantPiezas = piezas.size();
	//Obtengo la coordenada del casillero donde voy a probar todas las piezas.
	Coordenada posicionActual = determinarCoordenada(casillero, tablero.Ancho());
	for (Nat i = 1; i <= cantPiezas; i++) {
		const Pieza& pieza = *(piezas.front());
		piezas.pop_front();
		
		if (tablero.SePuedeInsertar(pieza, posicionActual)) {
			tablero.Insertar(pieza, posicionActual);
			solucionParcial.push_back(make_pair(&pieza, posicionActual));
			//Actualizo la solucion si encontre una mejor.
			if (solucion.size() < solucionParcial.size())
				solucion = solucionParcial;
			//Hago recursion si no estoy en el ultimo casillero.
			if (casillero < tablero.Ancho()*tablero.Altura()-1)
				BacktrackPorFilasSinPodas(tablero, piezas, solucion, solucionParcial, casillero+1);
			//Cuando vuelvo de esta rama de la recursion, remuevo la pieza del tablero y de mi solucion parcial.
			tablero.RemoverPieza(posicionActual);
			solucionParcial.pop_back();
		}
		//pieza, que inicialmente estaba al principio de la lista, es insertada ahora al final.
		piezas.push_back(&pieza);
	}
	//Finalmente, miro la posibilidad de dejar este casillero vacio.
	if (casillero < tablero.Ancho()*tablero.Altura()-1)
		BacktrackPorFilasSinPodas(tablero, piezas, solucion, solucionParcial, casillero+1);
}

//Con esta funcion, se recorre casillero por casillero probando todas las piezas de las que se dispone.
void BacktrackPorFilas(Tablero& tablero, list<const Pieza*>& piezas, list<PiezaYCoordenada>& solucion, list<PiezaYCoordenada>& solucionParcial, Nat casillero) {
	
	//Si tengo n*m*4 colores, entonces no puedo poner ninguna pieza al lado de otra. Poda 4.
	if (tablero.CantidadDeColoresMaxima() == tablero.Ancho()*tablero.Altura()*4 && usarPoda4) {
		//Creo un vector de booleanos del tamaño de la cantidad de colores y lo inicializo con false.
		vector<bool> estaColor(tablero.CantidadDeColoresMaxima(), false);
		//Pongo true para cada color que encuentro.
		ObtenerColores(estaColor, piezas);
		//Reviso a ver si estan todos los colores.
		if (estanTodos(estaColor)) {
			GenerarSolucionTrivial(solucion, piezas, tablero.Ancho(), tablero.Altura());
			return;
		} else
			usarPoda4 = false; //Con esto hago el checkeo una sola vez, en la primer llamada del algoritmo.
	}

	//Evito explorar el tablero cuando se que no me va a dar una solucion mejor a la encontrada. Poda 2.
	Nat cantCasillerosRestantes = (tablero.Ancho()*tablero.Altura())-casillero;
	if (solucion.size() >= solucionParcial.size() + cantCasillerosRestantes && usarPoda2)
		return;

	//En este ciclo pruebo todas las piezas que tengo en un determinado casillero.
	Nat cantPiezas = piezas.size();
	//Obtengo la coordenada del casillero donde voy a probar todas las piezas.
	Coordenada posicionActual = determinarCoordenada(casillero, tablero.Ancho());
	for (Nat i = 1; i <= cantPiezas; i++) {
		const Pieza& pieza = *(piezas.front());
		piezas.pop_front();
		
		if (tablero.SePuedeInsertar(pieza, posicionActual)) {
			tablero.Insertar(pieza, posicionActual);
			solucionParcial.push_back(make_pair(&pieza, posicionActual));
			//Actualizo la solucion si encontre una mejor.
			if (solucion.size() < solucionParcial.size())
				solucion = solucionParcial;

			//Hago recursion si no estoy en el ultimo casillero.
			if (casillero < tablero.Ancho()*tablero.Altura()-1)
				BacktrackPorFilas(tablero, piezas, solucion, solucionParcial, casillero+1);
			//Cuando vuelvo de esta rama de la recursion, remuevo la pieza del tablero y de mi solucion parcial.
			tablero.RemoverPieza(posicionActual);
			solucionParcial.pop_back();
		}
		
		//Aca va la poda que descarta las piezas iguales salteandolas. Poda 3.
		while (i < cantPiezas && usarPoda3) {
			if (pieza == *(piezas.front())) {
				piezas.push_back(piezas.front());
				piezas.pop_front();
				i++;
			}
			else break;
		}
		
		//pieza, que inicialmente estaba al principio de la lista, es insertada ahora al final.
		piezas.push_back(&pieza);
	}
	//Finalmente, miro la posibilidad de dejar este casillero vacio.
	//La primer condicion evita irme fuera del tablero.
	if (casillero < tablero.Ancho()*tablero.Altura()-1) {
		//Poda 1. Si estoy en cualquier fila que no sea la primera miro el casillero que esta por encima de este.
		//Si puedo poner una pieza, entonces no tiene sentido seguir la recursion salteando este casillero.
		if (!tablero.PuedoPonerPiezaEnPosicionPorEncima(posicionActual) || !usarPoda1)
			BacktrackPorFilas(tablero, piezas, solucion, solucionParcial, casillero+1);
	}
}


Coordenada determinarCoordenada(const Nat casillero, const Nat columnas) {
	Coordenada res;
	//Calculo la fila
	res.first = casillero / columnas;
	//Calculo la columna
	res.second = casillero % columnas;
	return res;
}

void ObtenerColores(vector<bool>& estaColor, const list<const Pieza*>& piezas) {
	for (list<const Pieza*>::const_iterator it = piezas.begin(); it != piezas.end(); ++it) {
		Color sup, izq, der, inf;
		sup = (*it)->ColorSuperior();
		izq = (*it)->ColorIzquierdo();
		der = (*it)->ColorDerecho();
		inf = (*it)->ColorInferior();
		estaColor[sup - 1] = true;
		estaColor[izq - 1] = true;
		estaColor[der - 1] = true;
		estaColor[inf - 1] = true;
	}
}

bool estanTodos(const vector<bool>& estaColor) {
	for (vector<bool>::const_iterator it = estaColor.begin(); it != estaColor.end(); it++) {
		if (!(*it))
			return false;
	}
	return true;
}

void GenerarSolucionTrivial(list<PiezaYCoordenada>& solucion, const list<const Pieza*>& piezas, const Nat columnas, const Nat filas) {
	list<const Pieza*>::const_iterator it = piezas.begin();
	for (Nat i = 0; i<filas; i++) {
		for (Nat j = 0; j<columnas; j++) {
			if ((i+j)%2 == 0) {
				Coordenada posicion(i,j);
				solucion.push_back(make_pair(*it, posicion));
				it++;
			}
		}
	}
}

