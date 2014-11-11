#include "problema3.h"

int main(int argc, char* argv[]);
void MedirTiempo(string& nombreDeArchivo);
void ResolverNormalmente();
void BacktrackPorFilas(Tablero& tablero, list<const Pieza*>& piezas, list<PiezaYCoordenada>& solucion, list<PiezaYCoordenada>& solucionParcial, Nat casillero);
void BacktrackPorFilasSinPodas(Tablero& tablero, list<const Pieza*>& piezas, list<PiezaYCoordenada>& solucion, list<PiezaYCoordenada>& solucionParcial);
Coordenada determinarCoordenada(const Nat casillero, const Nat columnas);
void GenerarSolucionTrivial(list<PiezaYCoordenada>&, const list<const Pieza*>&, const Nat, const Nat);
void ObtenerColores(vector<bool>&, const list<const Pieza*>&);
bool estanTodos(const vector<bool>&);
