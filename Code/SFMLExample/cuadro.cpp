#include "stdafx.h"
#include "cuadro.h"

int x;
int y;
int ancho;
int alto;

cuadro::cuadro(int xx, int yy, int an, int al)
{
	x = xx;
	y = yy;
	ancho = an;
	alto = al;
}


cuadro::~cuadro()
{
}

bool checkCollision(cuadro otro) {
	if ((otro.x <= x && x <= otro.x + otro.ancho) || x <= (otro.x && otro.x <= x + ancho)) {
		if ((otro.y <= y && y <= otro.y + otro.alto) || y <= (otro.y && otro.y <= y + alto)) {
			return true;
		}
	}
	return false;
}
