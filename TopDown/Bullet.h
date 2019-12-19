#ifndef BULLET_HEADER
#define BULLET_HEADER

#include <SFML\Graphics.hpp>

class Bullet
{

public:
	Bullet(sf::Vector2f someStartPosition, sf::Vector2f someDirection, sf::Vector2f someScale, float someSpeed);
	~Bullet();

	void Update(float someDeltaTime);
	bool OutOfWindow();
	void Draw(sf::RenderWindow &someWindow);

private:
	float mySpeed;

	sf::Sprite mySprite;
	sf::Vector2f myDirection;
	sf::Vector2f myPosition;
	sf::Texture myTexture;
	sf::Vector2f myWindowSize;
};

#endif