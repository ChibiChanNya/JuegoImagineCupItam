#include "stdafx.h"
#include "personaje.h"

#define PlayerSpeed 100;
#define ARRIBA 0
#define ABAJO 128
#define IZQUIERDA 64
#define DERECHA 192

using namespace sf;

personaje::personaje(int x, int y, int h, int w) : super(x, y, h, w)
{
	estado = 0;
	moviendose = false;
	frame = 0;
}

void personaje::update(Time elapsedTime){
	Vector2f movement(0,0);
	if (mIsMovingUp) {
		movement.y -= PlayerSpeed;
		estado = ARRIBA;
	}
	if (mIsMovingDown) {
		movement.y += PlayerSpeed;
		estado = ABAJO;
	}
	if (mIsMovingLeft) {
		movement.x -= PlayerSpeed;
		estado = IZQUIERDA;
	}
	if (mIsMovingRight) {
		movement.x += PlayerSpeed;
		estado = DERECHA;
	}
	if (movement.x == 0 && movement.y == 0)
		moviendose = false;
	else
		moviendose = true;
	mPlayer.move(movement * elapsedTime.asSeconds());
}
void personaje::draw(Time elapsedTime) {
	frame += elapsedTime.asMilliseconds();
	frame %= 900;
	if (moviendose) {
		mPlayer.setTextureRect(IntRect(576 * (frame / 100) / 9, estado, 576 / 9, 256 / 4));
	}
	else {
		mPlayer.setTextureRect(IntRect(0, estado, 576 / 9, 256 / 4));
	}
}
personaje::~personaje()
{
}
