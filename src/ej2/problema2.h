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


//list<int> listaDeTareas(list<pair <int,int> >);
int main(int argc, char* argv[]);
bool criterioDeComparacion(const Joya&, const Joya&);
void cargarJoyas(Instancia& joyas, const Nat npiezas);
void resolver(Instancia instancia, bool mostrarResultado);
timespec diff(timespec , timespec);
