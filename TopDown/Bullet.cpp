#include "pch.h"
#include "Bullet.h"
#include "Math.h"

#include <SFML\Graphics.hpp>



Bullet::Bullet(sf::Vector2f someStartPosition, sf::Vector2f someDirection, sf::Vector2f someScale, float someSpeed)
{

	myDirection = Math::NormalizeVector(someDirection - someStartPosition);
	mySpeed = someSpeed;
	myPosition = sf::Vector2f(someStartPosition.x + (myDirection.x * 80), someStartPosition.y + (myDirection.y * 80));
	myWindowSize = sf::Vector2f(1500, 900);
	myTexture.loadFromFile("Content/Bullet.png");

	mySprite.setRotation(Math::DegToRad(Math::AngleBetweenPoints(sf::Vector2f(0, 0), myDirection)) - 90);
	mySprite.setPosition(myPosition);
	mySprite.setScale(someScale);
	mySprite.setOrigin(myTexture.getSize().x / 2, myTexture.getSize().y / 2);
}

Bullet::~Bullet()
{

}

void Bullet::Update(float someDeltaTime)
{
	myPosition = myPosition + (myDirection * (mySpeed * someDeltaTime));
}

bool Bullet::OutOfWindow()
{
	if (myPosition.x < -50 || myPosition.x > myWindowSize.x + 50 || 
		myPosition.y < -50 || myPosition.y > myWindowSize.y + 50)
	{
		return true;
	}
	
	return false;
}

void Bullet::Draw(sf::RenderWindow &someWindow)
{
	myWindowSize.x = someWindow.getSize().x;
	myWindowSize.y = someWindow.getSize().y;
	mySprite.setTexture(myTexture);
	mySprite.setPosition(myPosition);
	someWindow.draw(mySprite);
}