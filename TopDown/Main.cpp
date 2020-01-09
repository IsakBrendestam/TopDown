#include "Player.h"
#include "Enemy.h"
#include "Enviroment.h"
#include <iostream>

#include <SFML/Graphics.hpp>

int main()
{
	#pragma region Initialize
	sf::Clock tempClock;
	sf::Time tempDeltaTime;
	sf::RenderWindow window(sf::VideoMode(1500, 900), "Top Down Game");
	sf::View tempView(sf::Vector2f(0, 0), sf::Vector2f(window.getSize()));

	window.setSize(sf::Vector2u(1500, 900));

	Enviroment tempEnviroment(window);

	std::vector<Tank*> tempTanks;

	Player tempPlayer(sf::Vector2f(100, 100), sf::Vector2f(0.15f, 0.15f), 300, 1, 0.2f, 100, 10);
	tempTanks.push_back(&tempPlayer);

	for (int i = 0; i < 3; i++)
	{
		tempTanks.push_back(new Enemy(sf::Vector2f(300 + i * 400, 500), sf::Vector2f(0.15f, 0.15f), 100, 1, 0.6f, 100, 5, i));
	}

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

		for(int i = 0; i < tempTanks.size(); i++)
		{		
			std::vector<sf::Sprite> tempSprites;
			for (int j = 0; j < tempTanks.size(); j++)
			{
				if (i != j)
				{
					for (int k = 0; k < tempTanks[j]->mySprites.size(); k++)
					{
						tempSprites.push_back(tempTanks[j]->mySprites[k]);
					}
				}
			}

			tempTanks[i]->Update(tempDeltaTime.asSeconds(), window, tempTanks[0]->myPosition, tempSprites, tempTanks);

			tempSprites.clear();

			if (!tempTanks[i]->GetAlive())
			{
				tempTanks.erase(tempTanks.begin() + i);
			}
		}

		tempView.setCenter(tempPlayer.myPosition);

		#pragma endregion
		

		#pragma region Draw

		window.clear(sf::Color(110, 110, 110));

		tempEnviroment.Draw(window);

		for (int i = 0; i < tempTanks.size(); i++)
		{
			tempTanks[i]->Draw(window);
		}

		window.setView(tempView);

		window.display();

		#pragma endregion

	}

	return 0;
}
