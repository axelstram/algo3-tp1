#include "problema2.h"


int main(int argc, char* argv[]) {
	//Primer parametro: nombre de archivo de entrada. Por default no toma mediciones.
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
		Nat npiezas;
		Instancia joyas;
		//Cargo la cantidad de piezas. Esto asume que no se le pasan caracteres no numericos.
		cin >> npiezas;
		//if (cin.peek()!='\n') {
			//cerr << "Se esperaba una nueva linea despues de la cantidad de joyas." << endl;
			//exit(EXIT_FAILURE);
		//}
		//Agrego las joyas a una lista
		cargarJoyas(joyas, npiezas);
		instancias.push_back(joyas);
		// Ignoro el newline que viene a continuacion. Asi, la proxima linea me deberia dar un 0 o el numero de piezas de la proxima instancia.
		cin.ignore(1, '\n');
	}
	
	//El codigo incluido dentro del if solo se encarga de tomar mediciones
	while (!instancias.empty()){
		list<Joya>& joyas = instancias.front();	
		resolver(joyas,true);
		if (hayQueTomarMediciones) {
			timespec startT, endT; //Para calcular el tiempo
			ofstream fileMediciones;
			string nombreDeArchivo = argv[1];
			nombreDeArchivo += ".xls";
			fileMediciones.open(nombreDeArchivo, ofstream::app); //append
			unsigned long long int sumaNanosegundos = 0;
			long double sumaSegundos = 0;
			Nat cantMediciones = 50;
			for(Nat medicion = 1; medicion <= cantMediciones; medicion++) {
				clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &startT); //comienzo a medir tiempo
				resolver(joyas,false);
				clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &endT);	//termino de medir
				timespec estaMedicion = diff(startT,endT);
				sumaNanosegundos += estaMedicion.tv_nsec;
				sumaSegundos += estaMedicion.tv_sec;
			}
			unsigned long long int promedioNanosegundos = sumaNanosegundos / cantMediciones;
			long double promedioSegundos = sumaSegundos / cantMediciones;
			fileMediciones << joyas.size() << " " << promedioSegundos << " " << promedioNanosegundos << endl;
			fileMediciones.close();	
		}
		instancias.pop_front();
	}
	return 0;
}

bool criterioDeComparacion(const Joya& joya1, const Joya& joya2) {
	double d1, t1, d2, t2;
	d1 = get<1>(joya1);
	t1 = get<2>(joya1);
	d2 = get<1>(joya2);
	t2 = get<2>(joya2);
	if (d1/t1 != d2/t2){
		return ( d1/t1 > d2/t2 );
	}
	else{
		return( d1 > d2 );
	}
}

void cargarJoyas(Instancia& joyas, const Nat npiezas) {
	for (Nat n=1; n<=npiezas && cin.good(); n++) {
		double d, t;
		cin >> d >> t;
		if (d<=0 || t<=0) {
			cerr << "La pieza " << n << " parece ser invalida. Su perdida de ganancia diaria o el tiempo de manufactura es nulo o negativo." << endl;
			exit(EXIT_FAILURE);
		}
		Joya j(n,d,t);
		joyas.push_back(j);
	}
	// En realidad esta condicion tambien se cumple si intento tomar un float del stream y no pudo porque era un caracter no numerico.
	if (!cin.good()) {
		cerr << "La cantidad de piezas a fabricar no es la esperada." << endl;
		exit(EXIT_FAILURE);
	}
}



//resolver toma un bool que le indica cuando debe mostrar por pantalla el resultado y cuando no. Lo hacemos asi para que la experimentacion quede mas legible.
void resolver(Instancia joyas, bool mostrarResultado) {
	joyas.sort(criterioDeComparacion); //uso algoritmo de stl, preguntar por el "aproximadamente" n.log n
	Nat montoPerdido = 0;
	Nat diasTranscurridos = 0;
	//Muestro la solucion optima que encontre para cada instancia. 
	for (list<Joya>::iterator it=joyas.begin(); it != joyas.end(); it++) {
		double d, t;
		Nat npieza = get<0>(*it);
		d = get<1>(*it);
		t = get<2>(*it);			
		diasTranscurridos += t;
		montoPerdido += diasTranscurridos*d;
		if (mostrarResultado == true)
			cout << npieza << ' ';
	}
	if (mostrarResultado == true)
		cout << montoPerdido << endl;
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
