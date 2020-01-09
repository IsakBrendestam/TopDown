#include "pch.h"
#include "Tank.h"
#include "Math.h"
#include "Bullet.h"
#include "Collision.h"
#include <random>
#include <iostream>

void Tank::Initialize(sf::Vector2f somePosition, float someSpeed, int someHealth)
{
	myAlive = true;
	myPosition = somePosition;
	mySpeed = someSpeed;
	myMaxHealth = someHealth;
	myHealth = myMaxHealth;

	ChangeHealth(0);
}

Tank::~Tank()
{

}

void Tank::Update(float someDeltaTime, sf::RenderWindow &someWindow, sf::Vector2f somePlayerPosition, std::vector<sf::Sprite> someOtherSprites, std::vector<Tank*> &someTanks)
{
	if (myAlive)
	{
		myPosition = myPosition + (MovementDir() * (mySpeed * someDeltaTime));

		myPlayerPosition = somePlayerPosition;

		//Defence
		Defence();

		//bullet update & removal
		BulletManagement(someDeltaTime, someTanks, someWindow);
	}
}

void Tank::BulletManagement(float someDeltaTime, std::vector<Tank*> &someTanks, sf::RenderWindow &someWindow)
{
	//bullet
	for (int i = 0; i < myBullets.size(); i++)
	{
		myBullets[i].Update(someDeltaTime);

		//tank	
		for (int j = 0; j < someTanks.size(); j++)
		{
			//sprites
			for (int k = 0; k < someTanks[j]->mySprites.size(); k++)
			{
				if (myBullets[i].GetSprite().getGlobalBounds().intersects(someTanks[j]->mySprites[k].getGlobalBounds()) && someTanks[j]->ChildName() != ChildName())
				{
					//std::cout << someTanks[j]->myHealth << std::endl;
					someTanks[j]->ChangeHealth(myBullets[i].myDamage);
					myBullets[i].myAlive = false;
				}
			}
		}

		if (myBullets[i].OutOfWindow())
		{
			myBullets[i].myAlive = false;
		}

		if (!myBullets[i].myAlive)
		{
			myBullets.erase(myBullets.begin() + i);
		}
	}
}

void Tank::Attack(float someDeltaTime, float someSpeed, int someDamage, sf::RenderWindow &someWindow, sf::Vector2f someTarget, Bullet::TypeOfBullet someTypeOfBullet)
{
	myBullets.push_back(Bullet(myPosition, someTarget, sf::Vector2f(0.5f, 0.5f), someSpeed, someDamage, someTypeOfBullet));
}

//Display and change health
void Tank::ChangeHealth(int someDamage)
{
	myHealth -= someDamage;

	if (myHealth <= 0)
	{
		myHealth = 0;
	}

	if (myHealth <= 0)
	{
		myAlive = false;
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

		//Body rotation
		if (MovementDir() != sf::Vector2f(0, 0) && i != 2)
		{
			mySprites[i].setRotation(MovementDir().x * 90 - std::abs(std::abs(MovementDir().y * 90) + MovementDir().y * 90));
		}
		
		//Drawig tank
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

	//Updateing Health Display
	DisplayHealth(someWindow);
}

bool Tank::GetAlive()
{
	return myAlive;
}