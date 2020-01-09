#ifndef PLAYER_HEADER
#define PLAYER_HEADER

#include "Tank.h"

class Player : public Tank
{

public:

	Player(sf::Vector2f somePosition, sf::Vector2f someScale, float someSpeed, float someAttackFireRate, float someMainAttackFireRate, int someHealth, int someDamage);
	~Player();

	void SpriteSetup(sf::Vector2f sclae, sf::Vector2f somePosition);
	void Update(float someDeltaTime, sf::RenderWindow &someWindow, sf::Vector2f somePlayerPosition, std::vector<sf::Sprite> someOtherSprites, std::vector<Tank*> &someTank);
	void DisplayHealth(sf::RenderWindow &someWindow);
	void Draw(sf::RenderWindow &someWindow);

	sf::Vector2f MovementDir();
	std::string ChildName();

private:
	int myDamage;
	float myAttackFireRate;
	float myMainAttackFireRate;
	float myAttackElapsedTime;
	float myMainAttackElapsedTime;

};

#endif