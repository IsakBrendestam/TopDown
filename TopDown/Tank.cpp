#include "pch.h"
#include "Tank.h"
#include <iostream>
#include "Math.h"
#include "Bullet.h"


Tank::Tank()
{
	myElapsedTime = myFireRate;
}


Tank::~Tank()
{

}


void Tank::Update(float someDeltaTime, sf::RenderWindow &someWindow)
{
	//movement update
	myPosition = myPosition + (MovementDir() * (mySpeed * someDeltaTime));

	Attack(someDeltaTime, someWindow);
	
	Defence();
	
	//bullet update + removal
	for(int i = 0; i < myBullets.size(); i++)
	{
		myBullets[i].Update(someDeltaTime);		

		if (myBullets[i].OutOfWindow())
		{
			myBullets.erase(myBullets.begin() + i);
		}
	}
	
}

void Tank::Attack(float someDeltaTime, sf::RenderWindow &someWindow)
{
	myElapsedTime += someDeltaTime;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && myElapsedTime > myFireRate)
	{
		myBullets.push_back(Bullet(myPosition, sf::Vector2f(sf::Mouse::getPosition(someWindow)), sf::Vector2f(0.7f, 0.7f), 800));
		myElapsedTime = 0;
	}
}

bool Tank::Defence()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		return true;
	}	

	return false;
}

void Tank::Draw(sf::RenderWindow &someWindow)
{
	for (int i = 0; i < mySprites.size(); i++)
	{
		mySprites[i].setPosition(myPosition);

		//body rotation
		if (MovementDir() != sf::Vector2f(0, 0) && i != 2)
		{
			mySprites[i].setRotation(MovementDir().x * 90 - (MovementDir().y * 90 + (std::abs(MovementDir().y) * 90)));
		}

		//top part rotation
		sf::Vector2f tempMousePosition(sf::Mouse::getPosition(someWindow));
		sf::Vector2f tempSpritePosition(mySprites[mySprites.size() - 1].getPosition());
		mySprites[2].setRotation(Math::DegToRad(Math::AngleBetweenPoints(tempMousePosition, tempSpritePosition)) + 90);
		
		//draw
		if (myBullets.size() > 0)
		{
			for (int i = 0; i < myBullets.size(); i++)
			{
				myBullets[i].Draw(someWindow);
			}
		}

		if (i != 3 || Defence())
		{
			someWindow.draw(mySprites[i]);
		}
	}
}