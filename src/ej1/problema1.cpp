#include "problema1.h"
int main(int argc, char* argv[]) {
	
	//Primer parámetro: nombre de archivo de mediciones. Por default no toma mediciones.
	if (argc > 2) {
		cerr << "Demasiados parametros." << endl;
		exit(EXIT_FAILURE);
	}
	bool hayQueTomarMediciones = false;
	if (argc == 2)
		hayQueTomarMediciones = true;
	
	list<Instancia> instancias;
	//Aca leo el archivo
	while (cin.peek() != '0') {
		Nat contrato, cantidad;
		list<Nat> diasDeLlegada;
		cin >> contrato >> cantidad;
		//assert((contrato > 0) && (cantidad > 0));
		if (cantidad==0) {
			cerr << "Hay un caso invalido porque la cantidad de camiones es 0." << endl;
			exit(EXIT_FAILURE);
		}
		//vector<bool> coloresObtenidos(cantColores, false);
		//Agrego las piezas a una lista
		while (cin.peek() != '\n') {
			Nat c;
			cin >> c;
			if (c==0) {
				cerr << "Hay un caso invalido porque el dia de llegada de un camion es 0." << endl;
				exit(EXIT_FAILURE);
			}
			diasDeLlegada.push_back(c);
		}
		//Verifico que la cantidad de camiones es la correcta.
		if (diasDeLlegada.size() != cantidad) {
			cerr << "La cantidad de camiones no coincide con la pasada por parametro." << endl;
			exit(EXIT_FAILURE);
		}
		Instancia ins(contrato, cantidad, diasDeLlegada);
		instancias.push_back(ins);
		// Ignoro el newline que viene a continuacion. Asi, la proxima linea me deberia dar un 0 o la proxima instancia.
		cin.ignore(1, '\n');
	}
	
	while (!instancias.empty()){
		Instancia& casoActual = instancias.front();
		resolver(casoActual,true);
		if (hayQueTomarMediciones) {
			timespec startT, endT; //Para calcular el tiempo
			ofstream fileMediciones;
			string nombreDeArchivo = argv[1];
			nombreDeArchivo += ".xls";
			fileMediciones.open(nombreDeArchivo, ofstream::app); //append
			unsigned long long int sumaNanosegundos = 0;
			long double sumaSegundos = 0;
			Nat cantMediciones = 50; //50 minimo
			for(Nat medicion = 1; medicion <= cantMediciones; medicion++) {
				clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &startT); //comienzo a medir tiempo
				resolver(casoActual,false);
				clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &endT);	//termino de medir
				timespec estaMedicion = diff(startT,endT);
				sumaNanosegundos += estaMedicion.tv_nsec;
				sumaSegundos += estaMedicion.tv_sec;
			}
			unsigned long long int promedioNanosegundos = sumaNanosegundos / cantMediciones;
			long double promedioSegundos = sumaSegundos / cantMediciones;
			fileMediciones << (get<2>(casoActual)).size() << " " << promedioSegundos << " " << promedioNanosegundos << endl;
			fileMediciones.close();
		}
		instancias.pop_front();
	}
	return 0;
}
	
	

void resolver(Instancia& casoActual, bool mostrarResultado) {
	Nat& contrato = get<0>(casoActual);
	// Dado que este es un parametro innecesario, se podria usar un par en lugar de una tupla.
	//Nat& cantidad = get<1>(instanciaActual);
	list<Nat> diasDeLlegada = get<2>(casoActual);

	//vector<Nat> diasDeLlegada(diasDeLlegadaAux.size())
	diasDeLlegada.sort(); //uso algoritmo de stl, preguntar por el "aproximadamente" n.log n
	//list<Nat> diasDeLlegadaj = diasDeLlegadai;
	Nat mejorCantidad = 0;
	Nat mejorDiaDeInicio = 0;
	list<Nat>::iterator primero=diasDeLlegada.begin(), ultimo=diasDeLlegada.begin();
	for (Nat i=0, j=0; primero != diasDeLlegada.end() || ultimo != diasDeLlegada.end();) {
		bool entraUnoMas = (*ultimo-*primero < contrato);
		if (entraUnoMas){
			if (mejorCantidad < i+1-j) {
				mejorCantidad = i+1-j;
				mejorDiaDeInicio = *primero;
			}
			i++;
			ultimo++;
		}
		//Como no entra el nuevo elemento que agarre, avanzo el iterador que apunta al primer camion que estoy agarrando.
		else {
			j++;
			primero++;
		}
	}
	//Muestro la solucion optima que encontre para cada instancia.
	if (mostrarResultado == true)
		cout << mejorDiaDeInicio << ' ' << mejorCantidad << endl;
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
