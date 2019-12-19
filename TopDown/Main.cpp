#include "pch.h"
#include <iostream>
#include "Player.h"

#include <SFML/Graphics.hpp>

int main()
{
	#pragma region Initialize

	sf::Clock tempClock;
	sf::Time tempDeltaTime;
	sf::RenderWindow window(sf::VideoMode(1500, 900), "Top Down Game");

	window.setSize(sf::Vector2u(1500, 900));

	Player tempPlayer(sf::Vector2f(100, 100), sf::Vector2f(0.25f, 0.25f), 300, 0.5f);

	#pragma endregion

	while (window.isOpen())
	{

		#pragma region Update

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
		}

		tempDeltaTime = tempClock.restart();

		tempPlayer.Update(tempDeltaTime.asSeconds(), window);

		#pragma endregion
		

		#pragma region Draw

		window.clear(sf::Color(110, 110, 110));
		tempPlayer.Draw(window);
		window.display();

		#pragma endregion

	}

	return 0;
}
