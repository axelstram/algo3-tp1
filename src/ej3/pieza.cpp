#include "pieza.h"


Pieza::Pieza(Nat nro, Color superior, Color izquierdo, Color derecho, Color inferior) {

	_numero = nro;
	_colorIzquierdo = izquierdo;
	_colorDerecho = derecho;
	_colorSuperior = superior;
	_colorInferior = inferior;

}



Color Pieza::ColorIzquierdo() const {

	return _colorIzquierdo;

}


Color Pieza::ColorDerecho() const {

	return _colorDerecho;

}


Color Pieza::ColorSuperior() const {

	return _colorSuperior;

}


Color Pieza::ColorInferior() const {

	return _colorInferior;

}


Nat Pieza::ObtenerNumero() const {

	return _numero;

}


bool Pieza::operator==(const Pieza& pieza) const {
	
	if (_colorIzquierdo == pieza.ColorIzquierdo() && _colorDerecho == pieza.ColorDerecho()
	    && _colorSuperior == pieza.ColorSuperior() && _colorInferior == pieza.ColorInferior()) {
			
			return true;
			
		}
		
	return false;
	
}

