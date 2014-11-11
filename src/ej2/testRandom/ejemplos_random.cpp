#include <iostream>
#include <list>
#include <utility> 
#include <tuple>
#include <assert.h>
#include <fstream>
#include <time.h>
#include <cstring>

using namespace std;

#ifndef NAT
#define NAT
typedef unsigned int Nat;
#endif

#ifndef JOYA
#define JOYA
typedef tuple<Nat, double, double> Joya;
#endif

#ifndef INSTANCIA
#define INSTANCIA
typedef list<Joya> Instancia;
#endif

int main();



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
	testFile.open("tests1");
		//Creo una instancia del problema

	for (unsigned int cantidadDeJoyas = 1; cantidadDeJoyas <= cantidadDeJoyasMax; cantidadDeJoyas=cantidadDeJoyas+100) {
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
