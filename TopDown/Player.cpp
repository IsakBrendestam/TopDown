#include "Player.h"
#include "Math.h"
#include <sstream>
#include <iostream>

#include "SFML\Graphics.hpp"

Player::Player(sf::Vector2f somePosition, sf::Vector2f someScale, float someSpeed, float someAttackFireRate, float someMainAttackFireRate, int someHealth, int someDamage)
{
	myAttackFireRate = someAttackFireRate;
	myMainAttackFireRate = someMainAttackFireRate;
	myAttackElapsedTime = myAttackFireRate;
	myMainAttackElapsedTime = myMainAttackFireRate;
	myDamage = someDamage;

	Initialize(somePosition, someSpeed, someHealth);
	SpriteSetup(someScale, somePosition);
}

void Player::SpriteSetup(sf::Vector2f someScale, sf::Vector2f somePosition)
{
	//loading textures
	sf::Texture tempPlayerTexture;

	tempPlayerTexture.loadFromFile("Content/SmallTracks.png");
	myTextures.push_back(tempPlayerTexture);
	tempPlayerTexture.loadFromFile("Content/PlayerBase.png");
	myTextures.push_back(tempPlayerTexture);
	tempPlayerTexture.loadFromFile("Content/PlayerHead.png");
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
		tempSprite.setPosition(somePosition);

		mySprites.push_back(tempSprite);
	}

	myTextFont.loadFromFile("Content/Font.ttf");
}

Player::~Player()
{

}

void Player::Update(float someDeltaTime, sf::RenderWindow &someWindow, sf::Vector2f somePlayerPosition, std::vector<sf::Sprite> someOtherSprites, std::vector<Tank*> &someTank)
{
	Tank::Update(someDeltaTime, someWindow, somePlayerPosition, someOtherSprites, someTank);

	myMainAttackElapsedTime += someDeltaTime;
	myAttackElapsedTime += someDeltaTime;
	sf::Vector2f tempTarget = someWindow.mapPixelToCoords(sf::Mouse::getPosition(someWindow));

	//Attack
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && myAttackElapsedTime > myAttackFireRate)
	{
		Attack(someDeltaTime, 800, 40, someWindow, tempTarget, Bullet::BulletAmmo);
		myAttackElapsedTime = 0;
	}

	//Main Attack
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && myMainAttackElapsedTime > myMainAttackFireRate)
	{
		Attack(someDeltaTime, 1500, 10, someWindow, tempTarget, Bullet::MissileAmmo);
		myMainAttackElapsedTime = 0;
	}
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

void Player::DisplayHealth(sf::RenderWindow &someWindow)
{
	//Converting health to string
	std::ostringstream tempSS;
	tempSS << myHealth;
	std::string tempHealth(tempSS.str());

	//Text setup
	myHealthText.setFont(myTextFont);
	myHealthText.setScale(sf::Vector2f(0.1f, 0.1f));
	myHealthText.setString("Health: " + tempHealth);
	myHealthText.setPosition(someWindow.mapPixelToCoords(sf::Vector2i(10, 10)));
	myHealthText.setCharacterSize(200);
	myHealthText.setFillColor(sf::Color::White);
	myHealthText.setStyle(sf::Text::Bold);

	someWindow.draw(myHealthText);
}

void Player::Draw(sf::RenderWindow &someWindow)
{
	sf::Vector2f tempTargetPosition = someWindow.mapPixelToCoords(sf::Mouse::getPosition(someWindow));

	mySprites[2].setRotation(Math::DegToRad(Math::AngleBetweenPoints(tempTargetPosition, myPosition)) + 90);

	Tank::Draw(someWindow);
}

std::string Player::ChildName()
{
	return "Player";
}