#ifndef BULLET_HEADER
#define BULLET_HEADER

#include <SFML\Graphics.hpp>

class Bullet
{

public:
	static enum TypeOfBullet { MissileAmmo, BulletAmmo };

	Bullet(sf::Vector2f someStartPosition, sf::Vector2f someTarget, sf::Vector2f someScale, float someSpeed, int someDamage, TypeOfBullet someBullet);
	~Bullet();

	void Update(float someDeltaTime);
	bool OutOfWindow();
	void Draw(sf::RenderWindow &someWindow);
	sf::Sprite GetSprite();
	bool myAlive;
	int myDamage;



private:
	float mySpeed;
	sf::Sprite mySprite;
	sf::Vector2f myStartPosition;
	sf::Vector2f myDirection;
	sf::Vector2f myPosition;
	sf::Texture myTexture;
	sf::Vector2f myWindowSize;
};

#endif