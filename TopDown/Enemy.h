#define ENEMY_HEADER
#ifdef ENEMY_HEADER

#include "Tank.h"
#include "SFML\Graphics.hpp"

class Enemy : public Tank
{
public:
	Enemy(sf::Vector2f somePosition, sf::Vector2f someScale, float someSpeed, float someAttackFireRate, float someMainAttackFireRate, int someHealth, int someDamage, int someID);
	~Enemy();

	void SpriteSetup(sf::Vector2f sclae, sf::Vector2f somePosition);
	void Update(float someDeltaTime, sf::RenderWindow &someWindow, sf::Vector2f somePlayerPosition, std::vector<sf::Sprite> someOtherSprites, std::vector<Tank*> &someTank);
	void DisplayHealth(sf::RenderWindow &someWindow);
	void Draw(sf::RenderWindow &someWindow);

	sf::Vector2f MovementDir();
	std::string ChildName();

private:
	sf::Texture myFullHealthTexture;
	sf::Texture myEmptyHealthTexture;
	sf::Sprite myFullHealthSprite;
	sf::Sprite myEmptyHealthSprite;

	int myID;
	int myDamage;

	float myAttackFireRate;
	float myMainAttackFireRate;
	float myAttackElapsedTime;
	float myMainAttackElapsedTime;
};

#endif 