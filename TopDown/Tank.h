#ifndef ENTITY_HEADER
#define ENTITY_HEADER

#include"Bullet.h"
#include <SFML/Graphics.hpp>

class Tank
{

public:
	void Initialize(sf::Vector2f somePosition, float someMainAttackFireRate, int someHealth);
	virtual ~Tank();

	void virtual Update(float someDeltaTime, sf::RenderWindow &someWindow, sf::Vector2f somePlayerPosition, std::vector<sf::Sprite> someOtherSprite, std::vector<Tank*> &someTank) = 0;
	void BulletManagement(float someDeltaTime, std::vector<Tank*> &someTank, sf::RenderWindow &someWindow);
	void virtual Draw(sf::RenderWindow &someWindow);
	void virtual Attack(float someDeltaTime, float someSpeed, int someDamage, sf::RenderWindow &someWindow, sf::Vector2f someTarget, Bullet::TypeOfBullet someTypeOfBullet);
	void virtual ChangeHealth(int someDamage);
	void virtual DisplayHealth(sf::RenderWindow &someWindow) = 0;
	bool virtual Defence();
	bool GetAlive();
	sf::Vector2f virtual MovementDir() = 0;
	std::string virtual ChildName() = 0;

	std::vector<sf::Sprite> mySprites;;
	std::vector<sf::Texture> myTextures;

	sf::Vector2f myPosition;
	sf::Vector2f myPlayerPosition;
	sf::Vector2f myMovementDir;

	sf::Font myTextFont;
	sf::Text myHealthText;

	int myMaxHealth;
	int myHealth;

private:
	bool myAlive;
	float mySpeed;

	std::vector<Bullet> myBullets;
};

#endif