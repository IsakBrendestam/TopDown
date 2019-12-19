#ifndef PLAYER_HEADER
#define PLAYER_HEADER

#include "Tank.h"

class Player : public Tank
{

public:

	Player(sf::Vector2f somePosition, sf::Vector2f someScale, float someSpeed, float someFireRate);
	~Player();
	void SpriteSetup(sf::Vector2f sclae);

	sf::Vector2f MovementDir();

};

#endif