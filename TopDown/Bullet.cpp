#include "Bullet.h"
#include "Math.h"
#include <iostream>
#include <SFML\Graphics.hpp>



Bullet::Bullet(sf::Vector2f someStartPosition, sf::Vector2f someTarget, sf::Vector2f someScale, float someSpeed, int someDamage, TypeOfBullet someBullet)
{
	myAlive = true;
	myStartPosition = someStartPosition;
	myDamage = someDamage;
	myDirection = Math::NormalizeVector(someTarget - someStartPosition);
	mySpeed = someSpeed;
	myPosition = sf::Vector2f(someStartPosition.x + (myDirection.x * 25), someStartPosition.y + (myDirection.y * 25));
	myWindowSize = sf::Vector2f(1500, 900);
	switch (someBullet)
	{
		case TypeOfBullet::MissileAmmo:
			myTexture.loadFromFile("Content/Bullet.png");
			mySprite.setColor(sf::Color::White);
			break;
		case TypeOfBullet::BulletAmmo:
			myTexture.loadFromFile("Content/Missile.png");
			break;
	}

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
	float tempBoundaries = Math::DistanceBetweenPoints(myStartPosition, myPosition);
	if (tempBoundaries > myWindowSize.x*2 || tempBoundaries < -myWindowSize.x*2 ||
		tempBoundaries > myWindowSize.y*2 || tempBoundaries < -myWindowSize.y*2)
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

sf::Sprite Bullet::GetSprite()
{
	return mySprite;
}