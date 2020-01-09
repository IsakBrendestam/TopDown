#ifndef ENVIROMENT_HEADER
#define ENVIROMENT_HEADER

#include "SFML\Graphics.hpp"

class Enviroment
{
public:
	Enviroment(sf::RenderWindow &someWindow);
	~Enviroment();

	void Draw(sf::RenderWindow &someWindow);

private:
	sf::Texture myGroundTexture;
	sf::Texture myWallTexture;
	std::vector<sf::Sprite> myGroundSprite;
	std::vector<sf::Sprite> myWallSprite;
};

#endif