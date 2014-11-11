#include <fstream>
#include <cstdlib>
#include <time.h>
#include <iostream>

using namespace std;

int main() {
	srand(time(NULL));
	ofstream testFile;
	unsigned int cantidadDeJoyasMax;
	unsigned int descuentoMax;
	unsigned int tiempoMax;
	unsigned int descuento;
	unsigned int tiempo;
	cout << "inserte cantidad de joyas:";
	cin >> cantidadDeJoyasMax;
	cout << "inserte descuento maximo:";
	cin >> descuentoMax;
	cout << "inserte tiempo maximo:";
	cin >> tiempoMax;
	testFile.open("tests_random");
		//Creo una instancia del problema

	for (unsigned int cantidadDeJoyas = 1; cantidadDeJoyas <= cantidadDeJoyasMax; cantidadDeJoyas++) {
		testFile << cantidadDeJoyas << endl;
		for (unsigned int joya = 1; joya <= cantidadDeJoyas; joya++) {
			descuento = (rand() % descuentoMax)+1;
			tiempo = (rand() % tiempoMax)+1;
			testFile << descuento << " " << tiempo << endl;
		}
		
	}
	testFile << "0" << endl;
	testFile.close();
	
} 
