#ifndef BOOK_GAME_HPP
#define BOOK_GAME_HPP

#include <SFML/Graphics.hpp>
#include "personaje.h"


class Game : private sf::NonCopyable
{
public:
	Game();
	void					run();


private:
	void					processEvents();
	void					update(sf::Time elapsedTime);
	void					render(sf::Time elapsedTime);

	void					updateStatistics(sf::Time elapsedTime);
	void					handlePlayerInput(sf::Keyboard::Key key, bool isPressed);


private:
	static const sf::Time	TimePerFrame;

	sf::RenderWindow		mWindow;
	sf::Texture				mTexture;
	sf::Font				mFont;
	sf::Text				mStatisticsText;
	sf::Time				mStatisticsUpdateTime;

	std::size_t				mStatisticsNumFrames;
};

#endif // BOOK_GAME_HPP
