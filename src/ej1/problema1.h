using namespace std;
#include <iostream>
#include <list>
#include <tuple>
#include <string>
#include <cstring>
#include <fstream>
#include <cassert>

#ifndef NAT
#define NAT
typedef unsigned int Nat;
#endif

#ifndef INSTANCIA
#define INSTANCIA
typedef tuple<Nat, Nat, list<Nat> > Instancia;
#endif

int main(int argc, char* argv[]);
void resolver(Instancia& casoActual, bool mostrarResultado);
timespec diff(timespec start, timespec end);
