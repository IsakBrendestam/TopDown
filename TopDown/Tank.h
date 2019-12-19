#ifndef ENTITY_HEADER
#define ENTITY_HEADER

#include"Bullet.h"
#include <SFML/Graphics.hpp>

class Tank
{

public:
	Tank();
	virtual ~Tank();

	void virtual Update(float someDeltaTime, sf::RenderWindow &someWindow);
	void virtual Draw(sf::RenderWindow &someWindow);
	void virtual Attack(float someDeltaTime, sf::RenderWindow &someWindow);
	bool virtual Defence();
	sf::Vector2f virtual MovementDir() = 0;

	std::vector<sf::Sprite> mySprites;
	std::vector<sf::Texture> myTextures;
	sf::Vector2f myPosition;

	float mySpeed;
	float myFireRate;

private:
	std::vector<Bullet> myBullets;
	float myElapsedTime;
};

#endif