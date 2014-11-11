#include "pieza.h"
#include <iostream>
#include <list>
#include <vector>
#include "assert.h"


#ifndef MATRIZ
#define MATRIZ
typedef vector<vector<const Pieza *> > Matriz;
#endif


#ifndef COORDENADA
#define COORDENADA
typedef pair<Nat, Nat> Coordenada;
#endif


#ifndef TABLERO_H_
#define TABLERO_H_

class Tablero {

	private:

		Nat _alto;
		Nat _ancho;
		Nat _cantPiezas;
		Nat _cantColoresMaxima;
		Matriz _matriz;


	public:

		Tablero(Nat alturaTablero, Nat anchoTablero, Nat cantColores);
		Nat Altura() const;
		Nat Ancho() const;
		Nat CantidadPiezasColocadas() const;
		Nat CantidadDeColoresMaxima() const;
		void Insertar(const Pieza& pieza, const Coordenada pos);
		void RemoverPieza(const Coordenada pos);
		void Mostrar() const;
		//Indica si colocar una pieza en una posición cumple con las reglas del rompecolores.
		bool SePuedeInsertar(const Pieza& pieza, Coordenada pos) const;
		bool PuedoPonerPiezaEnPosicionPorEncima(const Coordenada pos) const;
		bool TieneUnaPiezaEn(Coordenada posicion) const;

};


#endif
