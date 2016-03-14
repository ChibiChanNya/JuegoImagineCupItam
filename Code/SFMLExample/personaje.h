#pragma once
#include "cuadro.h"
#include <SFML/Graphics.hpp>
using namespace sf;

class personaje: public cuadro
{
public:
	sf::Sprite				mPlayer;
	int estado = 0;
	int moviendose;
	int frame;
	bool mIsMovingUp;
	bool mIsMovingDown;
	bool mIsMovingRight;
	bool mIsMovingLeft;
	void update(Time elapsedTime);
	void draw(Time elapsedTime);
	personaje(int x,int y, int h, int w);
	~personaje();
	typedef cuadro super;
};

