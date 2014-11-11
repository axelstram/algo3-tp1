#include "problema3.h"

int main(int argc, char* argv[]);
void Resolver(Tablero& tablero, list<const Pieza*>& piezas, list<PiezaYCoordenada>& solucion, list<PiezaYCoordenada>& solucionParcial);
void SeguirBuscandoUnaSolucion(Tablero& tablero, list<const Pieza*>& piezas, list<PiezaYCoordenada>& solucion, list<PiezaYCoordenada>& solucionParcial);
int ChequearColoresProximasPiezas(list<const Pieza*>& piezas);
