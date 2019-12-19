#include "pch.h"
#include "Player.h"
#include "Math.h"

#include "SFML\Graphics.hpp"

Player::Player(sf::Vector2f somePosition, sf::Vector2f someScale, float someSpeed, float someFireRate)
{
	myPosition = somePosition;
	mySpeed = someSpeed;
	myFireRate = someFireRate;

	SpriteSetup(someScale);
}

void Player::SpriteSetup(sf::Vector2f someScale)
{
	//loading textures
	sf::Texture tempPlayerTexture;

	tempPlayerTexture.loadFromFile("Content/SmallTracks.png");
	myTextures.push_back(tempPlayerTexture);
	tempPlayerTexture.loadFromFile("Content/LightBase.png");
	myTextures.push_back(tempPlayerTexture);
	tempPlayerTexture.loadFromFile("Content/LightHead.png");
	myTextures.push_back(tempPlayerTexture);
	tempPlayerTexture.loadFromFile("Content/Barrier.png");
	myTextures.push_back(tempPlayerTexture);

	//set up for sprites
	for (int i = 0; i < myTextures.size(); i++)
	{
		sf::Sprite tempSprite;

		tempSprite.setOrigin(sf::Vector2f(myTextures[i].getSize().x / 2, myTextures[i].getSize().y / 2 + 40));
		tempSprite.setTexture(myTextures[i]);
		tempSprite.setScale(someScale);
		tempSprite.setPosition(myPosition);

		mySprites.push_back(tempSprite);
	}
}

Player::~Player()
{

}

sf::Vector2f Player::MovementDir()
{	
	sf::Vector2f tempVector(0, 0);
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		tempVector += sf::Vector2f(0, -1);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		tempVector += sf::Vector2f(0, 1);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		tempVector += sf::Vector2f(-1, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		tempVector += sf::Vector2f(1, 0);
	}

	return Math::NormalizeVector(tempVector);
	
}