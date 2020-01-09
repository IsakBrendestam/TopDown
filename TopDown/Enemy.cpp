#include "pch.h"
#include "Enemy.h"
#include "Math.h"
#include <iostream>

Enemy::Enemy(sf::Vector2f somePosition, sf::Vector2f someScale, float someSpeed, float someAttackFireRate, float someMainAttackFireRate, int someHealth, int someDamage, int someID)
{
	myAttackFireRate = someAttackFireRate;
	myMainAttackFireRate = someMainAttackFireRate;
	myAttackElapsedTime = myAttackFireRate;
	myMainAttackElapsedTime = myMainAttackFireRate;

	myDamage = someDamage;
	myID = someID;

	Initialize(somePosition, someSpeed, someHealth);	
	SpriteSetup(someScale, somePosition);
}

Enemy::~Enemy()
{

}

void Enemy::SpriteSetup(sf::Vector2f someScale, sf::Vector2f somePosition)
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

	myFullHealthTexture.loadFromFile("Content/HealthBarFull.png");
	myEmptyHealthTexture.loadFromFile("Content/HealthBarEmpty.png");

	//set up for sprites
	for (int i = 0; i < myTextures.size(); i++)
	{
		sf::Sprite tempSprite;

		tempSprite.setOrigin(sf::Vector2f(myTextures[i].getSize().x / 2, myTextures[i].getSize().y / 2 + 40));
		tempSprite.setTexture(myTextures[i]);
		tempSprite.setScale(someScale);
		tempSprite.setPosition(somePosition);

		mySprites.push_back(tempSprite);
	}

	myFullHealthSprite.setOrigin(sf::Vector2f(0, myFullHealthTexture.getSize().y / 2));
	myFullHealthSprite.setTexture(myFullHealthTexture);
	myFullHealthSprite.setScale(sf::Vector2f(0.15f, 0.1f));
	myFullHealthSprite.setPosition(myPosition - sf::Vector2f(20, 50));

	myEmptyHealthSprite.setOrigin(sf::Vector2f(0, myEmptyHealthTexture.getSize().y / 2));
	myEmptyHealthSprite.setTexture(myEmptyHealthTexture);
	myEmptyHealthSprite.setScale(sf::Vector2f(0.15f, 0.1f));
	myEmptyHealthSprite.setPosition(myFullHealthSprite.getPosition());
}

void Enemy::Update(float someDeltaTime, sf::RenderWindow &someWindow, sf::Vector2f somePlayerPosition, std::vector<sf::Sprite> someOtherSprites, std::vector<Tank*> &someTank)
{
	Tank::Update(someDeltaTime, someWindow, somePlayerPosition, someOtherSprites, someTank);

	myMainAttackElapsedTime += someDeltaTime;
	myAttackElapsedTime += someDeltaTime;

	//Attack
	if (myAttackElapsedTime > myAttackFireRate)
	{
		int tempFireOffset = rand() % 100 + (-100);
		Attack(someDeltaTime, 600, 20, someWindow, sf::Vector2f(myPlayerPosition.x + tempFireOffset, myPlayerPosition.y + tempFireOffset), Bullet::BulletAmmo);
		myAttackElapsedTime = 0;
	}

	//Main Attack
	if (myMainAttackElapsedTime > myMainAttackFireRate && Math::DistanceBetweenPoints(myPosition, myPlayerPosition) > 200 && ChildName() == "Enemy")
	{
		int tempFireOffset = rand() % 100 + (-100);
		Attack(someDeltaTime, 1000, 5, someWindow, sf::Vector2f(myPlayerPosition.x + tempFireOffset, myPlayerPosition.y + tempFireOffset), Bullet::MissileAmmo);
		myMainAttackElapsedTime = 0;
	}
}

sf::Vector2f Enemy::MovementDir()
{
	if (Math::DistanceBetweenPoints(myPosition, myPlayerPosition) >= 200)
	{
		return Math::DirectionBetweenPoitns(myPosition, myPlayerPosition);
	}

	return sf::Vector2f(0, 0);
}

void Enemy::DisplayHealth(sf::RenderWindow &someWindow)
{
	myFullHealthSprite.setPosition(myPosition - sf::Vector2f(20, 50));
	myEmptyHealthSprite.setPosition(myFullHealthSprite.getPosition());

	float tempScale = (static_cast<float>(myHealth) / static_cast<float>(myMaxHealth));
	myFullHealthSprite.setScale(sf::Vector2f(0.15f * tempScale, myFullHealthSprite.getScale().y));

	someWindow.draw(myEmptyHealthSprite);
	someWindow.draw(myFullHealthSprite);
}

void Enemy::Draw(sf::RenderWindow &someWindow)
{
	sf::Vector2f tempTargetPosition = myPlayerPosition;

	mySprites[2].setRotation(Math::DegToRad(Math::AngleBetweenPoints(tempTargetPosition, myPosition)) + 90);

	Tank::Draw(someWindow);
}

std::string Enemy::ChildName()
{
	return "Enemy " + std::to_string(myID);
}
