using namespace std;


#ifndef NAT
#define NAT
typedef unsigned int Nat;
#endif


#ifndef COLOR
#define COLOR
typedef unsigned int Color;
#endif



#ifndef PIEZA_H_
#define PIEZA_H_

class Pieza {

	private:

		Nat _numero;
		Color _colorIzquierdo;
		Color _colorDerecho;
		Color _colorSuperior;
		Color _colorInferior;

	public:

		Pieza(Nat n, Color superior, Color izquierdo, Color derecho, Color inferior);
		~Pieza() {};
		Color ColorIzquierdo() const;
		Color ColorDerecho() const;
		Color ColorSuperior() const;
		Color ColorInferior() const;
		Nat ObtenerNumero() const;
		bool operator==(const Pieza& pieza) const;

};

#endif
