#include "tablero.h"
#include <cstdlib>
#include <fstream>
#include <time.h>
#include <cstring>

using namespace std;


#ifndef PIEZAYCOORDENADA
#define PIEZAYCOORDENADA
typedef pair<const Pieza*, Coordenada> PiezaYCoordenada;
#endif


void CargarPiezas(list<const Pieza*>& piezas, const Nat n, const Nat m, const Nat cantColores);
void Imprimir(list<PiezaYCoordenada>& solucion, Tablero& tablero);
void InsertarOrdenado(list<const Pieza*>& piezas, const Pieza* pieza);
timespec diff(timespec start, timespec end);
