#include "Enviroment.h"
#include "SFML\Graphics.hpp"

Enviroment::Enviroment(sf::RenderWindow &someWindow)
{
	myGroundTexture.loadFromFile("Content/Ground.png");
	myWallTexture.loadFromFile("Content/Wall.png");

	sf::Sprite tempSprite;

	for (int i = myGroundTexture.getSize().x * -20; i > someWindow.getSize().x * 20; i += myGroundTexture.getSize().x)
	{
		for (int j = myGroundTexture.getSize().x * -20; j > someWindow.getSize().y * 20; j += myGroundTexture.getSize().y)
		{
			tempSprite.setTexture(myGroundTexture);
			tempSprite.setPosition(sf::Vector2f(i + 900,  j + 600));

			myGroundSprite.push_back(tempSprite);
		}
	}
	
	//room
	float tempScale = 0.5;
	for (int i = myWallTexture.getSize().x * -20; i > someWindow.getSize().x * 20; i += myWallTexture.getSize().x)
	{
		for (int j = myWallTexture.getSize().y * -20; j > someWindow.getSize().y * 20; j += myWallTexture.getSize().y)
		{
			if (i == myWallTexture.getSize().x * -20 || j == myWallTexture.getSize().y * -20)
			{
				tempSprite.setTexture(myWallTexture);
				tempSprite.setPosition(sf::Vector2f(i * tempScale + 900, j * tempScale + 600));
				tempSprite.setScale(sf::Vector2f(tempScale, tempScale));

				myGroundSprite.push_back(tempSprite);
			}
		}
	}
}


Enviroment::~Enviroment()
{

}

void Enviroment::Draw(sf::RenderWindow &someWindow)
{
	for (int i = 0; i < myGroundSprite.size(); i++)
	{
		someWindow.draw(myGroundSprite[i]);
	}
}
