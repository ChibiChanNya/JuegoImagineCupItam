#include "stdafx.h"
#include "game.h"
#include "StringHelpers.hpp"

using namespace sf;

const Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

personaje andre(0, 0, 64, 1);

Game::Game()
	: mWindow(VideoMode(640, 480), "SFML Application", sf::Style::Close)
	, mTexture()
	, mFont()
	, mStatisticsText()
	, mStatisticsUpdateTime()
	, mStatisticsNumFrames(0)
{
	if (!mTexture.loadFromFile("Media/Textures/pelon.png"))
	{
		// Handle loading error
	}

	andre.mPlayer.setTexture(mTexture);
	andre.mPlayer.setPosition(100.f, 100.f);

	mFont.loadFromFile("Media/Sansation.ttf");
	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10);
	mWindow.setFramerateLimit(60);
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processEvents();
			update(TimePerFrame);
		}

		updateStatistics(elapsedTime);
		render(elapsedTime);
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;

		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;

		case sf::Event::Closed:
			mWindow.close();
			break;
		}
	}
}

void Game::update(sf::Time elapsedTime)
{
	andre.update(elapsedTime);
	
	
}

void Game::render(Time elapsedTime)
{
	mWindow.clear();
	andre.draw(elapsedTime);
	mWindow.draw(andre.mPlayer);
	mWindow.draw(mStatisticsText);
	mWindow.display();
}

void Game::updateStatistics(sf::Time elapsedTime)
{
	mStatisticsUpdateTime += elapsedTime;
	mStatisticsNumFrames += 1;

	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString(
			"Frames / Second = " + toString(mStatisticsNumFrames) + "\n" +
			"Time / Update = " + toString(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + "us");

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W)
		andre.mIsMovingUp = isPressed;
	else if (key == sf::Keyboard::S)
		andre.mIsMovingDown = isPressed;
	else if (key == sf::Keyboard::A)
		andre.mIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		andre.mIsMovingRight = isPressed;
}
