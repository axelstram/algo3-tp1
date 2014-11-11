#include <fstream>
#include <cstdlib>
#include <time.h>
#include <iostream>
#include <sstream>

using namespace std;

void CrearInstanciaDelProblema(unsigned int i, unsigned int j, unsigned int cantColores, ostream& testFile);
void CrearTodasLasInstanciasDeDimension(unsigned int dimension, unsigned int cantColores, unsigned int tanda, unsigned int tandas, ostream& testFile);


int main(int argc, char* argv[]) {
	
	//primer parámetro: nombre base del archivo donde guardar el test
	//segundo parámetro: dimension maxima.
	//tercer parámetro: número de colores máximo.
	//cuarto parámetro: número de archivos para repartir las instancias.
	
	if (argc > 5) {
		cout << "Demasiados parametros." << endl;
		exit(EXIT_FAILURE);
	}
	else if (argc < 5) {
		cout << "Pocos parametros." << endl;
		exit(EXIT_FAILURE);
	}
	
	
	unsigned int dimension_maxima = atoi(argv[2]);
	unsigned int cantColores = atoi(argv[3]);
	unsigned int tandas = atoi(argv[4]);
	for (unsigned int i = 1; i <= tandas; i++) {
		string nombreDeArchivo = argv[1];
		nombreDeArchivo += "-";
		stringstream n;
		n << i;
		nombreDeArchivo += n.str();
		ofstream testFile;
		testFile.open(nombreDeArchivo);
		
		srand(time(NULL));
		for (unsigned int dimension = 1; dimension <= dimension_maxima; dimension++) {
		
			CrearTodasLasInstanciasDeDimension(dimension, cantColores, i-1, tandas, testFile);

		}

		testFile.close();
	
	}
	return 0;
}


void CrearTodasLasInstanciasDeDimension(unsigned int dimension, unsigned int cantColores, unsigned int tanda, unsigned int tandas, ostream& testFile) {
	for (unsigned int i = 1; i <= dimension; i++) {
		for (unsigned int j = 1; j <= dimension; j++) {
			if (i*j == dimension && (i+j)%tandas == tanda) {
				CrearInstanciaDelProblema(i, j, cantColores, testFile);
			}
		}
	}
} 


void CrearInstanciaDelProblema(unsigned int i, unsigned int j, unsigned int cantColores, ostream& testFile) {
	testFile << i << " " << j << " " << cantColores << endl;
	
	for (unsigned int cantPiezasDefinidas = 0; cantPiezasDefinidas < i * j; cantPiezasDefinidas++) {
		
		unsigned int colorSuperior = (rand() % cantColores) + 1;
		unsigned int colorIzquierdo = (rand() % cantColores) + 1;
		unsigned int colorDerecho = (rand() % cantColores) + 1;
		unsigned int colorInferior = (rand() % cantColores) + 1;
		
		testFile << colorSuperior << " " << colorIzquierdo << " " << colorDerecho << " " << colorInferior << endl;
	}
}
