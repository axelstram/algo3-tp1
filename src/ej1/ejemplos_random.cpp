#include <fstream>
#include <cstdlib>
#include <time.h>
#include <iostream>

using namespace std;

int main() {
	srand(time(NULL));
	ofstream testFile;
	unsigned int diferenciaMax;
	unsigned int camionesMin;
	unsigned int camionesMax;
	unsigned int contrato;
	cout << "inserte hasta que dia llegan camiones:";
	cin >> diferenciaMax;
	cout << "inserte la cantidad de camiones minima:";
	cin>> camionesMin;
	cout << "inserte la cantidad de camiones maxima:"; 
	cin>> camionesMax;
	testFile.open("tests_random");
	

	
	for (unsigned int camiones = camionesMin; camiones <= camionesMax; camiones++) {
		contrato = (rand() % diferenciaMax)+1;
		//Creo una instancia del problema
		testFile << contrato << " " << camiones;
		for (unsigned int i = 1; i <= camiones; i++) {
	
			unsigned int diaCamion = (rand() % diferenciaMax) + 1;
			testFile << " " << diaCamion ;
			
		}
		testFile << endl;
	}
		
	testFile << "0";
	
	testFile.close();
	
} 
