#include "tablero.h"


Tablero::Tablero(Nat alturaTablero, Nat anchoTablero, Nat cantColoresMaxima) :_matriz(alturaTablero, vector<Pieza const *>(anchoTablero, NULL))  {

	_alto = alturaTablero;
	_ancho = anchoTablero;
	_cantPiezas = 0;
	_cantColoresMaxima = cantColoresMaxima;

	// Inicializamos el vector con el fill constructor así que ya viene todo nulo.
	/*
	for (Nat fil = 0; fil < alturaTablero; fil++) {
		
		for (Nat col = 0; col < anchoTablero; col++) {

			assert(_matriz[fil][col] == NULL);

		}

	}*/

}


Nat Tablero::Altura() const {

	return _alto;

}


Nat Tablero::Ancho() const {

	return _ancho;

}


Nat Tablero::CantidadPiezasColocadas() const {

	return _cantPiezas;

}

Nat Tablero::CantidadDeColoresMaxima() const {
	return _cantColoresMaxima;
}


bool Tablero::SePuedeInsertar(const Pieza& pieza, Coordenada posicion) const {

	Nat fil = posicion.first;
	Nat col = posicion.second;
	assert((fil < Altura()) && (col < Ancho()) && "Coordenadas invalidas en SePuedeInsertar"); 

	const Pieza* piezaInferior = NULL;
	const Pieza* piezaSuperior = NULL;
	const Pieza* piezaDerecha = NULL;
	const Pieza* piezaIzquierda = NULL;
	
	if (TieneUnaPiezaEn(posicion))		
		return false;
	
	//Inicialización de las piezas a mirar.
	if (fil >= 1) {
		piezaSuperior = _matriz[fil-1][col];
	}
	if (fil < Altura() - 1) {
		piezaInferior = _matriz[fil+1][col];
	}
	if (col >= 1) {
		piezaIzquierda = _matriz[fil][col-1];
	}
	if (col < Ancho() - 1) {
		piezaDerecha = _matriz[fil][col+1];
	}

	//Verificación de las piezas.
	if (piezaIzquierda != NULL) {
		if (piezaIzquierda->ColorDerecho() != pieza.ColorIzquierdo()) {
			return false;
		}
	}
	if (piezaDerecha != NULL) {
		if (piezaDerecha->ColorIzquierdo() != pieza.ColorDerecho()) {
			return false;
		}
	}
	if (piezaSuperior != NULL) {
		if (piezaSuperior->ColorInferior() != pieza.ColorSuperior()) {
			return false;
		}
	}
	if (piezaInferior != NULL) {
		if (piezaInferior->ColorSuperior() != pieza.ColorInferior()) {
			return false;
		}
	}
	return true;
}

//Esta función me dice si puedo poner una pieza cualquiera en posicion.
bool Tablero::PuedoPonerPiezaEnPosicionPorEncima(const Coordenada posicion) const {

	Coordenada posicionAMirar = posicion;
	if (posicion.first > 0)
		posicionAMirar.first -= 1;
	else return false; //En caso contrario, no hay posición por encima.
	Nat fil = posicionAMirar.first;
	Nat col = posicionAMirar.second;
	assert((fil < Altura()) && (col < Ancho()) && "Coordenadas invalidas en PuedoPonerPiezaEnPosicionPorEncima");

	const Pieza* piezaInferior = NULL;
	const Pieza* piezaSuperior = NULL;
	const Pieza* piezaDerecha = NULL;
	const Pieza* piezaIzquierda = NULL;
	
	if (TieneUnaPiezaEn(posicionAMirar))		
		return false;
	
	//Inicialización de las piezas a mirar.
	if (fil >= 1) {
		piezaSuperior = _matriz[fil-1][col];
	}
	if (fil < Altura() - 1) {
		piezaInferior = _matriz[fil+1][col];
	}
	if (col >= 1) {
		piezaIzquierda = _matriz[fil][col-1];
	}
	if (col < Ancho() - 1) {
		piezaDerecha = _matriz[fil][col+1];
	}

	//Verificación de las piezas.
	if (piezaIzquierda != NULL) {
		return false;
	}
	if (piezaDerecha != NULL) {
		return false;
	}
	if (piezaSuperior != NULL) {
		return false;
	}
	if (piezaInferior != NULL) {
		return false;
	}
	return true;
}



//pre: se chequeo que la pieza se puede insertar en la coordenada "pos"
void Tablero::Insertar(const Pieza& pieza, const Coordenada pos) {
	Nat fil = pos.first;
	Nat col = pos.second;
	assert((fil < Altura()) && (col < Ancho()) && "Coordenadas invalidas en InsertarPieza"); //Coordenadas invalidas
	
	const Pieza* p = _matriz[fil][col];
	if (p == NULL)
		_cantPiezas++;
	_matriz[fil][col] = &pieza;
}


void Tablero::RemoverPieza(const Coordenada pos) {
	Nat fil = pos.first;
	Nat col = pos.second;
	assert((fil < Altura()) && (col < Ancho()) && "Coordenadas invalidas en RemoverPieza"); //Coordenadas invalidas
	
	const Pieza* p = _matriz[fil][col];
	//Si había una pieza disminuyo la cantidad de piezas.
	if (p != NULL) 
		_cantPiezas--;
	_matriz[fil][col] = NULL;
}

void Tablero::Mostrar() const {
	for (Nat fil = 0; fil < Altura(); fil++) {
		for (Nat col = 0; col < Ancho(); col++) {
			const Pieza* pieza = _matriz[fil][col];

			if (pieza != NULL)
				cout << pieza->ObtenerNumero() << " ";
			else
				cout << "0" << " ";
		}
		cout << endl;
	}
}


bool Tablero::TieneUnaPiezaEn(Coordenada posicion) const {
	Nat fil = posicion.first;
	Nat col = posicion.second;
	
	if (_matriz[fil][col] != NULL)
		return true;
	else
		return false;
}
